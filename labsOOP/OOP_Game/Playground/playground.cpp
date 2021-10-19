#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "../Data/DataManager.h"
#include "../Characters/Monster.h"

using namespace std;

class Solve {
    int n;
    int m;
    int stx;
    int sty;
    int finx;
    int finy;
public:

    Solve(int n, int m, int stx, int sty, int finx, int finy) : n(n), m(m), stx(stx), sty(sty), finx(finx),
                                                                finy(finy) {}

    int calcDist(int stx, int sty) const {
        return abs(stx - finx) + abs(sty - finy);
    }


    bool rightWay(int stx, int sty, int curDist) {
        return 0 <= stx && stx < m && 0 <= sty && sty < n && calcDist(stx, sty) < curDist;
    }

    void solve() {
        vector<vector<char>> nodes(n, vector<char>(m, '.'));
        vector<pair<int, int>> points;
        nodes[sty][stx] = 'S';
        int dist = calcDist(stx, sty);
        srand(time(0));
        int deltaX = -(stx - finx) / max(1, abs(stx - finx));
        int deltaY = -(sty - finy) / max(1, abs(sty - finy));
        while (stx != finx || sty != finy) {
            switch (rand() % 2) {
                case 0:
                    if (rightWay(stx + deltaX, sty, dist)) {
                        stx += deltaX;
                        dist = calcDist(stx, sty);
                        points.emplace_back(sty, stx);
                    }
                    break;
                case 1:
                    if (rightWay(stx, sty + deltaY, dist)) {
                        sty += deltaY;
                        dist = calcDist(stx, sty);
                        points.emplace_back(sty, stx);
                    }
                    break;
            }
        }
        for (auto &point: points) {
            nodes[point.first][point.second] = 'X';
        }
        nodes[finy][finx] = 'F';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << nodes[i][j];
            }
            cout << '\n';
        }
    }

};

class A {
public:
    vector<int> b;

    A() {
        std::cout << "constr\n";
        b = vector<int>(10);
    }

    ~A() {
        std::cout << "destr\n";
    }
};

void func() {
    A a = A();
    std::cout << a.b.size() << '\n';
    std::cout << "func exit\n";
}

enum ENUM {
    A,
    B,
    C,
    ENUM_SIZE
};

#define MONSTER_PERCENT_FOR_FOLLOW_TO_HERO 80

//bool willFollowToHero() {
//    double k = ((long double) (2 * 3.1416 * MONSTER_PERCENT_FOR_FOLLOW_TO_HERO) /
//                std::ceil(100 / 3.1416)); // коэффициент для того, чтобы на промежутке от 0 до 100 было PERCENT корней
//    double chance = std::sin(
//            (rand() % 100 + 1 / double(std::max(rand(), 1) % 100) * k)); // шанс того, что монстр пойдёт за героем
//    return (chance - int(chance)) <= ROOT_EPSILON;
//
//}

int main() { //проверено

//    auto enemy = DataManager().getHero(true, true);
//    for (int i = 0; i < enemy.size(); ++i) {
//        std::cout << enemy[i] << '\n';
//    }
//	int n;
//	int m;
//	int stx, sty, finx, finy;
//	cin >> n >> m;
//	cin >> stx >> sty >> finx >> finy;
//	Solve(n, m, stx, sty, finx, finy).solve();
//    func();
//    std::vector<int> a = {1,2,3};
//    a.clear();
//    a.resize(3);
//    std::cout << a[1];

//    std::cout << ENUM_SIZE;
//    std::cout  << 1.1512 << '\n';
//    std::cout << std::fixed << std::setprecision(6) << 1.1512 << '\n';
//    std::cout << 1.1512 << '\n';
//    for (int i = -2; i <= 2; ++i) {
//        for (int j = -2; j <= 2; ++j) { // получение ходов в форме +
//            if (i == 0 ^ j == 0) {
//                std::cout << i << ' ' << j << '\n';
//            }
//        }
//    }




#define ROOT_EPSILON 1e-3
    int percent = 354;

    auto k = double((3.1416 * (percent - 1)) / 100);
    int cnt = 0;
    for (double i = 0.00001; k*i <= 100; i += 0.00001) {
        if (abs(sin(k*i) - int(sin(k*i))) <= ROOT_EPSILON)
            cnt++;
    }
    cout << cnt;






//    int cnt = 0;
//    int percent = 20;
//    double k = ((long double)(3.1416 * double(percent)) / 100); // коэффициент для того, чтобы на промежутке от 0 до 100 было PERCENT корней
//    for (double i = 0.00; i <= 100; i += 0.01) {
////        double chance = std::sin((rand() % 100 + 1 / double(std::max(rand(),1) % 100) * k)); // шанс того, что монстр пойдёт за героем
//        if (abs(i -  1.235) < ROOT_EPSILON)
//            int z1 = 2;
//        double z2 = sin(k*i);
//        double z3 = int(sin(k*i));
//        double z = abs(z2 - z3);
//        if (abs(z) <= ROOT_EPSILON) {
//            std::cout << cnt + 1 << ") " << i << '\n';
//            cnt++;
//        }
//    }
//    cout << cnt;

//    int size = 10;
//    int *arr = new int[size];
//    int *arr2 = new int[size];
//    for (int i = 0; i < size; ++i) {
//        arr[i] = i * 2;
//    }
//    *arr2 = *arr;
//    *(arr2 + 1) = *(arr + 1);
//    *(arr2 + 2) = *(arr + 2);
//    for (int i = 0; i < size; ++i) {
//        std::cout << arr2[i] << ' ';
//    }
    return 0;
}