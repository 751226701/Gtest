#include "SDK_TEST.h"


class SgpTests : public testing::Test
{
public:
    SGP_HANDLE handle;

    void SetUp() override
    {
        handle = SGP_InitDevice();
        ASSERT_NE(handle, 0) << "SGP_InitDevice failed!";

        const char* server = "192.168.21.154";
        const char* username = "root";
        const char* password = "guide123";
        int port = 80;
        int retl = SGP_Login(handle, server, username, password, port);
        ASSERT_EQ(retl, SGP_OK) << "SGP_Login failed";
    }

    void TearDown() override
    {
        int retq = SGP_Logout(handle);
        EXPECT_EQ(retq, SGP_OK) << "SGP_Logout failed";

        SGP_UnInitDevice(handle);
    }
};

TEST_F(SgpTests, ChangePasswords)
{
    const char* username = "admin";
    const char* oldpassword = "admin123";
    const char* newpassword = "admin567";
    int ret = SGP_ChangePassword(handle, username, oldpassword, newpassword);
    EXPECT_EQ(ret, SGP_OK) << "SGP_ChangePassword failed";
}

//02.ÖØÖÃÃÜÂë
TEST_F(SgpTests, ResetPasswords)
{
    const char* usernames = "admin";
    int ret = SGP_ResetPassword(handle, usernames);
    EXPECT_EQ(ret, SGP_OK) << "SGP_ResetPassword failed";
}