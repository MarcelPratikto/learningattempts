def testString():
    xVariable = 'test'
    return xVariable

def testList(xList):
    xList[0] = 'changed value means list is passed as a reference'
    xList.append('I added this string')
    del xList[1]
    xList[1] = 'I can edit b from here!'

def testTuples(xTuples):
    xTuples = (xTuples,) + ('changed value means tuples is passed as a reference',)

# __main__
a = 'test'
x = testString()
b = ['0', '1']
testList(b)
c = ('0', '1')
testTuples(c)
# even though they are initialized at different scopes,
# both x and a still points to the same object
# because both contain the string 'test'
print(x is a)
# from the output, only lists are changed through reference.
print(dict(enumerate(b)))
# string and tuples are immutable, cannot be changed through reference.
print(c)
