val input = generateSequence { readLine() }.toList()

fun itemPriority(ch: Char) =
    if (ch.isLowerCase()) ch.code - 'a'.code + 1 else ch.code - 'A'.code + 27

// for each rucksack see which is the common element
val rucksacks = input.map { rucksack -> rucksack.chunked(rucksack.length / 2) }
val prioSum = rucksacks
    .map { chunks -> chunks[0].first { chunks[1].contains(it) } }
    .map { itemPriority(it) }
    .sum()

println("prioSum: $prioSum")

// for each group (three chunks) map each chunk to a set and aggregate the intersections
val rucksacksGrouped = input.chunked(3)
val prioSumGrouped = rucksacksGrouped
    .map { group -> group.map { it.toSet() } }
    .map { group -> group.reduce { agg, set -> agg.intersect(set) } }
    .map { itemPriority(it.first()) }
    .sum()

println("groupedPrioSum: $prioSumGrouped")