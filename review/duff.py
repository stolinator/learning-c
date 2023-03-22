#!/usr/bin/env python

import sys

if len(sys.argv) == 2:
    n = int(sys.argv[1])
    print('count\tc + 7 / 8\tc % 8')
    for i in range(n):
        print(f'{n}:\t{(n +7)//8}\t\t{n % 8}')
else:
    print("Usage: ./duff.py <n>")
