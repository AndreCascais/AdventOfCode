import sys
import numpy as np

lines = np.array([list(line) for line in sys.stdin.read().splitlines()])


def tiltUp():
    for colIndex in range(lines.shape[1]):
        tilted = "".join(
            [
                f"{'O'*section.count('O')}{'.'*section.count('.')}#"
                for section in "".join(lines[:, colIndex]).split("#")
            ]
        )[:-1]
        lines[:, colIndex] = list(tilted)


def getLoad(lines=lines):
    return sum(
        [
            (idx + 1) * np.count_nonzero(line == "O")
            for idx, line in enumerate(reversed(lines))
        ]
    )


print(getLoad())


def spin():
    global lines
    for _ in range(4):
        tiltUp()
        lines = np.rot90(lines, axes=(1, 0))


d = {}
cycle = 0
while lines.tobytes() not in d:
    d[lines.tobytes()] = cycle
    spin()
    cycle += 1
cycleStart = d[lines.tobytes()]

cycleLen = cycle - cycleStart
leftover = (1000000000 - cycleStart) % cycleLen + cycleStart
finalLines = [
    np.frombuffer(arr, dtype=lines.dtype).reshape(lines.shape)
    for arr, cycles in d.items()
    if cycles == leftover
][0]
print(getLoad(finalLines))
