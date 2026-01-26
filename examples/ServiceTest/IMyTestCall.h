#pragma once

#include <RpcBase/BaseService.h>

namespace mytest
{
    enum MyTestCallErrCode
    {
        ReturnTestError = 1
    };

    struct echoResp
    {
        int data;
    };

    class IMyTestCall : public rpc::BaseService
    {
    public:
        IMyTestCall(bool isClient = true, unsigned int timeOut = 5) : BaseService(isClient, timeOut)
        {
            addFunction<&IMyTestCall::addOne>();
            addFunction<&IMyTestCall::fiber_test>(true);
            addFunction<&IMyTestCall::returnError>();
            addFunction<&IMyTestCall::array_test>();
            addFunction<&IMyTestCall::fiberTest>(true);
        }

        CLIENT_CALL(addOne, int, int);
        CLIENT_CALL(fiber_test, std::string, echoResp);
        CLIENT_CALL(returnError, rpc::VoidParam, rpc::VoidParam);

        virtual int array_test(const int (&req)[2], int (&resp)[2])
        {
            return clientCall(__FUNCTION__, req, resp);
        }

        CLIENT_CALL(fiberTest, std::string, std::string);
    };

}