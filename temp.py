mat = [
    [61, 21, 52, 50],
    [74, 89, 45, 35],
    [89, 79, 60, 25],
    [22, 36, 30, 54],
]

sums = list(map(sum, mat))
indices = [3, 0, 1, 2]

#print("\n".join(map(str, mat)))
print(sums)

for i in range(4):
    idx = indices[i]
    while idx != i:
        print("swapping", i, idx) 
        # mat[i], mat[idx] = mat[idx], mat[i]
        indices[i], indices[idx] = indices[idx], indices[i]
        sums[i], sums[idx] = sums[idx], sums[i]
        idx = indices[i]

#print("\n".join(map(str, mat)))

print(indices)
print(sums)