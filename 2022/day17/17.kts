val jetPattern = readLine()!!
val jetPatternSize = jetPattern.length
println("$jetPattern, ${jetPatternSize}")

class Point(val row: Int, val col: Int) {
    fun plus(other: Point): Point {
        return Point(row + other.row, col + other.col)
    }

    override fun toString(): String {
        return "[$row, $col]"
    }

    override fun equals(other: Any?): Boolean {
        return when (other) {
            is Point -> row == other.row && col == other.col
            else -> false

        }
    }

    override fun hashCode(): Int {
        return row.hashCode() * 31 + col.hashCode()
    }
}

val lineRock = listOf<Point>(
    Point(0, 0),
    Point(0, 1),
    Point(0, 2),
    Point(0, 3)
)

val plusRock = listOf<Point>(
    Point(0, 1),
    Point(1, 0),
    Point(1, 1),
    Point(1, 2),
    Point(2, 1)
)

val lRock = listOf<Point>(
    Point(0, 0),
    Point(0, 1),
    Point(0, 2),
    Point(1, 2),
    Point(2, 2),
)

val colRock = listOf<Point>(
    Point(0, 0),
    Point(1, 0),
    Point(2, 0),
    Point(3, 0),
)

val squareRock = listOf<Point>(
    Point(0, 0),
    Point(0, 1),
    Point(1, 0),
    Point(1, 1)
)

val rocks = listOf(lineRock, plusRock, lRock, colRock, squareRock)
val filled = (0..7).map { Point(-1, it) }.toSet().toMutableSet()
var rockIdx = 0
var jetIdx = 0

val colOffset = Point(0, 2)
val dropOffset = Point(-1, 0)

fun getJetOffset(): Point {
    val ch = jetPattern[jetIdx++ % jetPatternSize]
    if (ch == '<') {
        return Point(0, -1)
    }
    return Point(0, 1)
}

fun colides(rock: List<Point>): Boolean {
    return rock.any { filled.contains(it) || (it.col !in 0..6) }
}

fun markRock(rock: List<Point>) {
    rock.forEach {
        filled.add(it)
    }
}

var firstRowPosition: Point? = null
var firstRowIndex: Int? = null

// (col where starts - jet idx) - (firstCoords, rockIdx)
val rowToRockMap = mutableMapOf<Pair<Int, Int>, Pair<Point, Int>>()
val heightMap = mutableMapOf<Int, Int>()

fun getRockHeight() {
    val nRocks = 2022
    val totalRocks = 1000000000000
    repeat(nRocks) repeat@{
        var rock = rocks[rockIdx++ % rocks.size].map {
            it.plus(colOffset).plus(Point(filled.maxOf { it.row }.plus(4), 0))
        }
        while (true) {
            val jetOffset = getJetOffset()
            var offsetRock = rock.map { it.plus(jetOffset) }
            if (!colides(offsetRock)) {
                rock = offsetRock
            }
            offsetRock = rock.map { it.plus(dropOffset) }
            if (colides(offsetRock)) {
                heightMap[rockIdx - 1] = rock.maxOf { it.row }
                // first type of rock
                if (rockIdx % rocks.size == 1) {
                    val p = Pair(rock[0].col, (jetIdx - 1) % jetPatternSize)
                    if (!rowToRockMap.contains(p)) {
                        rowToRockMap[p] = Pair(rock[0], rockIdx - 1)
                    } else {
                        val (cycleCoords, cycleIdx) = rowToRockMap[p]!!
                        val cycleSize = rockIdx - 1 - cycleIdx
                        val totalOneCycle = rock[0].row - cycleCoords.row
                        val cycles = totalRocks / cycleSize
                        val cyclesHeightSummed = cycles * totalOneCycle
                        println("${cyclesHeightSummed+heightMap[(totalRocks%cycleSize).toInt() - 1]!! + 1} ")
                        return
                    }

                }
                markRock(rock)
                return@repeat
            }
            rock = offsetRock
        }
    }
}

println("${filled.maxOf { it.row } + 1}")
getRockHeight()