from collections import defaultdict
from itertools import combinations
from operator import itemgetter


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


def has_uniq(acc_dict):
    for val in acc_dict.values():
        if len(val) == 1:
            return True
    return False


def print_res(func_list):
    print(len(func_list))
    if not func_list:
        return
    for var in zip(*var_list):
        print(' '.join(var))
    print('____________________________________\n')
    for j in map(itemgetter(0), func_list):
        print(' '.join(j), end='\n\n')


def main():
    func_list = read_sep()
    print_res([func for func in combinations(func_list, 1) if not is_secure(get_acc_dict(func))])
    """
    print_res([func for func in combinations(func_list, 1) if not is_secure(get_acc_dict(func)) and not has_uniq(get_acc_dict(func))])
    print('\n______________\n')
    print_res([func for func in combinations(func_list, 1) if not is_secure(get_acc_dict(func)) and has_uniq(get_acc_dict(func))])
    """


if __name__ == "__main__":
    main()
