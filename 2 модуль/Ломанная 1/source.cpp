//
// Created by elena on 21.10.17.
//

#include <iostream>
#include <vector>
using namespace std;

struct CSgment{
    int Left = 0;
    int Right = 0;
    //сравнение по левой координате
    bool operator<(const CSgment& other) const
    {
        return Left<other.Left || (Left==other.Left && Right<other.Right);
    }
};

//Функция сравнения по координатам
bool CompareByCoordinatess(const CSgment& first, const CSgment& second){
    if (first.Left>=second.Left ) 
        return true;
    else
    if (first.Left==second.Left  &&  first.Right>=second.Right) 
        return true;
    return false;
}






void MyFirstSort2(vector<CSgment>& arr, bool (*compare)(const CSgment &, const CSgment &)){
    int j=0;
    for ( int i=0; i < arr.size(); i++) { // цикл проходов, i - номер прохода
        CSgment   x = arr[i];

// поиск места элемента в готовой последовательности
        for (j=i-1; j>=0 && !(arr[j] < x); j--)
            arr[j+1] = arr[j]; // сдвигаем элемент направо, пока не дошли

// место найдено, вставить элемент
        arr[j+1] = x;
    }
}



int main(){
    std::vector<CSgment> segments;
    CSgment segment;
    // >> возвращает объект потока
    int a;
    cin>>a;
    for(int i = 0; i < a; i++) {
        cin >> segment.Left >> segment.Right;
            segments.push_back(segment);

    }
    // MyFirstSort(segments);
    MyFirstSort2(segments,CompareByCoordinatess);

    for (int i = 0; i <segments.size(); ++i) {
        cout<<segments[i].Left<<" "<<segments[i].Right<<endl;
    }
}