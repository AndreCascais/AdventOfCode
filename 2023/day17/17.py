from collections import defaultdict
import sys
import queue

heatLossMap = [list(map(int, line)) for line in sys.stdin.read().splitlines()]

nodes = [
    (row, col) for row in range(len(heatLossMap)) for col in range(len(heatLossMap[0]))
]

dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]

def makeEdges(straightRange, rotationRange):
    edges = defaultdict(list)
    for node in nodes:
        x, y = node
        for dir in dirs:
            dx, dy = dir
            nx = x + dx
            ny = y + dy
            for steps in straightRange:
                if (nx, ny) != (
                    len(heatLossMap) - 1,
                    len(heatLossMap[0]) - 1,
                ) or steps >= rotationRange[0] - 1:
                    edges[(node, dir, steps)].append(((nx, ny), dir, steps + 1))

            rotations = [(-abs(dy), -abs(dx)), (abs(dy), abs(dx))]
            for rx, ry in rotations:
                for steps in rotationRange:
                    edges[(node, dir, steps)].append(((x, y), (rx, ry), 0))
    return edges


def dijkstra(edges):
    visited = set()
    distances = defaultdict(lambda : sys.maxsize)
    startDirs = [(0, 1), (1, 0)]
    q = queue.PriorityQueue()
    for dir in startDirs:
        start = ((0, 0), dir, 0)
        distances[start] = 0
        q.put((0, start))
    while not q.empty():
        distance, node = q.get()
        if node[0] == (len(heatLossMap) - 1, len(heatLossMap[0]) - 1):
            return distance

        visited.add(node)
        for neighbor in edges[node]:
            if neighbor in visited:
                continue
            try:
                updatedDist = distance + (
                    0
                    if neighbor[2] == 0
                    else heatLossMap[neighbor[0][0]][neighbor[0][1]]
                )
                if updatedDist <= distances[neighbor]:
                    distances[neighbor] = updatedDist
                    q.put((updatedDist, neighbor))
            except:
                pass

crucibleEdges = makeEdges(range(4), range(len(heatLossMap)))
superCrucibleEdges = makeEdges(range(11), range(4, 11))
print(dijkstra(crucibleEdges))
print(dijkstra(superCrucibleEdges))
