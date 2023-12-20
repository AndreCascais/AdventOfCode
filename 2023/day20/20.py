from collections import defaultdict
import sys
from enum import Enum
from math import lcm


class Type(Enum):
    Conjuntion = 1
    FlipFlop = 2
    Broadcast = 3
    Untyped = 4


class Pulse(Enum):
    High = 1
    Low = 2


class Controller:
    def __init__(self, controllerStr = "", noType = False):
        self.memory = defaultdict(lambda: Pulse.Low)
        if (noType):
            self.type = Type.Untyped
            return
        label, targets = [s.strip() for s in controllerStr.split("->")]
        self.type = self.getType(label)
        self.name = label if label[0] not in "%&" else label[1:]
        self.targets = [target.strip() for target in targets.split(",")]
        self.on = False
    
    def reset(self):
        self.on = False
        self.memory = {key: Pulse.Low for key in self.memory.keys()}
        return self


    def getType(self, label):
        if label[0] == "%":
            return Type.FlipFlop
        elif label[0] == "&":
            return Type.Conjuntion
        else:
            return Type.Broadcast

    def propagatePulse(self, pulse, src):
        if self.type == Type.Broadcast:
            return [(self.name, target, pulse) for target in self.targets]
        elif self.type == Type.FlipFlop:
            if pulse == Pulse.High:
                return []
            self.on = not self.on
            nextPulse = Pulse.High if self.on else pulse.Low
            return [(self.name, target, nextPulse) for target in self.targets]
        elif self.type == Type.Conjuntion:
            self.memory[src] = pulse
            if all([mem == Pulse.High for mem in self.memory.values()]):
                nextPulse = Pulse.Low
            else:
                nextPulse = Pulse.High
            return [(self.name, target, nextPulse) for target in self.targets]
        else:
            return []


def processPulses(times = 100000):
    global controllerMap
    pulseCount = defaultdict(int)
    for time in range(1, times):
        queue = [("button", "broadcaster", Pulse.Low)]
        while queue:
            src, target, pulse = queue.pop(0)
            # for the second part, finding the Conjuntions leading to qt and their loops
            # would give the answer after lcm'ing them
            if (target == "qt" and pulse == Pulse.High):
                print(src, target, pulse)
                print(time)
            pulseCount[pulse] += 1
            for next in controllerMap[target].propagatePulse(pulse, src):
                queue.append(next)
        # controllerMap = {name:controller.reset() for name, controller in controllerMap.items()}
    return pulseCount


controllers = [Controller(line) for line in sys.stdin.read().splitlines()]
controllerMap = defaultdict(
    lambda: Controller(noType=True), {controller.name: controller for controller in controllers}
)


conjs = [controller for controller in controllers if controller.type == Type.Conjuntion]
print(conjs)

for conj in conjs:
    for controller in controllers:
        if conj.name in controller.targets:
            conj.memory[controller.name] = Pulse.Low


pulseCounts = processPulses()
print(pulseCounts[Pulse.Low] * pulseCounts[Pulse.High])
