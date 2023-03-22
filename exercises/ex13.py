#!/usr/bin/env python

import os
import random
from urllib import request

url = 'https://www.mit.edu/~ecprice/wordlist.10000'
filename = 'words.txt'
argument_size = 400
increment = 50

if not os.path.isfile(filename):
    res = request.urlopen(url)
    with open(filename, 'w') as f:
        f.write(res.read().decode())

# was trying to do a generator
#words = (word for word in open(filename))
with open(filename) as f:
    words = f.read().split('\n')


while input('press Ctl-C to exit or ENTER to continue\n> ') == '':
    print(f'running with {argument_size} arguments')
    os.system('./ex13 ' + ' '.join(random.choices(words, k=argument_size)))
    argument_size += increment
