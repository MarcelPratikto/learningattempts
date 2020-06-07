'''
exercise 11.2
use dictionary get() method
to create a histogram: a set of counters/frequencies
'''
# create a histogram:
# dict {character: frequency}
def createHistogram(string):
    dictionary = dict()
    for character in string:
        # if character is not in dictionary,
        # initialize frequency as 0
        # if character is in dictionary,
        # increase frequency by 1
        frequency = dictionary.get(character, 0)
        frequency += 1
        dictionary[character] = frequency
    # sort in ascending order
    dictionary = sortDict(dictionary)
    return dictionary

# create an invert histogram:
# dict {frequency: [list of characters]}
def createInvertHistogram(hist):
    invHist = dict()
    # for each character in histogram
    for char in hist:
        # key of invert histogram = frequency of character
        freq = hist[char]
        # if frequency is not in the invert histogram,
        # create a new list as value
        # { frequency:[character]}
        if freq not in invHist:
            invHist[freq] = [char]
        # if value is in the invert histogram,
        # append to existing list
        # { frequency:[character, character1]}
        else:
            invHist[freq].append(char)
    # sort in ascending order
    invHist = sortDict(invHist)
    return invHist

'''
exercise 11.3
take a dictionary,
then sort in an ascending order
'''
def sortDict(d):
    # turn from data type dict_keys into list
    ascending = list(d.keys())
    # sort list from low to high (ascending)
    ascending.sort()
    # assign sorted old dictionary to new dictionary
    sortedDict = dict()
    for key in ascending:
        sortedDict[key] = d[key]
    return sortedDict

'''
NOT THE SAME AS CREATE DICTIONARY FUNCTIONS ABOVE
THESE SEARCHES A DICTIONARY
lookup:
searches for frequency of a character in a dictionary
reverse lookup:
searches for characters based on frequency
'''
def Lookup(d, character):
    frequency = d[character]
    return frequency
def RevLookup(d, frequency):
    characters = []
    for c in d:
        if d[c] == frequency:
            characters.append(c)
    return characters

# print each key:value of a dictionary in a new line
def printDict(d):
    for key in d:
        value = d[key]
        print(key, ":", value)
    

# __main__
testString = input("Type a word or sentence: ")
print("histogram, {character:frequency}:")
histogram = createHistogram(testString)
printDict(histogram)
print("inverse histogram, {frequency:[list of characters]}:")
inverseHistogram = createInvertHistogram(histogram)
printDict(inverseHistogram)

