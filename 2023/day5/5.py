from collections import defaultdict
import sys
import re

data = [line.splitlines() for line in sys.stdin.read().split("\n\n")]

seeds = [int(seed) for seed in re.findall("seeds: (.*)", data[0][0])[0].split()]

categoryToIntervals = defaultdict(list)
for mapIndex, maps in enumerate(data[1:]):
    for map in maps[1:]:
        categoryToIntervals[mapIndex].append([int(entry) for entry in map.split()])

def getLastCategory(seed):
    mapKey = seed
    for intervals in categoryToIntervals.values():
        mapKey = next(
            (
                mapKey + dest - src
                for dest, src, rangeLength in intervals
                if mapKey in range(src, src + rangeLength)
            ),
            mapKey,
        )
    return mapKey
seedMap = [getLastCategory(seed) for seed in seeds]

minPart1 = min(seedMap)
print(minPart1)

minPart2 = getLastCategory(seeds[0])
# Brute force wont work
# for seedIndex in range(0, len(seeds), 2):
#     print(f"seraching {seedIndex} out of {len(seeds)/2}")
#     for seed in range(seeds[seedIndex], seeds[seedIndex] + seeds[seedIndex + 1]):
#         minPart2 = min(minPart2, getLastCategory(seed))
print(minPart2)


