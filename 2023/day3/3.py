from collections import defaultdict
import sys
import re
import math

document = sys.stdin.read().splitlines()
document = [f".{line}." for line in document]

dummyLine = "".join(["." for _ in range(len(document[0]))])

document.insert(0, dummyLine)
document.insert(len(document), dummyLine)

count = 0
for lineIndex, line in enumerate(document):
    for match in re.finditer("\\d+", line):
        span = (match.start() - 1, match.end() + 1)
        above = [x for y in document[lineIndex - 1][span[0]:span[1]] for x in y]
        below = [x for y in document[lineIndex + 1][span[0]:span[1]] for x in y]
        horizontal = [document[lineIndex][span[0]], document[lineIndex][span[1] - 1]]
        isPartNumber = any(x != "." and not x.isalnum() for x in above + below + horizontal)
        count += int(match.group()) if isPartNumber else 0

print(count)

partNumberDic = defaultdict(list)
for lineIndex, line in enumerate(document):
    for match in re.finditer("\\d+", line):
        span = (match.start() - 1, match.end() + 1)
        above = [(lineIndex - 1, col) for col in range(span[0], span[1])]
        below = [(lineIndex + 1, col) for col in range(span[0], span[1])]
        horizontal = [(lineIndex,span[0]), (lineIndex, span[1] - 1)]
        asterix = [(row, col) for (row, col) in above + below + horizontal if document[row][col] == "*"]
        for ast in asterix:
            partNumberDic[ast].append(int(match.group()))
gears = [numbers for numbers in partNumberDic.values() if len(numbers) == 2]
ratioSums = sum([math.prod(gear) for gear in gears])
print(ratioSums)

