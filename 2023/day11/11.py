import sys
import numpy as np
import itertools

lines = sys.stdin.read().splitlines()

# Using np here just to easily traverse cols
matrix = np.array([list(line) for line in lines])

noGalaxyRows = [
    rowIndex for rowIndex, row in enumerate(matrix) if list(row).count("#") == 0
]
noGalaxyCols = [
    colIndex for colIndex, col in enumerate(matrix.T) if list(col).count("#") == 0
]

galaxies = [
    (row, col)
    for (row, col) in itertools.product(range(matrix.shape[0]), range(matrix.shape[1]))
    if matrix[row, col] == "#"
]


def getShortestPathSum(galaxies, expansionRate=2):
    galaxyPairs = itertools.combinations(galaxies, 2)
    distances = 0
    for (row1, col1), (row2, col2) in galaxyPairs:
        rowRange = range(min(row1, row2), max(row1, row2))
        for row in rowRange:
            distances += expansionRate if row in noGalaxyRows else 1
        colRange = range(min(col1, col2), max(col1, col2))
        for col in colRange:
            distances += expansionRate if col in noGalaxyCols else 1
    return distances


print(getShortestPathSum(galaxies))
print(getShortestPathSum(galaxies, 1000000))
