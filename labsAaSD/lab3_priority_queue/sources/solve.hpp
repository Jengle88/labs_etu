#include <iostream>

struct ParallelProcess {
    int idProcess;
    int finishTime;
    friend bool operator<(const ParallelProcess& a, const ParallelProcess& b) {
        return a.finishTime < b.finishTime || (a.finishTime == b.finishTime && a.idProcess < b.idProcess);
    }
    explicit ParallelProcess(int idProcess = -1, int finishTime = -1): idProcess(idProcess), finishTime(finishTime) {}
};

class BinaryLimitMinHeap {
    ParallelProcess *array;
    int maxSize;
    int currentSize;

    void siftDown(int i) {
        int left, right, less;
        while (true) {
            left = 2 * i + 1;
            right = 2 * i + 2;
            less = i;
            if (left < currentSize && array[left] < array[less])
                less = left;
            if (right < currentSize && array[right] < array[less])
                less = right;
            if (less == i)
                break;
            std::swap(array[i], array[less]);
            i = less;
        }
    }

    void siftUp(int i) {
        int parent = (i - 1) / 2;
        while (i > 0 && array[i] < array[parent]) {
            std::swap(array[i], array[parent]);

            i = parent;
            parent = (i - 1) / 2;
        }
    }
public:
    explicit BinaryLimitMinHeap(int maxSize, int arrSize = 0, const ParallelProcess *arr = nullptr) {
        this->maxSize = maxSize;
        array = new ParallelProcess[maxSize];
        currentSize = 0;
        if (arr != nullptr) {
            currentSize = std::min(arrSize, maxSize); // если массив инициализации меньше или больше допустимого
            for (int i = 0; i < currentSize; ++i) {
                array[i] = arr[i];
            }
            for (int i = currentSize / 2; i >= 0; i--) {
                siftDown(i);
            }
        }
    }
    ~BinaryLimitMinHeap() {
        delete[] array;
    }
    void add(ParallelProcess val) {
        array[currentSize++] = val;
        int i = currentSize - 1;
        siftUp(i);
    }
    ParallelProcess getMin() const {
        if (currentSize > 0)
            return array[0];
        else
            throw -1;
    }
    ParallelProcess popMin() {
        if (currentSize <= 0)
            throw -1;
        ParallelProcess res = array[0];
        array[0] = array[currentSize - 1];
        currentSize--;
        siftDown(0);
        return res;
    }
};

class PriorityLimitMinQueue {
    BinaryLimitMinHeap heap;
public:
    explicit PriorityLimitMinQueue(int size, int arrSize = 0, ParallelProcess* arr = nullptr) : heap(BinaryLimitMinHeap(size, arrSize, arr)) {}
    ParallelProcess top() const {
        return heap.getMin();
    }
    ParallelProcess pop() {
        return heap.popMin();
    }
    void push(ParallelProcess val) {
        heap.add(val);
    }
};

struct ResultTask {
    int idProcess;
    int startTime;
    friend bool operator !=(const ResultTask& a, const ResultTask& b) {return a.idProcess != b.idProcess || a.startTime != b.startTime;}
    explicit ResultTask(int idProcess = -1, int startTime = -1) : idProcess(idProcess), startTime(startTime) {}
};

ResultTask* solve(int n, int m, const std::vector<int> &arrayDuration) {
//    int n, m;
//    std::cin >> n >> m;
    PriorityLimitMinQueue queue(n);
    auto* res = new ResultTask[m];
    int duration;
    int indexDuration = 0;
    for (int i = 0; i < n; ++i) {
        if (i < m) {
//        std::cin >> duration;
            duration = arrayDuration[indexDuration++];
            queue.push(ParallelProcess(i, duration));
            res[i] = ResultTask(i, 0);
        } else { // количество задач меньше или равно количеству процессов
            break;
        }
    }
    for (int i = n; i < m;) { // количество задач больше, чем процессов
        int currentTime = queue.top().finishTime;
        while (queue.top().finishTime == currentTime && i < m) { // если в один момент освободилось больше одного процесса
            auto topProcess = queue.pop();
            res[i] = ResultTask(topProcess.idProcess, currentTime); // начало новой задачи
//            std::cin >> duration;
            duration = arrayDuration[indexDuration++];
            queue.push(ParallelProcess(topProcess.idProcess, currentTime + duration));
            i++;
        }
    }
//    for (int i = 0; i < m; ++i) {
//        std::cout << res[i].idProcess << ' ' << res[i].startTime << '\n';
//    }
//    delete[] res;
    return res;
}
