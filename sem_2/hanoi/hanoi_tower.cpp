#include <iostream>
using namespace std;

const int MAX = 10;
int t[3][MAX];
int h[3] = { 0 };

void show()
{
    for (int i = 0; i < 3; i++)
    {
        cout << "Стержень " << i + 1 << ": ";
        for (int j = 0; j < h[i]; j++)
        {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

void move(int n, char from, char to, char tmp)
{
    if (n == 0) return;

    move(n - 1, from, tmp, to);

    int f = from - '1';
    int d = to - '1';

    int disk = t[f][h[f] - 1];
    h[f]--;

    t[d][h[d]] = disk;
    h[d]++;

    cout << "Сдвиг " << n << " кольца с " << from << " стержня на " << to << endl;
    show();

    move(n - 1, tmp, to, from);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n;

    cout << "Кол-во колец (1-" << MAX << "): ";
    cin >> n;
    cout << endl;

    if (n < 1 || n > MAX)
    {
        cout << "Неверно!" << endl;
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        t[0][i] = n - i;
    }
    h[0] = n;

    cout << "Начало:" << endl;
    show();

    move(n, '1', '3', '2');
    return 0;
}

