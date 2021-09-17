#include <iostream>
#include <vector>

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
		while (stx != finx || sty != finy) {
			switch (rand() % 4) {
				case 0:
					if (rightWay(stx + 1, sty, dist)) {
						stx++;
						dist = calcDist(stx, sty);
						points.emplace_back(sty, stx);
					}
					break;
				case 1:
					if (rightWay(stx - 1, sty, dist)) {
						stx--;
						dist = calcDist(stx, sty);
						points.emplace_back(sty, stx);
					}
					break;
				case 2:
					if (rightWay(stx, sty + 1, dist)) {
						sty++;
						dist = calcDist(stx, sty);
						points.emplace_back(sty, stx);
					}
					break;
				case 3:
					if (rightWay(stx, sty - 1, dist)) {
						sty--;
						dist = calcDist(stx, sty);
						points.emplace_back(sty, stx);
					}
					break;
			}
		}
		for (auto &point: points) {
			nodes[point.first][point.second] = 'X';
		}
//		std
//		nodes[finy][finx] = 'F';
//		for (int i = 0; i < n; ++i) {
//			for (int j = 0; j < m; ++j) {
//				cout << nodes[i][j];
//			}
//			cout << '\n';
//		}
	}

};

void divider() {
	cout << '\n';
	for (int i = 0; i < 30; ++i) {
		cout << '-';
	}
	cout << '\n';
}
// TODO: проверить алг построения на стресс тестах

int main() {
//	Solve(3, 5, 0, 1, 4, 1).solve();
//	divider();
//	Solve(4, 4, 0, 2, 3, 1).solve();
//	divider();
//	Solve(4, 4, 0, 0, 3, 3).solve();
//	divider();
	int startTime = clock();
	int cnt = 0;
	int n = 700, m = 700; // 2285 раз за сек
	while((clock() - startTime) / CLOCKS_PER_SEC < 1) {
		Solve(n, m, 0, 0, m - 1, n - 1).solve();
		cnt++;
	}
	cout << cnt;
	return 0;
}