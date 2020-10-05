#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
void heapify(int *arr, int *n, int i)
{
	int largest = i;
	// �������������� ���������� ������� ��� ������
	int l = 2 * i + 1; // ����� = 2*i + 1
	int r = 2 * i + 2; // ������ = 2*i + 2

					   // ���� ����� �������� ������� ������ �����
	if (l < *n && arr[l] > arr[largest])
		largest = l;

	// ���� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
	if (r < *n && arr[r] > arr[largest])
		largest = r;

	// ���� ����� ������� ������� �� ������
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// ���������� ����������� � �������� ���� ���������� ���������
		heapify(arr, n, largest);
	}
}
void heapSort(int *arr, int *n)
{
	// ���������� ���� (�������������� ������)
	for (int i = *n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// ���� �� ������ ��������� �������� �� ����
	for (int i = *n - 1; i >= 0; i--)
	{
		// ���������� ������� ������ � �����
		swap(arr[0], arr[i]);

		// �������� ��������� heapify �� ����������� ����
		heapify(arr, &i, 0);
	}
}
void printArray(int *arr, int *n, ofstream &file)
{
	for (int i = 0; i<*n; ++i)
		file << arr[i] << " ";
}
int compare(const void * x1, const void * x2)   // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2);              // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}
int main()
{
	ofstream create("Random.txt"); //�������� �����
	cout << "Range of values for generating random numbers [0;" << RAND_MAX << "]"<< endl; //������ ����� ��������� �������
	for (int i = 0; i < 100000; i++) { //���� ��������� ��������� ����� 
		create << (rand() % 11) << " "; //� ������ �� � ����
	}
	create.close(); //�������� �����

	ifstream input("Random.txt"); //�������� ����� �� ����������
	int count=-1; //������� ���������� � ������ ������
	int masiv[100000]; //������������� ������ �� 100 000 ���������
	while (!input.eof()) { //���� ���������� ������ �� ����� Random.txt � ������, ���� �� ���������� ��� ����
		count++; //������� � ������ ������� ������������
		input >> masiv[count]; //������ �������� �� ����� � ������
	}
	input.close(); //�������� �����
	unsigned int start_time = clock(); //������ �������� ����� ���������� ���������
	heapSort(masiv, &count); //������ �������������� ������ ����������
	unsigned int end_time = clock(); //�������� �����
	unsigned int search_time = end_time - start_time; //������� �����
	cout << "Sorting of the array using the pyramid sorting method has been started." << endl;
	cout << "\tStart_time = " << start_time << endl;
	cout << "\tEnd_time = " << end_time << endl;
	cout << "Result_time = " << search_time << endl;
	ofstream sort1("Sort1.txt"); //�������� �����
	printArray(masiv, &count, sort1); //������� ������ ��������������� � ����
	sort1.close(); //�������� �����

	ifstream input2("Random.txt");
	count = -1;
	while (!input2.eof()) {
		count++;
		input2 >> masiv[count];
	}
	input2.close();

	start_time = clock();
	qsort(&masiv[0], count, sizeof(int), compare);      // ��������� ������ �����
	end_time = clock(); // �������� �����
	search_time = end_time - start_time; // ������� �����
	cout << "\n\nSorting the array using the quick sort method has started." << endl;
	cout << "\tStart_time = " << start_time << endl;
	cout << "\tEnd_time = " << end_time << endl;
	cout << "Result_time = " << search_time << endl;
	ofstream sort2("Sort2.txt"); //�������� �����
	printArray(masiv, &count, sort2); //������� ������ ��������������� � ����
	sort2.close(); //�������� �����
	return 0;
}