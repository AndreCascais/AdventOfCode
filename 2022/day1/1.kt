val elfCalories = generateSequence {
    generateSequence {
        readLine()?.ifEmpty { null }?.toInt()
    }.toList().ifEmpty { null }
}.toList().map { it .sum() }

val mostCalories = elfCalories.max()

println("Max calories a elf is carrying: $mostCalories")

val topThreeCalories = elfCalories.sortedDescending().take(3).sum()

println("Sum of top 3 elf calories: $topThreeCalories")
