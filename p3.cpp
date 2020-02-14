#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<typename T>
class heap {
public:
	heap(): count(0), v() { }
	
	bool is_empty() {
		return count == 0;
	}

	void push(const T& t) {
		v.push_back(t);
		int index = count;
		count++;
		while(index) {
			if(v[index] < v[(index - 1)/2]) {
				swap(v[index], v[(index - 1)/2]);
				index = (index - 1)/2;
			} else {
				break;
			}
		}
	}

	void pop() {
		swap(v[0], v[count - 1]);
		v.pop_back();
		count--;
		int i = 0;
		int minindex = 0;
		while(2 * i < count - 1) {
			if(2 * i + 2 < count && v[2 * i + 1] > v[2 * i + 2]) {
				minindex = 2 * i + 2;
			} else {
				minindex = 2 * i + 1;
			}
			if(v[i] > v[minindex]) {
				swap(v[i], v[minindex]);
				i = minindex;
			} else {
				break;
			}
		}
	}

	T min() {
		return v[0];
	}
private:
	int count;
	vector<T> v;
};

int n, m, T;
vector< pair<pair<long long, int>, int> > ed[205];
int t[105][105];
long long r[205][105];

ifstream fin("p3.in");
ofstream fout("p3.out");

void init(int n, int T) {
	for(int i = 0; i < (n + 1) * (T + 1); i++) {
		r[i/(T + 1)][i % (T + 1)] = (1LL << 60);
	}
}

void readM(int T) {
	for(int i = 0; i < T * T; i++) {
		fin >> t[i/T + 1][(i % T) + 1];
	}
}

void readE(int m) {
	for(int i = 0; i < m; i++) {
		int x, y, z;
		long long c;
		fin >> x >> y >> c >> z;
		ed[x].push_back({{c, y}, z});
                ed[y].push_back({{c, x}, z});
	}
}

int main() {
	heap<pair<pair<long long, int>, int>> h;
	fin >> n >> m >> T;
	int x, y, z;
	long long c;
	readE(m);
	readM(T);
	init(n, T);
	r[1][0] = 0;
	h.push({{0, 1}, 0});
	long long r1 = (1LL << 60);
	while(!h.is_empty()) {
		pair<pair<long long, int>, int> p = h.min();
		h.pop();
		for(pair<pair<long long, int>, int>& x : ed[p.first.second]) {
			if(r[x.first.second][x.second] > 
				p.first.first + x.first.first + 
				 	t[p.second][x.second]) {
				
				r[x.first.second][x.second] =
                                	p.first.first + x.first.first +
                                        	t[p.second][x.second];

				h.push({{r[x.first.second][x.second], x.first.second}, x.second});
			}
			if(x.first.second == n) {
				r1 = min(r1, r[n][x.second]);
			}
		}
	}
	fout << (r1 == (1LL << 60) ? -1 : r1) << endl;
	fin.close();
	fout.close();				
	return 0;
}
