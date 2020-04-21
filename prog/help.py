from collections import defaultdict

from itertools import combinations, product
from functools import reduce

from numpy.polynomial import polynomial


def comb(n, k):
    ans = 1
    for i in range(k + 1, n + 1):
        ans *= i
    for i in range(1, n - k + 1):
        ans //= i
    return ans


def fact(n):
    ans = 1
    for i in range(1, n + 1):
        ans *= i
    return ans


def pow(base, n):
    if n == 0:
        return {0: 1}
    ret = defaultdict(lambda: 0)
    tmp1 = base if n % 2 == 1 else pow(base, n // 2)
    tmp2 = pow(base, n - 1) if n % 2 == 1 else tmp1
    for key_b, val_b in tmp1.items():
        for key_m, val_m in tmp2.items():
            ret[key_b + key_m] += val_b * val_m
            if ret[key_b + key_m] == 0:
                del ret[key_b + key_m]
    return ret


def num_not_0_in_base(num, base):
    ret = 0
    while num != 0:
        ret += num % base != 0
        num //= 5
    return ret


def comb_out_of_n(n, b):
    ans = 0
    for i in product(range(1, b + 1), repeat=n):
        if len(set(i)) == b:
            ans += fact(n) // reduce(lambda x, y: x * fact(y), i, 1)
    return ans


#TODO попробовать range(n)
def col_raskras(a, j):
    Q_t = {(a + 1) ** (i + 1): 1 for i in range(j)}
    Z_g = pow(Q_t, a)
    ret = 0
    for key, val in Z_g.items():
        if num_not_0_in_base(key // (a + 1), a + 1) == j:
            ret += val
    return ret


def find_number(n):
    count = 0
    for i in range(1, n + 1):
        if i % 2 == 1:
            count += (2 ** 2 ** (n - i) - 1) * comb(n, i) * 2 ** i * 2
        else:
            count -= (2 ** 2 ** (n - i) - 1) * comb(n, i) * 2 ** i * 2
    return count - n * 2


def find_number_bad(n, b):
    a = 2 ** (n - 1)
    return sum(comb(b, i) * (b ** a - i ** a) * col_raskras(a, i) for i in range(1, b))


from main import get_acc_dict


all_set = set()


def check(ind, x_n, bit):
    tmp = 2 ** (4 - x_n)
    return (ind % tmp < tmp // 2) ^ bit


def search_bad(x_n, bit=False):
    ret = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[0] == '\n' or len(line) < 16:
                continue
            ch = set()
            for ind, var in enumerate(line.split()):
                if not check(ind, x_n, bit):
                    ch.add(var)
            for ind, var in enumerate(line.split()):
                if check(ind, x_n, bit) and var not in ch:
                    ret.add(line[:-1])
                    break
    return ret


def search_good(x_n):
    ret = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[0] == '\n' or len(line) < 16:
                continue
            left = set()
            right = set()
            for ind, var in enumerate(line.split()):
                if check(ind, x_n, True):
                    right.add(var)
                else:
                    left.add(var)
            if left == right:
                ret.add(line)
    return ret


def search_by_k(k):
    ret = set()
    for line in search_bad(1, True).intersection(search_bad(1, False)):
        tmp = line.split()
        l = set(tmp[:4])
        r = set(tmp[4:])
        if len(l.difference(r)) == k:
            ret.add(line)
    return ret
