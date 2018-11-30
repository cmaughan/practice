#!/usr/bin/env python
'''
A rosalind problem - in python
http://rosalind.info/problems/revc/
Reverse complement the DNA strand
First reverse it, then use string translate to map A->T and C->G and back
My first attempt used a dictionary to do the mapping by walking the characters
and mapping.  But I later found the built in translate function
'''


def main():

    # Read the input data.
    with open('data/rosalind_revc.txt') as input_data:
        dna = input_data.read().strip()[::-1]

    dna = str.translate(dna, str.maketrans("ATCG", "TAGC"))

    # Print and save the answer.
    with open('output/rosalind_revc.txt', 'w') as output_data:
        output_data.write(dna)


if __name__ == '__main__':
    main()
