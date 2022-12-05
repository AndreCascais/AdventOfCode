var inputStacks = generateSequence { readLine()?.ifEmpty { null } }
    .toList()
    .map { line -> line.chunked(4).map { block -> block[1] } }
    .dropLast(1)
    .reversed()

val orders = generateSequence {
    readLine()
        ?.split(" ")
        ?.mapNotNull { it.toIntOrNull() }
}.toList()

fun createStacks(s: List<List<Char>>): List<ArrayDeque<Char>> {
    val deques = MutableList(s[0].size) { ArrayDeque<Char>() }
    s[0].forEachIndexed { index, _ ->
        s.forEach { line ->
            if (!line[index].equals(' ')) {
                deques[index].add(line[index])
            }
        }
    }
    return deques
}

val stacks = createStacks(inputStacks)
var fancyStacks = createStacks(inputStacks)


orders.forEach { (ammount, from, to) ->
    repeat(ammount) {
        stacks[to - 1].add(stacks[from - 1].removeLast())
    }
}


orders.forEach { (ammount, from, to) ->
    val tempStack = ArrayDeque<Char>()
    repeat(ammount) {
        tempStack.addFirst(fancyStacks[from - 1].removeLast())
    }
    fancyStacks[to - 1].addAll(tempStack)
}

val result = stacks.map { stack -> stack.last() }.joinToString("")
val fancyResult = fancyStacks.map { stack -> stack.last() }.joinToString("")
println("$result")
println("$fancyResult")
