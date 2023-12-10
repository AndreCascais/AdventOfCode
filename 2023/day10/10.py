import sys

pipes = sys.stdin.read().splitlines()
pipes = [list(f".{pipe}.") for pipe in pipes]
pipes.append(["." for _ in pipes[0]])
pipes.insert(0, ["." for _ in pipes[0]])

pipeMap = {
    "F": [(1, 0), (0, 1)],
    "7": [(1, 0), (0, -1)],
    "J": [(-1, 0), (0, -1)],
    "L": [(-1, 0), (0, 1)],
    "|": [(1, 0), (-1, 0)],
    "-": [(0, 1), (0, -1)],
}

startPosition = [
    (row, col)
    for row in range(len(pipes))
    for col in range(len(pipes[0]))
    if pipes[row][col] == "S"
][0]


visited = {startPosition: 0}

initialRow, initialCol = startPosition

connectedUp = pipes[initialRow - 1][initialCol] in "|F7"
connectedDown = pipes[initialRow + 1][initialCol] in "|JL"
connectedRight = pipes[initialRow][initialCol + 1] in "-7J"
connectedLeft = pipes[initialRow][initialCol - 1] in "-LF"

startLine = list(pipes[initialRow])
if connectedDown and connectedRight:
    pipes[initialRow][initialCol] = "F"
elif connectedDown and connectedLeft:
    pipes[initialRow][initialCol] = "7"
elif connectedUp and connectedLeft:
    pipes[initialRow][initialCol] = "J"
elif connectedUp and connectedRight:
    pipes[initialRow][initialCol] = "L"
elif connectedUp and connectedDown:
    pipes[initialRow][initialCol] = "|"
elif connectedLeft and connectedRight:
    pipes[initialRow][initialCol] = "-"


def flood(start):
    queue = [start]
    while queue != []:
        pipe = queue.pop(0)
        row, col = pipe
        for offsetRow, offsetCol in pipeMap[pipes[row][col]]:
            nextPipe = (row + offsetRow, col + offsetCol)
            if nextPipe not in visited:
                visited[nextPipe] = visited[pipe] + 1
                queue.append(nextPipe)


print(f"Longest distance from staring pipe is {max(visited.values())}")

# Clear garbage
for row, line in enumerate(pipes):
    for col, _ in enumerate(line):
        if (row, col) not in visited:
            pipes[row][col] = "."

# Using Point in polygon: https://en.wikipedia.org/wiki/Point_in_polygon
# We assume our line is cast from left to right below 50% of the |
# (so that it does not hit the edge) so and so it will intersect | 7 and F (and not L or J)

insideCount = 0
for row, line in enumerate(pipes):
    for col, _ in enumerate(line):
        if (row, col) not in visited:
            insideCount += sum([1 for ch in line[col + 1 :] if ch in "7F|"]) % 2

print(f"Elements inside pipes: {insideCount}")
