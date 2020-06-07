'''
When you use indices to traverse the values in a sequence,
it is tricky to get the beginning and end
of the traversal right.
'''
# this function checks if two words are palindromes
def is_reverse(word1, word2):
    # if their lengths aren't equal, they're not palindromes
    if len(word1) != len(word2):
        return False

    # index of word1
    i = 0
    # index of word2
    j = len(word2) - 1
    # go through each letter in both words
    # go from beginning to end of word1
    # go from end to beginning of word2
    while j >= 0:
        print(word1[i], word2[j])
        if word1[i] != word2[j]:
            return False
        i += 1
        j -= 1

    return True

# __main__
word1 = 'stop'
word2 = 'pots'
if is_reverse(word1, word2):
    print('palindrome')
else:
    print('not a palindrome')
