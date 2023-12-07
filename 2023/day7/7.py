import sys
import re
from collections import Counter


class Hand:
    cardRanks = "23456789TJQKA"
    cardWildcardRanks = "J23456789TQKA"

    def __init__(self, cards, bid, wildcards=False):
        self.cards = cards
        self.bid = bid
        self.wildcards = wildcards

    def __gt__(self, other):
        combos = self.getCombos()
        otherCombos = other.getCombos()
        for n in range(5, -1, -1):
            if combos[n] > otherCombos[n]:
                return True
            if combos[n] < otherCombos[n]:
                return False
        ranks = self.cardRanks if not self.wildcards else self.cardWildcardRanks
        for card, otherCard in zip(self.cards, other.cards):
            cardRank = ranks.index(card)
            otherCardRank = ranks.index(otherCard)
            if cardRank > otherCardRank:
                return True
            if cardRank < otherCardRank:
                return False
        return False

    def __str__(self):
        return f"{self.cards} - {self.bid}"

    def getCombos(self):
        counter = Counter(self.cards)
        if not self.wildcards:
            return Counter(counter.values())
        else:
            wildcardCount = counter["J"]
            if wildcardCount == 5:
                return Counter({5: 1})
            del counter["J"]
            mostCommon = counter.most_common(1)[0][0]
            counter[mostCommon] += wildcardCount
            return Counter(counter.values())


lines = sys.stdin.read().splitlines()
hands = [
    Hand(cards, int(bid))
    for line in lines
    for cards, bid in re.findall("(\w+) (\w+)", line)
]
handsWildcards = [Hand(hand.cards, hand.bid, True) for hand in hands]
hands.sort()
handsWildcards.sort()
result = sum([hand.bid * (rank + 1) for rank, hand in enumerate(hands)])
resultWildcard = sum(
    [hand.bid * (rank + 1) for rank, hand in enumerate(handsWildcards)]
)
print(result)
print(resultWildcard)
