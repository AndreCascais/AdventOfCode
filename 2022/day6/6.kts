val packetMarkerSize = 4
val messageMarkerSize = 14

val input = readLine()!!

fun getMarkerIndex(input: String, markerSize: Int): Int {
    val windows =
        input.windowed(markerSize, 1)
    val marker = windows.first { it.toSet().size == markerSize }
    return windows.indexOf(marker) + markerSize

}

val packetIndex = getMarkerIndex(input, packetMarkerSize)
val messageIndex = getMarkerIndex(input, messageMarkerSize)
println("packetIndex: $packetIndex")
println("messageIndex: $messageIndex")
