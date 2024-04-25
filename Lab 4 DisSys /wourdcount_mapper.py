#!/usr/bin/env python

import sys

# Initialize a dictionary to store word counts
word_counts = {}

# Input comes from standard input:
for line in sys.stdin:
    # Remove leading and trailing whitespace
    line = line.strip()
    # Split the line into words
    words = line.split()
    # Increment count for each word
    for word in words:
        # Update word count in dictionary
        word_counts[word] = word_counts.get(word, 0) + 1

# Output word counts to standard output:
for word, count in word_counts.items():
    print(f"{word}\t{count}")
