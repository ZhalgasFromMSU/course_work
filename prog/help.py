from itertools import combinations, product


all_set = set()


def search_1_0(s):
    res = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[:8:2] == s:
                res.add(line)
                all_set.add(line)
    return res


def search_1_1(s):
    res = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[8::2] == s:
                res.add(line)
                all_set.add(line)
    return res


def search_2_0(s):
    res = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[:4:2] == s[:2] and line[8:12:2] == s[-2:]:
                res.add(line)
                all_set.add(line)
    return res


def search_2_1(s):
    res = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[4:8:2] == s[:2] and line[12::2] == s[-2:]:
                res.add(line)
                all_set.add(line)
    return res


def search_3_0(s):
    res = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[::4] == s:
                res.add(line)
                all_set.add(line)
    return res


def search_3_1(s):
    res = set()
    with open('res.tsv', 'r') as f:
        for line in f:
            if line[0] == '_':
                break
        for line in f:
            if line[2::4] == s:
                res.add(line)
                all_set.add(line)
    return res


funcs = (search_1_0, search_1_1, search_2_0, search_2_1, search_3_0, search_3_1)


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


def find_number(n):
    count = 0
    for i in range(1, n + 1):
        if i % 2 == 1:
            count += (2 ** 2 ** (n - i) - 1) * comb(n, i) * 2 ** i * 2
        else:
            count -= (2 ** 2 ** (n - i) - 1) * comb(n, i) * 2 ** i * 2
    return count - n * 2
