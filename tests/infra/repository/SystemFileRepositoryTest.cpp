#include <gmock/gmock.h>
#include <server/SystemClock.h>
#include <fstream>
#include "../../server/MockClock.h"
#include "infra/repository/FileNotFoundException.h"
#include "infra/repository/SystemFileRepository.h"

using ::testing::Eq;
using ::testing::IsEmpty;
using ::testing::Not;
using ::testing::Return;
using ::testing::UnorderedElementsAre;

TEST(SystemFileRepositoryTest, SavesFile) {
    system("mkdir -p sync_dir_first");
    File file("afile", Timestamps(0, 0, 0), "file body");

    SystemClock clock;
    SystemFileRepository repository(clock);
    repository.save("first", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_first/afile", &st), Eq(0));
}

TEST(SystemFileRepositoryTest, MakesDirIfNotExistAndSavesFile) {
    system("rm -fr sync_dir_second");
    File file("afile", Timestamps(0, 0, 0), "file body");

    SystemClock clock;
    SystemFileRepository repository(clock);
    repository.save("second", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_second/afile", &st), Eq(0));
}

TEST(SystemFileRepositoryTest, OverwritesExistingFile) {
    system("mkdir -p sync_dir_third");
    system("touch sync_dir_third/existing_file");
    File file("existing_file", Timestamps(0, 0, 0), "file body");

    SystemClock clock;
    SystemFileRepository repository(clock);
    repository.save("third", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_third/existing_file", &st), Eq(0));
}

TEST(SystemFileRepositoryTest, SavesFileLocally) {
    system("rm -fr afile");
    File file("afile", Timestamps(0, 0, 0), "file body");

    SystemClock clock;
    SystemFileRepository repository(clock);
    repository.saveLocal(file);

    struct stat st;
    EXPECT_THAT(stat("afile", &st), Eq(0));
}

TEST(SystemFileRepositoryTest, GetsFileFromFileSystem) {
    system("mkdir -p sync_dir_fourth");
    system("touch sync_dir_fourth/content");
    system("echo \"file body\" > sync_dir_fourth/content");

    SystemClock clock;
    SystemFileRepository repository(clock);
    File file = repository.get("fourth", "content");

    EXPECT_THAT(file.getName(), Eq("content"));
    EXPECT_THAT(file.getBody(), Eq("file body\n"));
}

TEST(SystemFileRepositoryTest, ThrowsExceptionForNonExistentFile) {
    SystemClock clock;
    SystemFileRepository repository(clock);
    EXPECT_THROW(repository.get("fifth", "non_existent"),
                 FileNotFoundException);
}

TEST(SystemFileRepositoryTest, GetsEmptyListForNonExistentDir) {
    SystemClock clock;
    SystemFileRepository repository(clock);
    std::list<FileEntry> entries = repository.getEntries("nonexistent");

    EXPECT_THAT(entries, IsEmpty());
}

MATCHER_P(FileEntryWithName, name, "") {
    return arg.getName() == name;
}

TEST(SystemFileRepositoryTest, GetsFileEntriesFromDir) {
    system("rm -fr sync_dir_sixth");
    system("mkdir -p sync_dir_sixth");
    system("touch sync_dir_sixth/first");
    system("touch sync_dir_sixth/second");
    SystemClock clock;
    SystemFileRepository repository(clock);
    std::list<FileEntry> entries = repository.getEntries("sixth");

    EXPECT_THAT(entries,
                UnorderedElementsAre(FileEntryWithName("first"),
                                     FileEntryWithName("second")));
}

TEST(SystemFileRepositoryTest, RemovesFiles) {
    system("rm -fr sync_dir_seventh");
    system("mkdir -p sync_dir_seventh");
    system("touch sync_dir_seventh/first");
    system("touch sync_dir_seventh/second");
    MockClock clock;
    EXPECT_CALL(clock, now()).WillOnce(Return(10)).WillOnce(Return(20));

    SystemFileRepository repository(clock);
    repository.remove("seventh", "first");
    repository.remove("seventh", "second");

    std::ifstream fileStream("sync_dir_seventh/.removed_files");
    std::string deleted_files((std::istreambuf_iterator<char>(fileStream)),
                              std::istreambuf_iterator<char>());

    struct stat st;
    EXPECT_THAT(stat("sync_dir_seventh/first", &st), Not(Eq(0)));
    EXPECT_THAT(stat("sync_dir_seventh/second", &st), Not(Eq(0)));
    EXPECT_THAT(deleted_files, Eq("5,first,10\n6,second,20\n"));
}

TEST(SystemFileRepositoryTest, ThrowsExceptionForRemovingNonExistentFile) {
    MockClock clock;
    SystemFileRepository repository(clock);

    EXPECT_THROW(repository.remove("fifth", "non_existent"),
                 FileNotFoundException);
}