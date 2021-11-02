#include <iostream>

struct ParallelProcess {
    int idProcess;
    int finishTime;
    friend bool operator<(const ParallelProcess& a, const ParallelProcess& b) {
        return a.finishTime < b.finishTime || (a.finishTime == b.finishTime && a.idProcess < b.idProcess);
    }
    explicit ParallelProcess(int idProcess = -1, int leftTime = -1): idProcess(idProcess), finishTime(leftTime) {}
};

class BinaryLimitMinHeap {
    ParallelProcess *array;
    int currentSize;

    void heapify(int i) {
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
public:
    BinaryLimitMinHeap() = default;
    explicit BinaryLimitMinHeap(int maxSize, int arrSize = 0, const ParallelProcess *arr = nullptr) {
        array = new ParallelProcess[maxSize];
        currentSize = 0;
        if (arr != nullptr) {
            currentSize = std::min(arrSize, maxSize);
            for (int i = 0; i < currentSize; ++i) {
                array[i] = arr[i];
            }
            for (int i = currentSize / 2; i >= 0; i--) {
                heapify(i);
            }
        }
    }
    ~BinaryLimitMinHeap() {
        delete[] array;
    }
    void add(ParallelProcess val) {
        array[currentSize++] = val;
        int i = currentSize - 1;
        int parent = (i - 1) / 2;
        while (i > 0 && array[i] < array[parent]) {
            std::swap(array[i], array[parent]);

            i = parent;
            parent = (i - 1) / 2;
        }
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
        heapify(0);
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
    ResultTask(int idProcess = -1, int startTime = -1) : idProcess(idProcess), startTime(startTime) {}
};

void solve() {
    int n, m;
    std::cin >> n >> m;
    PriorityLimitMinQueue queue(n);
    auto* res = new ResultTask[m];
    int t = 0;
    int duration;
    for (int i = 0; i < n; ++i) {
        std::cin >> duration;
        if (i < m) {
            queue.push(ParallelProcess(i, duration));
            res[i] = ResultTask(i, 0);
        } else { // задач меньше, чем процессов
            for (int j = 0; j < m; ++j) {
                std::cout << res[j].idProcess << ' ' << res[j].startTime << '\n';
            }
            delete[] res;
            return;
        }
    }
    for (int i = n; i < m;) { // задач больше, чем процессов
        auto currentTime = queue.top().finishTime;
        t = currentTime;
        while (queue.top().finishTime == t && i < m) { // если в один момент освободилось больше одного процесса
            auto topProcess = queue.pop();
            std::cin >> duration;
            res[i] = ResultTask(topProcess.idProcess, t);
            queue.push(ParallelProcess(topProcess.idProcess, t + duration));
            i++;
        }
    }
    for (int i = 0; i < m; ++i) {
        std::cout << res[i].idProcess << ' ' << res[i].startTime << '\n';
    }
    delete[] res;
}

int main() {
    solve();
    return 0;
}
