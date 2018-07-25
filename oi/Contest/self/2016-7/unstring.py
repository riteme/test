#!/usr/bin/env pypy

import re

while True:
    text = ""
    pattern = ""
    try:
        while text == "":
            text = raw_input().strip()
        while pattern == "":
            pattern = raw_input().replace("?", ".").strip()
    except EOFError:
        exit(0)

    # print(text)
    # print(pattern)
    result = re.match(".*" + pattern, text)
    if result is None:
        print("NO")
    else:
        print("YES")
