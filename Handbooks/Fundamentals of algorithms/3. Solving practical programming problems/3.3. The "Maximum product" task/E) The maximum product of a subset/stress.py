import random
import subprocess
import sys
import os

FAST_EXE = "./a.out"

if not os.path.exists(FAST_EXE):
    print("Compiling main.cpp...")
    subprocess.run(["g++", "-std=c++17", "-O2", "main.cpp"], check=True)

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

def run_fast(a):
    inp = f"{len(a)}\n{' '.join(map(str, a))}\n"
    res = subprocess.run([FAST_EXE], input=inp, text=True, capture_output=True, timeout=2)
    if res.returncode != 0:
        print("Runtime error")
        print(res.stderr)
        sys.exit(1)
    try:
        return list(map(int, res.stdout.split()))
    except:
        print("Parse error:", res.stdout)
        sys.exit(1)

random.seed(42)

for it in range(1, 10001):
    n = random.randint(1, 15)
    a = [random.randint(-10**9, 10**9) for _ in range(n)]

    brute_prod, brute_ans = brute(a)
    fast_ans = run_fast(a)
    fast_prod = product_of_subset(a, fast_ans)

    if fast_prod != brute_prod:
        print("❌ COUNTEREXAMPLE")
        print(f"n = {n}")
        print(f"a = {a}")
        print(f"brute: {brute_ans} → {brute_prod}")
        print(f"fast:  {fast_ans} → {fast_prod}")
        sys.exit(0)

    if it % 1000 == 0:
        print(f"✅ {it} OK")

print("✅ All tests passed")