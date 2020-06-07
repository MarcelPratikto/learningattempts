def print_n_recursive(s, n, prompt):
    if prompt > 0:
        print("recursive function, " + str(n) + " iterations:")
        prompt -= 1
    if n <= 0:
        return
    print(s)
    print_n_recursive(s, n-1, prompt)

def print_n_whileloop(s, n):
    print("while loop, " + str(n) + " iterations:")
    while n > 0:
        print(s)
        n -= 1 #n = n - 1

def print_n_forloop(s, n):
    print("for loop, iteration " + str(n) + ":")
    for i in range(n):
        print(s)

#__main__
#strPrint = '\tJAJAJA'
strPrint = 7
iteration = 3
print_n_recursive(strPrint, iteration, 1)
print_n_whileloop(strPrint, iteration)
print_n_forloop(strPrint, iteration)
