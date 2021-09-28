def main():
  ALPH = "abcdefghijklmnopqrstuvwxyz"
  LETTERS = len(ALPH)
  TO_NUM = dict(zip(ALPH, range(LETTERS)))

  tests = int(input())
  for test in range(tests):
    chars = [input() for _ in range(LETTERS)]
    ciphered = input()
    message = input()
    
    my_ciphered = ''.join((chars[TO_NUM[char]] for char in message))
    print("Yes" if ciphered == my_ciphered else "No")


main()

