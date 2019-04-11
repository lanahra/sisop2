#include <gmock/gmock.h>
#include "infra/repository/SystemFileRepository.h"

using ::testing::Eq;

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
    system("mkdir -p test_dir");
    File file("afile", Timestamps(0, 0, 0), "file body");

    repository->save("test_dir", file);

    struct stat st;
    EXPECT_THAT(stat("test_dir/afile", &st), Eq(0));
}

TEST_F(SystemFileRepositoryTest, OverwritesExistingFile) {
    system("mkdir -p test_dir");
    system("touch test_dir/existing_file");
    File file("existing_file", Timestamps(0, 0, 0), "file body");

    repository->save("test_dir", file);

    struct stat st;
    EXPECT_THAT(stat("test_dir/existing_file", &st), Eq(0));
}

TEST_F(SystemFileRepositoryTest, GetsFileFromFileSystem) {
    system("mkdir -p test_dir");
    system("touch test_dir/content");
    system("echo \"file body\" > test_dir/content");

    File file = repository->get("test_dir", "content");

    EXPECT_THAT(file.getName(), Eq("content"));
    EXPECT_THAT(file.getBody(), Eq("file body\n"));
}

TEST_F(SystemFileRepositoryTest, ThrowsExceptionForNonExistentFile) {
    EXPECT_THROW(repository->get("test_dir", "non_existent"),
                 FileNotFoundException);
}
