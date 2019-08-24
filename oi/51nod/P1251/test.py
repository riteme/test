def check(S, m):
    cnt = [0] * m

    for x in S:
        cnt[x - 1] += 1

    return cnt.count(max(cnt)) == 1

def dfs(seq, pos, m, last):
    if pos == len(seq):
        if check(seq, m):
            print(seq)
            return 1
        return 0
    else:
        answer = 0

        for x in range(last, m + 1):
            seq[pos] = x

            answer += dfs(seq, pos + 1, m, x)

        return answer
