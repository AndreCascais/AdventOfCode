import sys
import re
from functools import reduce


def flat(l):
    return reduce(lambda x, y: x + y, l)


lines = sys.stdin.read().splitlines()
times, distances = [re.findall("(\d+)", line) for line in lines]

timeFlattened = int(flat(times))
recordFlattened = int(flat(distances))

times = [int(time) for time in times]
distances = [int(distance) for distance in distances]

races = zip(times, distances)

records = []
for time, record in races:
    records.append(
        [
            distance
            for press in range(time)
            for distance in [press * (time - press)]
            if distance > record
        ]
    )

recordCounts = [len(result) for result in records]
multiplied = reduce(lambda x, y: x * y, recordCounts)
print(multiplied)

recordCountsFlattened = len(
    [
        distance
        for press in range(timeFlattened)
        for distance in [press * (timeFlattened - press)]
        if distance > recordFlattened
    ]
)
print(recordCountsFlattened)
