#! /usr/bin/env python
# -*- coding:utf-8 -*-

import urllib
import urllib2
import time
import json
import random
import hmac
import hashlib
from pynvml import *


def getGpuUtilization(handle):
    try:
        util = nvmlDeviceGetUtilizationRates(handle)
        gpu_util = int(util.gpu)
    except NVMLError as err:
        error = handleError(err)
        gpu_util = error
    return gpu_util


def main():

        nvmlInit()
        deviceCount = nvmlDeviceGetCount()

        while True:

                for i in range(deviceCount):

                        handle = nvmlDeviceGetHandleByIndex(i)
                        gpu_util = getGpuUtilization(handle)
                        print(gpu_util)

                time.sleep(0.1)

if __name__=='__main__':
        main()
