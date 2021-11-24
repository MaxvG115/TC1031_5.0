#include <iostream>
#include <functional>
#include <cmath>
#include <utility>
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

//Complejidad:O(n)
void MyHashTable::get(string ip){
//ese metodo falta que regrese los accesos ordenados
    int pos = getPos(ip);
    //bubble sort
    list<IPAccess>::iterator end=this->tabla[pos].end();
    end--;
    //end--;
    for(list<IPAccess>::iterator it=this->tabla[pos].begin();it!=end;it++){
    //cout<<"entre"<<endl;
        for(list<IPAccess>::iterator jt=this->tabla[pos].begin();jt!=end;jt++){
            //cout<<"entre1"<<endl;
            list<IPAccess>::iterator aux=jt;
            aux++;
            cout<<jt->mes<<": jt"<<endl;
            cout<<aux->mes<<": aux"<<endl;
            cout<<"*************"<<endl;
            IPAccess temp;
            if(*jt<*aux){
            cout<<"entre1"<<endl;
                temp=(*jt);
                *jt=*aux;
                *aux=temp;
            }
        }
    }
    for(list<IPAccess>::iterator it=this->tabla[pos].begin();it!=this->tabla[pos].end();it++){
        cout<<it->ip<<endl;
        cout<<it->mes<<endl;
        cout<<it->dia<<endl;
        cout<<it->hora<<endl;
        cout<<it->minutos<<endl;
        cout<<it->segundos<<endl;
    }
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