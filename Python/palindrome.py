def first(word):
    return word[0]

def last(word):
    return word[-1]

def middle(word):
    return word[1:-1]

def is_palindrome(sArgument):
    if first(word) != last(word):
        return False
    if len(sArgument) > 1:
        checkmid = middle(sArgument)
        is_palindrome(checkmid)
    return True

def pfml(word):
    print(word)
    print("\tfirst:", first(word))
    print("\tmiddle:", middle(word))
    print("\tlast:", last(word))
    print("\n")

#__main__
word = input("input a word/sentence: ")
print("Is '", word, "' a palindrome?")
check = is_palindrome(word)
print(check)
