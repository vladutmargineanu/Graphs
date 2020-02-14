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
int t[10];
long long r[205][200];

ifstream fin("p4.in");
ofstream fout("p4.out");

void readE(int m) {
	 for(int i = 0; i < m; i++) {
		int x, y, z;
		long long c;
                fin >> x >> y >> c >> z;
                ed[x].push_back({{c, y}, z});
                ed[y].push_back({{c, x}, z});
        }
}

void readT() {
	for(int i = 1; i <= T; i++) {
		int x;
		fin >> x;
		t[i] = x;
	}
}

void init(int n, int TT) {
	for(int i = 0; i < (n + 1) * (TT + 1); i++) {
		r[i/(TT + 1)][i % (TT + 1)] = (1LL << 60);
	}
}
int main() {
	heap<pair<pair<long long, int>, int>> h;
	fin >> n >> m >> T;
	int TT = (1 << T);
	int x, y, z;
	long long c;
	readE(m);
	readT();
	init(n, TT);

	r[1][0] = 0;
	h.push({{0, 1}, 0});
	long long r1 = (1LL << 60);
	while(!h.is_empty()) {
		pair<pair<long long, int>, int> p = h.min();
		h.pop();
		int bitmask = p.second;
		for(pair<pair<long long, int>, int> x : ed[p.first.second]) {
			int bitmask1 = x.second;
			bitmask1 = (1 << (x.second - 1));
			int y = bitmask | bitmask1;
			if(((bitmask1 & bitmask) == 0) && 
				r[x.first.second][y] > 
					p.first.first + x.first.first +
				 		t[x.second]) {
				
				r[x.first.second][y] =
                                	p.first.first + x.first.first +
                            			t[x.second];

				h.push({{r[x.first.second][y], x.first.second}, y});
			}
			if(((bitmask1 & bitmask) != 0) && 
                                r[x.first.second][y] >
                                        p.first.first + x.first.first) {

                                r[x.first.second][y] =
                                        p.first.first + x.first.first;

                                h.push({{r[x.first.second][y], x.first.second}, y});
                        }

			 if(x.first.second == n) {
				r1 = min(r[x.first.second][y], r1);
                         }
		}
	}

	fout << (r1 == (1LL << 60) ? -1 : r1) << endl;
	fin.close();
	fout.close();				
	return 0;
}
