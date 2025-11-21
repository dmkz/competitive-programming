# File 'A.py'
MOD = 1000000007

def main():
    a, b = map(int, input().split())
    s = (a + b) % MOD
    print(s)

if __name__ == "__main__":
    main()
