import sys

from numpy.matrixlib import defmatrix

matrix = sys.stdin.read().splitlines()
matrix = [f"#{row}#" for row in matrix]
matrix.insert(0, "#" * len(matrix[0]))
matrix.append("#" * len(matrix[0]))


def getNextDirs(pos, dir):
    row, col = pos
    ch = matrix[row][col]
    dx, dy = dir
    if ch == ".":
        return [dir]
    elif ch == "|":
        if dir in [(0, 1), (0, -1)]:
            return [(1, 0), (-1, 0)]
        return [dir]
    elif ch == "-":
        if dir in [(1, 0), (-1, 0)]:
            return [(0, 1), (0, -1)]
        return [dir]
    elif ch in "/":
        return [(-dy, -dx)]
    elif ch == "\\":
        return [(dy, dx)]
    return []


def bfs(start, dir):
    s = set()
    q = [(start, dir)]
    while q:
        pos, dir = q.pop(0)
        if (matrix[pos[0]][pos[1]]) != "#":
            s.add((pos, dir))
        for nextDir in getNextDirs(pos, dir):
            nextPos = pos[0] + nextDir[0], pos[1] + nextDir[1]
            if (nextPos, nextDir) not in s:
                q.append((nextPos, nextDir))
    energized = set({pos for pos, _ in s})
    return len(energized)


print(bfs((1, 1), (0, 1)))

# This assumes matrix is squared
rightEdges = [((row, 1), (0, 1)) for row in range(len(matrix))]
leftEdges = [((row, len(matrix) - 2), (0, -1)) for row in range(len(matrix))]
upEdges = [((len(matrix) - 2, col), (-1, 0)) for col in range(len(matrix))]
downEdges = [((1, col), (1, 0)) for col in range(len(matrix))]

energized = [bfs(pos, dir) for pos, dir in rightEdges + leftEdges + upEdges + downEdges]
print(max(energized))
