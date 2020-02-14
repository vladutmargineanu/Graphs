#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

ifstream fin("p2.in");
ofstream fout("p2.out");

const int dim = 105;
const int dimM = 1e6 + 3;

int n, m, k;
int v[dim][dim];
pair<int, int> stiva[dimM];
int varf = 0;
int vi[dim][dim];

constexpr int u[4] = {1, 0, -1, 0};
constexpr int l[4] = {0, 1, 0, -1};

int solve(int i, int j, int z) {
	vi[i][j] = z;
	varf = 0;
	stiva[varf] = {i, j};
	varf++;
	int r = 1;
	while(varf) {
		pair<int, int> p = stiva[varf - 1];
		varf--;
		for(int t = 3; t >= 0; t--) {
			int x = p.first + u[t];
			int y = p.second + l[t];
			if(x == -1 || y == -1 || x == n
				|| y == m || vi[x][y] == z) {
				
				continue;
			}

			if(v[x][y] > v[i][j] || 
				v[x][y] < v[i][j] - k) {
				continue;
			}
			vi[x][y] = z;
			stiva[varf] = {x, y};
			varf++;
			r++;
		}
	}
	return r;
}

void read() {
	fin >> n >> m >> k;
	for(int i = 0; i < n * m; i++) {
		int x;
		fin >> x;
		v[i / m][i % m] = x;
	}
		
}

int main() {
	read();
	int r = 0;
	int z = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			r = max(r, solve(i, j, ++z));
		}
	}
	fout << r << endl;
	fout.close();
	return 0;
}
