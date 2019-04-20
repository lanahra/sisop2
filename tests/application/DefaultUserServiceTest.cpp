#include <gmock/gmock.h>
#include "application/DefaultUserService.h"
#include "application/UserFactory.h"
#include "../server/MockFileRepository.h"

TEST(DefaultUserServiceTest, GetsUserFileEntries) {
    MockFileRepository repository;
    EXPECT_CALL(repository, getEntries("name"));

    UserFactory factory(repository);
    DefaultUserService service(factory);

    service.listFileEntries("name");
}
