from collections import defaultdict
from itertools import combinations


var_list = list()


def read_sep():
    ret = list()
    with open("inp.tsv", "r") as inp:
        for line in inp:
            a, *b = line.rstrip().split('\t')
            var_list.append(a.split())
            if len(ret) == 0:
                ret = b
            else:
                ret = [x + y for x, y in zip(ret, b)]
    return ret


def get_acc_dict(func_list):
    ch = defaultdict(list)
    for ind, combination in enumerate(zip(*func_list)):
        ch[combination].append(var_list[ind])
    return ch


def is_secure(acc_dict):
    for val in acc_dict.values():
        for col in zip(*val):
            if len(set(col)) == 1:
                return False
    return True 


def print_res(func_list):
    for i, *j in zip(var_list, *func_list[0]):
        print(' '.join(i), *j, sep='\t')


def main():
    func_list = read_sep()
    comb = combinations(func_list, 3)
    ans = [func for func in comb if not is_secure(get_acc_dict(func))]
    print_res(ans)


if __name__ == "__main__":
    main()