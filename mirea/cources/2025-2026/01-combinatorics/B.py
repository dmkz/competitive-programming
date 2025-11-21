# File 'B.py'
MOD = 1000000007

def main():
    a, b = map(int, input().split())
    d = (a - b) % MOD
    if d < 0:
        d += MOD
    print(d)

if __name__ == "__main__":
    main()
