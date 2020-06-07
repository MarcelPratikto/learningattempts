def ack(m, n):
    if m == 0:
        return n + 1
    elif m > 0 and n == 0:
        return ack(m - 1, 1)
    elif m > 0 and n > 0:
        An = 0
        An = ack(m, n - 1)
        return ack(m - 1, An)
    #else:
        #print("Doesn't work with negative values: m =", m, ", n =", n)
        #return None

print(ack(3, 4))
print(ack(0, 0))
print(ack(3, 6))
