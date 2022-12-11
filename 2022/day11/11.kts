import java.math.BigInteger

val input = generateSequence {
    generateSequence {
        readLine()?.replace(",", "")?.split(" ")?.filter({ !it.isEmpty() })?.ifEmpty { null }
    }.toList().ifEmpty { null }
}.toList()

data class Monkey(
    val items: MutableList<BigInteger>,
    val op: (BigInteger) -> BigInteger,
    val divisibleTest: BigInteger,
    val monkeysToSend: List<Int>
)

fun getOp(op: String, arg: String): (BigInteger) -> BigInteger =
    when (op) {
        "*" -> { n: BigInteger -> n.times(if (arg.equals("old")) n else arg.toBigInteger()) }
        "+" -> { n: BigInteger -> n.plus(if (arg.equals("old")) n else arg.toBigInteger()) }
        else -> { n -> n }
    }


val monkeys = input.map { monkey ->
    Monkey(
        monkey[1].map { it.toIntOrNull()?.toBigInteger() }.filterNotNull().toMutableList(),
        getOp(monkey[2][4], monkey[2][5]),
        monkey[3][3].toBigInteger(),
        listOf(monkey[4][5].toInt(), monkey[5][5].toInt())
    )
}


// Since the stress levels can keep multiplying, we can use the product of the required modulo tests
// instead of actually multiplying everytime.
val modTrick = monkeys.map { monkey ->
    monkey.divisibleTest
}.reduce({ acc, n -> acc * n })


fun getInspectedItems(worryDivideBy: BigInteger, rounds: Int): Array<BigInteger> {
    val inspected = Array(monkeys.size, { BigInteger.ZERO })
    repeat(rounds) {
        monkeys.forEachIndexed { index, monkey ->
            monkey.items.forEach {
                inspected[index]++
                val nextWorry = monkey.op(it).div(worryDivideBy).mod(modTrick)
                val testResult = (nextWorry.mod(monkey.divisibleTest)) == BigInteger.ZERO
                val monkeyToSend =
                    if (testResult) monkey.monkeysToSend[0] else monkey.monkeysToSend[1]
                monkeys[monkeyToSend].items.add(nextWorry)
            }
            monkey.items.clear()
        }
    }
    return inspected
}

/*
val mostInspectedMultiplied = getInspectedItems(3, 20).toList().sorted().takeLast(2).reduce({acc, n -> acc * n})
println("$mostInspectedMultiplied")
 */
val mostInspectedMultipliedStress =
    getInspectedItems(BigInteger.ONE, 10000).toList().sorted().takeLast(2)
        .reduce({ acc, n -> acc * n })
println("$mostInspectedMultipliedStress")