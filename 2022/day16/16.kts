data class Valve(val label: String, val rate: Int, val neighbors: List<String>)

val MAX = Int.MAX_VALUE / 2

val valves = generateSequence {
    readLine()?.replace("?", "")?.replace(",", "")?.replace(";", "")?.split(" ")
        ?.let { Valve(it[1], it[4].split("=")[1].toInt(), it.subList(9, it.size)) }
}.toList()

val valveMap = valves.associateBy { it.label }
val workingValves = valveMap.filter { it.value.rate > 0 }.keys.toSet()

val minDistanceMap: MutableMap<Pair<String, String>, Int> = valves.flatMap { valve ->
    valve.neighbors.map { neighbor ->
        Pair(valve.label, neighbor) to 1
    }
}.toMap().toMutableMap()

valveMap.keys.forEach { i ->
    valveMap.keys.forEach { j ->
        valveMap.keys.forEach { k ->
            val currentDist = minDistanceMap[Pair(j, k)] ?: MAX
            val nextDist =
                (minDistanceMap[Pair(j, i)] ?: MAX) + (minDistanceMap[Pair(i, k)] ?: MAX)
            if (nextDist < currentDist) {
                minDistanceMap[Pair(j, k)] = nextDist
            }
        }
    }
}

fun getBestFlow(
    label: String,
    timeLeft: Int = 30,
    canUseElephant: Boolean = false,
    opened: Set<String> = setOf<String>(),
): Int {
    if (timeLeft <= 0 || opened.size == workingValves.size) {
        return 0
    }
    val options =
        workingValves.minus(opened).map {
            val neighbor = valveMap[it]!!
            val distance = minDistanceMap[Pair(label, it)]!!
            val timeAfterOpening = timeLeft - distance - 1
            if (timeAfterOpening >= 0) {
                neighbor.rate * timeAfterOpening + getBestFlow(
                    it,
                    timeAfterOpening,
                    canUseElephant,
                    opened.toSet().plus(it),
                )
            } else {
                0
            }
        }.toMutableList()
    if (canUseElephant) {
        options.add(getBestFlow("AA", 26,false, opened))
    }

    return options.max()
}

val bestFlow = getBestFlow("AA")
println("$bestFlow")
val bestFlowElephants = getBestFlow("AA", 26, true)
println("$bestFlowElephants")
