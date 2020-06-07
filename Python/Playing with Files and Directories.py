import os

# From whatever directory is provided,
# print the file names,
# and then walk to a folder in that directory
# and print the file names.
# Continue until all file names inside
# the original directory are printed.
def walk(dir):
    print(dir, ': ')
    for name in os.listdir(dir):

        # join() joins a directory and a file name
        # and returns a complete address/path name
        # ex: D:/desktop/example.txt
        path = os.path.join(dir, name)

        # if content of dir is a file
        if os.path.isfile(path):
            print(name)
        # else go into the folder within dir
        else:
            print('')   # empty line for formatting
            walk(path)

# __main__
walk("C:\\Users\\Marcel Pratikto\\Desktop\\Python Experiments")

#currentWorkingDirectory = os.getcwd()
#print(os.path.isdir(currentWorkingDirectory))
#print(os.path.join(currentWorkingDirectory, "Playing with Files and Directories.py"))
