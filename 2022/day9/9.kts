import kotlin.math.absoluteValue

val motions =
    generateSequence {
        readLine()?.split(" ")?.let {
            Pair(it[0], it[1].toInt())
        }
    }.toList()

val dirMap = mapOf(
    "R" to Pair(0, 1),
    "L" to Pair(0, -1),
    "U" to Pair(1, 0),
    "D" to Pair(-1, 0),
)

fun add(p1: Pair<Int, Int>, p2: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(p1.first + p2.first, p1.second + p2.second)
}

fun sub(p1: Pair<Int, Int>, p2: Pair<Int, Int>): Pair<Int, Int> {
    return Pair(p1.first - p2.first, p1.second - p2.second)
}

fun getTailVisited(knots: Int): Set<Pair<Int, Int>> {
    var knotPositions = MutableList(knots, { Pair(0, 0) })
    var visited = mutableSetOf(knotPositions[0])

    motions.forEach { (dir, ammount) ->
        val offset = dirMap[dir] ?: (0 to 0)
        repeat(ammount) {
            knotPositions[0] = add(knotPositions[0], offset)
            for (idx in 1..(knots - 1)) {
                val (diffRow, diffCol) = sub(knotPositions[idx - 1], knotPositions[idx])
                if (diffRow.absoluteValue > 1 || diffCol.absoluteValue > 1) {
                    val (row, col) = knotPositions[idx]
                    knotPositions[idx] = Pair(
                        row + diffRow.coerceIn(-1..1),
                        col + diffCol.coerceIn(-1..1)
                    )
                }
            }
            visited.add(knotPositions[knots - 1])
        }
    }
    return visited
}


println("${getTailVisited(2).size}")
println("${getTailVisited(10).size}")