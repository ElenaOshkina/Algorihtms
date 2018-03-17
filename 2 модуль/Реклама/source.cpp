//
// Created by elena on 29.11.17.
//

#include <iostream>
#include <vector>
using namespace std;

struct Client{
    int timeIn;
    int timeOut;
    bool operator<(const Client& other) const
    {
        if(timeOut!=other.timeOut){
            return timeOut<other.timeOut;//у кого время ухода меньше
        }else{
            return timeIn>other.timeIn;
        }
    }
};

void showCustomersData(vector<Client> & customers, int n){
    cout<<"Customers data"<<endl;
    for(int i = 0; i < n; i++){
        cout<<customers[i].timeIn<<" "<<customers[i].timeOut<<endl;
    }
}

void getDataForCustomers(vector<Client> & customers, int n){

    for(int i = 0; i < n; i++){
        Client tempClient;
        cin>>tempClient.timeIn>>tempClient.timeOut;
        customers.push_back(tempClient);
    }
}
//
// Проталкивание элемента вниз. CArray – целочисленный массив.
void SiftDown( vector<Client> & customers, int i , int size)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем большего сына, если такой есть.
    int largest = i;
    if( left < size && !(customers[left] < customers[i]) )
        largest = left;
    if( right < size && !(customers[right] < customers[largest]) )
        largest = right;
    // Если больший сын есть, то проталкиваем корень в него.
    if( largest != i ) {
        std::swap( customers[i], customers[largest] );
        SiftDown( customers, largest, size );
    }
}

// Построение кучи.
void BuildHeap( vector<Client> & customers,int n )
{
    for( int i = n / 2 - 1; i >= 0; --i ) {
        SiftDown( customers, i, n );
    }
}

// Проталкивание элемента наверх.
void SiftUp( vector<Client> & customers, int index )
{
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( customers[index] < customers[parent] )
            return;
        std::swap( customers[index], customers[parent] );
        index = parent;
    }
}
//N-1 раз достаем максимальный элемент, кладем его на освободившееся место в правой части
void HeapSort( vector<Client> & customers, int n ) {
    int heapSize = n;
    BuildHeap( customers, heapSize );
    while( heapSize > 1 ) {
        // Немного переписанный ExtractMax.
        swap( customers[0], customers[heapSize - 1] );
        --heapSize;
        SiftDown( customers,0, heapSize );
    }
}


int getAmountShow(vector<Client> & customers, int n){
    if(n==0)
        return 0;
    int amount=2;

    int rPoint=customers[0].timeOut;
    int lPoint=rPoint-1;

    for(int i=0; i<n; i++){
        //если время пребывания покупателя совпадает с временем двух показов
        if(lPoint>=customers[i].timeIn && rPoint<=customers[i].timeOut){}
        //если покупатель просмотрел только одну рекламу
        else if (rPoint>=customers[i].timeIn && rPoint<=customers[i].timeOut){
            lPoint=rPoint;
            rPoint=customers[i].timeOut;
            amount++;
        }else{//если покупатель не видел еще ни одной рекламы
            rPoint=customers[i].timeOut;
            lPoint=rPoint-1;
            amount+=2;
        }
    }
    return amount;
}

int main(){
    int n=0;
    cin>>n;
    vector<Client>customers;
    getDataForCustomers(customers, n);
    //showCustomersData(customers,n);
    BuildHeap(customers,customers.size());
    //showCustomersData(customers,n);
    HeapSort(customers,n);
    //showCustomersData(customers,n);
    int amount=getAmountShow(customers,n);
    cout<<amount;
    return 0;
}