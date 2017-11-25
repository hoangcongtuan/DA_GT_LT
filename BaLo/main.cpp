#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
#define gach_ngang 196
#define chu_thap 197
#define gach_doc 179

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const char * FILE_INPUT = "input.txt";
const char * FILE_OUTPUT = "output.txt";
int N;
int MAX_W;
int *khoi_luong;
int *gia_tri;

int **table;

void loadData() {
	ifstream ifsInput;
	ifsInput.open(FILE_INPUT, ios::in);
	if (!ifsInput.is_open()) {
		cout << "Loi khi mo file! Exit!";
		exit(0);
	}
	
	ifsInput >> N;
	ifsInput >> MAX_W;
	
	khoi_luong = new int [MAX_W + 1];
	gia_tri = new int [N + 1];
	
	table = new int *[N + 1];
	for(int i = 0; i <= N; i++) {
		*(table + i) = new int[MAX_W + 1];
	}
	
	khoi_luong[0] = 0;
	gia_tri[0] = 0;
	//read data from file
	for(int i = 1; i <= N; i++) {
		ifsInput >> khoi_luong[i];
		ifsInput >> gia_tri[i];
	}
	
	//khoi tao cot 0
	for(int i = 0; i <= N; i++) {
		table[i][0] = 0;
	}
	
	//khoi tao hang 0
	for(int i = 0; i <= MAX_W; i++) {
		table[0][i] = 0;
	}
	
	ifsInput.close();
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

void writeResult() {	
	int pa[N];
	int w = MAX_W;
	int n = N;
	int count = 0;
	
	fstream ofsOutput;
	ofsOutput.open(FILE_OUTPUT, ios::out);
	if (!ofsOutput.is_open()) {
		cout << "Loi khi mo file! Exit!";
		exit(0);
	}
 	
	//in bang
	for(int k = 0; k <= N; k++) {
		for(int w = 0; w <= MAX_W; w++)
			ofsOutput << setw(3) << table[k][w];
		ofsOutput << endl;
	}
	
	int res = table[N][MAX_W];
	ofsOutput << "Gia tri toi da la: " << res << endl;
	
	//in phuong an 
	

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
	
	//in tieu de cua bang
	ofsOutput << setw(10) << "Do vat" 
		<< setw(15) << "Khoi luong" << setw(10) << "Gia tri" << endl;
	ofsOutput << endl;
	for(int i = 0; i < count; i++) {
		ofsOutput << setw(10) << pa[i]
			<<  setw(15) << khoi_luong[pa[i]]
			<< setw(10) << gia_tri[pa[i]] << endl;
	}
	
	ofsOutput.close();
	
}

void printSymbol(char symbol, int count) {
	for(int i = 0 ; i < count; i++)
		cout << char(symbol);
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
	
	//in tieu de cua bang
	cout << setw(7) << "Do vat" << char(gach_doc) 
		<< setw(10) << "Khoi luong" << char(gach_doc) << setw(8) << "Gia tri" << endl;
	printSymbol(gach_ngang, 7);
	cout << char(chu_thap);
	printSymbol(gach_ngang, 10);
	cout << char(chu_thap);
	printSymbol(gach_ngang, 8);
	cout << endl;
	for(int i = 0; i < count; i++) {
		cout << setw(7) << pa[i] << char(gach_doc) 
			<<  setw(10) << khoi_luong[pa[i]] << char(gach_doc) 
			<< setw(8) << gia_tri[pa[i]] << endl;
	}
}



int main(int argc, char** argv) {
	loadData();
	int res = balo();
	cout <<"Gia tri toi da cua balo = " << res << endl;
	cout << "Phuong an: " << endl;
	phuongAn();
	writeResult();
	return 0;
}
