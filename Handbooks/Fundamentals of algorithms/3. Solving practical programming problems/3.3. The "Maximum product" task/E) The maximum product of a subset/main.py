def product_of_subset(a, idxs):
    p = 1
    for i in idxs:
        p *= a[i - 1]
    return p

def brute(a):
    n = len(a)
    best_prod = None
    best_idxs = []
    for mask in range(1, 1 << n):
        cur = []
        for i in range(n):
            if mask >> i & 1:
                cur.append(i + 1)
        prod = product_of_subset(a, cur)
        if best_prod is None or prod > best_prod:
            best_prod = prod
            best_idxs = cur[:]
    return best_prod, sorted(best_idxs)

n = int(input())
vec = list(map(int, input().split()))
_, answer = brute(vec)
for ind in answer:
    print(f'{ind} ', end='')
print()