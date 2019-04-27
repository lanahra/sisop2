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
    DefaultUserService service(factory, repository);

    service.getFile("name", "file");
}

TEST(DefaultUserServiceTest, GetsUserFileEntries) {
    MockFileRepository repository;
    EXPECT_CALL(repository, getEntries("name"));

    UserFactory factory(repository);
    DefaultUserService service(factory, repository);

    service.listFileEntries("name");
}

TEST(DefaultUserServiceTest, RemovesUserFile) {
    MockFileRepository repository;
    EXPECT_CALL(repository, remove("name", "file"));

    UserFactory factory(repository);
    DefaultUserService service(factory, repository);

    service.removeFile("name", "file");
}

TEST(DefaultUserServiceTest, IgnoresRemoveForFileNotFound) {
    MockFileRepository repository;
    EXPECT_CALL(repository, remove("name", "file"))
        .WillOnce(Throw(FileNotFoundException("file")));

    UserFactory factory(repository);
    DefaultUserService service(factory, repository);

    service.removeFile("name", "file");
}

TEST(DefaultUserServiceTest, SavesFileLocally) {
    MockFileRepository repository;
    File file("file", Timestamps(10, 20, 30), "body");
    EXPECT_CALL(repository, saveLocal(file));

    UserFactory factory(repository);
    DefaultUserService service(factory, repository);

    service.saveLocal(file);
}