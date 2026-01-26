#include "IFiberCall.h"
#include "RpcCommu/NormalClient.h"
#include <unistd.h>
#include <backward_dw.hpp>

int main()
{
    IFiberCall gCall;

    EchoMessage req{1, "hello"};

    gCall.waitForService(100);

    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });
    sleep(1);
    req.message = "hello1";
    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });

    sleep(5);
    req.index = 2;
    req.message = "hello";
    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });
    sleep(1);
    req.message = "hello1";
    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });

    sleep(5);
    req.index = 3;
    req.message = "hello";
    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });
    sleep(1);
    req.message = "hello1";
    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });

    sleep(5);
    req.index = 4;
    req.message = "hello";
    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });
    sleep(1);
    req.message = "hello1";
    gCall.async(&IFiberCall::fiberTest, req, [](int res, proto::EchoMessage &resp)
                { printf("fiberTest async res:%d %d %s\n", res, resp.index(), resp.message().c_str()); });

    
    sleep(5);
    return 0;
}