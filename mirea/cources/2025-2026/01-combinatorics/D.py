# File 'D.py'
MOD = 1000000007

def main():
    a, n = map(int, input().split())
    print(pow(a, n, MOD))

if __name__ == "__main__":
    main()
