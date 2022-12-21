val monkeys =
    generateSequence {
        readLine()?.replace(":", "")?.split(' ')
    }.map { it[0] to it }.toMap()


fun getOp(n1: Long, n2: Long, op: String): Long =
    when (op) {
        "*" -> n1 * n2
        "+" -> n1 + n2
        "-" -> n1 - n2
        "/" -> n1 / n2
        else -> n1
    }

fun reverse(op: String) =
    when (op) {
        "+" -> "-"
        "-" -> "+"
        "*" -> "/"
        "/" -> "*"
        else -> "+"
    }

val monkeyMap = mutableMapOf<String, Long>()
val deterministicMonkeyMap = mutableMapOf<String, Long>()

fun getMonkeyYell(name: String): Long {
    if (monkeyMap.contains(name)) {
        return monkeyMap[name]!!
    }
    val monkey = monkeys[name]!!
    if (monkey[1].toLongOrNull() != null) {
        return monkey[1].toLong()

    }
    val left = getMonkeyYell(monkey[1])
    val right = getMonkeyYell(monkey[3])
    val total = getOp(left, right, monkey[2])
    monkeyMap[name] = total
    return total
}

println("${getMonkeyYell("root")}")

fun fillMonkeyYells(name: String) {
    if (name == "humn") {
        return
    }
    val monkey = monkeys[name]!!
    if (monkey[1].toLongOrNull() != null) {
        deterministicMonkeyMap[name] = monkey[1].toLong()
        return
    }
    fillMonkeyYells(monkey[1])
    fillMonkeyYells(monkey[3])
    if (!deterministicMonkeyMap.contains(monkey[1]) || !deterministicMonkeyMap.contains(monkey[3])) {
        return
    }
    val left = deterministicMonkeyMap[monkey[1]]!!
    val right = deterministicMonkeyMap[monkey[3]]!!

    deterministicMonkeyMap[name] = getOp(left, right, monkey[2])
}

fillMonkeyYells("root")

fun solve(): Long {
    var total: Long = 0
    var monkey = monkeys["root"]!!.toMutableList().also { it[2] = "-" }.toList()
    while (monkey[0] != "humn") {
        var (_, left, op, right) = monkey
        if (deterministicMonkeyMap.contains(right)) {
            val knownMonkey = deterministicMonkeyMap[right]!!
            op = reverse(op)
            monkey = monkeys[left]!!
            total = getOp(total, knownMonkey, op)
        } else {
            val left = deterministicMonkeyMap[monkey[1]]!!
            op = reverse(op)
            // edge case 2 - x = total means x = (total - 2)*-1
            if (op == "+" && monkey[0] != "root") {
                op = "-"
                monkey = monkeys[right]!!
                total = getOp(total, left, op) * -1
            } else {
                monkey = monkeys[right]!!
                total = getOp(total, left, op)
            }
        }
    }
    return total
}

val humnValue = solve()
println("$humnValue")