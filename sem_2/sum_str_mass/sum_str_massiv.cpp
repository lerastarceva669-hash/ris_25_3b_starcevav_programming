
//сумма строк двумерного массива

#include <iostream>
#include <clocale>
#include <cstdlib>
using namespace std;


int main()
{
    setlocale(LC_ALL, "ru");
    const int size = 50;
    int matrix[size][size];
    int N;
    int sum_arr[size];

    cout << "Введите размер матрицы (0 < N <= 50): ";
    cin >> N;

    while (N <= 0 || N > size)
    {
        cout << "Ошибка. Введите другой размер матрицы: ";
        cin >> N;
    }

    cout << "Матрица:\n";

    for (int i = 0; i < N; i++)
    {
        int sum = 0;
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 101 - 50;
            cout << matrix[i][j] << '\t';
            sum += matrix[i][j];
        }
        cout << endl;
        sum_arr[i] = sum;
    }
    cout << "Массив суммы строк:\n";
    for (int i = 0; i < N; i++)
    {
        cout << sum_arr[i] << '\t';
    }
    
    
    
    
    return 0;
}
