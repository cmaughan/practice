#!/usr/bin/env python
'''
A rosalind problem - in python 
http://rosalind.info/problems/gc
First problem using fasta format parser.
Find the string with the highest percentage GC, and print the fasta string and percentage
'''


def main():
    import fasta
    import collections

    # Read the input data.
    entries = fasta.read('data/rosalind_gc.txt')

    found_entry = ""
    max = 0
    for entry in entries:
        entry_counts = collections.Counter(entries[entry])
        total = sum(entry_counts.values())
        gc = entry_counts['G'] + entry_counts['C']
        percent = gc / total
        if (percent > max):
            max = percent
            found_entry = entry

    with open('output/rosalind_gc.txt', 'w') as output_data:
        output_data.write("{0} {1}".format(found_entry, max * 100.0))


if __name__ == '__main__':
    main()
