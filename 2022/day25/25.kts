import kotlin.math.absoluteValue
import kotlin.math.pow
import kotlin.math.roundToInt
import kotlin.math.roundToLong

val input = generateSequence { readLine() }.toList()

fun Char.toDecimal() = when (this) {
    '1' -> 1
    '2' -> 2
    '-' -> -1
    '=' -> -2
    else -> 0
}

fun getClosest(pow: Long, target: Long): Long {
    return listOf(1, 2, -1, -2).minBy { (it * pow - target).absoluteValue }.toLong()
}

fun Long.toSNAFUChar(): Char =
    when (this) {
        1L -> '1'
        2L -> '2'
        -1L -> '-'
        else -> '='
    }

fun SNAFUtoDecimal(num: String): Long {
    if (num.length == 0) {
        return 0
    }
    return num[0].toDecimal() * ((5.toDouble()).pow(num.length - 1)).toLong() + SNAFUtoDecimal(
        num.substring(
            1
        )
    )
}

fun getClosestPower(num: Long): Long {
    val nonRoundedLog = kotlin.math.log(num.absoluteValue.toDouble(), 5.0)
    return listOf(
        kotlin.math.ceil(nonRoundedLog),
        kotlin.math.floor(nonRoundedLog)
    ).minBy {
        val pow = 5.toDouble().pow(it).toLong()
        val diff = (pow - num.absoluteValue).absoluteValue
        diff
    }.toLong()

}

fun DecimalToSNAFU(num: Long): String {
    if (num == 0L) {
        return ""
    }
    var closestPow = getClosestPower(num)
    var calcPow = 5.toDouble().pow(closestPow.toDouble()).toLong()
    var closest = getClosest(calcPow, num)
    println("Calculating SNAFU for $num")
    println("ClosestPow: $closestPow, calcPow: $calcPow, closestMult $closest")
    val nextNum = num - closest * calcPow
    val nextClosestPow = getClosestPower(nextNum).let { if (it < 0) -1 else it}
    println("NextClosestPow: $nextClosestPow")
    Thread.sleep(100)
    val zeros =
        if (nextClosestPow == closestPow) "" else "0".repeat((closestPow - nextClosestPow - 1).toInt())
    return closest.toSNAFUChar() + zeros + DecimalToSNAFU(num - closest * calcPow)
}
println("${DecimalToSNAFU(12)}")
println("${DecimalToSNAFU(13)}")
listOf(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 2022, 12345, 314159265).forEach {
    println("${DecimalToSNAFU(it.toLong())}")
}
listOf(1747, 906, 198, 11, 201, 31, 1257, 31, 353, 107, 7, 3, 37).forEach {
    println("${DecimalToSNAFU(it.toLong())}")
}

val sum = input.sumOf { SNAFUtoDecimal(it) }
println("$sum")

val totalSNAFU = DecimalToSNAFU(sum)
println("$totalSNAFU")
println("${SNAFUtoDecimal(totalSNAFU)}")



