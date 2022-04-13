// поиск всех строк pattern в text
// начало
fun findAllIncludesPatternKMP(text: String, pattern: String): MutableList<Int> {
    val scanText = "$pattern$$text"
    val kmpTable: Array<Int> = Array(scanText.length) { 0 }
    val listOfIndexIncludes = mutableListOf<Int>()
    for (i in 1 until scanText.length) {
        var kmpIndex = kmpTable[i - 1]
        while (kmpIndex > 0 && scanText[i] != scanText[kmpIndex]) {
            kmpIndex = kmpTable[kmpIndex - 1]
        }
        if (scanText[i] == scanText[kmpIndex]) {
            kmpIndex++
        }
        kmpTable[i] = kmpIndex
        if (kmpTable[i] == pattern.length)
            listOfIndexIncludes.add(i - 2 * pattern.length)
    }
    return listOfIndexIncludes.ifEmpty { mutableListOf(-1) }
}


fun solve1() {
    val pattern = readLine()!!
    val text = readLine()!!
    val result = findAllIncludesPatternKMP(text, pattern)
    for (i in result.indices) {
        if (i != result.size - 1)
            print("${result[i]},")
        else
            println("${result[i]}")
    }
}
// конец

// Проверка, является ли строка pattern циклическим сдвигом text
// начало
fun buildPrefixFunction(text: String): Array<Int> {
    val prefFunctionTable: Array<Int> = Array(text.length) { 0 }
    for (i in 1 until text.length) {
        var kmpIndex = prefFunctionTable[i - 1]
        while (kmpIndex > 0 && text[i] != text[kmpIndex]) {
            kmpIndex = prefFunctionTable[kmpIndex - 1]
        }
        if (text[i] == text[kmpIndex]) {
            kmpIndex++
        }
        prefFunctionTable[i] = kmpIndex
    }
    return prefFunctionTable
}

fun findIndexCycleShift(text: String, pattern: String): Int {
    if (pattern.length != text.length)
        return -1
    val scanText = "$pattern$$text"
    val kmpTable: Array<Int> = buildPrefixFunction(pattern) // строим префикс функцию для шаблона
    var prevIndex = 0 // фиксируем прошлое значение из массива
    for (i in 1 until scanText.length) { // просматриваем первую часть (вместо объединения в одну строку просматриваем текст два раза)
        var kmpIndex = prevIndex
        while (kmpIndex > 0 && scanText[i] != scanText[kmpIndex]) { // если символы не равны, то откатываем индекс KMP назад на основании таблицы
            kmpIndex = kmpTable[kmpIndex - 1]
        }
        if (scanText[i] == scanText[kmpIndex]) { // если символы равны, то увеличиваем KMP индекс
            kmpIndex++
        }
        prevIndex = kmpIndex // запоминаем текущее значение
        if (prevIndex == pattern.length) // нашли ответ
            return i - 2 * pattern.length // убираем первый паттерн и длину найденного
    }
    for (i in scanText.length until scanText.length + text.length) { // повторяем аналогичные действия
        var kmpIndex = prevIndex
        while (kmpIndex > 0 && scanText[i - text.length] != scanText[kmpIndex]) { // убираем длину text, чтобы не выходить за границы массива
            kmpIndex = kmpTable[kmpIndex - 1]
        }
        if (scanText[i - text.length] == scanText[kmpIndex]) { // убираем длину text, чтобы не выходить за границы массива
            kmpIndex++
        }
        prevIndex = kmpIndex
        if (prevIndex == pattern.length) // нашли ответ
            return i - 2 * pattern.length // убираем первый паттерн и длину найденного
    }
    return -1
}

fun solve2() {
    val text = readLine()!!
    val pattern = readLine()!!
    val result = findIndexCycleShift(text, pattern)
    println(result)
}
// конец

fun main() {
    solve1()
    solve2()
}

