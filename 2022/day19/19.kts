operator fun <T> List<T>.component6(): T = get(5)
val blueprints =
    generateSequence { readLine() }.map {
        Regex("-?[0-9]+").findAll(it).map(MatchResult::value).toList().map { it.toInt() }.let {
            listOf(
                listOf(it[1], 0, 0, 0),
                listOf(it[2], 0, 0, 0),
                listOf(it[3], it[4], 0, 0),
                listOf(it[5], 0, it[6], 0)
            )
        }
    }.toList()

var maxGeodes = 0
val blueprintGeodeProductions = blueprints.take(3).mapIndexed { idx, blueprint ->
    val resourceMap = mutableListOf(0, 0, 0, 0)
    val robotMap = mutableListOf(1, 0, 0, 0)
    println("$blueprint")
    maxGeodes = 0
    getMostGeodes(32, resourceMap, robotMap, blueprint)
}


fun timeToBuildRobot(
    resources: MutableList<Int>,
    robots: MutableList<Int>,
    costs: List<Int>
): Int {
    return costs.mapIndexed { i, cost ->
        if (cost == 0) {
            0
        } else if (robots[i] == 0) {
            1000
        } else (cost - resources[i] - 1 + robots[i]) / robots[i]
    }.max()
}

fun getMostGeodes(
    timeLeft: Int,
    resources: MutableList<Int>,
    robots: MutableList<Int>,
    costs: List<List<Int>>
): Int {
    val remainingGeodes = resources[3] + robots[3] * timeLeft
    if ((timeLeft * timeLeft - timeLeft) / 2 + remainingGeodes <= maxGeodes) {
        return remainingGeodes
    }
    val options = robots.mapIndexed { robotType, _ ->
        val timeToBuildRobot = timeToBuildRobot(resources, robots, costs[robotType]) + 1
        if (timeLeft - timeToBuildRobot < 1) {
            0
        } else {
            getMostGeodes(
                timeLeft - timeToBuildRobot,
                resources.mapIndexed { resourceIndex, resource -> resource + timeToBuildRobot * robots[resourceIndex] - costs[robotType][resourceIndex] }
                    .toMutableList(),
                robots.toMutableList().also { it[robotType]++ },
                costs
            )
        }
    }
    maxGeodes = maxOf(options.max(), maxGeodes, remainingGeodes)
    return maxOf(options.max(), remainingGeodes)
}

println("${blueprintGeodeProductions.sum()}")
val s = blueprintGeodeProductions.reduce { acc, elem -> acc * elem }
println("$s")