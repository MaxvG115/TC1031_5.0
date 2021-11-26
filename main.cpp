#include <iostream>
#include "MyHashTable.h"

using namespace std;

int main(){
    MyHashTable ht;
    ht.loadData();
    ht.get("423.2.230.77");

    return 0;
}