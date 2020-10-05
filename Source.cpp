#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
void heapify(int *arr, int *n, int i)
{
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; // левый = 2*i + 1
	int r = 2 * i + 2; // правый = 2*i + 2

					   // Если левый дочерний элемент больше корня
	if (l < *n && arr[l] > arr[largest])
		largest = l;

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (r < *n && arr[r] > arr[largest])
		largest = r;

	// Если самый большой элемент не корень
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(arr, n, largest);
	}
}
void heapSort(int *arr, int *n)
{
	// Построение кучи (перегруппируем массив)
	for (int i = *n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Один за другим извлекаем элементы из кучи
	for (int i = *n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(arr[0], arr[i]);

		// вызываем процедуру heapify на уменьшенной куче
		heapify(arr, &i, 0);
	}
}
void printArray(int *arr, int *n, ofstream &file)
{
	for (int i = 0; i<*n; ++i)
		file << arr[i] << " ";
}
int compare(const void * x1, const void * x2)   // функция сравнения элементов массива
{
	return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}
int main()
{
	ofstream create("Random.txt"); //создание файла
	cout << "Range of values for generating random numbers [0;" << RAND_MAX << "]"<< endl; //правая грань диапазона рандома
	for (int i = 0; i < 100000; i++) { //цикл генерации случайных чисел 
		create << (rand() % 11) << " "; //и записи их в файл
	}
	create.close(); //закрытие файла

	ifstream input("Random.txt"); //открытие файла на считывание
	int count=-1; //счетчик считываний в массив данных
	int masiv[100000]; //целочисленный массив на 100 000 элементов
	while (!input.eof()) { //цикл считывания данных из файла Random.txt в массив, пока не закончится сам файл
		count++; //счетчик и индекс массива одновременно
		input >> masiv[count]; //запись значения из файла в массив
	}
	input.close(); //закрытие файла
	unsigned int start_time = clock(); //узнаем нынешнее время выполнения программы
	heapSort(masiv, &count); //запуск пирамидального метода сортировки
	unsigned int end_time = clock(); //конечное время
	unsigned int search_time = end_time - start_time; //искомое время
	cout << "Sorting of the array using the pyramid sorting method has been started." << endl;
	cout << "\tStart_time = " << start_time << endl;
	cout << "\tEnd_time = " << end_time << endl;
	cout << "Result_time = " << search_time << endl;
	ofstream sort1("Sort1.txt"); //создание файла
	printArray(masiv, &count, sort1); //функция вывода осортированного в файл
	sort1.close(); //закрытие файла

	ifstream input2("Random.txt");
	count = -1;
	while (!input2.eof()) {
		count++;
		input2 >> masiv[count];
	}
	input2.close();

	start_time = clock();
	qsort(&masiv[0], count, sizeof(int), compare);      // сортируем массив чисел
	end_time = clock(); // конечное время
	search_time = end_time - start_time; // искомое время
	cout << "\n\nSorting the array using the quick sort method has started." << endl;
	cout << "\tStart_time = " << start_time << endl;
	cout << "\tEnd_time = " << end_time << endl;
	cout << "Result_time = " << search_time << endl;
	ofstream sort2("Sort2.txt"); //создание файла
	printArray(masiv, &count, sort2); //функция вывода осортированного в файл
	sort2.close(); //закрытие файла
	return 0;
}