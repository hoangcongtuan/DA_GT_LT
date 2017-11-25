#include <iostream>
#define MAX 1000

using namespace std;

long long **arr;

int toHop(int k, int n) {
	if (k > n)
		return 0;
	if (n == 0)
		return 0;
	if (k == 0)
		return 1;
	if (k == n)
		return 1;
	return toHop(k - 1, n - 1) + toHop(k, n - 1);
}

void init() {
	arr = new long long * [MAX];
	for(int i = 0; i < MAX; i++)
		*(arr + i) = new long long[MAX];
		
	
	for(int i = 0; i < MAX; i++) {
		for(int j = 0; j < MAX; j++) {
			arr[i][j] = -1;
		}
		arr[i][i] = 1;
		arr[i][0] = 1;
	}
	
}

void dispose() {
	delete [] arr;
}

long long dynToHop(int k, int n) {
//	if (k > n)
//		arr[n][k] = 0;
//	else if (k == n)
//		arr[n][k] = 1;
	if (arr[n][k] != -1)
		return arr[n][k];
	else 
		arr[n][k] = dynToHop(k - 1, n - 1) + dynToHop(k, n - 1);
	return arr[n][k];
}

long long dynToHop2(int k, int n) {
	for(int i = 2; i <= n; i++) {
		for(int j = 1; j < i; j++) {
			arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
		}
	}
	return arr[n][k];
}



int main() {
	init();
	//long long res = toHop(20, 30);
	long long res = dynToHop2(20, 30);
	cout << res << endl;
	dispose();
	return 0;
}
