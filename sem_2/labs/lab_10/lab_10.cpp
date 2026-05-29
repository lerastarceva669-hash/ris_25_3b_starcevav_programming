#include <iostream>
#include <clocale>
using namespace std;



int main() {
	setlocale(LC_ALL, "ru");

	int n, m;
	cout << "Введите количество строк в массиве:\n";
	cin >> n;
	cout << "Введите количество столбцов в массиве:\n";
	cin >> m;

	int **arr = new int*[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}

	//заполнение массива
	cout << "Заполните массив: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	cout << "Исходный массив: " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j]<<"\t";
		}
		cout << endl;
	}

	// поиск максимального элемента и его позиции
	int max_elem = arr[0][0];
	int n_max = 0, m_max = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
		{
			if (arr[i][j] > max_elem)
			{
				max_elem = arr[i][j];
				n_max = i;
				m_max = j;
			}
		}
	}

	cout << "Максимальный элемент: " << max_elem << endl;
	cout << "Позиция: [" << n_max << "][" << m_max << "]" << endl;

	//новый масиив без 1 столбца и  1 строки

	int new_n = n - 1;
	int new_m = m - 1;

	int** new_arr = new int* [new_n];
	for (int i = 0; i < new_n; i++)
	{
		new_arr[i] = new int[new_m];
	}

	//копирование массива с пропусками строки и столбца

	//копирование части до удаляемой строки
	int ni = 0;
	for (int i = 0; i < n_max; i++)
	{
		int nj = 0; 
		for (int j = 0; j < m_max; j++)
		{
			new_arr[ni][nj++] = arr[i][j];
		}
		for (int j = m_max + 1; j < m; j++) {
			new_arr[ni][nj++] = arr[i][j];
		}
		ni++;
	}
	//копирование части после удаляемой строки
	for (int i = n_max + 1; i < n; i++)
	{
		int nj = 0;
		for (int j = 0; j < m_max; j++)
		{
			new_arr[ni][nj++] = arr[i][j];
		}
		for (int j = m_max + 1; j < m; j++)
		{
			new_arr[ni][nj++] = arr[i][j];
		}
		ni++;
	}
	//вывод нового массива
	cout << "Массив после удаления строки " << n_max << " и столбца " << m_max << endl;
	for (int i = 0; i < new_n; i++)
	{
		for (int j = 0; j < new_m;j++)
		{
			cout << new_arr[i][j]<<"\t";
		}
		cout << endl;
	}

	//очистка памяти
	for (int i = 0; i < n; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

	for (int i = 0; i < new_n; i++)
	{
		delete[] new_arr[i];
	}
	delete[] new_arr;

	return 0;
	
}