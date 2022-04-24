//import java.io.FileOutputStream
//import java.io.OutputStreamWriter
//
//var DEBUG1 = true
//val fileWriter1 by lazy {
//    OutputStreamWriter(FileOutputStream("fileLog1.txt")) // Файловый поток для вывода
//}
//
//fun printLog1(message: String, text: String) {
//    if (DEBUG1)
//        fileWriter1.write("$message: $text\n")
//}
//
//fun getKMPTableInfo1(kmpTable: Array<Int>): String {
//    if (kmpTable.isEmpty() || !DEBUG1)
//        return ""
//    val result = StringBuilder("${kmpTable.first()}")
//    for (i in 1 until kmpTable.size) {
//        result.append(", ${kmpTable[i]}")
//    }
//    return result.toString()
//}
//
//// вычисление префикс-функции
//fun prefFunc(prevIndex: Int, scanTextIndex: Int, prefFuncTable: Array<Int>, scanText: String): Int {
//    var kmpIndex = prevIndex // получаем прошлое значение префикс-функции
//    printLog1("Сравниваем символ", scanText[scanTextIndex].toString())
//    printLog1("Прошлое значение КМП функции", kmpIndex.toString())
//    while (kmpIndex > 0 && scanText[scanTextIndex] != scanText[kmpIndex]) { // пока значения префикса и суффикса не равны, уменьшаем kmpIndex
//        printLog1("Промежуточное значение", prefFuncTable[kmpIndex - 1].toString())
//        kmpIndex = prefFuncTable[kmpIndex - 1]
//    }
//    // kmpIndex либо 0, либо уменьшился до той степени, что префикс равен суффиксу
//    if (scanText[scanTextIndex] == scanText[kmpIndex]) { // если символы равны, то увеличиваем значение префикс-функции на 1
//        kmpIndex++
//    }
//    return kmpIndex
//}
//
//fun findAllIncludesPatternKMP(text: String, pattern: String): MutableList<Int> { // КМП
//    val scanText = "$pattern$$text" // текст для сканирования
//    val kmpTable: Array<Int> = Array(scanText.length) { 0 } // таблица значений КМП функции
//    printLog1("Строка для анализа", scanText)
//    printLog1("Данные строки", "Размер входной строки = ${scanText.length}, из них: длина текста = " +
//            "${text.length}, длина шаблона = ${pattern.length}")
//    val listOfIndexIncludes = mutableListOf<Int>() // итоговый ответ
//    for (i in 1 until scanText.length) { // сканируем текст, по ходу высчитывая значения префикс-функции для каждого префикса scanText
//        val kmpTempValue = prefFunc(kmpTable[i - 1], i, kmpTable, scanText) // вызываем префикс-функцию
//        printLog1("Новое значение КМП функции", kmpTempValue.toString())
//        kmpTable[i] = kmpTempValue // заносим значение префикс-функции в таблицу
//        printLog1("Актуальное состояние КМП таблицы", getKMPTableInfo1(kmpTable))
//        if (kmpTable[i] == pattern.length) { // если мы нашли подстроку, то записываем ответ
//            printLog1("Добавление нового индекса", (i - 2 * pattern.length).toString())
//            listOfIndexIncludes.add(i - 2 * pattern.length) // (индекс) - (длина шаблона в начале строки) - (длина найденной подстроки, равная длине шаблона)
//        }
//    }
//    printLog1("Количество найденных индексов", listOfIndexIncludes.size.toString())
//    return listOfIndexIncludes.ifEmpty { mutableListOf(-1) } // если listOfIndexIncludes == 0, то возвращаем список с элементом -1
//}
//
//fun main() {
//    val pattern = readLine()!!
//    val text = readLine()!!
//    val result = findAllIncludesPatternKMP(text, pattern)
//    for (i in result.indices) {
//        if (i != result.size - 1)
//            print("${result[i]},")
//        else
//            println("${result[i]}")
//    }
//    if (DEBUG1)
//        fileWriter1.close()
//}
