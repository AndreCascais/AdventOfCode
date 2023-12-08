import sys
import re
import math

lines = sys.stdin.read().splitlines()

directions = lines[0]
network = lines[2:]

networkMap = dict(
    [
        (key, (left, right))
        for line in network
        for key, left, right in re.findall("(\w+) = \((\w+), (\w+)\)", line)
    ]
)

element = "AAA"
steps = 0

while element != 'ZZZ':
    direction = 0 if directions[steps % len(directions)] == 'L' else 1
    element = networkMap[element][direction]
    steps += 1

elements = [key for key in networkMap.keys() if key[2] == "A"]
endingElements = [key for key in networkMap.keys() if key[2] == "Z"]
print(f"AAA reaches ZZZ in {steps} steps")


stepMap = []
for element in elements:
    steps = 0
    while element not in endingElements:
        direction = 0 if directions[steps % len(directions)] == "L" else 1
        element = networkMap[element][direction]
        steps += 1
    stepMap.append(steps)

print(f"All paths Reached --Z in {math.lcm(*stepMap)} steps")
