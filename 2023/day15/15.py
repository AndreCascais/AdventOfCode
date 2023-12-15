from collections import defaultdict
import sys
from functools import reduce
import re

sequence = sys.stdin.read().splitlines()[0].split(",")


def hash(step):
    return reduce(lambda total, element: ((total + ord(element)) * 17) % 256, step, 0)


hashSum = sum([hash(step) for step in sequence])

print(hashSum)

boxes = defaultdict(lambda: defaultdict(int))

for step in sequence:
    op = re.split("=|-", step.strip("-"))
    label = op[0]
    box = hash(label)
    # - case
    if len(op) == 1:
        if label in boxes[box]:
            del boxes[box][label]
    # = case
    else:
        boxes[box][label] = int(op[1])

focusingPowers = [
    (boxIdx + 1) * (slot + 1) * length
    for boxIdx, box in boxes.items()
    for slot, length in enumerate(box.values())
]

print(sum(focusingPowers))
