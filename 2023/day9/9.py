import sys

lines = sys.stdin.read().splitlines()

lines = [list(map(int, line.split())) for line in lines]

lastElementSum = 0
firstElementSum = 0
for history in lines:
    sequences = [history]
    while sum(sequences[-1]) != 0:
        nextSequence = [
            second - first for first, second in zip(sequences[-1], sequences[-1][1::])
        ]
        sequences.append(nextSequence)
    sequences[-1] += [0, 0]
    for index, sequence in reversed(list(enumerate(sequences[:-1]))):
        sequence.append(sequence[-1] + sequences[index + 1][-1])
        sequence.insert(0, (sequence[0] - sequences[index + 1][0]))
    lastElementSum += sequences[0][-1]
    firstElementSum += sequences[0][0]

print(f"Sum of last extrapolated values: {lastElementSum}")
print(f"Sum of first extrapolated values: {firstElementSum}")
