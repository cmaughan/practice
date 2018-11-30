"""
My first attempt at a fasta reader in python
"""

def read(filename):
    fasta_entries = {  }
    name = ""
    with open(filename, 'r') as input_data:
        for line in input_data:
            line = line.strip()
            if line[0] == '>':
                name = line[1:]
                fasta_entries[name] = ""
            else:
                fasta_entries[name] += line
    return fasta_entries