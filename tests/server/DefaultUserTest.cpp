#include <gmock/gmock.h>
#include "MockFileRepository.h"
#include "server/DefaultUser.h"

using ::testing::Eq;
using ::testing::Return;
using ::testing::StrictMock;

TEST(UserTest, GetsUserFile) {
    MockFileRepository repository;
    EXPECT_CALL(repository, get("name", "file"));

    DefaultUser user("name", repository);
    user.getFile("file");
}

TEST(UserTest, ListsUserEntries) {
    MockFileRepository repository;
    EXPECT_CALL(repository, getEntries("name"));

    DefaultUser user("name", repository);
    user.listEntries();
}

TEST(UserTest, RemovesUserFile) {
    MockFileRepository repository;
    EXPECT_CALL(repository, remove("name", "file"));

    DefaultUser user("name", repository);
    user.removeFile("file");
}

TEST(UserTest, SyncNewRemote) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(std::list<FileEntry>()));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(std::list<FileEntry>()));
    EXPECT_CALL(repository,
                saveStatus("name",
                           std::list<FileEntry>(
                               {FileEntry("new", Timestamps(10, 20, 30))})));

    std::list<FileEntry> remote({FileEntry("new", Timestamps(10, 20, 30))});

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected(
        {SyncOperation(SyncOperation::DOWNLOAD, "new")});
    EXPECT_THAT(user.sync(remote), Eq(expected));
}

TEST(UserTest, SyncNewLocal) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("new", Timestamps(10, 20, 30))})));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(std::list<FileEntry>()));
    EXPECT_CALL(repository,
                saveStatus("name",
                           std::list<FileEntry>(
                               {FileEntry("new", Timestamps(10, 20, 30))})));

    std::list<FileEntry> remote;

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected(
        {SyncOperation(SyncOperation::UPLOAD, "new")});
    EXPECT_THAT(user.sync(remote), Eq(expected));
}

TEST(UserTest, SyncRemovedRemote) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("removed", Timestamps(10, 20, 30))})));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("removed", Timestamps(10, 20, 30))})));
    EXPECT_CALL(repository, remove("name", "removed"));
    EXPECT_CALL(repository, saveStatus("name", std::list<FileEntry>()));

    std::list<FileEntry> remote;

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected;
    EXPECT_THAT(user.sync(remote), Eq(expected));
}

TEST(UserTest, SyncRemovedLocal) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(std::list<FileEntry>()));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("removed", Timestamps(10, 20, 30))})));
    EXPECT_CALL(repository, saveStatus("name", std::list<FileEntry>()));

    std::list<FileEntry> remote({FileEntry("removed", Timestamps(10, 20, 30))});

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected(
        {SyncOperation(SyncOperation::DELETE, "removed")});
    EXPECT_THAT(user.sync(remote), Eq(expected));
}

TEST(UserTest, SyncMissing) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(std::list<FileEntry>()));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("missing", Timestamps(10, 20, 30))})));
    EXPECT_CALL(repository, saveStatus("name", std::list<FileEntry>()));

    std::list<FileEntry> remote;

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected;
    EXPECT_THAT(user.sync(remote), Eq(expected));
}

TEST(UserTest, SyncNewerRemote) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("file", Timestamps(0, 10, 0))})));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(std::list<FileEntry>()));
    EXPECT_CALL(repository,
                saveStatus("name",
                           std::list<FileEntry>(
                               {FileEntry("file", Timestamps(0, 20, 0))})));

    std::list<FileEntry> remote({FileEntry("file", Timestamps(0, 20, 0))});

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected(
        {SyncOperation(SyncOperation::DOWNLOAD, "file")});
    EXPECT_THAT(user.sync(remote), Eq(expected));
}

TEST(UserTest, SyncNewerLocal) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("file", Timestamps(0, 20, 0))})));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(std::list<FileEntry>()));
    EXPECT_CALL(repository,
                saveStatus("name",
                           std::list<FileEntry>(
                               {FileEntry("file", Timestamps(0, 20, 0))})));

    std::list<FileEntry> remote({FileEntry("file", Timestamps(0, 10, 0))});

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected(
        {SyncOperation(SyncOperation::UPLOAD, "file")});
    EXPECT_THAT(user.sync(remote), Eq(expected));
}

TEST(UserTest, DoNotSyncForAlreadySynchronized) {
    StrictMock<MockFileRepository> repository;
    EXPECT_CALL(repository, getEntries("name"))
        .WillOnce(Return(std::list<FileEntry>({FileEntry("sync", Timestamps(10, 20, 30))})));
    EXPECT_CALL(repository, getStatus("name"))
        .WillOnce(Return(
            std::list<FileEntry>({FileEntry("sync", Timestamps(10, 20, 30))})));
    EXPECT_CALL(repository,
                saveStatus("name",
                           std::list<FileEntry>(
                               {FileEntry("sync", Timestamps(10, 20, 30))})));

    std::list<FileEntry> remote({FileEntry("sync", Timestamps(10, 20, 30))});

    DefaultUser user("name", repository);

    std::list<SyncOperation> expected;
    EXPECT_THAT(user.sync(remote), Eq(expected));
}