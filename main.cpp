#include <iostream>
#include "MyHashTable.h"

using namespace std;

int main(){
    MyHashTable ht;
    ht.put("12.15.26","Jan","16","8","16","30");
    ht.put("12.15.26","Dec","16","8","16","30");
    ht.put("12.15.26","Nov","16","8","16","30");
    ht.get("12.15.26");
    return 0;
}