N = 4
mat = [[0 for i in range(N)] for j in range(N)]



for i in range(N):
    for j in range(N):
        if i > j:
            mat[i][j] = 1
print("\n".join(map(str, mat)))