#include <iostream>
#include <clocale>
using namespace std;

int f(int n) {
	if (n == 1) return 0;
	else if (n == 2) return 1;
	else return f(n - 2) + f(n - 1);

}

int main() {
	setlocale(LC_ALL, "RU");
	int n;
	cout << "Введите число для последовательности чисел Фибоначчи: ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cout << f(i) << " ";
	}

	return 0;
}