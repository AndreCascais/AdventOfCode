from collections import defaultdict
import sys
import numpy as np

lines = [list(map(list, line.splitlines())) for line in sys.stdin.read().split("\n\n")]


def getMirrorDifferences(pattern, positionsToDiffs):
    for position in positionsToDiffs:
        left = reversed(pattern[:position])
        right = pattern[position:]
        leftTruncated, rightTrucated = list(zip(*zip(left, right)))
        diffs = [(x, y) for (x, y) in zip(leftTruncated, rightTrucated) if x != y]
        positionsToDiffs[position] += len(diffs)
    return positionsToDiffs


def sumNotes(possibleDiffs=0):
    total = 0
    for line in lines:
        for pattern, ratio in [(line, 1), (np.array(line).T, 100)]:
            splitPositionsDiffs = defaultdict(
                int, map(lambda x: (x, 0), range(1, len(pattern[0])))
            )
            for row in pattern:
                splitPositionsDiffs = getMirrorDifferences(row, splitPositionsDiffs)
            relevantDiffs = [
                row
                for row, count in splitPositionsDiffs.items()
                if count == possibleDiffs
            ]
            if len(relevantDiffs) == 1:
                total += relevantDiffs[0] * ratio
    return total


print(sumNotes(0))
print(sumNotes(1))
