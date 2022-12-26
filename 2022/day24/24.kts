val input = generateSequence { readLine() }.toList()


typealias Coord = Pair<Int, Int>
// place, dir
typealias Blizzard = Pair<Coord, Coord>

val LEFT = Pair(0, -1)
val RIGHT = Pair(0, 1)
val UP = Pair(-1, 0)
val DOWN = Pair(1, 0)
val NOTHING = Pair(0, 0)
val DIRS = listOf(LEFT, RIGHT, UP, DOWN, NOTHING)

fun blizzardCharToCoord(ch: Char): Coord =
    when (ch) {
        '^' -> Pair(-1, 0)
        '>' -> Pair(0, 1)
        '<' -> Pair(0, -1)
        else -> Pair(1, 0)
    }


var initialBlizzards =
    input.flatMapIndexed { rowIndex, row ->
        row.mapIndexedNotNull { colIndex, ch ->
            if (ch in "<>^v") {
                Pair(Pair(rowIndex, colIndex), blizzardCharToCoord(ch))
            } else {
                null
            }
        }
    }.toSet()

val nRows = input.size
val nCols = input[0]!!.length

fun Pair<Int, Int>.plus(other: Pair<Int, Int>): Pair<Int, Int> =
    Pair((this.first + other.first).mod(nRows), (this.second + other.second).mod(nCols))

val start = Pair(0, input.take(1)[0]!!.indexOfFirst { it == '.' })
val finish = Pair(nRows - 1, input.takeLast(1)[0]!!.indexOfFirst { it == '.' })


fun moveBlizzard(blizzard: Blizzard): Blizzard {
    val nextCoord = blizzard.first.plus(blizzard.second)
    val (nextRow, nextCol) = nextCoord
    return if (input[nextRow][nextCol] == '#') moveBlizzard(
        Blizzard(
            nextCoord,
            blizzard.second
        )
    ) else Blizzard(nextCoord, blizzard.second)
}

fun moveBlizzards(blizzards: Set<Blizzard>): Set<Blizzard> {
    return blizzards.map { blizzard ->
        moveBlizzard(blizzard)
    }.toSet()
}


fun printMap() {
    input.forEachIndexed { rowIndex, row ->
        row.forEachIndexed { colIndex, col ->
            val ch = initialBlizzards.firstOrNull {
                it.first == Pair(
                    rowIndex,
                    colIndex
                )
            }?.let { 'B' } ?: input[rowIndex][colIndex]
            print("$ch")
        }
        println("")
    }
}


fun BFS(targets : List<Coord>): Int {
    // blizzard locations for each minute (to cache)
    var blizzardMap = mutableMapOf(0 to initialBlizzards)
    val timeLocationSet = mutableSetOf<Pair<Int, Coord>>()
    var targetIdx = 0

    var queue = ArrayDeque<Pair<Int, Coord>>()
    queue.add(Pair(0, start))
    while (!queue.isEmpty()) {
        val (time, pos) = queue.removeFirst()
        if (timeLocationSet.contains(Pair(time, pos))) {
            // that position was already searched
            continue
        }
        if (pos == targets[targetIdx]) {
            if (++targetIdx >= targets.size) {
                return time
            }
            queue.clear()
            queue.add(Pair(time, pos))
            timeLocationSet.clear()
        }

        timeLocationSet.add(Pair(time, pos))
        if (!blizzardMap.contains(time + 1)) {
            val blizz = moveBlizzards(blizzardMap[time]!!)
            blizzardMap[time + 1] = blizz
        }
        val blizzards = blizzardMap[time + 1]!!
        DIRS.forEach {
            val nextPos = pos.plus(it)
            if (nextPos.first in 0..(nRows - 1) && input[nextPos.first][nextPos.second] != '#' && !blizzards.any { it.first == nextPos }) {
                queue.addLast(Pair(time + 1, nextPos))
            }
            // since the blizzard map increases a lot in size, we can cut it by removing older time
            // maps. this works since we are doing a bfs and we know that we won't visit earlier times
            blizzardMap = blizzardMap.filter { it.key >= time }.toMutableMap()
        }
    }
    return -1
}

val pt1 = BFS(listOf(finish))
println("$pt1")
val pt2 = BFS(listOf(finish, start, finish))
println("$pt2")




