//import java.io.FileOutputStream
//import java.io.OutputStreamWriter
//import java.util.SortedSet
//
//var DEBUG2 = false
//val INDIVIDUAL_TASK = true
//val fileWriter2 by lazy {
//    OutputStreamWriter(FileOutputStream("filelog2.txt")) // Файловый поток для вывода
//}
//
//fun log2(message: String, text: String) {
//    if (DEBUG2)
//        fileWriter2.write("$message: $text\n")
//}
//
//class StringInclusion( // класс для хранения ответа
//    val startPos: Int, // позиция строки в тексте
//    val strIndex: Int // индекс строки в списке шаблонов
//) : Comparable<StringInclusion> {
//    override fun compareTo(other: StringInclusion) : Int { // компаратор для сортировки
//        return if (this.startPos == other.startPos)
//            this.strIndex.compareTo(other.strIndex)
//        else
//            this.startPos.compareTo(other.startPos)
//    }
//}
//
//class BorNode(
//    val parentNode: BorNode? = null, // родитель
//    val mapOfEdges: MutableMap<Char, BorNode?> = mutableMapOf(), // map для сопоставления символа и вершины
//    val symbolOnEdge: Char = '.', // символ, лежащий на ребре между родителем и данной вершины
//    var sufLink: BorNode? = null, // суффиксная ссылка
//    var indicesPattern: MutableList<Int> = mutableListOf() // индексы шаблонов, оканчивающихся в данной вершине
//) {
//    fun addNewEdge(symbol: Char) { // добавить ребро
//        mapOfEdges[symbol] = BorNode(this, mutableMapOf(), symbol)
//    }
//}
//
//class Bor(
//    patterns: Array<String> // шаблоны искомых строк
//) {
//    private val root = BorNode() // корень бора
//    fun getRoot(): BorNode = root // геттер для корня
//    init {
//        log2("Построение бора", "начало")
//        for ((i, pattern) in patterns.withIndex()) { // делаем DFS для первичного построения бора (без рекурсии)
//            // под первичным бором подразумевается простое построение рёбер по шаблонам строк, без суфф ссылок
//            log2("Обработка шаблона", "№${i+1}")
//            var tempNode = root
//            for ((index, symb) in pattern.withIndex()) { // Ребра для актуальных символов
//                if (!tempNode.mapOfEdges.containsKey(symb)) { // не было ребра
//                    log2("Добавление ребра", "добавлено ребро из вершины с состоянием ${pattern.substring(0, index)}")
//                    tempNode.addNewEdge(symb) // добавляем ребро
//                }
//                log2("Спуск по ребру", "спуск по ребру с символом $symb")
//                tempNode = tempNode.mapOfEdges[symb]!! // спускаемся по ребру
//            }
//            log2("Метка терминальной вершины", "в вершине была отмечена строка $pattern")
//            tempNode.indicesPattern.add(i) // когда построили очередной шаблон - конечная вершина является терминальной
//        }
//    }
//
//    fun buildAhoCorasick(alphabet: List<Char>) {
//        log2("Алфавит", "Алфавит $alphabet был установлен")
//        root.sufLink = root // исключительный случай - у корня суфф ссылка ведёт в себя
//        val queue: MutableList<BorNode> =
//            mutableListOf(root) // делаем BFS для расстановки суффиксных ссылок и переходов
//        while (queue.isNotEmpty()) { // пока BFS не закончен
//            val tempNode = queue.first() // достаём вершину из очереди
//            log2("Взятие вершины", "из очереди была взята вершина, в которую ведёт символ ${tempNode.symbolOnEdge}")
//            queue.removeFirst() // и удаляем её
//            for (node in tempNode.mapOfEdges) { // добавляем все рёбра бора для продолжения BFS
//                queue.add(node.value!!)
//                log2("Добавление в очередь", "в очередь была добавлена вершина, в которую ведёт " +
//                        "символ ${node.value!!.symbolOnEdge}")
//            }
//            if (tempNode in root.mapOfEdges.values) { // если находимся в вершине, являющейся дочерней корню
//                tempNode.sufLink = root // то суффиксная ссылка ведёт в корень
//                log2("Добавление суффиксной ссылки", "суффиксная ссылка ведёт в корень (дочерняя вершина корня)")
//            } else if (tempNode != root) { // иначе если это общая вершина (или корень)
//                tempNode.sufLink = tempNode.parentNode?.sufLink?.mapOfEdges?.get(tempNode.symbolOnEdge)
//                    ?: root // добавляем суфф ссылку
//                log2("Добавление суффиксной ссылки", "была добавлена суффиксная ссылка из ${tempNode.symbolOnEdge} " +
//                        "в ${tempNode.sufLink?.symbolOnEdge}")
//            }
//            if ((tempNode.sufLink?.indicesPattern?.size?: 0) != 0) { // если есть суффикс, являющийся терминальным, то добавляем его
//                tempNode.indicesPattern.addAll(tempNode.sufLink?.indicesPattern ?: mutableListOf())
//                log2("Метка терминальной вершины", "в вершину ${tempNode.symbolOnEdge} были добавлены индексы шаблонов " +
//                        "${tempNode.sufLink?.indicesPattern ?: mutableListOf()}")
//            }
//            for (symb in alphabet) {
//                if (!tempNode.mapOfEdges.containsKey(symb)) { // добавляем возможные переходы
//                    tempNode.mapOfEdges[symb] = tempNode.sufLink?.mapOfEdges?.get(symb)
//                    log2("Добавление перехода", "был добавлен переход из ${tempNode.symbolOnEdge} " +
//                            "в ${tempNode.sufLink?.symbolOnEdge} через $symb" )
//                }
//            }
//        }
//    }
//}
//
//fun findAllInclusions(text: String, patterns: Array<String>): MutableList<StringInclusion> {
//    val alphabet = listOf('A','C','G','T','N') // алфавит
//    val bor = Bor(patterns) // построение бора
//    log2("Построение бора", "выполнено")
//    bor.buildAhoCorasick(alphabet)
//    log2("Ахо-Корасик", "алгоритм применён")
//    var node = bor.getRoot()
//    val result = mutableListOf<StringInclusion>() // будущий ответ
//    for ((i, symb) in text.withIndex()) { // проверяем вершины на терминальность через DFS обхода бора
//        log2("Обработка символа", "просматривается символ $symb")
//        node = node.mapOfEdges[symb] ?: bor.getRoot()
//        if (node.indicesPattern.size != 0) { // вершина терминальная
//            log2("Обнаружены подстроки", "найдено ${node.indicesPattern.size} подстрок")
//            for (index in node.indicesPattern) {
//                log2("Информация о подстроке", "подстрока №$index найдена на позиции ${i - patterns[index].length + 1}")
//                result.add(StringInclusion(i - patterns[index].length + 1, index)) // добавляем ответ
//            }
//        }
//    }
//    return result // возвращаем ответ
//}
//
//fun findPositionsJokerStr(text: String, textWithJoker: String, joker: Char): Pair<MutableList<String>, MutableList<Int>> {
//    log2("Текст", text)
//    log2("Строка с джокерами", textWithJoker)
//    log2("Джокер", joker.toString())
//    val patterns = mutableListOf<String>() // храним отдельно каждую подстроку (результат разделения textWithJoker на подстроки без джокера)
//    val strBuilder = java.lang.StringBuilder("")
//    var cntLeftJokers = 0  // количество джокеров слева от первого символа не джокера
//    var cntRightJokers = 0 // количество джокеров справа от последнего символа не джокера
//    while (textWithJoker[cntLeftJokers] == joker) // считаем джокеров слева
//        cntLeftJokers++
//    log2("Количество джокеров слева", "$cntLeftJokers")
//    for (i in textWithJoker.length - 1 downTo 0) { // считаем джокеров справа
//        if (textWithJoker[i] == joker)
//            cntRightJokers++
//        else
//            break
//    }
//    log2("Количество джокеров справа", "$cntRightJokers")
//    val distsBetweenNonJokerSubstr = mutableListOf<Int>() // храним расстояния между отделёнными подстроками (количество джокеров между ними)
//    var tempDist = 0 // расстояние между строками без джокеров
//    for (i in cntLeftJokers until textWithJoker.length - cntRightJokers) { // расстояние между осмысленными частями текста
//        if (textWithJoker[i] == joker) { // если это джокер
//            tempDist++ // увеличиваем счётчик
//            if (strBuilder.isNotEmpty()) { // если начался джокер, то обычная подстрока закончилась - заносим её как шаблон
//                patterns.add(strBuilder.toString()) // добавляем
//                log2("Добавление подстроки", "добавлена подстрока $strBuilder")
//                strBuilder.clear() // очищаем для новой строки
//            }
//        } else { // если обычная строка
//            if (tempDist != 0) { // если расстояние не 0, то до этого были джокеры - заносим их количество
//                distsBetweenNonJokerSubstr.add(tempDist) // добавляем
//                log2("Добавление длины подстроки джокеров", "добавлено расстояние между подстроками - $tempDist джокеров")
//                tempDist = 0 // обнуляем счётчик
//            }
//            strBuilder.append(textWithJoker[i]) // добавляем символ в подстроку, которая станет одним из шаблонов
//        }
//    }
//    log2("Шаблоны", "были найдены шаблоны $patterns")
//    log2("Длины подстрок джокеров", "были найдены длины между подстроками $distsBetweenNonJokerSubstr")
//    if (strBuilder.isNotEmpty()) { // если осталась подстрока
//        patterns.add(strBuilder.toString()) // добавляем
//        log2("Добавление последней подстроки", "была добавлена последняя подстрока $strBuilder")
//        log2("Шаблоны", "Актуальное состояние шаблонов $patterns")
//    }
//    log2("Получение расположений шаблонов", "начато")
//    val resultInclusions = findAllInclusions(text, patterns.toTypedArray()) // решаем задачу: поиск шаблонов patterns в тексте text
//    log2("Получение расположений шаблонов", "закончено")
//    val resultInclusionsMap = mutableMapOf<Int, SortedSet<Int>>() // будем хранить данные (номер шаблона -> его позиции в тексте)
//    for (inclusion in resultInclusions) { // сохраняем данные в Map
//        if (resultInclusionsMap.containsKey(inclusion.strIndex))
//            resultInclusionsMap[inclusion.strIndex]?.add(inclusion.startPos)
//        else
//            resultInclusionsMap[inclusion.strIndex] = sortedSetOf(inclusion.startPos)
//    }
//    log2("Структуризация шаблонов", "шаблоны были упорядочены - $resultInclusionsMap")
//    if (resultInclusionsMap.size != patterns.size) { // если в тексте не были найдены все подстроки (без джокеров) textWithJoker
//        log2("Алгоритм прерван", "количество обнаруженных шаблонов (${resultInclusionsMap.size}) не совпало " +
//                "с количеством требуемых (${patterns.size})")
//        return Pair(patterns, mutableListOf()) // дальше нет смысла искать
//    }
//    val result = mutableListOf<Int>()
//    for (firstSubstrStartPos in resultInclusionsMap[0]!!) { // делаем цикл for по первой подстроке
//        log2("Подбор подстроки для textWithJoker", "начальная позиция - $firstSubstrStartPos")
//        if (firstSubstrStartPos - cntLeftJokers < 0) { // если слева мало символов (не все джокеры будут задействованы)
//            log2("Подбор подстроки для textWithJoker", "не все джокеры слева задействованы, поиск прерван")
//            continue // такой случай не подходит
//        }
//        var prevPos = firstSubstrStartPos + patterns[0].length // следующая позиция для проверки
//        log2("Подбор подстроки для textWithJoker", "актуальная позиция - $prevPos")
//        // (позиция начала подстроки + её длина = начало подстроки с джокерами)
//        var badSubstr = false // если при просмотре очередной подстроки она окажется неподходящей
//        for (i in 1 until resultInclusionsMap.size) { // просмотр остальных подстрок
//            if (resultInclusionsMap[i]!!.contains(prevPos + distsBetweenNonJokerSubstr[i-1])) { // если расположение
//                // следующей подстроки удовлетворяет
//                prevPos += distsBetweenNonJokerSubstr[i - 1] + patterns[i].length // добавляем количество джокеров и длину шаблона
//                log2("Подбор подстроки для textWithJoker", "актуальная позиция - $prevPos")
//            } else {
//                badSubstr = true // ни одно из расположений не удовлетворяет -> такой случай не подходит
//                break
//            }
//        }
//        if (badSubstr) { // если расположение не подошло
//            log2("Подбор подстроки для textWithJoker", "не было найдено подходящей подстроки")
//            continue // такой случай не подходит
//        }
//        if (prevPos + cntRightJokers > text.length) { // если справа недостаточно символов, чтобы покрыть всех джокеров
//            log2("Подбор подстроки для textWithJoker", "не все джокеры справа задействованы, поиск прерван")
//            continue // такой случай не подходит
//        }
//        result.add(firstSubstrStartPos - cntLeftJokers)
//        log2("Добавление ответа", "найдена подходящая подстрока - её начальная позиция " +
//                "${firstSubstrStartPos - cntLeftJokers}")
//    }
//    return Pair(patterns, result)
//}
//
//fun individualTask(
//    text: String, // текст
//    textWithJoker: String, // строка с джокерами
//    patterns: Array<String>, // шаблоны искомых строк
//    foundIndicesOfPatterns: MutableList<Int> // найденные шаблоны в тексте
//): Pair<String, String> {
//    log2("\n\nИндивидуальное задание", "начало")
//    val bor = Bor(patterns) // построение бора
//    log2("Построение бора", "выполнено")
//    // поиск вершины с самым большим количеством дуг
//    var nodeResult: BorNode = bor.getRoot()
//    for (pattern in patterns) { // делаем DFS по шаблонам для поиска наибольшего количества рёбер
//        var node = bor.getRoot()
//        for (symb in pattern) {
//            node = node.mapOfEdges[symb] ?: bor.getRoot()
//            log2("Переход по ребру", "спуск по ребру с символом $symb")
//            if (node.mapOfEdges.size > nodeResult.mapOfEdges.size) {
//                nodeResult = node
//                log2("Количество дуг", "было найдено большее число рёбер из вершины - ${nodeResult.mapOfEdges.size}")
//            }
//        }
//    }
//    log2("Количество дуг", "было найдено максимальное количество дуг - ${nodeResult.mapOfEdges.size}")
//
//    // удаление из текста найденные подстроки
//    val textForEditing = java.lang.StringBuilder(text)
//    for (index in foundIndicesOfPatterns) {
//        for (i in textWithJoker.indices) {
//            textForEditing[index + i] = '.' // замена на '.', чтобы в дальнейшем удалить
//        }
//    }
//    log2("Замена символов", "символы были заменены $text -> $textForEditing")
//    return Pair(
//        "Node: is ${if(nodeResult.symbolOnEdge == '.') "root" else nodeResult.symbolOnEdge}" + // первый ответ
//                " (parent is ${
//                    when(nodeResult.parentNode?.symbolOnEdge) {
//                        null -> "?"
//                        '.' -> "root"
//                        else -> nodeResult.parentNode?.symbolOnEdge
//                    }
//                }) with ${nodeResult.mapOfEdges.size} edges",
//        "Edited text: $text -> $textForEditing -> ${textForEditing.filter { it != '.' }}" // второй ответ
//    )
//}
//
//fun main() {
//    val text = readLine()!!
//    val textWithJoker = readLine()!!
//    val joker = readLine()!![0]
//
//    val result = findPositionsJokerStr(text, textWithJoker, joker)
//    for (pos in result.second) {
//        println(pos + 1)
//    }
//
//    if (INDIVIDUAL_TASK) {
//        val resultIndividualTask = individualTask(text, textWithJoker, result.first.toTypedArray(), result.second)
//        println(resultIndividualTask.first)
//        println(resultIndividualTask.second)
//    }
//    if (DEBUG2)
//        fileWriter2.close()
//}
