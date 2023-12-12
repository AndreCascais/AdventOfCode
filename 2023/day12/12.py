import sys

lines = [line.split() for line in sys.stdin.read().splitlines()]
conditionRecords = [
    (spring, tuple(map(int, damaged.split(",")))) for spring, damaged in lines
]
conditionRecordsUnfolded = [
    ((f"{spring}?" * 5)[:-1], damaged * 5) for spring, damaged in conditionRecords
]


class Memoize:
    memo = {}

    def __init__(self, fn):
        self.fn = fn

    def __call__(self, *args):
        if args not in self.memo:
            Memoize.memo[args] = self.fn(*args)
        return Memoize.memo[args]

    @classmethod
    def clear(cls):
        cls.memo = {}


@Memoize
def getCombinations(spring, damagedRecords):
    if len(spring) == 0 and len(damagedRecords) == 0:
        return 1
    if len(spring) == 0:
        return 0
    if len(damagedRecords) == 0:
        return 0 if spring.count("#") > 0 else 1
    if spring[0] == ".":
        return getCombinations(spring[1:], damagedRecords)
    nextRecord = damagedRecords[0]
    if nextRecord > len(spring):
        return 0

    currentDamaged = (
        0
        if (
            spring[:nextRecord].count(".") > 0
            or (len(spring) > nextRecord and spring[nextRecord] == "#")
        )
        else getCombinations(spring[nextRecord + 1 :], damagedRecords[1:])
    )

    if spring[0] == "#":
        return currentDamaged
    skipDamaged = getCombinations(spring[1:], damagedRecords)
    return currentDamaged + skipDamaged


def getCombinationsSummed(records):
    sum = 0
    for spring, records in records:
        sum += getCombinations(spring, records)
        Memoize.clear()
    return sum


print(f"Arrangements count: {getCombinationsSummed(conditionRecords)}")
print(f"Arrangements unfolded count: {getCombinationsSummed(conditionRecordsUnfolded)}")
