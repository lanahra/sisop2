#include <gmock/gmock.h>
#include "infra/repository/SystemFileRepository.h"
#include "infra/repository/FileNotFoundException.h"

using ::testing::Eq;
using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

class SystemFileRepositoryTest : public ::testing::Test {
  protected:
    FileRepository* repository;

    void SetUp() {
        repository = new SystemFileRepository();
    }

    void TearDown() {
        delete repository;
        repository = nullptr;
    }
};

TEST_F(SystemFileRepositoryTest, SavesFile) {
    system("mkdir -p sync_dir_first");
    File file("afile", Timestamps(0, 0, 0), "file body");

    repository->save("first", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_first/afile", &st), Eq(0));
}

TEST_F(SystemFileRepositoryTest, MakesDirIfNotExistAndSavesFile) {
    system("rm -fr sync_dir_second");
    File file("afile", Timestamps(0, 0, 0), "file body");

    repository->save("second", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_second/afile", &st), Eq(0));
}

TEST_F(SystemFileRepositoryTest, OverwritesExistingFile) {
    system("mkdir -p sync_dir_third");
    system("touch sync_dir_third/existing_file");
    File file("existing_file", Timestamps(0, 0, 0), "file body");

    repository->save("third", file);

    struct stat st;
    EXPECT_THAT(stat("sync_dir_third/existing_file", &st), Eq(0));
}

TEST_F(SystemFileRepositoryTest, GetsFileFromFileSystem) {
    system("mkdir -p sync_dir_fourth");
    system("touch sync_dir_fourth/content");
    system("echo \"file body\" > sync_dir_fourth/content");

    File file = repository->get("fourth", "content");

    EXPECT_THAT(file.getName(), Eq("content"));
    EXPECT_THAT(file.getBody(), Eq("file body\n"));
}

TEST_F(SystemFileRepositoryTest, ThrowsExceptionForNonExistentFile) {
    EXPECT_THROW(repository->get("fifth", "non_existent"),
                 FileNotFoundException);
}

TEST_F(SystemFileRepositoryTest, GetsEmptyListForNonExistentDir) {
    std::list<FileEntry> entries = repository->getEntries("nonexistent");

    EXPECT_THAT(entries, IsEmpty());
}

MATCHER_P(FileEntryWithName, name, "") {
    return arg.getName() == name;
}

TEST_F(SystemFileRepositoryTest, GetsFileEntriesFromDir) {
    system("rm -fr sync_dir_sixth");
    system("mkdir -p sync_dir_sixth");
    system("touch sync_dir_sixth/first");
    system("touch sync_dir_sixth/second");
    std::list<FileEntry> entries = repository->getEntries("sixth");

    EXPECT_THAT(entries,
                UnorderedElementsAre(FileEntryWithName("first"),
                                     FileEntryWithName("second")));
}
