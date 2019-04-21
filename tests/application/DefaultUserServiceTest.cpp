#include <gmock/gmock.h>
#include "application/DefaultUserService.h"
#include "application/UserFactory.h"
#include "../server/MockFileRepository.h"

TEST(DefaultUserService, GetsUserFile) {
    MockFileRepository repository;
    EXPECT_CALL(repository, get("name", "file"));

    UserFactory factory(repository);
    DefaultUserService service(factory);

    service.getFile("name", "file");
}

TEST(DefaultUserServiceTest, GetsUserFileEntries) {
    MockFileRepository repository;
    EXPECT_CALL(repository, getEntries("name"));

    UserFactory factory(repository);
    DefaultUserService service(factory);

    service.listFileEntries("name");
}
