n = int(raw_input())

memory = {}

def dfs(x):
    if x == 0:
        return 0
    if x == 1:
        return 1

    global memory

    if x in memory:
        return memory[x]

    result = None
    if x % 2 == 0:
        result = dfs(x / 2)
    else:
        result = dfs(x / 2) + dfs(x / 2 + 1)

    memory[x] = result
    return result

print(dfs(n))
