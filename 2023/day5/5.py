from collections import defaultdict
from functools import reduce
import sys
import re
import portion as P

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


locations = [getLastCategory(seed) for seed in seeds]

print(f"Part1: {min(locations)}")

seedRanges = reduce(
    lambda x, y: x | y,
    [
        P.closedopen(begin, begin + length)
        for begin, length in zip(seeds[::2], seeds[1::2])
    ],
    P.empty(),
)


def getLastCategoryIntervals(intervals):
    for intervalMaps in categoryToIntervals.values():
        mappedIntervals = P.empty()
        for destBegin, srcBegin, length in intervalMaps:
            sourceInterval = P.closedopen(srcBegin, srcBegin + length)
            offset = destBegin - srcBegin
            intersections = [
                sourceInterval.intersection(interval)
                for interval in intervals
                if sourceInterval.intersection(interval) != P.empty()
            ]
            for intersection in intersections:
                intervals -= intersection
                intervalLength = intersection.upper - intersection.lower
                mappedInterval = P.closedopen(
                    intersection.lower + offset,
                    intersection.lower + offset + intervalLength,
                )
                mappedIntervals |= mappedInterval
        # intervals that dont have a map carry over to next section
        intervals |= mappedIntervals
    return intervals


locationIntervals = getLastCategoryIntervals(seedRanges)
print(f"min part2: {locationIntervals.lower}")
