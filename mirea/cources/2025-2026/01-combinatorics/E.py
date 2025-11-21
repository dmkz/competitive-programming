# File 'E.py'
MOD = 1000000007

def main():
    a, b = map(int, input().split())
    a %= MOD
    b %= MOD
    inv = pow(b, -1, MOD)
    d = a * inv % MOD
    print(d)

if __name__ == "__main__":
    main()
