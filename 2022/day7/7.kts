val input = generateSequence { readLine()?.split(" ") }!!.toList().drop(1)

class TreeNode<T>(val value: T, val parent: TreeNode<T>? = null) {
    val children: MutableList<TreeNode<T>> = mutableListOf()
    fun isLeaf() = children.isEmpty()
    fun cd(dir: String): TreeNode<T> {
        if (dir == "..") {
            return parent!!
        } else {
            return children.first { child ->
                child.value == dir
            }
        }
    }
}

val root = TreeNode<String>("/")
var current = root

input.forEach { line ->
    if (line[0].equals("$")) {
        if (line[1].equals("cd")) {
            current = current.cd(line[2])
        }
    } else {
        // if a file we add its value, otherwise the dir name
        current.children.add(
            TreeNode<String>(
                (line[0].toIntOrNull() ?: line[1]).toString(),
                current
            )
        )
    }
}

fun getDirSize(root: TreeNode<String>): Int {
    return if (root.isLeaf()) root.value.toInt() else root.children.map { getDirSize(it) }.sum()
}

fun getDirs(root: TreeNode<String>): List<TreeNode<String>> {
    return if (root.isLeaf()) emptyList() else root.children.flatMap { getDirs(it) } + root
}

val benchmarkSize = 100000
val totalDirSize = getDirSize(root)
val fsSize = 70000000
val updateSize = 30000000
val freeSpaceNeeded = totalDirSize - (fsSize - updateSize)

val allDirs = getDirs(root)
val dirSizeSumSmallerThanBenchmark = allDirs
    .map { getDirSize(it) }.filter { it <= benchmarkSize }.sum()

println("Sum of dir sizes <= $benchmarkSize is $dirSizeSumSmallerThanBenchmark")

val smallestDirToDelete =
    allDirs.map { getDirSize(it) }.filter { it > freeSpaceNeeded }.min()

println("Smallest dir size to free $freeSpaceNeeded is $smallestDirToDelete")

