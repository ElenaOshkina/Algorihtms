#include <iostream>

using namespace std;
#include <stdlib.h>
#include <time.h>
#include <vector>

void quick_sort(int[],int,int);
int partition(int[],int,int);





void InsertionSort(int *arr, const size_t &end) {
    int j;
    for (size_t i =  1; i < end; ++i) {
        int x=arr[i];
        j=i;
        while(j>0 && x<arr[j-1]){
            arr[j]=arr[j-1];
            j--;
        }
        arr[j]=x;
    }
}



int Partition(int *  a, int & n)
{
    if( n <= 1 ) {
        return 0;
    }
   // int med=median(a[0],a[n-1],a[n/2]);
    //std::swap(a[med],a[n-1]);
    int index = rand() % n;

    swap(a[index], a[n-1]);
    const int& pivot = a[n-1];
    int i = 0, j = n - 2;
    while( i <= j ) {
// Не проверяем, что i < n - 1, т.к. a[n - 1] == pivot.
        for( ; a[i] < pivot; ++i ) {}
        for( ; j >= 0 && !( a[j] < pivot ); --j ) {}
        if( i < j ) {
            std::swap( a[i++], a[j--] );
        }
    }
    std::swap( a[i], a[n - 1] );
    return i;
}


void QuickSort(int * data, int n){
    if(n<15){
        InsertionSort(data,n);
    }else {
        int part = Partition(&data[0], n);
        if (part > 0) {
            QuickSort(data, part);
        }
        if (part + 1 < n)
            QuickSort(&data[0] + part + 1, n - (part + 1));
    }
}

bool read_int_unlocked(int & out)
{
    int c = getchar_unlocked();
    int x = 0;
    int neg = 0;

    for (; !('0'<=c && c<='9') && c != '-'; c = getchar_unlocked())
    {
        if (c == EOF)
            return false;
    }
    if (c == '-')
    {
        neg = 1;
        c = getchar_unlocked();
    }
    if (c == EOF)
        return false;
    for (; '0' <= c && c <= '9' ; c = getchar_unlocked())
    {
        x = x*10 + c - '0';
    }
    out = neg ? -x : x;
    return true;
}

int main()
{

    srand(time(NULL));
    std::vector<int> data;
    int value;
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    while(read_int_unlocked(value)){
        data.push_back(value);
    }

    QuickSort(&data[0],data.size());
    std::ios::sync_with_stdio(false);
    for( int i = 9; i < data.size(); i+=10 ) {
        //for(int i=0; i<data.size(); i++){
        std::cout<< data[i]<<" ";
    }
    return 0;
}