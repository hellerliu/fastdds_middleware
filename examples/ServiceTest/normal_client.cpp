#include "IMyTestCall.h"
#include "RpcCommu/NormalClient.h"
#include <unistd.h>
#include <backward_dw.hpp>

int main()
{
    mytest::IMyTestCall gCall;

    /*auto funcSet = gCall.getLocalFuncNames();
    std::set<std::string> serverFuncSet;
    int result = gCall.getServerFuncNames({}, serverFuncSet);
    assert(result == 0 && funcSet == serverFuncSet);*/

    int seq = 0;
    while (true)
    {
        seq++;
        // gCall.setCurrentTimeout(2000);
        gCall.async(&mytest::IMyTestCall::addOne, seq, [](int res, int &resp)
                    { printf("addOne async res:%d %d\n", res, resp); });

        gCall.async(&mytest::IMyTestCall::fiber_test, std::string{"run in fiber"}, [](int res, mytest::echoResp &resp)
                    { printf("fiber_test async res:%d %d\n", res, resp.data); });

        int resp = 0;

        int res = gCall.addOne(seq, resp);
        printf("addOne sync resp:%d %d\n", res, resp);

        gCall.async(&mytest::IMyTestCall::returnError, rpc::VoidParam{}, [](int res, rpc::VoidParam &resp)
                    { 
                        if(res == 0)
                            return;                       
                        auto str = rpc::rpc_error_str<mytest::MyTestCallErrCode>(res);                        
                        printf("returnError async error:%d %s\n", res, str.data()); });

        int arrReq[2] = {10, 11};
        int arrResp[2];
        res = gCall.array_test(arrReq, arrResp);
        printf("array_test sync res:%d %d %d\n", res, arrResp[0], arrResp[1]);

        sleep(5);
    }
    return 0;
}