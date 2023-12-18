from collections import defaultdict
import sys
import queue

heatLossMap = [list(map(int, line)) for line in sys.stdin.read().splitlines()]

start = (0, 0)
end = (len(heatLossMap) - 1, len(heatLossMap[0]) - 1)


nodes = [
    (row, col) for row in range(len(heatLossMap)) for col in range(len(heatLossMap[0]))
]

dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]

edges = defaultdict(list)

for node in nodes:
    x, y = node
    for dir in dirs:
        dx, dy = dir
        nx = x + dx
        ny = y + dy
        for steps in range(1, 3):
            edges[(node, dir, steps)].append(((nx, ny), dir, steps + 1))

        rotations = [(-abs(dy), -abs(dx)), (abs(dy), abs(dx))]
        for rx, ry in rotations:
            lx = x + rx
            ly = y + ry
            for steps in range(1, 4):
                edges[(node, dir, steps)].append(((lx, ly), (rx, ry), 1))


ultraEdges = defaultdict(list)

for node in nodes:
    x, y = node
    for dir in dirs:
        dx, dy = dir
        nx = x + dx
        ny = y + dy
        for steps in range(1, 10):
            if not (
                (nx <= 0 and dx == -1)
                or (nx >= len(heatLossMap) - 1 and dx == 1)
                or (ny <= 0 and dy == -1)
                or (ny >= len(heatLossMap[0]) - 1 and dy == 1)
            ) or steps >= 4:
                ultraEdges[(node, dir, steps)].append(((nx, ny), dir, steps + 1))

        rotations = [(-abs(dy), -abs(dx)), (abs(dy), abs(dx))]
        for rx, ry in rotations:
            lx = x + rx
            ly = y + ry
            maxX = x + 4 * rx
            maxY = y + 4 * ry
            # if (maxX <= 0 or maxX >= len(heatLossMap) - 1 or maxY <= 0 or maxY >= len(heatLossMap[0]) - 1):
            for steps in range(4, 11):
                ultraEdges[(node, dir, steps)].append(((lx, ly), (rx, ry), 1))


def dijkstra(edges=edges):
    visited = set()
    distances = {node: sys.maxsize for node in edges.keys()}
    start = ((0, 0), (0, 1), 1)
    distances[start] = 0
    prev = {}
    q = queue.PriorityQueue()
    q.put((0, start))
    while not q.empty():
        prio, node = q.get()
        # print(f"Checking node {node} with prio {prio}")
        if node[0] == (len(heatLossMap) - 1, len(heatLossMap[0]) - 1):
            print(f"dist is {prio} for node {node}")
            return (node, prev)

        visited.add(node)
        for neighbor in edges[node]:
            # print(f"Checking neighbor {neighbor}")
            if neighbor in visited:
                continue
            try:
                updatedDist = prio + heatLossMap[neighbor[0][0]][neighbor[0][1]]
                if updatedDist < distances[neighbor]:
                    distances[neighbor] = updatedDist
                    q.put((updatedDist, neighbor))
                    prev[neighbor] = node
            except:
                pass


# last, prevDic = dijkstra()
# 889 -- last guess - too high
last, prevDic = dijkstra(ultraEdges)

# while last[0] != (0, 0):
#     print(f"{last} with weight {heatLossMap[last[0][0]][last[0][1]]}")
#     last = prevDic[last]
