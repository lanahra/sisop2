#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "infra/repository/FileUserRepository.h"
#include "server/File.h"

using ::testing::Eq;
using ::testing::IsTrue;
using ::testing::IsEmpty;
using ::testing::ContainerEq;

class FileUserRepositoryTest : public ::testing::Test {
  protected:
    UserRepository* repository;

    void SetUp() {
        repository = new FileUserRepository();
    }

    void TearDown() {
        delete repository;
        repository = nullptr;
    }
};

TEST_F(FileUserRepositoryTest, CreatesSyncDirIfNotExists) {
    system("rm -rf sync_dir_john");
    std::string name = "john";

    std::shared_ptr<User> user = repository->get(name);

    std::string syncDirPath = "sync_dir_" + name;
    struct stat st;
    ASSERT_THAT(stat(syncDirPath.c_str(), &st), Eq(0));
    EXPECT_THAT(S_ISDIR(st.st_mode), IsTrue());
    EXPECT_THAT(user->getFiles(), IsEmpty());
}

TEST_F(FileUserRepositoryTest, LoadsFilesFromSyncDir) {
    system("rsync -a --delete ../tests/resources/sync_dir_paul .");
    std::string name = "paul";

    std::shared_ptr<User> user = repository->get(name);

    std::list<File> expected({File("file_a"), File("file_b")});
    EXPECT_THAT(user->getFiles(), ContainerEq(expected));
}
