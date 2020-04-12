import numpy as np

def badness(line,textwidth):

    # Number of gaps
    length_line = len(line) - 1

    for word in line:
        length_line += len(word)

    if length_line > textwidth: return float('inf')

    return ( textwidth - length_line )**2

textwidth = int(input())
words = list(input().split())

DP = [0] * (len(words) + 1)

for i in range(len(words) - 1, -1, -1):
    DP[i] = np.min([DP[j] + badness(words[i:j], textwidth) for j in range(i + 1, len(words) + 1)])

print(DP[0])
