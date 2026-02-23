#!/usr/bin/python3

import sys
sys.path.append("../lib")

import time
import RpcCommu
import json



if __name__ == "__main__":
    publisher = RpcCommu.NormalPublisher("hello_world")
   
    data = {
    "data" : 0,
    "msg" : "hello"
    }

    
    while True:
        data["data"] += 1
        data_str = json.dumps(data)
        publisher.publish_json(data_str)
        print(f"py pub:{data_str}")
        time.sleep(1) 

    exit()


