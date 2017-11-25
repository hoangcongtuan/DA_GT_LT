#include <iostream>
#include <fstream>
#define MAX 1000

using namespace std;

//mang quy hoach dong arr[i, j] = C[i, j] = C[n, k]
long long **arr;
const char * FILE_INPUT = "input.txt";
const char * FILE_OUTPUT = "output.txt";
long long n;
long long k;
long long res;


void loadData() {
	fstream file;
	file.open(FILE_INPUT, ios::in);
	
	if(!file.is_open()) {
		cout << "Loi khi mo file! Exit!";
		exit(0);
	}
	
	file >> n;
	file >> k;
	
	file.close();
	
}

void writeResult() {
	fstream file;
	file.open(FILE_OUTPUT, ios::out);
	
	if(!file.is_open()) {
		cout << "Loi khi mo file! Exit!";
		exit(0);
	}
	
	file << res;
	file.close();
}

void init() {
	//khoi tao mang co max phan tu
	arr = new long long * [n + 1];
	for(int i = 0; i <= n; i++)
		*(arr + i) = new long long[k + 1];
		
	
	//khoi tao bang
	//C(i, j)
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= k; j++) {
			arr[i][j] = -1;
		}
		arr[i][i] = 1;
		arr[i][0] = 1;
	}	
}

//giai phong vung nho
void dispose() {
	delete [] arr;
}


long long dynToHop2(int n, int k) {
	for(int j = 1; j <= k; j++) {
		for(int i = j + 1 ; i <= n - k + j; i++) {
			arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
		}
	}
	return arr[n][k];
}

int main() {
	loadData();
	init();
	res = dynToHop2(n ,k);
	cout << "C(" << n << ", " << k << ") = " << res << endl;
	writeResult();
	dispose();
	return 0;
}

