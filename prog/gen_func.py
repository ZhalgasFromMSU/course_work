import sys


def gen_var(b, n):
    ret = ["0" for i in range(n)]
    for i in range(b ** n):
        yield ret
        for j in range(n - 1, -1, -1):
            if ret[j] == str(b - 1):
                ret[j] = '0'
            else:
                ret[j] = chr(ord(ret[j]) + 1)
                break


def gen_func(b, n):
    ret = ["0" for i in range(b ** n)]
    for i in range(b ** b ** n):
        yield ret.copy()
        for j in range(b ** n - 1, -1, -1):
            if ret[j] == str(b - 1):
                ret[j] = '0'
            else:
                ret[j] = chr(ord(ret[j]) + 1)
                break


def main(b, n):
    var_l = [i for i in gen_var(b, n)]
    for var, *func in zip(gen_var(b, n), *gen_func(b, n)):
        print(' '.join(var), *func, sep='\t')


if __name__ == '__main__':
    b, n = sys.argv[1:]
    main(int(b), int(n))
