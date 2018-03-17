//
// Created by elena on 01.12.17.
//

#include <iostream>
#include <cstring>
using namespace std;
int getByte(const unsigned long long& v, int byteNum) ;
void CountingSort(unsigned long long* arr, size_t amount, int byte);
void LSDSort(unsigned long long* begin, const size_t count) ;

	//Основная функция сортировки по байтам
	void LSDSort(unsigned long long* begin, const size_t count) {
		for (int i = 0; i < static_cast<int>(sizeof(*begin)); ++i) {
			CountingSort(begin, count, i);//i номер байта
		}
	}


	//определяем число в текущем байте
	 int getByte(const unsigned long long& v, int byteNum) {
		int result = (v >> (8 * byteNum)) & 255;
		return result;
	 }


	void CountingSort(unsigned long long* arr, size_t amount, int byte) {
		unsigned long long* bArray = new unsigned long long[amount];
		int cArray[256] = {0};//1 байт вмещает в себя 2^8 различных чисел

		for (size_t j = 0; j < amount; ++j) {
			cArray[getByte(arr[j], byte)]++;//выполняем подсчет чисел из данного байта
		}

		for (int j = 1; j < 256; ++j) { //выполняем суммирование, чтобы опередлить места для чисел после сорировки
			cArray[j] += cArray[j - 1];
		}

		for (int j = static_cast<int>(amount) - 1; j >= 0; --j) {//в соответствии с найденной суммой выставляем числа в массиве b
			bArray[--cArray[getByte(arr[j], byte)]] = arr[j];
		}

		swap_ranges(arr, arr + amount, bArray);//копируем массив a в массив b

		delete [] bArray;
	}






int main() {
	size_t n;
	ios::sync_with_stdio(false);
	std::cin >> n;

	unsigned long long* arr = new unsigned long long[n];
	for (size_t i = 0; i < n; ++i) {
		std::cin >> arr[i];
		//arr[i]=rand();
	}

	LSDSort(arr, n);

	for (size_t i = 0; i < n; ++i) {
		std::cout << arr[i] << " ";

	}

	delete[] arr;
	return 0;
}