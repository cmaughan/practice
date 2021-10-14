
#!/usr/bin/env python
'''
A rosalind problem - in python 
http://rosalind.info/problems/rna/
RNA substitutes T for U.
'''

def main():
    # Read the input data.
    with open('data/rosalind_rna.txt') as input_data:
        dna = input_data.read().strip().replace('T', 'U')

    # Print and save the answer.
    with open('output/rosalind_rna.txt', 'w') as output_data:
        output_data.write(dna)

if __name__ == '__main__':
    main()
    