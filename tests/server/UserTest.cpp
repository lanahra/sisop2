#include <gmock/gmock.h>
#include "server/User.h"
#include "MockFileRepository.h"

TEST(UserTest, GetsUserFile) {
    MockFileRepository repository;
    EXPECT_CALL(repository, get("name", "file"));

    User user("name", repository);
    user.getFile("file");
}

TEST(UserTest, ListsUserEntries) {
    MockFileRepository repository;
    EXPECT_CALL(repository, getEntries("name"));

    User user("name", repository);
    user.listEntries();
}
