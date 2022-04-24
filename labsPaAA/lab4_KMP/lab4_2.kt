import java.io.FileOutputStream
import java.io.OutputStreamWriter

var DEBUG2 = true
val fileWriter2 by lazy {
    OutputStreamWriter(FileOutputStream("fileLog2.txt")) // Файловый поток для вывода
}

fun printLog2(message: String, text: String) {
    if (DEBUG2)
        fileWriter2.write("$message: $text\n")
}

fun getKMPTableInfo2(kmpTable: Array<Int>): String {
    if (kmpTable.isEmpty() || !DEBUG2)
        return ""
    val result = StringBuilder("${kmpTable.first()}")
    for (i in 1 until kmpTable.size) {
        result.append(", ${kmpTable[i]}")
    }
    return result.toString()
}

// вычисление префикс-функции
fun prefFunc(prevIndex: Int, scanTextIndex: Int, prefFuncTable: Array<Int>, scanText: String): Int {
    var kmpIndex = prevIndex // получаем прошлое значение префикс-функции
    printLog2("Сравниваем символ", scanText[scanTextIndex].toString())
    printLog2("Прошлое значение КМП функции", kmpIndex.toString())
    while (kmpIndex > 0 && scanText[scanTextIndex] != scanText[kmpIndex]) { // пока значения префикса и суффикса не равны, уменьшаем kmpIndex
        printLog2("Промежуточное значение", prefFuncTable[kmpIndex - 1].toString())
        kmpIndex = prefFuncTable[kmpIndex - 1]
    }
    // kmpIndex либо 0, либо уменьшился до той степени, что префикс равен суффиксу
    if (scanText[scanTextIndex] == scanText[kmpIndex]) { // если символы равны, то увеличиваем значение префикс-функции на 1
        kmpIndex++
    }
    return kmpIndex
}

fun buildPrefixFunction(text: String): Array<Int> { // функция построения префикс-функции для произвольной строки и возврат массива значений
    val prefFunctionTable: Array<Int> = Array(text.length) { 0 } // таблица значений префикс-функции
    for (i in 1 until text.length) {
        val kmpTempValue = prefFunc(prefFunctionTable[i - 1], i, prefFunctionTable, text) // значение префикс-функции для подстроки
        printLog2("Новое значение КМП функции", kmpTempValue.toString())
        prefFunctionTable[i] = kmpTempValue // заносим значение в массив
        printLog2("Актуальное состояние КМП таблицы", getKMPTableInfo2(prefFunctionTable))
    }
    return prefFunctionTable
}



fun findIndexCycleShift(text: String, pattern: String): Int {
    if (pattern.length != text.length) { // дальше нет смысла смотреть, т.к строки разной длины
        printLog2("Длины не совпали", "text ${text.length} != pattern ${pattern.length}")
        return -1
    }
    val scanText = "$pattern$$text"
    printLog2("Строка для анализа", scanText)
    printLog2("Данные строки", "Размер входной строки = ${scanText.length}, из них: длина текста = " +
            "${text.length}, длина шаблона = ${pattern.length}")
    val kmpTable: Array<Int> = buildPrefixFunction(pattern) // строим префикс-функцию для шаблона
    var prevIndex = 0 // фиксируем прошлое значение префикс-функции
    printLog2("Предпросчёт префикс-функции шаблона завершён", getKMPTableInfo2(kmpTable))

    printLog2("\n\nОбработка основного текста (первый text)", "Процесс начат")
    for (i in pattern.length + 1 until scanText.length) { // просматриваем первую часть (вместо объединения в одну строку просматриваем текст два раза)
        val kmpTempValue = prefFunc(prevIndex, i, kmpTable, scanText)
        printLog2("Новое значение КМП функции", kmpTempValue.toString())
        prevIndex = kmpTempValue // запоминаем текущее значение
        if (prevIndex == pattern.length) { // нашли ответ
            printLog2("Ответ найден", "Ответ: ${i - 2 * pattern.length}")
            return i - 2 * pattern.length // убираем первый паттерн и длину найденного
        }
    }
    printLog2("\n\nОбработка основного текста (второй text)", "Процесс начат")
    for (i in scanText.length until scanText.length + text.length) { // повторяем аналогичные действия
        val kmpTempValue = prefFunc(prevIndex, i - text.length, kmpTable, scanText)
        printLog2("Новое значение КМП функции", kmpTempValue.toString())
        prevIndex = kmpTempValue
        if (prevIndex == pattern.length) { // нашли ответ
            printLog2("Ответ найден", "Ответ: ${i - 2 * pattern.length}")
            return i - 2 * pattern.length // убираем первый паттерн и длину найденного
        }
    }
    printLog2("Ответ не найден", "Ответ: -1")
    return -1
}

fun main() {
    val text = readLine()!!
    val pattern = readLine()!!
    val result = findIndexCycleShift(text, pattern)
    println(result)
    if (DEBUG2)
        fileWriter2.close()
}

