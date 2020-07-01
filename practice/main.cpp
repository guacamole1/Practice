#include "Stopwatch.h"

int compare(const void * x1, const void * x2);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Stopwatch *timer; // указатель на объект секундомера
	int* mass;// массив с которым мы будем работать
	int* buff;// массив для копирования
	double counter[10]; // сюда будем сохранять промежуточные данные вычисленного времени
	double sum=0; // среднее значение по времени
	int i, j, n, m;
	i = 0;
	j = 0;
	n = 100;
	// 1-ое испытание сортировка массива на 1000 эл-ов
	for (j = 0; j < 4; j++) {
		n = n*10;
		mass = new int[n];
		buff = new int[n];
		for (int i = 0; i < n; i++)
		{
			buff[i] = rand() % 1000 - rand() % 1000; // заполняем массив случайными значениями в диапазоне от -999 до 999 включительно
		}
		//начало
		cout << "Испытание№" << j << "массив из " << n << " элементов" <<endl;

		cout << endl << "Сортировка с помощью древестного алгоритма:" << endl;
		for (i = 0; i < 10; i++)
		{
			memcpy(mass, buff, sizeof(int)*n);// заранее сохранёный массив копируется в нужный нам
			timer = new Stopwatch; // начинаем отсчёт 
			//далее алгоритм древестной(пирамидальной) сортировки
			heapSort(mass, n);
			counter[i] = timer->stop().duration<Stopwatch::mks>(); // отсчёт закончен
			cout << "Проход № " << i << "  Время: " << counter[i] << " mks"<< endl;
			delete timer;
		}
		for (i = 0; i < 10; i++)
			sum += counter[i];
		cout << "Среднее время за которое был отсортирован массив из " << n << " элементов:" << sum << " mks" << endl;

		cout << endl << "Сортировка с помощью qsort:" << endl;
		for (i = 0; i < 10; i++)
		{
			memcpy(mass, buff, sizeof(int)*n);// заранее сохранёный массив копируется в нужный нам
			timer = new Stopwatch; // начинаем отсчёт 
			//далее сортировка с помощью qsort
			qsort(mass, n, sizeof(int), compare);
			counter[i] = timer->stop().duration<Stopwatch::mks>(); // отсчёт закончен
			cout << "Проход № " << i << "  Время: " << counter[i] << " mks" << endl;
			delete timer;
		}
		for (i = 0; i < 10; i++)
			sum += counter[i];
		cout << "Среднее время за которое был отсортирован массив из " << n << " элементов:" << sum << " mks" << endl;

		delete[] mass;
		delete[] buff;
	}
	system("pause");
}

int compare(const void * x1, const void * x2)   // функция сравнения элементов массива нужна для 3-го параметра функции qsort
{
	return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

void heapify(int arr[], int n, int i)
{
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; // левый = 2*i + 1
	int r = 2 * i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// Если самый большой элемент не корень
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(arr, n, largest);
	}
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int arr[], int n)
{
	// Построение кучи (перегруппируем массив)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(arr[0], arr[i]);

		// вызываем процедуру heapify на уменьшенной куче
		heapify(arr, i, 0);
	}
}
