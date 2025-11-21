# File 'F.py'
MOD = 1000000007

def main():
    a = int(input())
    r = a % MOD
    if r < 0:
        r += MOD
    print(r)

if __name__ == "__main__":
    main()
