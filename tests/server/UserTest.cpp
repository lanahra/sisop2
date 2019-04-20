#include <gmock/gmock.h>
#include "server/User.h"
#include "MockFileRepository.h"

TEST(UserTest, ListUserEntries) {
    MockFileRepository repository;
    EXPECT_CALL(repository, getEntries("name"));

    User user("name", repository);
    user.listEntries();
}
