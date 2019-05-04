#include <gmock/gmock.h>
#include "../../server/MockFileRepository.h"
#include "../../server/MockUser.h"
#include "infra/repository/DefaultUserRepository.h"

using ::testing::Not;
using ::testing::Eq;

TEST(DefaultUserRepositoryTest, GetsUser) {
    MockFileRepository fileRepository;

    DefaultUserRepository repository(fileRepository);

    auto user = repository.getUser("name");

    EXPECT_THAT(dynamic_cast<DefaultUser*>(user.get()), Not(Eq(nullptr)));
}