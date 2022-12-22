val traverseOrder = generateSequence { readLine()?.toLong() }.toList()
val key = 811589153
val groveIndexes = listOf(1000, 2000, 3000)

fun mix(times: Int = 1, key: Int = 1): List<Long> {
    val mix = traverseOrder.map { it * key }.withIndex().toMutableList()
    repeat(times) {
        traverseOrder.indices.forEach { index ->
            val idx = mix.indexOfFirst { it.index == index }
            val elem = mix.removeAt(idx)
            val nextPosition = idx + elem.value
            mix.add(nextPosition.mod(mix.size), elem)
        }
    }
    return mix.map { it.value }
}

val mix = mix()
val mixDecrypted = mix(10, key)

listOf(mix, mixDecrypted).forEach { mix ->
    val zeroIdx = mix.indexOf(0)
    val groveSum = groveIndexes.sumOf {
        val nextPosition = zeroIdx + it
        mix[nextPosition.mod(mix.size)]
    }
    println("$groveSum")
}