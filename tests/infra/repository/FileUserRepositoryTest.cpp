#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "infra/repository/FileUserRepository.h"

class FileUserRepositoryTest : public ::testing::Test {
  protected:
    UserRepository* repository;

    void SetUp() {
        repository = new FileUserRepository();
        system("rm -rf sync_dir*");
    }

    void TearDown() {
        delete repository;
        repository = nullptr;
    }
};

TEST_F(FileUserRepositoryTest, CreatesSyncDirIfNotExists) {
    std::string name = "user";

    std::shared_ptr<User> user = repository->get(name);

    std::string syncDirPath = "sync_dir_" + name;
    struct stat st;
    ASSERT_EQ(stat(syncDirPath.c_str(), &st), 0);
    EXPECT_EQ(S_ISDIR(st.st_mode), true);
}
