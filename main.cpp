#include <iostream>
#include "MyHashTable.h"

using namespace std;


int main(){

  MyHashTable ht;
  ht.loadData();
  int cont;
  string IP;

  do{
    cout << "Ingrese una IP" << endl;
    cin >> IP;
    ht.get(IP);
    cout<<"presione 0 para salir o 1 para continuar: "<<endl;
    cin>>cont;  
  }while(cont);

  return 0;
}
