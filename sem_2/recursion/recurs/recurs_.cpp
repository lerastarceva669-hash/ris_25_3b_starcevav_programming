//ФАКТОРИАЛ

//#include <iostream>
//using namespace std;
//int n;
//
//int fact(int n) {
//	if (n <= 1) return 1;
//	return n * fact(n - 1);
//}
//
//
//int main() {
//	cout << fact(1) << fact(2) << fact(3);
//	return 0;
//}

//---------------------------------------------------------------
//СУММА ЭЛЕМЕНТОВ МАССИВА

//#include <iostream>
//using namespace std;
//
//int sum(int arr[], int i, int ans = 0) {
//	if (i == 0) return ans;
//
//	return sum(arr, i - 1, ans + arr[i - 1]);
//}
//
//int main() {
//	int arr[] = { 4, 2, 7 };
//	cout << sum(arr, 3);
//	return 0;
//}

//----------------------------------------------------------------

//ВВОД ЧИСЕЛ ОТ 1 ДО N

//#include <iostream>;
//using namespace std;
//
//int f(int n) {
//	if (n <= 0) return 0;
//	else {
//		f(n - 1);
//		cout << n << " ";
//	}
//}
//
//int main() {
//	int n;
//	cin >> n;
//	f(n);
//	return 0;
//}

//--------------------------------------------------------------------
//ВВОД ЧИСЕЛ ОТ N ДО 1

//#include <iostream>
//using namespace std;
//
//int f(int n) {
//	if (n <= 0) return 0;
//	else {
//		cout << n << " ";
//		f(n - 1);
//	}
//}
//
//int main() {
//	int n;
//	cin >> n;
//	f(n);
//	return 0;
//}

//-----------------------------------------------------------------------------

//НОД

#include <iostream>
#include <clocale>
using namespace std;

int Evclid(int a, int b) {
	if (a == b) return a;
	else if (a > b) return Evclid(a - b, b);
	else return Evclid(a, b - a);

}

int main() {
	int n, m;
	setlocale(LC_ALL, "RU");

	cout << "Введите 2 числа:\n";
	cin >> m >> n;

	while (m < 0 || n < 0) {
		cout << "Введите другие числа:\n";
		cin >> n >> m;
	}

	if (n == 0 || m == 0) {
		if (n == 0 && m == 0) cout << "Ошибка!" << endl;
		else if (n == 0) cout << "НОД: " << m;
		else cout << "НОД: " << n;
	}
	else cout << "НОД: " << Evclid(n, m);
	return 0;
}