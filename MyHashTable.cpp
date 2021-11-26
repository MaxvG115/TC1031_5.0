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
#include <functional>
#include <cmath>
#include <utility>
#include <fstream>
#include "MyHashTable.h"

using namespace std;

//Complejidad:O(1)
MyHashTable::MyHashTable(){
    this->size = 0;
    this->sizeA=11;
    this->tabla=new list<IPAccess>[this->sizeA]();
}

//Complejidad:O(n^2)
MyHashTable::~MyHashTable(){
    for(int i=0;i<this->sizeA;i++){
        this->tabla[i].clear();
    }
    delete[] this->tabla;
}

//Complejidad:O(1)
bool MyHashTable::isEmpty(){
    return this->size==0;
}

//Complejidad:O(n)
int MyHashTable::getPos(string key){
    size_t hashC=hash<string>{}(key);
    int hashCode=static_cast<int>(hashC);
    return abs(hashCode)%this->sizeA;
}

//Complejidad:O(n^2)
void MyHashTable::reHash(){
    int newSize=(this->sizeA*2)+1;
    int oldSize=this->sizeA;
    this->sizeA=newSize;
    
    list<IPAccess>* temp=new list<IPAccess>[newSize]();
    
    for(int i=0;i<oldSize;i++){
        for(list<IPAccess>::iterator it=this->tabla[i].begin();it!=this->tabla[i].end();it++){
            int pos= getPos(it->ip);
            temp[pos].push_front(*it);
        }
    }
    
    //basicamente el destructor pero solo destruye el viejo arreglo
    for(int i=0;i<oldSize;i++){
        this->tabla[i].clear();
    }
    delete[] this->tabla;
    this->tabla=temp;
}

//Complejidad:O(n)
void MyHashTable::put(string ip,string mes,string dia,string hora,string minuto,string segundo){
    double loadFactor=static_cast<double>(this->size)/static_cast<double>(this->sizeA);

    if(loadFactor>.75){
        this->reHash();
        int pos= getPos(ip);
        IPAccess aux(ip,mes,dia,hora,minuto,segundo);
        this->tabla[pos].push_front(aux);
    }else{
        int pos= getPos(ip);
        IPAccess aux(ip,mes,dia,hora,minuto,segundo);
        this->tabla[pos].push_front(aux);
    }
    
    this->size++;
}

//Complejidad:O(n^2)
void MyHashTable::get(string ip){
    int pos = getPos(ip);
    //bubble sort para ordenar los datos
    list<IPAccess>::iterator end=this->tabla[pos].end();
    end--;
    for(list<IPAccess>::iterator it=this->tabla[pos].begin();it!=end;it++){
        for(list<IPAccess>::iterator jt=this->tabla[pos].begin();jt!=end;jt++){
            list<IPAccess>::iterator aux=jt;
            aux++;
            IPAccess temp;
            if(*aux<*jt){
                temp=(*jt);
                *jt=*aux;
                *aux=temp;
            }
        }
    }

    //contamos cuantas veces se repite la key
    int cont=0;
    for(list<IPAccess>::iterator it=this->tabla[pos].begin();it!=this->tabla[pos].end();it++){
        if(it->ip==ip){cont++;}
    }

    //imprimimos solo las ip que corresponden a la key
    for(list<IPAccess>::iterator it=this->tabla[pos].begin();it!=this->tabla[pos].end();it++){
        if(it->ip==ip){
            cout<<"IP: "<<it->ip<<endl;
            cout<<"Fecha: "<<it->dia<<" "<<it->mes<<" "<<it->hora<<":"<<it->minutos<<":"<<it->segundos<<endl;
            cout<<"-------------------------------------"<<endl;
        }
    }
    cout<<"Numero de accesos: "<<cont<<endl;

}

//Complejidad:O(n)
void MyHashTable::remove(string key){
    int pos = getPos(key);
    for(list<IPAccess>::iterator it=this->tabla[pos].begin();it!=this->tabla[pos].end();it++){
        if(it->ip==key){
            this->tabla[pos].erase(it);
            this->size--;
            return;
        }
    }
    cout<<"valor no encontrado"<<endl;
    //this->tabla[pos].remove_if([key](pair<string,int> data){return data.first==key;});
}

//Complejidad: O(n)
void MyHashTable::loadData(){
    string ip;
    string mes;
    string dia;
    string hora;
    string minuto;
    string segundo;
    string aux;
    ifstream file;//objeto para leer archivo
    int cont=0;

    file.open("bitacora.txt");

     if(file.fail()){
        exit(0);
    }else{
        while (!file.eof()){
            getline(file,mes,' ');
            getline(file,dia,' ');
            getline(file,hora,':');
            getline(file,minuto,':');
            getline(file,segundo,' ');
            getline(file,ip,':');
            getline(file,aux);

            put(ip,mes,dia,hora,minuto,segundo);
            cont++;
        }
    }
    file.close();
}
