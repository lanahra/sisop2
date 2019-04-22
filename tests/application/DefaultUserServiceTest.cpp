#include <gmock/gmock.h>
#include "../server/MockFileRepository.h"
#include "application/DefaultUserService.h"
#include "application/UserFactory.h"
#include "infra/repository/FileNotFoundException.h"

using ::testing::Throw;

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

TEST(DefaultUserServiceTest, RemovesUserFile) {
    MockFileRepository repository;
    EXPECT_CALL(repository, remove("name", "file"));

    UserFactory factory(repository);
    DefaultUserService service(factory);

    service.removeFile("name", "file");
}

TEST(DefaultUserServiceTest, IgnoresRemoveForFileNotFound) {
    MockFileRepository repository;
    EXPECT_CALL(repository, remove("name", "file"))
        .WillOnce(Throw(FileNotFoundException("file")));

    UserFactory factory(repository);
    DefaultUserService service(factory);

    service.removeFile("name", "file");
}