val matrix = generateSequence { readLine()?.map { it.digitToInt() } }.toList()
val rows = matrix.size
val cols = matrix[0].size


fun getTreeList(coords: Pair<Int, Int>): List<List<Pair<Int, Int>>> {
    val (row, col) = coords
    val height = matrix[row][col]
    val right = (col + 1..(cols - 1)).map { Pair(row, it) }
    val left = ((col - 1) downTo 0).map { Pair(row, it) }
    val up = ((row - 1) downTo 0).map { Pair(it, col) }
    val down = ((row + 1)..(rows - 1)).map { Pair(it, col) }
    return listOf(right, left, up, down)
}

val visible =
    matrix.mapIndexed { row, wholeRow ->
        wholeRow.filterIndexed { col, height ->
            getTreeList(Pair(row, col))
                .any { dir ->
                    dir.isEmpty() || dir.all { (checkRow, checkCol) -> matrix[checkRow][checkCol] < height }
                }
        }.count()
    }.sum()

println("$visible")

val bestScore =
    matrix.flatMapIndexed { row, wholeRow ->
        wholeRow.mapIndexed { col, height ->
            getTreeList(Pair(row, col))
                .map { dir ->
                    dir.indexOfFirst { (checkRow, checkCol) -> matrix[checkRow][checkCol] >= height }
                        .let { if (it == -1) dir.size else it + 1 }
                }
                .reduce { acc, dist -> acc * dist }
        }
    }.max()

println("$bestScore")