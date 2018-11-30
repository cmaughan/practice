#!/usr/bin/env python
'''
A rosalind problem - in python 
http://rosalind.info/problems/fib
I did it by taking the simple formula and evaluating it in a loop.
Recursive solutions didn't look any more elegant to me.
'''


def main():
    # Read the input data.
    with open('data/rosalind_fib.txt', 'r') as input_data:
        months, pairs = map(int, input_data.read().split())

    F1 = 1
    F2 = 1
    FN = 0
    for i in range(2, months, 1):
        FN = F1 + F2 * pairs
        F2 = F1
        F1 = FN

    with open('output/rosalind_fib.txt', 'w') as output_data:
        output_data.write(str(FN))
        print(FN)


if __name__ == '__main__':
    main()
