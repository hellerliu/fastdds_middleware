#!/usr/bin/python3

import sys
sys.path.append("../lib")

import time
import RpcCommu
import asyncio


# async or not
def handleHelloWorld(type, message):
    print("py sub:{} {}".format(type, message))

async def handleHelloWorld_async(type, message):
    print("py sub async:{} {}".format(type, message))
    await asyncio.sleep(5)
  




if __name__ == "__main__":
    subscriber = RpcCommu.NormalSubscriber("hello_world", handleHelloWorld)
    subscriber1 = RpcCommu.NormalSubscriber("hello_world", handleHelloWorld_async)

  
    while True:
        time.sleep(1)       

    exit()



