from collections import defaultdict
import sys
import re
import portion as P
from portion.api import functools
from portion.func import operator

workflows, parts = [section.splitlines() for section in sys.stdin.read().split("\n\n")]

workflows = [re.findall("(\w+)\{(.*,)(\w+)\}", workflow)[0] for workflow in workflows]
parts = [eval(re.sub("(\w+)=(\w)", "'\\1':\\2", part)) for part in parts]

workflowMap = {
    workflow[0]: re.findall("(\w+)([<>])(\d+):(\w+)", workflow[1])
    + [("x", ">", "0", workflow[2])]
    for workflow in workflows
}


def workflow(part, conds, index):
    src, op, dest, nextLabel = conds[index]
    if eval(f"{part[src]} {op} {dest}"):
        if nextLabel in "AR":
            return nextLabel
        return workflow(part, workflowMap[nextLabel], 0)
    else:
        return workflow(part, conds, index + 1)


ratingSum = sum(
    [
        sum(part.values())
        for part in parts
        if workflow(part, workflowMap["in"], 0) == "A"
    ]
)
print(ratingSum)

intervalWorkflowMap = defaultdict(list)
for label, workflows in workflowMap.items():
    for category, op, value, target in workflows:
        interval = (
            P.closedopen(1, int(value))
            if (op == "<")
            else P.openclosed(int(value), 4000)
        )
        intervalWorkflowMap[label].append((category, interval, target))


def getCombinations(intervalPart):
    return functools.reduce(
        operator.mul,
        [len(list(P.iterate(interval, 1))) for interval in intervalPart.values()],
        1,
    )


def intervalWorkflow(intervalPart, conds, index):
    category, interval, nextLabel = conds[index]
    intersectionPart = intervalPart.copy()
    complementPart = intervalPart.copy()

    intersection = intervalPart[category].intersection(interval)
    complement = intervalPart[category].intersection(~intersection)

    intersectionPart[category] = intersection
    complementPart[category] = complement

    combinations = (
        0
        if complement == P.empty()
        else intervalWorkflow(complementPart, conds, index + 1)
    )
    if nextLabel == "A":
        combinations += getCombinations(intersectionPart)
    elif nextLabel != "R":
        combinations += intervalWorkflow(
            intersectionPart, intervalWorkflowMap[nextLabel], 0
        )
    return combinations


intervalPart = {category: P.closed(1, 4000) for category in "xmas"}
totalCombinations = intervalWorkflow(intervalPart, intervalWorkflowMap["in"], 0)
print(totalCombinations)
