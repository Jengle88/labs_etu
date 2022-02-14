import kotlin.time.ExperimentalTime
import kotlin.time.measureTime

fun changeField(field: MutableList<Int>, xStart: Int, size: Int, delta: Int) {
    for (i in xStart until xStart + size) {
        field[i] += delta
    }
}

fun findFreeCell(field: MutableList<Int>): Pair<Int, Int> {
    var minX = 0
    for (i in field.indices) {
        if (field[i] < field[minX]) {
            minX = i
        }
    }
    if (field[minX] == field.size)
        return Pair(-1,-1)
    return Pair(minX, field[minX])
}

data class Square(val xUpLeft: Int, val yUpLeft: Int, var size: Int)

fun solve(n: Int): List<Square> {
    val field: MutableList<Int> = MutableList(n) { 0 }
    val squares: MutableList<Square> = mutableListOf()
    var minAnswerSquares: MutableList<Square> = MutableList(n * n) { Square(0, 0, 0) }
    for (i in 0 until n) {
        for (j in 0 until n) {
            minAnswerSquares[i] = Square(i, j, 1)
        }
    }
    squares.add(Square(0, 0, n - 1))
    changeField(field, 0, n-1, n - 1)
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
                changeField(field, squares.last().xUpLeft, squares.last().size, -squares.last().size)
                squares.removeLast()
            }
            if (squares.isNotEmpty()) {
                changeField(field, squares.last().xUpLeft, squares.last().size, -squares.last().size)
                changeField(field, squares.last().xUpLeft, squares.last().size - 1, squares.last().size - 1)
                squares.last().size--
            }
        } else {
            var delta = 1
            while (x + delta < field.size && y + delta < field.size && field[x] + delta < field.size && field[x + delta] <= y)
                delta++
            changeField(field, x, delta, delta)
            squares.add(Square(x, y, delta))
        }
    }
    return minAnswerSquares
}

val DEBUG = true

@OptIn(ExperimentalTime::class)
fun main() {
    if (DEBUG) {
        for (n in 2 until 25) {
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