val input = generateSequence { readLine() }.toList()

var elvePositions = mutableSetOf<Pair<Int, Int>>()

val NORTH = Pair(-1, 0)
val SOUTH = Pair(1, 0)
val WEST = Pair(0, -1)
val EAST = Pair(0, 1)

fun addDirs(dir1: Pair<Int, Int>, dir2: Pair<Int, Int>) =
    Pair(dir1.first + dir2.first, dir1.second + dir2.second)

input.forEachIndexed { rowIndex, row ->
    row.forEachIndexed { colIndex, elem ->
        if (input[rowIndex][colIndex] == '#') {
            elvePositions.add(Pair(rowIndex, colIndex))
        }
    }
}

fun printElves(elvePositions: Set<Pair<Int, Int>>) {
    val minRow = elvePositions.minOf { it.first }
    val maxRow = elvePositions.maxOf { it.first }
    val minCol = elvePositions.minOf { it.second }
    val maxCol = elvePositions.maxOf { it.second }
    (minRow..maxRow).forEach { row ->
        (minCol..maxCol).forEach { col ->
            val toPrint = if (elvePositions.contains(Pair(row, col))) "#" else "."
            print("$toPrint")
        }
        println("")
    }
}

fun countEmpty(elvePositions: Set<Pair<Int, Int>>): Int {
    val minRow = elvePositions.minOf { it.first }
    val maxRow = elvePositions.maxOf { it.first }
    val minCol = elvePositions.minOf { it.second }
    val maxCol = elvePositions.maxOf { it.second }
    return (minRow..maxRow).sumOf { row ->
        (minCol..maxCol).count { col ->
            !elvePositions.contains(Pair(row, col))
        }
    }
}

val dirs = listOf(
    NORTH,
    SOUTH,
    WEST,
    EAST
)

val dirMap = mapOf(
    NORTH to listOf(
        NORTH,
        addDirs(NORTH, WEST),
        addDirs(NORTH, EAST)
    ),
    SOUTH to listOf(
        SOUTH,
        addDirs(SOUTH, WEST),
        addDirs(SOUTH, EAST)
    ),
    WEST to listOf(
        WEST,
        addDirs(WEST, NORTH),
        addDirs(WEST, SOUTH)
    ),
    EAST to listOf(
        EAST,
        addDirs(EAST, NORTH),
        addDirs(EAST, SOUTH)
    ),
)

val allAdjacentDirs = dirMap.values.flatten().toSet()

var elveProposed = mutableMapOf<Pair<Int, Int>, Pair<Int, Int>>()
fun moveElves(rounds: Int, positions: Set<Pair<Int, Int>>): Set<Pair<Int, Int>> {
    var elvePositions = positions
    repeat(rounds) { round ->
        elveProposed.clear()
        elvePositions.forEach nextElve@{ elve ->
            if (allAdjacentDirs.all { dir -> !elvePositions.contains(addDirs(elve, dir)) }) {
                elveProposed[elve] = elve
                return@nextElve
            }
            (round..(round + 4)).map { it % 4 }.forEach { dirIndex ->
                val dir = dirs[dirIndex]!!
                val dirChecks = dirMap[dir]!!
                val isBusyDir = dirChecks.any { dirCheck ->
                    elvePositions.contains(addDirs(elve, dirCheck))
                }
                if (!isBusyDir) {
                    elveProposed[elve] = addDirs(elve, dir)
                    return@nextElve
                }
            }
            elveProposed[elve] = elve
        }
        val nextElvePositions = mutableSetOf<Pair<Int, Int>>()
        elvePositions.forEach { elve ->
            val nextPosition = elveProposed[elve]!!
            val nextPositionUnique = elveProposed.count { it.value == nextPosition } == 1
            nextElvePositions.add(if (nextPositionUnique) nextPosition else elve)
        }
        if (elvePositions.equals(nextElvePositions)) {
            println("Elves stopped after ${round + 1} rounds")
            return elvePositions
        }
        elvePositions = nextElvePositions
    }
    return elvePositions
}

val after10 = moveElves(10, elvePositions)
println("Empty spots after stopping: ${countEmpty(after10)}")
val afterNonStop = moveElves(100000, elvePositions)
