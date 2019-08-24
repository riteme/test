def bin(S):
    answer = 0

    t = 1 << (len(S) - 1)
    for i in range(0, len(S)):
        if S[i] == '1':
            answer += t
        t >>= 1

    return answer

def maxsum(S):
    answer = 0

    for state in range(1, 2**len(S)):
        result = 0
        for i in range(0, len(S)):
            if state & (1 << i):
                result ^= S[i]

        if result > answer:
            answer = result

    return answer
