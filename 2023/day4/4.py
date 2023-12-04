import sys
import re

games = sys.stdin.read().splitlines()

wins = [0 for _ in games]
for gameIndex, game in enumerate(games):
    winning, picks = re.match(".*:(.*)\|(.*)", game).groups()
    wins[gameIndex] = len([pick for pick in picks.split() if pick in winning.split()])

count = sum([pow(2, win - 1) for win in wins if win > 0])
print(count)

cards = [1 for _ in games]
for cardIndex, cardCount in enumerate(cards):
    for index in range(cardIndex + 1, cardIndex + 1 + wins[cardIndex]):
        cards[index] += int(cardCount)

print(sum(cards))

