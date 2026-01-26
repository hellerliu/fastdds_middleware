#pragma once

#include <RpcBase/BaseService.h>
#include <testProto/TestMessage.pb.h>
#include <string>

struct EchoMessage
{
    int index;
    std::string message;

    template <typename T>
    void serialize(T &ar)
    {
        ar & index & message;
    }
};

class IFiberCall : public rpc::BaseService
{
public:
    IFiberCall(bool isClient = true, unsigned int timeOut = 5) : BaseService(isClient, timeOut)
    {
        addFunction<&IFiberCall::fiberTest>(true);
    }
    CLIENT_CALL(fiberTest, EchoMessage, proto::EchoMessage);
};
