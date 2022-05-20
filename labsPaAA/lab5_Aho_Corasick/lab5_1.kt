import java.io.FileOutputStream
import java.io.OutputStreamWriter
import java.lang.Integer.max

var DEBUG1 = false
var INDIVIDUAL_TASK = false
val fileWriter1 by lazy {
    OutputStreamWriter(FileOutputStream("fileLog1.txt")) // Файловый поток для вывода
}

fun log1(message: String, text: String) {
    if (DEBUG1)
        fileWriter1.write("$message: $text\n")
}

class StringInclusion( // класс для хранения ответа
    val startPos: Int, // позиция строки в тексте
    val strIndex: Int // индекс строки в списке шаблонов
) : Comparable<StringInclusion> {
    override fun compareTo(other: StringInclusion) : Int { // компаратор для сортировки
        return if (this.startPos == other.startPos)
            this.strIndex.compareTo(other.strIndex)
        else
            this.startPos.compareTo(other.startPos)
    }
}

class BorNode(
    val parentNode: BorNode? = null, // родитель
    val mapOfEdges: MutableMap<Char, BorNode?> = mutableMapOf(), // map для сопоставления символа и вершины
    val symbolOnEdge: Char = '.', // символ, лежащий на ребре между родителем и данной вершины
    var sufLink: BorNode? = null, // суффиксная ссылка
    var indicesPattern: MutableList<Int> = mutableListOf() // индексы шаблонов, оканчивающихся в данной вершине
) {
    fun addNewEdge(symbol: Char) { // добавить ребро
        mapOfEdges[symbol] = BorNode(this, mutableMapOf(), symbol)
    }
}

class Bor(
    patterns: Array<String> // шаблоны искомых строк
) {
    private val root = BorNode() // корень бора
    fun getRoot(): BorNode = root // геттер для корня
    init {
        log1("Построение бора", "начало")
        for ((i, pattern) in patterns.withIndex()) { // делаем DFS для первичного построения бора (без рекурсии)
            // под первичным бором подразумевается простое построение рёбер по шаблонам строк, без суфф ссылок
            log1("Обработка шаблона", "№${i+1}")
            var tempNode = root
            for ((index, symb) in pattern.withIndex()) { // Ребра для актуальных символов
                if (!tempNode.mapOfEdges.containsKey(symb)) { // не было ребра
                    log1("Добавление ребра", "добавлено ребро из вершины с состоянием ${pattern.substring(0, index)}")
                    tempNode.addNewEdge(symb) // добавляем ребро
                }
                log1("Спуск по ребру", "спуск по ребру с символом $symb")
                tempNode = tempNode.mapOfEdges[symb]!! // спускаемся по ребру
            }
            log1("Метка терминальной вершины", "в вершине была отмечена строка $pattern")
            tempNode.indicesPattern.add(i) // когда построили очередной шаблон - конечная вершина является терминальной
        }
    }

    fun buildAhoCorasick(alphabet: List<Char>) {
        log1("Алфавит", "Алфавит $alphabet был установлен")
        root.sufLink = root // исключительный случай - у корня суфф ссылка ведёт в себя
        val queue: MutableList<BorNode> =
            mutableListOf(root) // делаем BFS для расстановки суффиксных ссылок и переходов
        while (queue.isNotEmpty()) { // пока BFS не закончен
            val tempNode = queue.first() // достаём вершину из очереди
            log1("Взятие вершины", "из очереди была взята вершина, в которую ведёт символ ${tempNode.symbolOnEdge}")
            queue.removeFirst() // и удаляем её
            for (node in tempNode.mapOfEdges) { // добавляем все рёбра бора для продолжения BFS
                queue.add(node.value!!)
                log1("Добавление в очередь", "в очередь была добавлена вершина, в которую ведёт " +
                        "символ ${node.value!!.symbolOnEdge}")
            }
            if (tempNode in root.mapOfEdges.values) { // если находимся в вершине, являющейся дочерней корню
                tempNode.sufLink = root // то суффиксная ссылка ведёт в корень
                log1("Добавление суффиксной ссылки", "суффиксная ссылка ведёт в корень (дочерняя вершина корня)")
            } else if (tempNode != root) { // иначе если это общая вершина (или корень)
                tempNode.sufLink = tempNode.parentNode?.sufLink?.mapOfEdges?.get(tempNode.symbolOnEdge)
                    ?: root // добавляем суфф ссылку
                log1("Добавление суффиксной ссылки", "была добавлена суффиксная ссылка из ${tempNode.symbolOnEdge} " +
                        "в ${tempNode.sufLink?.symbolOnEdge}")
            }
            if ((tempNode.sufLink?.indicesPattern?.size?: 0) != 0) { // если есть суффикс, являющийся терминальным, то добавляем его
                tempNode.indicesPattern.addAll(tempNode.sufLink?.indicesPattern ?: mutableListOf())
                log1("Метка терминальной вершины", "в вершину ${tempNode.symbolOnEdge} были добавлены индексы шаблонов " +
                        "${tempNode.sufLink?.indicesPattern ?: mutableListOf()}")
            }
            for (symb in alphabet) {
                if (!tempNode.mapOfEdges.containsKey(symb)) { // добавляем возможные переходы
                    tempNode.mapOfEdges[symb] = tempNode.sufLink?.mapOfEdges?.get(symb)
                    log1("Добавление перехода", "был добавлен переход из ${tempNode.symbolOnEdge} " +
                            "в ${tempNode.sufLink?.symbolOnEdge} через $symb" )
                }
            }
        }
    }
}

fun findAllInclusions(text: String, patterns: Array<String>): MutableList<StringInclusion> {
    log1("Текст", text)
    log1("Шаблоны", "${patterns.toList()}")
    val alphabet = listOf('A','C','G','T','N') // алфавит
//    val alphabet = listOf('a', 'b') // алфавит
    val bor = Bor(patterns) // построение бора
    log1("Построение бора", "выполнено")
    bor.buildAhoCorasick(alphabet)
    log1("Ахо-Корасик", "алгоритм применён")
    var node = bor.getRoot()
    val result = mutableListOf<StringInclusion>() // будущий ответ
    for ((i, symb) in text.withIndex()) { // проверяем вершины на терминальность через DFS обхода бора
        log1("Обработка символа", "просматривается символ $symb")
        node = node.mapOfEdges[symb] ?: bor.getRoot()
        if (node.indicesPattern.size != 0) { // вершина терминальная
            log1("Обнаружены подстроки", "найдено ${node.indicesPattern.size} подстрок")
            for (index in node.indicesPattern) {
                log1("Информация о подстроке", "подстрока №$index найдена на позиции ${i - patterns[index].length + 1}")
                result.add(StringInclusion(i - patterns[index].length + 1, index)) // добавляем ответ
            }
        }
    }
    return result // возвращаем ответ
}

fun individualTask(
    text: String, // текст
    patterns: Array<String>, // шаблоны искомых строк
    foundIndicesOfPatterns: MutableList<StringInclusion> // найденные шаблоны в тексте
): Pair<String, String> {
    log1("\n\nИндивидуальное задание", "начало")
    val bor = Bor(patterns) // построение бора
    log1("Построение бора", "выполнено")
    // поиск вершины с самым большим количеством дуг
    var nodeResult: BorNode = bor.getRoot()
    for (pattern in patterns) { // делаем DFS по шаблонам для поиска наибольшего количества рёбер
        var node = bor.getRoot()
        for (symb in pattern) {
            node = node.mapOfEdges[symb] ?: bor.getRoot()
            log1("Переход по ребру", "спуск по ребру с символом $symb")
            if (node.mapOfEdges.size > nodeResult.mapOfEdges.size) {
                nodeResult = node
                log1("Количество дуг", "было найдено большее число рёбер из вершины - ${nodeResult.mapOfEdges.size}")
            }
        }
    }

    log1("Количество дуг", "было найдено максимальное количество дуг - ${nodeResult.mapOfEdges.size}")

    // удаление из текста найденные подстроки
    val textForEditing = java.lang.StringBuilder(text)
    val mapIndicesOfBiggestString = mutableMapOf<Int, Int>()
    for (string in foundIndicesOfPatterns) { // ищем самые длинные подстроки, расположенные по определённому индексу, для дальнейшей замены
        mapIndicesOfBiggestString[string.startPos] = max( // берём самую длинную
            mapIndicesOfBiggestString.getOrDefault(string.startPos, 0), // прошлое значение (или 0, если его не было)
            patterns[string.strIndex].length // новое значение
        )
    }
    log1("Отбор позиций и подстрок", "будет задействовано ${mapIndicesOfBiggestString.size} подстрок - " +
            "$mapIndicesOfBiggestString")
    for ((index, length) in mapIndicesOfBiggestString) {
        for (i in 0 until length) {
            textForEditing[index + i] = '.' // замена на '.', чтобы в дальнейшем удалить
        }
    }
    log1("Замена символов", "символы были заменены $text -> $textForEditing")
    return Pair(
        "Node: is ${if(nodeResult.symbolOnEdge == '.') "root" else nodeResult.symbolOnEdge}" + // первый ответ
                " (parent is ${
                    when(nodeResult.parentNode?.symbolOnEdge) {
                        null -> "?"
                        '.' -> "root"
                        else -> nodeResult.parentNode?.symbolOnEdge
                    }
                }) with ${nodeResult.mapOfEdges.size} edges",
        "Edited text: $text -> $textForEditing -> ${textForEditing.filter { it != '.' }}" // второй ответ
    )
}

fun main() {
    val text = readLine()!!
    val countPatterns = readLine()!!.toInt()
    val patterns = Array(countPatterns) { "" }
    for (i in 0 until countPatterns) {
        patterns[i] = readLine()!!
    }
    val result = findAllInclusions(text, patterns)
    result.sortBy { it }
    for (strInclusion in result) {
        println("${strInclusion.startPos+1} ${strInclusion.strIndex + 1}")
    }
    if (INDIVIDUAL_TASK) {
        val resultIndividualTask = individualTask(text, patterns, result)
        println(resultIndividualTask.first)
        println(resultIndividualTask.second)
    }

    if (DEBUG1)
        fileWriter1.close()
}
