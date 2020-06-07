# need to import to use sys.float_info.epsilon
import sys

a = input("find square root of: ")
a = float(a)
x = input("inital guess: ")
x = float(x)
while True:
    print(x,)
    y = (x + a/x)/2
    # if not using sys.float_info.epsilon, epsilon can be
    # epsilon can be a value around 0.0000001 or smaller
    # depending on how accurate you need to be.
    if abs(y - x) < sys.float_info.epsilon:
        break
    x = y
