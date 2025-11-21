# File 'C.py'
MOD = 1000000007

def main():
    a, b = map(int, input().split())
    p = (a % MOD) * (b % MOD) % MOD
    print(p)

if __name__ == "__main__":
    main()
