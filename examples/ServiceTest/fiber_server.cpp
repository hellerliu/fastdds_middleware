#include "FiberCallService.h"
#include "MyTestCallService.h"
#include "RpcCommu/NormalServer.h"


using namespace rpc;

int main()
{
    auto service = std::make_shared<mytest::MyTestCallService>();
    auto baseService = std::dynamic_pointer_cast<rpc::BaseService>(service);
    auto server = RpcCommu::NormalServer::create(baseService);

    auto service1 = std::make_shared<FiberCallService>();
    auto baseService1 = std::dynamic_pointer_cast<rpc::BaseService>(service1);
    auto server1 = RpcCommu::NormalServer::create(baseService1);

    while (true)
    {
        sleep(10);
    }
    return 0;
}
