enum class RPS(val value: Int) {
    ROCK(1), PAPER(2), SCISSORS(3);

    companion object {
        fun fromString(str: String): RPS {
            return when (str) {
                in listOf("A", "X") -> ROCK
                in listOf("B", "Y") -> PAPER
                else -> SCISSORS
            }
        }
    }
}

enum class RESULT(val value: Int) {
    WIN(6), LOSE(0), DRAW(3);

    companion object {
        fun fromString(str: String): RESULT {
            return when (str) {
                "X" -> LOSE
                "Y" -> DRAW
                else -> WIN
            }
        }
    }
}

fun getResult(opponent: RPS, player: RPS): RESULT {
    return if (
        player == RPS.ROCK && opponent == RPS.SCISSORS ||
        player == RPS.PAPER && opponent == RPS.ROCK ||
        player == RPS.SCISSORS && opponent == RPS.PAPER
    ) {
        RESULT.WIN
    } else if (player == opponent) {
        RESULT.DRAW
    } else {
        RESULT.LOSE
    }
}

fun score(opponent: RPS, player: RPS): Int {
    return player.value + getResult(opponent, player).value
}

fun getPlay(opponent: RPS, wantedResult: RESULT): RPS {
    return RPS.values().first { getResult(opponent, it) == wantedResult }
}


val game = generateSequence {
    readLine()?.split(" ")
}.toList()

val totalScore = game.map { it -> score(RPS.fromString(it[0]), RPS.fromString(it[1])) }.sum()
println("Total score is $totalScore")


val totalScore2 = game.map {
    val opponentPlay = RPS.fromString(it[0])
    val desiredResult = RESULT.fromString(it[1])
    score(opponentPlay, getPlay(opponentPlay, desiredResult))
}.sum()
println("Total score2 is $totalScore2")


