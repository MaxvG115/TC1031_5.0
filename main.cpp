/*
===============================*
<Autores>
+Vicente Viera Guízar, ID: A01639784
+Maximiliano Villegas Garcia. ID: A01635825
+Emma Gabriela Alfaro De la Rocha. ID: A01740229
</Autores>
=================================*
*/
#include <iostream>
#include "MyHashTable.h"

using namespace std;

//main con menu de pruebas
int main(){

  MyHashTable ht;
  ht.loadData();
  int cont;
  string IP;

  do{
    cout << "++++++++ Ingrese una direccion IP ++++++++" << endl;
    cin >> IP;
    cout << "\n" << endl;
    ht.get(IP);
    cout << "\n" << "++++ presione 0 para salir o 1 para continuar: ++++" << endl;
    cin>>cont;
    cout << "//////////////////////////////////////////" << endl; 
  }while(cont);

  return 0;
}
