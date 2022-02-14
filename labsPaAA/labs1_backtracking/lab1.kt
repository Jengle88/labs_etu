import kotlin.time.ExperimentalTime
import kotlin.time.measureTime


fun fillSquare(field: MutableList<MutableList<Boolean>>, xStart: Int, yStart: Int, size: Int, value: Boolean) {
    for (i in xStart until xStart + size) {
        for (j in yStart until yStart + size) {
            field[j][i] = value
        }
    }
}


fun findFreeCell(field: MutableList<MutableList<Boolean>>, xStart: Int = 0, yStart: Int = 0): Pair<Int, Int> {
    for (j in yStart until field.size) {
        for (i in xStart until field[0].size) {
            if (!field[j][i])
                return Pair(i, j)
        }
    }
    return Pair(-1, -1)
}

data class Square(val xUpLeft: Int, val yUpLeft: Int, var size: Int)

fun solve(n: Int): List<Square> {
    val field: MutableList<MutableList<Boolean>> = MutableList(n) { MutableList(n) { false } }
    val squares: MutableList<Square> = mutableListOf()
    var minAnswerSquares: MutableList<Square> = MutableList(n * n) { Square(0, 0, 0) }
    for (i in 0 until n) {
        for (j in 0 until n) {
            minAnswerSquares[i] = Square(i, j, 1)
        }
    }
    squares.add(Square(0, 0, n - 1))
    fillSquare(field, 0, 0, n - 1, true)
    while (squares.isNotEmpty()) {
        val (x, y) = findFreeCell(field)
        if (x == -1 && y == -1) {
            if (minAnswerSquares.size > squares.size) {
                for (i in squares.indices) {
                    minAnswerSquares[i] = Square(squares[i].xUpLeft, squares[i].yUpLeft, squares[i].size)
                }
                minAnswerSquares = minAnswerSquares.dropLast(minAnswerSquares.size - squares.size).toMutableList()
            }
            while (squares.isNotEmpty() && (squares.last().size == 1 || squares.size >= minAnswerSquares.size)) {
                fillSquare(field, squares.last().xUpLeft, squares.last().yUpLeft, squares.last().size, false)
                squares.removeLast()
            }
            if (squares.isNotEmpty()) {
                fillSquare(field, squares.last().xUpLeft, squares.last().yUpLeft, squares.last().size, false)
                fillSquare(field, squares.last().xUpLeft, squares.last().yUpLeft, squares.last().size - 1, true)
//                for (i in 0 until squares.last().size) {
//                    field[squares.last().yUpLeft + squares.last().size - 1][squares.last().xUpLeft + i] = false
//                }
//                for (i in 0 until squares.last().size) {
//                    field[squares.last().yUpLeft + i][squares.last().xUpLeft + squares.last().size - 1] = false
//                }
                squares.last().size--
            }
        } else {
            var delta = 1
            while (x + delta < field.size && y + delta < field[0].size && !field[y][x + delta] && !field[y + delta][x])
                delta++
            fillSquare(field, x, y, delta, true)
            squares.add(Square(x, y, delta))
        }
    }
    return minAnswerSquares
}

val DEBUG = false

@OptIn(ExperimentalTime::class)
fun main() {
    if (DEBUG) {
        for (n in 2 until 21) {
            println("$n) ${measureTime { solve(n) }}")
        }
    } else {
        val n = readLine()!!.toInt()
        val answer = solve(n)
        println(answer.size)
        for (item in answer) {
            println("${item.xUpLeft + 1} ${item.yUpLeft + 1} ${item.size}")
        }
    }
}