import sys

digPlan = [line.split() for line in sys.stdin.read().splitlines()]
dirMap = {"R": (0, 1), "L": (0, -1), "U": (-1, 0), "D": (1, 0)}
codeDirMap = {0: (0, 1), 1: (1, 0), 2: (0, -1), 3: (-1, 0)}


instructions = [(dirMap[dir], int(ammount)) for dir, ammount, _ in digPlan]
codedInstructions = [
    (codeDirMap[int(hexCode[-2])], int(hexCode[2:-2], 16)) for _, _, hexCode in digPlan
]


def shoelaceArea(start, instructions):
    vertex = [current := start] + [
        current := (current[0] + dx * ammount, current[1] + dy * ammount)
        for (dx, dy), ammount in instructions
    ]

    area = 0.5 * abs(
        sum(
            [
                vertex[i][1] * (vertex[i - 1][0] - vertex[i + 1][0])
                for i in range(1, len(vertex) - 1)
            ]
        )
    )
    return area


def getBoundary(instructions):
    return sum([distance for _, distance in instructions])


def getCapacity(instructions):
    area = shoelaceArea((0, 0), instructions)
    boundary = getBoundary(instructions)
    # Picks theorem
    inPoints = area - boundary // 2 + 1
    return inPoints + boundary


print(getCapacity(instructions))
print(getCapacity(codedInstructions))

