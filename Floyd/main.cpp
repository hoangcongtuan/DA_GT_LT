#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#define gach_ngang 196
#define chu_thap 197
#define gach_doc 179

using namespace std;

int max_distance;
const char * FILE_INPUT = "input.txt";
const char * FILE_OUTPUT = "output.txt";
int **ma_tran_trong_so;
int n;
char start, end;

int **shortestWay;
int **path;


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void loadData() {
	//doc du lieu tu file luu vao ma tran
	ifstream ifsData;
	ifsData.open(FILE_INPUT, ios::in);
	
	if (!ifsData.is_open()) {
		//loi khi mo file
		cout << "Loi khi mo file! Exit!";
		exit(0);
	}
	
	//doc so luong dinh
	ifsData >> n;
	
	//khoi tao ma tran trong so
	ma_tran_trong_so = new int *[n];
	for(int i = 0; i < n; i++) {
		(*(ma_tran_trong_so+i)) = new int[n];
	}
	
	max_distance = 0;
	//doc du lieu tu tep vao ma tran
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			ifsData >> ma_tran_trong_so[i][j];
			max_distance += ma_tran_trong_so[i][j];
		}
	}
	
	
	//dong tap tin
	ifsData.close();	
}

void init() {
	//khoi tao cac mang
	//khoi tao mang luu duong di ngan nhat va duong di
	shortestWay = new int *[n];
	path = new int *[n];
	for(int i = 0 ; i < n; i++) {
		*(shortestWay + i) = new int[n];
		*(path + i) = new int[n];
	}
	
	//khoi tao du lieu cho 2 mang	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (i == j)
				shortestWay[i][j] = 0;
			else if (ma_tran_trong_so[i][j] == 0) 
				//khong ton tai duong di giua 2 dinh
				shortestWay[i][j] = max_distance;
			else
				shortestWay[i][j] = ma_tran_trong_so[i][j];
			path[i][j] = -1;
		}
	}	
}

//chay thuat toan floyd
void floyd() {	
	for(int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if (shortestWay[i][j] > shortestWay[i][k] + shortestWay[k][j]) {
					shortestWay[i][j] = shortestWay[i][k] + shortestWay[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}

//in ky hieu dac biet
void printSymbol(int symbol, int symbolWidth) {
	for(int i = 0; i < symbolWidth; i++) {
		cout << char(symbol);
	}
}

//in ma tran danh dau duong di
void printPath() {
	cout <<setw(5) << " " << char(gach_doc);
	
	//in ten dinh o tren
	for(int i = 0; i < n; i++)
		cout << setw(5) << char('A' + i);
	cout << endl;
	//in gach ngang o tren
	cout << setw(5) << char(gach_ngang);
	cout << char(chu_thap);
	for(int i = 0; i < n; i++)
		printSymbol(gach_ngang, 5);
	cout << endl;
	
	//in ma tran
	for(int i = 0; i < n; i++) {
		cout << setw(5) << char('A' + i) << char(gach_doc);
		for(int j = 0; j < n; j++) {
			if (path[i][j] == -1)
				cout << setw(5) << "_";
			else
				cout << setw(5) << char('A' +path[i][j]);
		}	
		cout << endl;
	}
}

//in mang
void printArray(int **mat, int n) {
	cout <<setw(5) << " " << char(gach_doc);
	
	//in ten dinh o tren
	for(int i = 0; i < n; i++)
		cout << setw(5) << char('A' + i);
	cout << endl;
	//in gach ngang o tren
	cout << setw(5) << char(gach_ngang);
	cout << char(chu_thap);
	for(int i = 0; i < n; i++)
		printSymbol(gach_ngang, 5);
	cout << endl;
	
	for(int i = 0; i < n; i++) {
		cout << setw(5) << char('A' + i) << char(gach_doc);
		for(int j = 0; j < n; j++) {
			if (mat[i][j] == max_distance)
				cout << setw(5) << "_";
			else cout << setw(5) << mat[i][j];
		}
			
		cout << endl;
	}
}


//giai phong vung nho da cap phat
void dispose() {
	delete [] ma_tran_trong_so;
	delete [] path;
	delete [] shortestWay;
}

//in duong di ngan nhat giua 2 dinh
void solve(int start, int end) {
	int i = start;
	int j = end;
	int k;
	
	cout << char('A' + start) << "->";
	while((k = path[i][j]) != -1) {
		cout << char(k + 'A')<< "->";
		i = k;
	}	
	cout << char('A' + end) << endl;
}

//ghi ma tran duong di ngan nhat ra file
void writeResult() {
	ofstream ofsData;
	ofsData.open(FILE_OUTPUT, ios::out);
	if (!ofsData.is_open()) {
		cout << "Loi khi mo file! Exit!";
		exit(0);
	}
	ofsData <<setw(5) << " ";
	
	//in ten dinh o tren
	for(int i = 0; i < n; i++)
		ofsData << setw(5) << char('A' + i);
	ofsData << endl;
	ofsData << endl;
	
	for(int i = 0; i < n; i++) {
		ofsData << setw(5) << char('A' + i);
		for(int j = 0; j < n; j++) {
			if (shortestWay[i][j] == max_distance)
				ofsData << setw(5) << "_";
			else
				ofsData << setw(5) << shortestWay[i][j];
		}
		
		ofsData << endl;
	}
	
	ofsData.close();
}

int main(int argc, char** argv) {
	loadData();
	
	init();
	
	cout << "Du lieu vao:" << endl;
	printArray(ma_tran_trong_so, n);

	cout << "Chay thuat toan Floyd..." << endl;
	floyd();
	
	
	cout << "Ma tran trong so: " << endl;
	printArray(shortestWay, n);
	
	cout << "Ma tran danh dau duong di:" << endl;
	printPath();
	
	writeResult();
	
	while(1) {
		do {
			cout << "Nhap dinh bat dau(A..." << char('A' + n - 1) << ") = ";
			cin >> start;
		}
		while(!((start >= 'A') && (start <= ('A' + n - 1))));
	
		do {
			cout << "Nhap dinh ket thuc(A..." << char('A' + n - 1) << ") = ";
			cin >> end;
		}
		while(!((end >= 'A') && (end <= ('A' + n - 1))));
			
		cout << "Duong di ngan nhat tu dinh " << char(start)<< "->" << char(end) << endl;
		solve(start - 'A', end - 'A');
		cout << "Do dai duong di ngan nhat la: " 
			<< shortestWay[start - 'A'][end - 'A'] << endl;
			
		char key;
		cout << "Tiep tuc (Y/N): ";
		cin >> key;
		if (key != 'Y')
			break;
			
	}
		
	
	dispose();
	return 0;
}
