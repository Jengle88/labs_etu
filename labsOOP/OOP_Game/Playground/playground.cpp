#include <iostream>
#include <vector>
#include <iomanip>
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
		vector <vector<char>> nodes(n, vector<char>(m, '.'));
		vector <pair<int, int>> points;
		nodes[sty][stx] = 'S';
		int dist = calcDist(stx, sty);
		srand(time(0));
		int deltaX = -(stx - finx) / max(1,abs(stx - finx));
		int deltaY = -(sty - finy) / max(1,abs(sty - finy));
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

int main() { //проверено
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
    std::cout  << 1.1512 << '\n';
    std::cout << std::fixed << std::setprecision(6) << 1.1512 << '\n';
    std::cout << 1.1512 << '\n';

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