def small_schroder(n):
    if n <= 2:
        return 1

    answer = 0
    if n == 3:
        answer = 1
    for w in range(2, n):
        for l in range(0, n - w + 1):
            answer += small_schroder(w) * small_schroder(n - l - w)

    return answer
