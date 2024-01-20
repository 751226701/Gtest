#include "SDK_TEST.h"
using namespace std;


class SgpTest : public testing::Test
{
public:
    SGP_HANDLE handle;

    void SetUp() override
    {
        handle = SGP_InitDevice();
        ASSERT_NE(handle, 0) << "SGP_InitDevice failed!";

        const char* server = IP;
        const char* username = "root";
        const char* password = "guide123";
        int port = 80;
        int ret1 = SGP_Login(handle, server, username, password, port);
        ASSERT_EQ(ret1, SGP_OK) << "SGP_Login failed";
    }

    void TearDown() override
    {
        int retq = SGP_Logout(handle);
        EXPECT_EQ(retq, SGP_OK) << "SGP_Logout failed";

        SGP_UnInitDevice(handle);
    }
};

TEST_F(SgpTest, FactoryReset)
{
    int ret = SGP_FactoryReset(handle);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FactoryReset failed";
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}








