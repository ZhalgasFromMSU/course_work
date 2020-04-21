import sys

from itertools import product


def main(b, n):
    for var, *func in zip(product(('0', '1'), repeat=n), *product(range(b), repeat=2**n)):
        print(' '.join(var), *func, sep='\t')


if __name__ == '__main__':
    b, n = sys.argv[1:]
    main(int(b), int(n))
