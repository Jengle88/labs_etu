import kotlin.math.ceil
import kotlin.math.sqrt
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
        return Pair(-1, -1)
    return Pair(minX, field[minX])
}

data class Square(val xUpLeft: Int, val yUpLeft: Int, var size: Int)

fun solve(n: Int): List<Square> {
    if (n % 2 == 0) {
        return listOf(
            Square(0, 0, n / 2),
            Square(n / 2, 0, n / 2),
            Square(0, n / 2, n / 2),
            Square(n / 2, n / 2, n / 2),
        )
    }

    val field: MutableList<Int> = MutableList(n) { 0 }
    val squares: MutableList<Square> = mutableListOf()
    var minAnswerSquares: MutableList<Square> = MutableList(n * n) { Square(0, 0, 0) }
    squares.add(Square(0, 0, n - 1))
    changeField(field, 0, n - 1, n - 1)
    while (squares.isNotEmpty()) {
        val (x, y) = findFreeCell(field)
        if (x == -1 && y == -1 || // заполнили поле
            squares.size >= minAnswerSquares.size || // до этого было решение лучше
            (minAnswerSquares.size - squares.size == 2 && field.maxOf { it } < field.size) // нужно разместить 2 квадрата, но нижняя часть поля не заполнена (значит либо 2 квадрата не расставить, либо мы повернули поле на 180 и больший квадрат снизу - аналог большего квадрата сверху слева)
        ) {
            if (minAnswerSquares.size > squares.size && x == -1 && y == -1) {
                for (i in squares.indices) {
                    minAnswerSquares[i] = Square(squares[i].xUpLeft, squares[i].yUpLeft, squares[i].size)
                }
                minAnswerSquares = minAnswerSquares.dropLast(minAnswerSquares.size - squares.size).toMutableList()
            }
            while (squares.isNotEmpty() && (squares.last().size == 1 || squares.size >= minAnswerSquares.size || (minAnswerSquares.size - squares.size == 2 && field.maxOf { it } < field.size))) {
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

val ALL_TEST = false

@OptIn(ExperimentalTime::class)
fun main() {
    if (ALL_TEST) {
        for (n in 2 until 35) {
            val lst: List<Square>
            val time = measureTime { lst = solve(n) }
            println("$n) ${time}, ansSize:${lst.size}")
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
