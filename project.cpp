#include"project.h"

using namespace std;

void isValley()
{
	int nrows, ncols;
	int count = 0;
	double map[N][N];
	string filename;
	ifstream  file;
	cout << "�������ļ��� \n";
	cin >> filename;
	file.open(filename.c_str());
	if (file.fail()) {
		cerr << "���ļ�����.\n";
		exit(1);
	}
	file >> nrows >> ncols;
	if (nrows > N || ncols > N) {
		cerr << "����̫�󣬵�������.\n";
		exit(1);
	}

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {

			file >> map[i][j];
		}
	}
	for (int i = 1; i < nrows - 1; i++) {
		for (int j = 1; j < ncols - 1; j++) {
			if (isPeak(map, i, j)) {
				count++;
				cout << "��ֵ��������: " << i << " ��:" << j << endl;
			}

		}
	}
	cout << "��ֵ��ĿΪ" << count << endl;
	file.close();
	


}
bool isPeak(const double grid[][N], int i, int j) {

	if ((grid[i - 1][j] < grid[i][j]) &&
		(grid[i + 1][j] < grid[i][j]) &&
		(grid[i][j - 1] < grid[i][j]) &&
		(grid[i][j + 1] < grid[i][j]))
		return true;
	else
		return false;
}