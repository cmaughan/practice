#!/usr/bin/env python
'''
A rosalind problem - in python
http://rosalind.info/problems/hamm
Find the hamming distance between 2 strings
'''


def main():

    with open('data/rosalind_hamm.txt', 'r') as input_data:
        string_a, string_b = input_data.read().split()

    with open('output/rosalind_hamm.txt', 'w') as output_data:
        output_data.write("{0} {1}".format(found_entry, max * 100.0))


if __name__ == '__main__':
    main()
