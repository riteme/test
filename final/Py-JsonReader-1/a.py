#!/usr/bin/env python
#
# Copyright 2015 riteme
#

import json
f = open("a.json", "r")
setting = json.loads(f.read())
f.close()
for e in setting:
    print(e, ":", setting[e])
