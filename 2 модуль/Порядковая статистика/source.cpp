//
// Created by elena on 29.11.17.
//

#include <assert.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
using std::vector;

int Partition(vector<int>& data, int left, int right)
{
    //Выбираем индекс опорного элемента
    int index = rand() % ( right - left + 1 ) + left;
    int pivot = data[index];
    //Опорный элемент меняется с последним элементом массива
    std::swap(data[index],data[right]);
    int i = left;//начало группы элементов строго больших опорного
    int j = left;//индекс первого нерасмотренного элемента
    while( i <= right && data[i] <= pivot )
        i++;
    if ( i >= right )
        return right;
    j = i + 1;
    while ( j < right )
    {
        while( data[j] > pivot )//если элемен,на который указывает j больше опорного,то двигаем j
        {
            j++;
        }
        if ( j < right) // меняем местами i и j , сдвигаем индексы
        {
            std::swap(data[i++], data[j++]);
        }
    }
    std::swap(data[i], data[right]);//меняем опорный элемент и тот на который указывает i
    return i;
}

// Возвращает k-ую порядковую статистику. k считается от 0.
int KStat( vector<int>& data, int k )
{
    assert( k >= 0 && k < static_cast<int>( data.size() ) );
    int left = 0;
    int right = data.size()-1; // Не включаем right.
    while( true ) {
        int pivotPos = Partition( data, left, right );
        if( pivotPos == k ) {
            return data[k];
        }
        if( pivotPos > k ) {
            right = pivotPos;
        } else {
            left = pivotPos + 1;
        }
    }
}

int main()
{
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    vector<int> data( n );
    for( int i = 0; i < n; ++i ) {
        std::cin >> data[i];
    }
    std::cout << KStat( data, k );
//    std::cout<<std::endl;
//    for( int i = 0; i < n; ++i ) {
//        std::cout<< data[i]<<" ";
//    }
    return 0;
}