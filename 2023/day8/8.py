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

def getSteps(element, targets):
    steps = 0
    while element not in targets:
        direction = 0 if directions[steps % len(directions)] == "L" else 1
        element = networkMap[element][direction]
        steps += 1
    return steps

print(f"AAA reaches ZZZ in {getSteps('AAA', ['ZZZ'])} steps")

# For part2, LCM should not work given that it is not explicit that
# The first step for a Z value is repeated every step steps.
elements = [key for key in networkMap.keys() if key[2] == "A"]
targets = [key for key in networkMap.keys() if key[2] == "Z"]

cycles = [getSteps(element, targets) for element in elements]

print(f"All paths Reached --Z in {math.lcm(*cycles)} steps")

