from itertools import combinations, product
from functools import reduce


def count_intersections(num, n=4):
    count = 0
    for pr in product(('0' * n, '1' * n), repeat=num):
        for func in combinations(funcs, num):
            count += len(func[0](pr[0]).intersection(*(a(b) for a, b in zip(func[1:], pr[1:]))))
    return count


def comb(n, k):
    ans = 1
    for i in range(k + 1, n + 1):
        ans *= i
    for i in range(1, n - k + 1):
        ans //= i
    return ans


def fact(n):
    ans = 1
    for i in range(1, n):
        ans *= 1
    return ans


def comb_out_of_n(n, b):
    ans = 0
    for i in product(range(1, b + 1), repeat=n):
        if len(set(i)) == b:
            ans += fact(n) // reduce(lambda x, y: x * fact(y), i, 1)
    return ans


def find_number(n):
    count = 0
    for i in range(1, n + 1):
        if i % 2 == 1:
            count += (2 ** 2 ** (n - i) - 1) * comb(n, i) * 2 ** i * 2
        else:
            count -= (2 ** 2 ** (n - i) - 1) * comb(n, i) * 2 ** i * 2
    return count - n * 2


def find_number_bad(b, n):
    ans = 0
    n_1 = 2 ** (n - 1)
    for i in range(1, b):
        ans += comb(b, i) * (b ** n_1 - i ** n_1) * comb_out_of_n(n_1, i)
    return ans


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
                    ret.add(line)
                    break
    return ret
