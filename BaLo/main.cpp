#include <iostream>
#include <math.h>
#include <iomanip>
#define N 5
#define MAX_W 13

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int khoi_luong[N + 1] = {0, 3, 4, 5, 2, 1};
int gia_tri[N + 1] = {0, 4, 5, 6, 3, 1};

int table[N + 1][MAX_W + 1];

void init() {
	//khoi tao cot 0
	for(int i = 0; i <= N; i++) {
		table[i][0] = 0;
	}
	
	//khoi tao hang 0
	for(int i = 0; i <= MAX_W; i++) {
		table[0][i] = 0;
	}
}

//giai thuat quy hoach dong
int balo() {
	for(int k = 1; k <= N; k++) {
		for(int w = 1; w <= MAX_W; w++) {
			if (khoi_luong[k] <= w) {
				int them = table[k - 1][w - khoi_luong[k]] + gia_tri[k];
				int khong_them = table[k - 1][w];
				if (them > khong_them)
					table[k][w] = them;
				else 
					table[k][w] = khong_them;
			}
			else 
				table[k][w] = table[k - 1][w];
		}
	}
	
	//in
	for(int k = 0; k <= N; k++) {
		for(int w = 0; w <= MAX_W; w++)
			cout << setw(3) << table[k][w];
		cout << endl;
	}
	
	return table[N][MAX_W];
}

void phuongAn() {
	int pa[N];
	int w = MAX_W;
	int n = N;
	int count = 0;
	while(n != 0) {
		if (table[n][w] != table[n - 1][w]) {
			pa[count] = n;
			count++;
			w = w - khoi_luong[n];
			n--;			
		}
		else {
			n--; 
		}
	}	
	for(int i = 0; i < count; i++) {
		cout << pa[i] << " : " << khoi_luong[pa[i]] << " : " << gia_tri[pa[i]] << endl;
	}
}
int main(int argc, char** argv) {
	init();
	int res = balo();
	cout << res << endl;
	phuongAn();
	return 0;
}
