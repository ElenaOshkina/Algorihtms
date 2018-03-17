//
// Created by elena on 28.11.17.
//
#include <assert.h>
#include <iostream>
using namespace std;

class PriorityHeap {
    struct Elem {
        int val;
        int priority;
        Elem(int v = 0, int p = 0) {
            val = v;
            priority = p;
        }
    } ;
    int size;
    int * places;
    Elem *a;
    int max_size;
    void up(int i) {
        while (i != 0 && a[i].val > a[(i - 1) / 2].val) {
            swap(a[i], a[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void down(int i) {
        while (i < size / 2) {
            int maxI = 2 * i + 1;
            if (2 * i + 2 < size && a[2 * i + 2].val > a[2 * i + 1].val)
                maxI = 2 * i + 2;
            if (a[i].val >= a[maxI].val)
                return;
            swap(a[i], a[maxI]);

            i = maxI;
        }
    }

public:

    PriorityHeap(int n) {
        size = 0;
        a=new Elem[n];
        max_size=n;
    }
    ~PriorityHeap(){
        delete []a;
    }
    void enqueue(int value, int priority) {
        assert(size + 1 < max_size+1);
        a[size++] = Elem(value, priority);
        up(size - 1);
    }
    int getMaxValue(int start_window_index){
        while(a[0].priority<start_window_index){
            dequeue();
        }
        return a[0].val;
    }
    int dequeue() {
        assert(size > 0);
        swap(a[0], a[--size]);
        down(0);
        return a[size].val;
    }

    
};

void getMaxValueFromWindows(int *arr, int n, int windowSize){
    PriorityHeap pr(n);
    for(int i = 0; i < windowSize; i++){
        pr.enqueue(arr[i],i);
    }
    cout<<pr.getMaxValue(0)<<" ";
    int i;
    for(i = windowSize; i < n; i++){
        pr.enqueue(arr[i],i);
        if (i == n-1)
            cout<<pr.getMaxValue( i- windowSize+1);
        else
            cout<<pr.getMaxValue(i - windowSize+1)<<" ";
    }
}

int main(){
    int n = 0;
    int windowSize = 0;
    cin>>n;
    int *arr = new int [n];
    for(int i = 0; i < n; i++) {
         cin >> arr[i];
    }
    cin>>windowSize;

    getMaxValueFromWindows(arr,n,windowSize);

    delete [] arr;
    return 0;
}

