val input = generateSequence { readLine()?.toMutableList() }.toMutableList()
var start = Pair(-1, -1)
var end = Pair(-1, -1)

val allCoords = input.flatMapIndexed { row: Int, line ->
    line.mapIndexedNotNull { col, _ -> Pair(row, col) }
}

println("$allCoords")

allCoords.forEach { (row, col) ->
    when (input[row][col]) {
        'S' -> start = Pair(row, col)
        'E' -> end = Pair(row, col)
        else -> Unit
    }
}


input[start.first][start.second] = 'a'
input[end.first][end.second] = 'z'

val matrix = input.map { line -> line.map { it.code } }

fun bfs(startCoords: Pair<Int, Int> = start): Int {
    val visited = mutableSetOf<Pair<Int, Int>>()
    val queue = ArrayDeque<Pair<Int, Int>>()
    queue.add(startCoords)

    var steps = 0
    while (!queue.isEmpty()) {
        val currentDistQueue = queue.toList()
        queue.clear()
        currentDistQueue.forEach { coords ->
            if (coords == end) {
                return steps
            }
            val (row, col) = coords
            val value = matrix[row][col]
            if (visited.contains(coords)) {
                return@forEach
            }
            visited.add(coords)
            val right = Pair(row, col + 1)
            val left = Pair(row, col - 1)
            val up = Pair(row - 1, col)
            val down = Pair(row + 1, col)
            listOf(right, left, up, down).forEach {
                val (nextRow, nextCol) = it
                val nextValue = matrix.getOrNull(nextRow)?.getOrNull(nextCol)
                if (nextValue ?: Int.MAX_VALUE in (0..(value + 1))) {
                    queue.add(it)
                }
            }
        }
        steps++
    }
    return Int.MAX_VALUE
}

println("reached end in ${bfs()} steps")
val minDist = allCoords.filter { (row, col) -> matrix[row][col] == 'a'.code }.map { bfs(it) }.min()
println("shortest path starting from an a is $minDist")
