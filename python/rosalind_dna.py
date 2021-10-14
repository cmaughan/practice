#!/usr/bin/env python
'''
A rosalind problem - in python 
http://rosalind.info/problems/dna/
Function to count nucleotides
Using the built in counter would be more efficient, but this was my first attempt
'''


def main():
    '''Main call. Parses, runs, and saves problem specific data.'''
    # Read the input data.
    with open('data/rosalind_dna.txt') as input_data:
        dna = input_data.read().strip()

    # Print and save the answer.
    with open('output/rosalind_dna.txt', 'w') as output_data:
        output_data.write(
            "{0} {1} {2} {3}".format(
                dna.count('A'),
                dna.count('C'),
                dna.count('G'),
                dna.count('T')
            )
        )


if __name__ == '__main__':
    main()