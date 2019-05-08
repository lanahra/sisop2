#include <gmock/gmock.h>
#include "../server/MockFileRepository.h"
#include "../server/MockUser.h"
#include "../server/MockUserRepository.h"
#include "MockKeyLock.h"
#include "application/DefaultUserService.h"
#include "infra/repository/FileNotFoundException.h"

using ::testing::ByMove;
using ::testing::InSequence;
using ::testing::Ref;
using ::testing::Return;
using ::testing::Throw;

TEST(DefaultUserService, GetsUserFile) {
    auto user = std::unique_ptr<MockUser>(new MockUser());

    MockUserRepository userRepository;
    MockFileRepository fileRepository;
    MockKeyLock keyLock;
    DefaultUserService service(userRepository, fileRepository, keyLock);

    {
        InSequence inSequence;

        EXPECT_CALL(keyLock, lockRead("name"));
        EXPECT_CALL(*user, getFile("file"));
        EXPECT_CALL(keyLock, unlockRead("name"));
    }

    EXPECT_CALL(userRepository, getUser("name"))
        .WillOnce(Return(ByMove(std::move(user))));

    service.getFile("name", "file");
}

TEST(DefaultUserServiceTest, GetsUserFileEntries) {
    auto user = std::unique_ptr<MockUser>(new MockUser());

    MockUserRepository userRepository;
    MockFileRepository fileRepository;
    MockKeyLock keyLock;
    DefaultUserService service(userRepository, fileRepository, keyLock);

    {
        InSequence inSequence;

        EXPECT_CALL(keyLock, lockRead("name"));
        EXPECT_CALL(*user, listEntries());
        EXPECT_CALL(keyLock, unlockRead("name"));
    }

    EXPECT_CALL(userRepository, getUser("name"))
        .WillOnce(Return(ByMove(std::move(user))));

    service.listFileEntries("name");
}

TEST(DefaultUserServiceTest, RemovesUserFile) {
    auto user = std::unique_ptr<MockUser>(new MockUser());

    MockUserRepository userRepository;
    MockFileRepository fileRepository;
    MockKeyLock keyLock;
    DefaultUserService service(userRepository, fileRepository, keyLock);

    {
        InSequence inSequence;

        EXPECT_CALL(keyLock, lockWrite("name"));
        EXPECT_CALL(*user, removeFile("file"));
        EXPECT_CALL(keyLock, unlockWrite("name"));
    }

    EXPECT_CALL(userRepository, getUser("name"))
        .WillOnce(Return(ByMove(std::move(user))));

    service.removeFile("name", "file");
}

TEST(DefaultUserServiceTest, SavesUserFile) {
    auto user = std::unique_ptr<MockUser>(new MockUser());
    File file("file", Timestamps(10, 20, 30), "body");

    MockUserRepository userRepository;

    MockFileRepository fileRepository;
    MockKeyLock keyLock;
    DefaultUserService service(userRepository, fileRepository, keyLock);

    {
        InSequence inSequence;

        EXPECT_CALL(keyLock, lockWrite("name"));
        EXPECT_CALL(*user, saveFile(file));
        EXPECT_CALL(keyLock, unlockWrite("name"));
    }

    EXPECT_CALL(userRepository, getUser("name"))
        .WillOnce(Return(ByMove(std::move(user))));

    service.saveFile("name", file);
}

TEST(DefaultUserServiceTest, SavesFileLocally) {
    MockFileRepository fileRepository;
    File file("file", Timestamps(10, 20, 30), "body");
    EXPECT_CALL(fileRepository, saveLocal(file));

    MockUserRepository userRepository;
    MockKeyLock keyLock;
    DefaultUserService service(userRepository, fileRepository, keyLock);

    service.saveLocal(file);
}