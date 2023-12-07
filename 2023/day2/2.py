import sys
from functools import reduce
import operator
import re

restrictions = {"red": 12, "green": 13, "blue": 14}

validGames = 0
games = sys.stdin.read().splitlines()
for game in games:
    splits = game.split(":")
    gameNumber = int(splits[0].split(" ")[1])
    draws = re.split(";|,", splits[1])
    for draw in draws:
        number, color = draw.split()
        if int(number) > restrictions[color]:
            break
    else:
        validGames += gameNumber
        continue
    break

print(f"ValidGames: {validGames}")


powerSum = 0
for game in games:
    splits = game.split(":")
    sets = splits[1].split(";")
    data = {"blue": [], "red": [], "green": []}
    draws = re.split(";|,", splits[1])
    for draw in draws:
        number, color = draw.split()
        number, color = draw.split()
        data[color].append(int(number))
    powerSum += reduce(operator.mul, [max(x) for _, x in data.items()], 1)

print(f"Powers summed: {powerSum}")
