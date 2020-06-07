def linecount(filename):
    count = 0
    for line in open(filename):
        count += 1
    return count

'''
__name__ is a built-in variable that is
set when the program starts.
If the program is running as a script,
__name__ has the same value __main__;
in that case, the test code is executed.
Otherwise, if the module is being imported,
the test code is skipped.
'''

# __name__ becomes 'wc' when imported
# because the file name is wc
print(__name__)
if __name__ == '__main__':
    print(linecount('wc.py'))
