#include "Stopwatch.h"

int compare(const void * x1, const void * x2);// функция сравнения элементов массива
void help_sort(int arr[], int n, int i);//вспомогательная функция для сортировки
void heapSort(int arr[], int n);// сортировка древесным методом

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Stopwatch *timer; // указатель на объект секундомера
	int* mass;// массив с которым мы будем работать
	int* buff;// массив для копирования
	double counter[10]; // сюда будем сохранять промежуточные данные вычисленного времени
	double sum=0; // среднее значение по времени
	int i, j, n,m=0;
	bool flag;
	i = 0;
	j = 0;
	n = 100;
	flag = true;
	// 1-ое испытание сортировка массива на 1000 эл-ов
	for (j = 0; j < 4; j++) { // будет проведено 4 испытания с разной размерностью массивов
		n = n*10;
		mass = new int[n];
		buff = new int[n];
		for (int i = 0; i < n; i++)
		{
			buff[i] = rand() % 1000 - rand() % 1000; // заполняем массив случайными значениями в диапазоне от -999 до 999 включительно
		}
		//начало
		cout << endl << "Испытание № " << j << "  массив из " << n << " элементов " << endl;
		for (m = 0; m < 2; m++) { // для каждого испытания две сортировки
			if (m == 0)
				cout << endl << "Сортировка с помощью древестного алгоритма:" << endl;
			else
				cout << endl << "Сортировка с помощью функции qsort:" << endl;
			for (i = 0; i < 10; i++) // всего 10 проходов
			{
				memcpy(mass, buff, sizeof(int)*n);// заранее сохранёный массив копируется в нужный нам
				timer = new Stopwatch; // начинаем отсчёт 
				//далее алгоритм древестной(пирамидальной)/qsort сортировки
				if (m==0)
					heapSort(mass, n);
				else
					qsort(mass, n, sizeof(int), compare);
				if (j == 0) {
					counter[i] = timer->stop().duration<Stopwatch::mks>(); // для 1-го испытания в mks, т.к. происходит очень быстро
					cout << "Проход № " << i << "  Время: " << counter[i] << " mks" << endl;
				}
				else {
					counter[i] = timer->stop().duration<Stopwatch::ms>(); // отсчёт закончен / заносим время в массив- накопитель
					cout << "Проход № " << i << "  Время: " << counter[i] << " ms" << endl;
				}
				delete timer;
			}
			for (i = 0; i < 10; i++) 
				sum += counter[i];
			sum = sum / 10; // считаем среденее арифметическое
			if (j == 0)
				cout << "Среднее время за которое был отсортирован массив из " << n << " элементов:" << sum << " mks" << endl;
			else
				cout << "Среднее время за которое был отсортирован массив из " << n << " элементов:" << sum << " ms" << endl;
			sum = 0;
		}
		delete[] mass;
		delete[] buff;
	}
	system("pause");
}

int compare(const void * x1, const void * x2)   // функция сравнения элементов массива нужна для 3-го параметра функции qsort
{
	return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

void help_sort(int mass[], int n, int i)
{
	int max = i;
	// Инициализируем наибольший элемент как корень
	int left = 2 * i + 1; // левый = 2*i + 1
	int right = 2 * i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
	if (left < n && mass[left] > mass[max])
		max = left;

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (right < n && mass[right] > mass[max])
		max = right;

	// Если самый большой элемент не корень
	if (max != i)
	{
		swap(mass[i], mass[max]);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		help_sort(mass, n, max);
	}
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int arr[], int n)
{
	// Построение кучи (перегруппируем массив)
	for (int i = n / 2 - 1; i >= 0; i--)
		help_sort(arr, n, i);

	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(arr[0], arr[i]);

		// вызываем процедуру heapify на уменьшенной куче
		help_sort(arr, i, 0);
	}
}
