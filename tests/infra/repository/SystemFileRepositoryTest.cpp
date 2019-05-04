#include <gmock/gmock.h>
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
    File file("afile", Timestamps(10, 20, 0), "file body");

    SystemFileRepository repository;
    repository.save("first", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_first/afile", &st), Eq(0));
    EXPECT_THAT(st.st_atim.tv_sec, Eq(file.getTimestamps().getLastAccess()));
    EXPECT_THAT(st.st_mtim.tv_sec,
                Eq(file.getTimestamps().getLastModification()));
}

TEST(SystemFileRepositoryTest, MakesDirIfNotExistAndSavesFile) {
    system("rm -fr sync_dir_second");
    File file("afile", Timestamps(0, 0, 0), "file body");

    SystemFileRepository repository;
    repository.save("second", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_second/afile", &st), Eq(0));
}

TEST(SystemFileRepositoryTest, OverwritesExistingFile) {
    system("mkdir -p sync_dir_third");
    system("touch sync_dir_third/existing_file");
    File file("existing_file", Timestamps(0, 0, 0), "file body");

    SystemFileRepository repository;
    repository.save("third", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_third/existing_file", &st), Eq(0));
}

TEST(SystemFileRepositoryTest, SavesFileLocally) {
    system("rm -fr afile");
    File file("afile", Timestamps(0, 0, 0), "file body");

    SystemFileRepository repository;
    repository.saveLocal(file);

    struct stat st;
    EXPECT_THAT(stat("afile", &st), Eq(0));
}

TEST(SystemFileRepositoryTest, GetsFileFromFileSystem) {
    system("mkdir -p sync_dir_fourth");
    system("touch sync_dir_fourth/content");
    system("echo \"file body\" > sync_dir_fourth/content");

    SystemFileRepository repository;
    File file = repository.get("fourth", "content");

    EXPECT_THAT(file.getName(), Eq("content"));
    EXPECT_THAT(file.getBody(), Eq("file body\n"));
}

TEST(SystemFileRepositoryTest, GetsFileFromFileSystemFromPath) {
    system("rm -rf Sisop2_Example_Folder");
    system("mkdir Sisop2_Example_Folder");
    system("touch Sisop2_Example_Folder/filename");
    system("echo \"file body\" > Sisop2_Example_Folder/filename");

    SystemFileRepository repository;
    std::string path = "Sisop2_Example_Folder/filename";
    File file = repository.getLocal(path);

    EXPECT_THAT(file.getName(), Eq("filename"));
    EXPECT_THAT(file.getBody(), Eq("file body\n"));
}

TEST(SystemFileRepositoryTest, ThrowsExceptionForNonExistentFile) {
    SystemFileRepository repository;
    EXPECT_THROW(repository.get("fifth", "non_existent"),
                 FileNotFoundException);
}

TEST(SystemFileRepositoryTest, GetsEmptyListForNonExistentDir) {
    SystemFileRepository repository;
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
    SystemFileRepository repository;
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

    SystemFileRepository repository;
    repository.remove("seventh", "first");
    repository.remove("seventh", "second");

    struct stat st;
    EXPECT_THAT(stat("sync_dir_seventh/first", &st), Not(Eq(0)));
    EXPECT_THAT(stat("sync_dir_seventh/second", &st), Not(Eq(0)));
}

TEST(SystemFileRepositoryTest, ThrowsExceptionForRemovingNonExistentFile) {
    SystemFileRepository repository;

    EXPECT_THROW(repository.remove("fifth", "non_existent"),
                 FileNotFoundException);
}

TEST(SystemFileRepositoryTest, ReturnsEmptyListForNonExistentStatus) {
    system("rm -fr sync_dir_eighth");
    system("mkdir -p sync_dir_eighth");

    SystemFileRepository repository;
    EXPECT_THAT(repository.getStatus("eighth"), Eq(std::list<FileEntry>()));
}

TEST(SystemFileRepositoryTest, ReturnsEmptyListForEmptyStatus) {
    system("rm -fr sync_dir_ninth");
    system("mkdir -p sync_dir_ninth");
    system("touch sync_dir_ninth/.status");

    SystemFileRepository repository;
    EXPECT_THAT(repository.getStatus("ninth"), Eq(std::list<FileEntry>()));
}

TEST(SystemFileRepositoryTest, GetsStatus) {
    system("rm -fr sync_dir_tenth");
    system("mkdir -p sync_dir_tenth");
    system("touch sync_dir_tenth/.status");
    system(R"(printf "5,first,10,20,30\n6,second,10,20,30\n" > sync_dir_tenth/.status)");

    std::list<FileEntry> entries({FileEntry("first", Timestamps(10, 20, 30)),
                                  FileEntry("second", Timestamps(10, 20, 30))});

    SystemFileRepository repository;
    EXPECT_THAT(repository.getStatus("tenth"), Eq(entries));
}

TEST(SystemFileRepositoryTest, DoNotSaveEmptyStatus) {
    system("rm -fr sync_dir_eleventh");
    system("mkdir -p sync_dir_eleventh");

    SystemFileRepository repository;
    repository.saveStatus("eleventh", std::list<FileEntry>());

    struct stat st;
    EXPECT_THAT(stat("sync_dir_eleventh/.status", &st), Not(Eq(0)));
}

TEST(SystemFileRepositoryTest, SavesStatus) {
    system("rm -fr sync_dir_eleventh");
    system("mkdir -p sync_dir_eleventh");

    std::list<FileEntry> entries({FileEntry("first", Timestamps(10, 20, 30)),
                                  FileEntry("second", Timestamps(10, 20, 30))});

    SystemFileRepository repository;
    repository.saveStatus("eleventh", entries);

    std::ifstream fileStream("sync_dir_eleventh/.status");
    std::string status((std::istreambuf_iterator<char>(fileStream)),
                       std::istreambuf_iterator<char>());

    EXPECT_THAT(status, Eq("5,first,10,20,30\n6,second,10,20,30\n"));
}