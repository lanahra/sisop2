#include <gtest/gtest.h>
#include "UserBuilder.h"

TEST(UserTest, EstablishesNewSession) {
    User user = UserBuilder().build();
    Session session;

    user.establishSession(session);

    std::list<Session> expected({session});
    EXPECT_EQ(user.getSessions(), expected);
}

TEST(UserTest, ThrowsExceptionForTooManySessions) {
    User user = UserBuilder().build();
    Session firstSession, secondSession, thirdSession;

    user.establishSession(firstSession);
    user.establishSession(secondSession);

    ASSERT_THROW(user.establishSession(thirdSession),
                 EstablishSessionException);
}
