val input = generateSequence {
    readLine()?.split(",")?.map { it.split("-").map { str -> str.toInt() } }
}.toList()

val included = input
    .map { ranges -> ranges.map { (it[0]..it[1]).toSet() } }
    .filter { ranges ->
        val intersection = ranges[1].intersect(ranges[0])
        intersection == ranges[1] || intersection == ranges[0]
    }.size

val overlap = input
    .map { ranges -> ranges.map { (it[0]..it[1]).toSet() } }
    .filter { ranges ->
        !ranges[0].intersect(ranges[1]).isNullOrEmpty()
    }.size

println("$included")
println("$overlap")

