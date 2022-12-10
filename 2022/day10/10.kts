val input = generateSequence { readLine()?.split(" ") }.toList()

val registerPositions = input.fold(mutableListOf(1), { acc, instruction ->
    acc += acc.last()
    if (instruction[0] == "addx") {
        acc += acc.last() + instruction[1].toInt()
    }
    acc
})

val cycles = listOf(20, 60, 100, 140, 180, 220)

val strengthCycleSum = cycles.sumOf { cycle -> registerPositions[cycle - 1] * (cycle) }

val crtWidth = 40

val crt = registerPositions.indices.fold("", { acc, signalIndex ->
    val crtIndex = signalIndex % crtWidth
    val registerPosition = registerPositions[signalIndex]
    val spriteIndexes = registerPosition..(registerPosition + 2)
    val isPixelBeingDrawn = crtIndex + 1 in spriteIndexes
    acc.plus(if (isPixelBeingDrawn) "#" else ".")
}).chunked(crtWidth).joinToString("\n")

println("$strengthCycleSum")
println("$crt")