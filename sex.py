result = []
s = set()
c = {}

def cmp(x):
    if x == x.lower():
        return chr(ord(x.lower()) * 2 + 1)
    else:
        return chr(ord(x.lower()) * 2)

def dfs(l1, l2, x, current):
    global result

    if x == len(l1):
        result.append("".join(sorted(current, key=cmp)))
        return

    p1 = l1[x]
    p2 = l2[x]
    for c1 in p1:
        for c2 in p2:
            dfs(l1, l2, x + 1, current + c1 + c2)

def fuck(s1, s2):
    global result
    global c
    global s

    result = []
    s = set()
    c = {}

    l1 = [s1[i:i+2] for i in range(0, len(s1), 2)]
    l2 = [s2[i:i+2] for i in range(0, len(s2), 2)]
    dfs(l1, l2, 0, "")

    for item in result:
        s.add(item)

        if item not in c:
            c[item] = 0

        c[item] += 1

    print(result, len(result))
    print(s, len(s))
    print(c)

if __name__ == "__main__":
    fuck("AaBb", "AaBb")
