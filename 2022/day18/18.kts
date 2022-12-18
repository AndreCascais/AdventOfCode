// lets add +1 so that we can access every coord -1 (the lowest coord is zero)
val lavaBlocks = generateSequence { readLine()?.split(',')?.map { it.toInt() + 1 } }.toList()

// +2 on the maxes so that we can access the indexes directly (+1) and to be able to go around the
// maxes when flooding
val maxX = lavaBlocks.maxOf { it[0] } + 2
val maxY = lavaBlocks.maxOf { it[1] } + 2
val maxZ = lavaBlocks.maxOf { it[2] } + 2

val matrix = Array(maxX, { Array(maxY, { BooleanArray(maxZ) }) })
lavaBlocks.forEach { (x, y, z) -> matrix[x][y][z] = true }

val dirOffsets = let {
    val up = listOf(0, 0, 1)
    val down = listOf(0, 0, -1)
    val right = listOf(1, 0, 0)
    val left = listOf(-1, 0, 0)
    val front = listOf(0, 1, 0)
    val back = listOf(0, -1, 0)
    listOf(up, down, right, left, front, back)
}

val lavaSurfaceArea = lavaBlocks.sumOf { (x, y, z) ->
    val up = listOf(0, 0, 1)
    val down = listOf(0, 0, -1)
    val right = listOf(1, 0, 0)
    val left = listOf(-1, 0, 0)
    val front = listOf(0, 1, 0)
    val back = listOf(0, -1, 0)
    dirOffsets.count { (offsetX, offsetY, offsetZ) ->
        !matrix[x + offsetX][y + offsetY][z + offsetZ]
    }
}

fun floodOutside(): MutableSet<List<Int>> {
    val visited = mutableSetOf<List<Int>>()
    val queue = ArrayDeque<List<Int>>()
    queue.add(listOf(0, 0, 0))
    while (!queue.isEmpty()) {
        val coord = queue.removeFirst()
        val (x, y, z) = coord
        if (x !in 0..(maxX - 1) || y !in 0..(maxY - 1) || z !in 0..(maxZ - 1)) {
            continue
        }
        if (visited.contains(listOf(x, y, z)) || matrix[x][y][z]) {
            continue
        }
        visited.add(coord)
        dirOffsets.forEach { (offsetX, offsetY, offsetZ) ->
            queue.add(listOf(x + offsetX, y + offsetY, z + offsetZ))
        }
    }
    return visited
}

val allBlocks = (0..maxX - 1).flatMap { x ->
    (0..maxY - 1).flatMap { y ->
        (0..maxZ - 1).map { z ->
            listOf<Int>(x, y, z)
        }
    }
}
val outsideAirBlocks = floodOutside()
val insideBlocks = allBlocks.filter { !outsideAirBlocks.contains(it) && !lavaBlocks.contains(it) }
val trappedSurfaceArea = insideBlocks.sumOf { (x, y, z) ->
    dirOffsets.count { (offsetX, offsetY, offsetZ) ->
        matrix[x + offsetX][y + offsetY][z + offsetZ]
    }
}

println("$lavaSurfaceArea ${lavaSurfaceArea - trappedSurfaceArea}")
