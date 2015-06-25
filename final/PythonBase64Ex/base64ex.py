#
# Copyright 2015 riteme
#

import base64

def encode(text):
    result1 = base64.urlsafe_b64encode(text)
    # print result1
    result2 = ''
    if result1.endswith('='):  # for better performance
        result2 = result1[:result1.find('=')]
    return result2

def decode(code):
    code += '=' * (len(code) % 4)
    # print code
    return base64.urlsafe_b64decode(code)

# example:
# origin = 'Hello, world!'
# print origin
# mixed = encode(origin)
# print mixed
# unmixed = decode(mixed)
# print unmixed
# print unmixed == origin
