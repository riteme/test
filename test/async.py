#!/usr/bin/env python3.7

import time
import asyncio

async def count():
    print(1)
    await asyncio.sleep(1)
    print(2)

async def main():
    #await asyncio.gather(count(), count(), count())
    tasks = [asyncio.create_task(count()) for i in range(3)]
    await asyncio.gather(*tasks)

def stuff():
    return 1, 2, 3

def get():
    yield list(range(1, 10))

#t1 = time.perf_counter()
#asyncio.run(main())
#t2 = time.perf_counter()
#print(t2 - t1)
print(get())
print(list(get()))
