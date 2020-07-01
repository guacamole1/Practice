#include "Stopwatch.h"

//индексы для массивов
const int is1= 1000;
const int is2 = 10000;
const int is3 = 100000;
const int is4 = 200000;

int compare(const void * x1, const void * x2)   // функция сравнения элементов массива нужна для 3-го параметра функции qsort
{
	return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Stopwatch *timer; // указатель на объект секундомера
	int* mass;// массив с которым мы будем работать
	int* buff;// массив для копирования
	double counter[10]; // сюда будем сохранять промежуточные данные вычисленного времени
	double sum; // среднее значение по времени
	int i, j, n, m;
	i = 0;
	j = 0;
	n = 0;
	m = 0;
	// 1-ое испытание сортировка массива на 1000 эл-ов
	for (j = 0; j < 4; j++) {
		n = 100 * (j+1) *10;
		mass = new int[n];
		buff = new int[n];
		for (int i = 0; i < n; i++)
		{
			buff[i] = rand() % 1000 - rand() % 1000; // заполняем массив случайными значениями в диапазоне от -999 до 999 включительно
		}
		//начало
		cout << "Испытание№" << j << "массив из " << n << " элементов" <<endl;
		for (i = 0; i < 10; i++)
		{
			memcpy(mass, buff, sizeof(int)*n);// заранее сохранёный массив копируется в нужный нам
			timer = new Stopwatch; // начинаем отсчёт 
			//далее алгоритм древестной(пирамидальной) сортировки
			counter[i] = timer->stop().duration<Stopwatch::ns>(); // отсчёт закончен
			cout << "Проход№" << i << "Время: " << counter[i] << endl;
			delete timer;
		}
		for (i = 0; i < 10; i++)
			sum += counter[i];
		cout << "Сортировка с помощью древестного алгоритма:" << endl;
		cout << "Среднее время за которое был отсортирован массив из " << n << " элементов:" << sum << endl;


		for (i = 0; i < 10; i++)
		{
			memcpy(mass, buff, sizeof(int)*n);// заранее сохранёный массив копируется в нужный нам
			timer = new Stopwatch; // начинаем отсчёт 
			//далее сортировка с помощью qsort
			qsort(mass, n, sizeof(int), compare);
			counter[i] = timer->stop().duration<Stopwatch::ns>(); // отсчёт закончен
			cout << "Проход№" << i << "Время: " << counter[i] << endl;
			delete timer;
		}
		for (i = 0; i < 10; i++)
			sum += counter[i];
		cout << "Сортировка с помощью qsort:" << endl;
		cout << "Среднее время за которое был отсортирован массив из " << n << " элементов:" << sum << endl;

		delete[] mass;
		delete[] buff;


	}

}