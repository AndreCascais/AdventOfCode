val input = generateSequence { readLine()?.ifEmpty { null } }.toList()
val instructions = readLine()!!.let {
    val toMove = Regex("[0-9]+").findAll(it).map(MatchResult::value).toList().map { it.toInt() }
    val toRotate = listOf("R").plus(Regex("R|L").findAll(it).map(MatchResult::value).toList())
    toRotate.zip(toMove)
}

val dirMap = mapOf(
    0 to Pair(0, 1),
    1 to Pair(1, 0),
    2 to Pair(0, -1),
    3 to Pair(-1, 0)
)


val coordMap = emptyMap<Pair<Int, Int>, Char>().toMutableMap()
input.forEachIndexed { rowIndex, row ->
    row.forEachIndexed { colIndex, elem ->
        if (elem in ".#") {
            coordMap[Pair(rowIndex, colIndex)] = elem
        }
    }
}

val rows = input.size
val cols = input.maxOf { it.length }

var coord = coordMap.filter { it.key.first == 0 }.minByOrNull { it.key.second }!!.key
var dir = 3

fun getNextCoord(coord: Pair<Int, Int>, dir: Pair<Int, Int>): Pair<Int, Int> {
    val nextRow = (coord.first + dir.first).mod(rows)
    val nextCol = (coord.second + dir.second).mod(cols)
    var nextCoord = Pair(nextRow, nextCol)
    if (coordMap.contains(nextCoord)) {
        return nextCoord
    }
    return getNextCoord(nextCoord, dir)
}

instructions.forEach { (rotate, move) ->
    dir = (dir + if (rotate == "R") 1 else -1).mod(dirMap.size)
    val offset = dirMap[dir]!!
    repeat(move) {
        val nextCoord = getNextCoord(coord, offset)
        if (coordMap[nextCoord]!!.equals('#')) {
            return@forEach
        }
        coord = nextCoord
    }
}

val password = (coord.first + 1) * 1000 + (coord.second + 1) * 4 + dir
println("$password")

// [coord, dir]
//  1 2
//  3
//4 5
//6
fun getNextCoord2(coord: Pair<Int, Int>, dir: Pair<Int, Int>): Pair<Pair<Int, Int>, Int> {
    val (row, col) = coord
    val nextRow = (coord.first + dir.first)
    val nextCol = (coord.second + dir.second)
    var nextCoord = Pair(nextRow, nextCol)
    if (coordMap.contains(nextCoord)) {
        return Pair(nextCoord, 0)
    }
    var wrapedRow = 0
    var wrapedCol = 0
    var wrapedOffset = 0
    // start with going right
    if (nextCol >= 150) {
        // 2 right - 5 right
        wrapedCol = 99
        wrapedRow = 149 - nextRow
        wrapedOffset = 2
    }
    else if (nextCol >= 100 && nextRow in 50..99) {
        // 3 right - 2 down
        wrapedRow = 49
        wrapedCol = 100 + (nextRow % 49)
        wrapedOffset = 3
    }
    else if (nextCol >= 100 && nextRow in 100..149) {
        // 5 right - 2 right
        wrapedCol = 149
        wrapedRow = 49 - (nextRow % 49)
        wrapedOffset = 2
    }
    else if (nextCol >= 50 && nextRow in 150..199) {
        // 6 right - 5 down
        wrapedRow = 149
        wrapedCol = 49 + (199 - nextRow)
        wrapedOffset = 3
    }
    // left
    else if (nextCol <= 49 && nextRow in 0..49 ) {
        // 1 left - 4 left
        wrapedCol = 0
        wrapedRow = 149 - nextRow
        wrapedOffset = 2
    }
    else if (nextCol <= 49 && nextRow in 50..99) {
        // 3 left - 4 up
        wrapedRow = 100
        wrapedCol = nextRow % 49
        wrapedOffset = 3
    }
    else if (nextCol < 0 && nextRow in 100..149) {
        // 4 left - 1 left
        wrapedCol = 50
        wrapedRow = 49 - (nextRow % 49)
        wrapedOffset = 2
    }
    else if (nextCol < 0 && nextRow > 150) {
        // 6 left - 1 up
        wrapedRow = 0
        wrapedCol = 50 + nextRow % 49
        wrapedOffset = 3
    }
    // up
    else if (nextRow < 0 && nextCol in 50..99) {
        // 1 up - 6 left
        wrapedCol = 0
        wrapedRow = 149 + nextCol % 49
        wrapedOffset = 1
    }
    else if (nextRow < 0 && nextCol >= 100) {
        // 2 up - 6 down
        wrapedRow = 199
        wrapedCol = nextCol % 49
        wrapedOffset = 0
    }
    else if (nextRow < 99 && nextCol in 0..49) {
        // 4 up - 3 left
        wrapedCol = 50
        wrapedRow = 99 - (nextCol % 49)
        wrapedOffset = 1
    }
    // down
    else if (nextRow > 49 && nextCol > 99) {
        // 2 down - 3 left
        wrapedCol = 100
        wrapedRow = 49 + (nextCol % 49)
        wrapedOffset = 3
    }
    else if (nextRow > 149 && nextCol in 49..99) {
        // 5 down - 6 right
        wrapedCol = 49
        wrapedRow = 159 + (nextCol % 49)
        wrapedOffset = 1
    }
    else if (nextRow > 199) {
        // 6 down - 2 up
        wrapedRow = 0
        wrapedCol = 99 + (nextCol % 49)
        wrapedOffset = 0
    }
    println("Special case $nextCoord, going to [$wrapedRow, $wrapedCol] and dir offset is $wrapedOffset")
    return Pair(Pair(wrapedRow, wrapedCol), wrapedOffset)
}

var coordCube = coordMap.filter { it.key.first == 0 }.minByOrNull { it.key.second }!!.key

instructions.forEach { (rotate, move) ->
    dir = (dir + if (rotate == "R") 1 else -1).mod(dirMap.size)
    val offset = dirMap[dir]!!
    println("$coord, $rotate, $move, $offset")
    repeat(move) {
        val (nextCoord, dirOffset) = getNextCoord2(coord, offset)
        dir = dir + dirOffset.mod(dirMap.size)
        if (coordMap[nextCoord]!!.equals('#')) {
            return@forEach
        }
        coord = nextCoord
    }
}
