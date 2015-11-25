#!/usr/bin/env python


def fab(n):
    a, b, c = 0, 1, 0
    while c <= n:
        yield a
        c += 1
        a, b = b, a + b
# a = (x for x in xrange(100) if not x % 3)


# print max(len(line.strip()) for line in open('./test.py'))

def isprime(n):
    for x in xrange(2, n):
        if n % x is 0:
            return False
    return True


def yang(n):
    a = 1
    L = [1]
    while a <= n:
        a += 1
        yield L
        L = [1] + [sum(L[m:m+2]) for m in xrange(len(L) - 1)] + [1]

def eq_sum_powdig(hMax, exp):
# your code here
    return [x for x in xrange(2, hMax + 1) if sum(map(lambda s: pow(s, 3), [int(n) for n in str(x)])) == x]
if __name__ == '__main__':
    # print [x for x in fab(10)]
#     print eq_sum_powdig(400, 3)
#     print [x for x in xrange(2, 900) if sum([int(n)**3 for n in str(x)]) is x]
#     print sum([int(n)**3 for n in str(153)]) is 153
    for x in yang(10):
        print x