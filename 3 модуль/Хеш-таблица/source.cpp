#include <assert.h>
#include <iostream>
#include <vector>
using std::string;
void show(std::vector<string> v,std::vector<bool> v1);
using std::cout;

unsigned int MyEffectiveHash( const string & key, int M )
{
    int hash=0, a=17;
    for(int i = key.size(); i >= 0; i--){
        hash = (a * hash + key[i]) % M;
    }
    // cout<<hash<<std::endl;
    return hash%M;
}

class CHashTable {
public:
    explicit CHashTable( int initialTableSize );
    ~CHashTable();

    // Проверка наличия ключа в хеш-таблице.
    bool Has( const string& key ) const;
    // Добавление ключа. Возвращает false, если ключ уже есть в хеш-таблице, повторно его не добавляет.
    bool Add( const string& key );
    // Удаление ключа. Возвращает false, если ключа нет в хеш-таблице.
    bool Remove( const string& key );
    int hashTwo(const string& key, int M) const;
    void init();
    void grow();
    void show();
private:
    std::vector<string> table;
    std::vector<bool> deleted;
    int M;
    int N;
};

CHashTable::CHashTable( int initialTableSize ) :
        table( initialTableSize ), deleted(initialTableSize), M(initialTableSize), N(0) {
    std::fill(deleted.begin(), deleted.end(), false);
    std::fill(table.begin(), table.end(), "");
}

CHashTable::~CHashTable() {

}

void CHashTable::grow() {
    std::vector<string> t (table.begin(), table.end());
    std::vector<bool> tDeleted (deleted.begin(), deleted.end());
    M*=2;
    init();
    for(int i=0; i<M/2; i++){
        if(!t[i].empty() && tDeleted[i]!=true)
            Add(t[i]);
    }
}

int CHashTable::hashTwo(const string& key, int M) const {
    int hash=0, a=19;
    for(int i = key.size(); i >= 0; i--){
        hash = (a * hash + key[i]) % M;
    }
    // cout<<hash<<std::endl;
    return (2*hash+1)%M;
}

void CHashTable::init(){
    //table.clear();
    //deleted.clear();
    N=0;
    table.resize(M);
    deleted.resize(M);
    std::fill(deleted.begin(), deleted.end(), false);
    std::fill(table.begin(), table.end(), "");
//    for(int i=0; i<M/2; i++){
//        table.push_back("");
//        deleted.push_back(false);
//    }
}

bool CHashTable::Has( const string& key ) const {

    int i = MyEffectiveHash( key, M );
    const int k=hashTwo(key, M);
    for(int j=0; j<M; j++) {
        if(table[i].empty()!=true ) {
            if (table[i] == key and deleted[i]!=true) {
                //show(table, deleted);
                return true;
            }
        }else{
            return false;
        }
        i=(i+k)%M;
    }

    return false;
}

bool CHashTable::Add( const string& key ) {
    if(Has(key)) return false;
    int i=MyEffectiveHash(key, M), k=hashTwo(key, M);
    for(int j=0; j<M; j++){
        if(table[i]==key and deleted[i]!=true) return false;
        if(table[i].empty() or deleted[i]==true){
            table[i]=key;
            deleted[i]=false;
            N++;
            if(N/(float)M>=0.75){
                grow();
            }
            return true;
        }
        i = (i + k) % M;
       // cout<<"i="<<i<<" "<< j<<std::endl;
    }
    return false;
}

bool CHashTable::Remove( const string& key ) {
   // show(table,deleted);
    //if(!Has(key)) return false;
    int i = MyEffectiveHash( key, M);
    const int k=hashTwo(key, M);
    for(int j = 0; j < M; j++){
        if(table[i].empty()) return false;
        if( deleted[i]!=true){
            if(table[i]==key){
                deleted[i]=true;
                N--;
                return true;
            }
        }
        i=(i+k)%M;
    }
    return false;
}

void CHashTable:: show(){
    cout<<std::endl;
    for (int i=0; i<M; i++){
        if(table[i].empty())
            cout<<"\t"<<"\t "<<deleted [i]<<std::endl;
        else
            cout<<table[i]<<"\t\t "<<deleted[i]<<std::endl;
    }
    //cout<<std::endl;
}

int main()
{
    CHashTable hashTable( 1 );
    char command = 0;
    string key;
    std::ios::sync_with_stdio(false);
    while( std::cin >> command >> key ) {
        switch( command ) {
            case '?':
                std::cout << ( hashTable.Has( key ) ? "OK" : "FAIL" ) << std::endl;
                //hashTable.show();
                break;
            case '+':
                std::cout << ( hashTable.Add( key ) ? "OK" : "FAIL" ) << std::endl;
               // hashTable.show();
                break;
            case '-':
                std::cout << ( hashTable.Remove( key ) ? "OK" : "FAIL" ) << std::endl;
               // hashTable.show();
                break;
        }
    }
    return 0;
} //