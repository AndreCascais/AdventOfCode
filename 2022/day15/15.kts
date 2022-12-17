import kotlin.math.abs

val input =
    generateSequence { readLine() }.map {
        Regex("-?[0-9]+").findAll(it).map(MatchResult::value).toList()
    }.toList()

val sensors = input.map { Pair(it[0].toInt(), it[1].toInt()) }
val beacons = input.map { Pair(it[2].toInt(), it[3].toInt()) }

var ranges = mutableSetOf<IntRange>()
val sensorDistanceMap = mutableMapOf<Pair<Int, Int>, Int>()
val lineToCount = 2000000

sensors.indices.forEach { index ->
    val sensor = sensors[index]!!
    val closestBeacon = beacons[index]!!
    val distance =
        abs(sensor.first - closestBeacon.first) + abs(sensor.second - closestBeacon.second)
    sensorDistanceMap[sensor] = distance
    val stepsToRow = abs(sensor.second - lineToCount)
    if (stepsToRow <= distance) {
        val diff = distance - stepsToRow
        ranges.add((sensor.first - diff)..(sensor.first + diff))
    }
}

val sortedRanges = ranges.sortedWith(compareBy({ it.first }, { it.last }))
var first = sortedRanges[0].first
var last = sortedRanges[0].last
var total = last - first
sortedRanges.forEach { range ->
    if (first > range.last && range.first > last) {
        // new segment
        total += range.last - range.first + 1
        first = range.first
    } else {
        // intersection
        total += range.last - last + 1
    }
    last = range.last + 1
}


val line10Beacons = beacons.filter { it.second == lineToCount }.distinct().size
println("${total - line10Beacons}")

fun caughtByAnySensor(point: Pair<Int, Int>): Boolean {
    return sensorDistanceMap.any { (sensor, distance) ->
        distance >= abs(sensor.first - point.first) + abs(sensor.second - point.second)
    }
}

fun getTuningFrequency(): Long {
    sensorDistanceMap.forEach { (sensor, distanceToBeacon) ->
        var margin = Pair(sensor.first + distanceToBeacon + 1, sensor.second)
        // only one margin needs to be look at since we know that the point not seen by the sensors
        // will be surrounded by other 4 margins
        (0..(distanceToBeacon + 1)).forEach inner@{
            margin = Pair(margin.first - 1, margin.second + 1)
            if (!(margin.first in 0..lineToCount * 2) or !(margin.second in 0..lineToCount * 2)) {
                return@inner
            }
            if (!caughtByAnySensor(margin)) {
                return margin.first.toLong() * 4000000 + margin.second.toLong()
            }
        }
    }
    return -1
}

println("${getTuningFrequency()}")
