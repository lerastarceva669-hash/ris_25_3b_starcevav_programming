#include <iostream>
#include <clocale>
using namespace std;

void merge(int* start1, int* end1, int* start2, int* end2)
{
	int* start = start1;
	int* end = end2;
	int size = end - start + 1;
	int* rez = new int[size];
	int i = 0;
	while (start1 <= end1 && start2 <= end2)
	{
		if ((*start1) < (*start2))
		{
			rez[i] = *start1;
			start1++;
		}
		else
		{
			rez[i] = *start2;
			start2++;
		}
		i++;
	}
	
	while (start1 <= end1)
	{
		rez[i] = *start1;
		start1++;
		i++;
	}

	while (start2 <= end2)
	{
		rez[i] = *start2;
		start2++;
		i++;
	}

	for (int j = 0; j < end - start + 1; j++)
	{
		start[j] = rez[j];
	}
	delete[] rez;
}

void sort(int* start, int* end)
{
	if (start < end)
	{
		sort(start, start + (end - start) / 2);
		sort(start + (end - start) / 2 + 1, end);
		merge(start, start + (end - start) / 2, start + (end - start) / 2 + 1, end);
	}
}


int main()
{
	setlocale(LC_ALL, "RU");
	int mass[7] = {1, 4, 8, 7, 6, 3, 10};

	for (int i = 0; i < 7; i++)
	{
		cout << mass[i] << ' ';
	}
	cout << endl;


	sort(mass, mass + 6);
	for (int i = 0; i < 7; i++)
	{
		cout << mass[i] << ' ';
	} 
	return 0;
}