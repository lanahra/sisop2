#include <gmock/gmock.h>
#include "../server/MockFileRepository.h"
#include "../server/MockUser.h"
#include "../server/MockUserRepository.h"
#include "application/DefaultUserService.h"
#include "infra/repository/FileNotFoundException.h"

using ::testing::Ref;
using ::testing::Return;
using ::testing::ByMove;
using ::testing::Throw;

TEST(DefaultUserService, GetsUserFile) {
    auto user = std::unique_ptr<MockUser>(new MockUser());
    EXPECT_CALL(*user, getFile("file"));

    MockUserRepository userRepository;
    EXPECT_CALL(userRepository, getUser("name"))
        .WillOnce(Return(ByMove(std::move(user))));

    MockFileRepository fileRepository;
    DefaultUserService service(userRepository, fileRepository);

    service.getFile("name", "file");
}

 TEST(DefaultUserServiceTest, GetsUserFileEntries) {
    auto user = std::unique_ptr<MockUser>(new MockUser());
    EXPECT_CALL(*user, listEntries());

    MockUserRepository userRepository;
    EXPECT_CALL(userRepository, getUser("name"))
        .WillOnce(Return(ByMove(std::move(user))));

    MockFileRepository fileRepository;
    DefaultUserService service(userRepository, fileRepository);

    service.listFileEntries("name");
}

 TEST(DefaultUserServiceTest, RemovesUserFile) {
    auto user = std::unique_ptr<MockUser>(new MockUser());
    EXPECT_CALL(*user, removeFile("file"));

    MockUserRepository userRepository;
    EXPECT_CALL(userRepository, getUser("name"))
        .WillOnce(Return(ByMove(std::move(user))));

    MockFileRepository fileRepository;
    DefaultUserService service(userRepository, fileRepository);

    service.removeFile("name", "file");
}

 TEST(DefaultUserServiceTest, SavesFileLocally) {
    MockFileRepository fileRepository;
    File file("file", Timestamps(10, 20, 30), "body");
    EXPECT_CALL(fileRepository, saveLocal(file));

    MockUserRepository userRepository;
    DefaultUserService service(userRepository, fileRepository);

    service.saveLocal(file);
}