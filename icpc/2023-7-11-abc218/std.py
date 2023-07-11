N, R = map(int, input().split())
A = list(map(int, input().split()))
R = min(R, N - R)
inf = 10**18

B = [0] * N
for i in range(N - 1):
  B[i] += A[i]
  B[i + 1] += A[i]

def f(C):
  dp = [(-inf, 0)] * (N + 1)
  ep = [(-inf, 0)] * (N + 1)
  ep[0] = (0, 0)
  for i in range(N):
    dp[i + 1] = (ep[i][0] + B[i] - C, ep[i][1] + 1)
    ep[i + 1] = max(dp[i], ep[i])
  return max(dp[N], ep[N])


ok = 0
ng = 1 << 31
while ok + 1 < ng:
  med = (ng + ok) // 2
  val, cnt = f(med)
  if cnt >= R:
    ok = med
  else:
    ng = med
val, cnt = f(ok)
print(val + R * ok)
