#include "Stopwatch.h"

//������� ��� ��������
const int is1= 1000;
const int is2 = 10000;
const int is3 = 100000;
const int is4 = 200000;

int compare(const void * x1, const void * x2)   // ������� ��������� ��������� ������� ����� ��� 3-�� ��������� ������� qsort
{
	return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	Stopwatch *timer; // ��������� �� ������ �����������
	int* mass;// ������ � ������� �� ����� ��������
	int* buff;// ������ ��� �����������
	double counter[10]; // ���� ����� ��������� ������������� ������ ������������ �������
	double sum; // ������� �������� �� �������
	int i, j, n, m;
	i = 0;
	j = 0;
	n = 0;
	m = 0;
	// 1-�� ��������� ���������� ������� �� 1000 ��-��
	for (j = 0; j < 4; j++) {
		n = 100 * (j+1) *10;
		mass = new int[n];
		buff = new int[n];
		for (int i = 0; i < n; i++)
		{
			buff[i] = rand() % 1000 - rand() % 1000; // ��������� ������ ���������� ���������� � ��������� �� -999 �� 999 ������������
		}
		//������
		cout << "���������" << j << "������ �� " << n << " ���������" <<endl;
		for (i = 0; i < 10; i++)
		{
			memcpy(mass, buff, sizeof(int)*n);// ������� ��������� ������ ���������� � ������ ���
			timer = new Stopwatch; // �������� ������ 
			//����� �������� ����������(�������������) ����������
			counter[i] = timer->stop().duration<Stopwatch::ns>(); // ������ ��������
			cout << "������" << i << "�����: " << counter[i] << endl;
			delete timer;
		}
		for (i = 0; i < 10; i++)
			sum += counter[i];
		cout << "���������� � ������� ����������� ���������:" << endl;
		cout << "������� ����� �� ������� ��� ������������ ������ �� " << n << " ���������:" << sum << endl;


		for (i = 0; i < 10; i++)
		{
			memcpy(mass, buff, sizeof(int)*n);// ������� ��������� ������ ���������� � ������ ���
			timer = new Stopwatch; // �������� ������ 
			//����� ���������� � ������� qsort
			qsort(mass, n, sizeof(int), compare);
			counter[i] = timer->stop().duration<Stopwatch::ns>(); // ������ ��������
			cout << "������" << i << "�����: " << counter[i] << endl;
			delete timer;
		}
		for (i = 0; i < 10; i++)
			sum += counter[i];
		cout << "���������� � ������� qsort:" << endl;
		cout << "������� ����� �� ������� ��� ������������ ������ �� " << n << " ���������:" << sum << endl;

		delete[] mass;
		delete[] buff;


	}

}