#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct inter {
	int x, y;
};

int cmpfunc(const void* x, const void* y) {
	return ((inter *)x)->x - ((inter *)y)->x;
}

int main() {
	int n;
	inter a[(int)(1e5) + 5];
	FILE* in = fopen("p1.in", "r");
	FILE* out = fopen("p1.out", "w");

	fscanf(in, "%d", &n);
	for(int i = 1; i <= n; i++) {
		int x;
		fscanf(in, "%d", &x);
		a[i - 1].x = x;	
		a[i - 1].y = i;
	}
	fclose(in);
	qsort(a, n, sizeof(inter), cmpfunc);
	bool ok = true;
	for(int i = 1; i < n; i++) {
		if(!a[i].x) {
			ok = false;
		} else if(a[i].x - a[i - 1].x >= 2) {
			ok = false;
		}
	}
	int p = 0;
	if(!ok) {
		fprintf(out, "-1");
	} else {
		fprintf(out, "%d", n - 1);
		fprintf(out, "\n");
		for(int i = 0; i < n - 1; i++) {
			if(a[i + 1].x - a[i].x == 1) {
				p = i;
			}
			fprintf(out, "%d", a[p].y);
			fprintf(out, " %d", a[i + 1].y);
			fprintf(out, "\n");
		}
	}
	fclose(out);
	return 0;
}
