#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include <list>
#include <utility>
#include <string>
#include <map>

struct IPAccess{
    public:
        std::string ip;
        std::string mes;
        std::string dia;
        std::string hora;
        std::string minutos;
        std::string segundos;
        std::map<std::string,std::string> Map {
            {"Jan","1"},
            {"Feb","2"},
            {"Mar","3"},
            {"Apr","4"},
            {"May","5"},
            {"Jun","6"},
            {"Jul","7"},
            {"Aug","8"},
            {"Sep","9"},
            {"Oct","10"},
            {"Nov","11"},
            {"Dec","12"},
        };

        IPAccess(std::string ip,std::string mes,std::string dia,std::string hora,std::string minutos,std::string segundos){
            this->ip=ip;
            this->mes=mes;
            this->dia=dia;
            this->hora=hora;
            this->minutos=minutos;
            this->segundos=segundos;
        }
        IPAccess():IPAccess("","","","","",""){}

        //funcion para pasar de meses a numeros
        std::string mon2num(std::string month){
            //regreso el valor numerico del map
            return this->Map.find(month)->second;
        }

        //funcion para comparar dos fechas
        bool operator<(IPAccess& a){
            if(stoi(mon2num(this->mes))<stoi(mon2num(a.mes))){
                return true;
            }else if(stoi(mon2num(this->mes))==stoi(mon2num(a.mes))){
                if(stoi(mon2num(this->dia))<stoi(mon2num(a.dia))){
                    return true;
                }else if(stoi(mon2num(this->dia))==stoi(mon2num(a.dia))){
                    if(stoi(mon2num(this->hora))<stoi(mon2num(a.hora))){
                        return true;
                    }else if(stoi(mon2num(this->hora))==stoi(mon2num(a.hora))){
                        if(stoi(mon2num(this->minutos))<stoi(mon2num(a.minutos))){
                            return true;
                        }else if(stoi(mon2num(this->minutos))==stoi(mon2num(a.minutos))){
                            if(stoi(mon2num(this->segundos))<stoi(mon2num(a.segundos))){
                                return true;
                            }else{
                                return false;
                            }
                        }
                    }
                }
            }
        }
};

class MyHashTable{
    public:
        std::list<IPAccess>* tabla;
        int size; //cantidad de valores almacenados en la tabla
        int sizeA; //tamaño del arreglo
        int getPos(std::string);
        void reHash();
   
        MyHashTable();
        ~MyHashTable();
        bool isEmpty();
        void put(std::string,std::string,std::string,std::string,std::string,std::string);
        void get(std::string);
        void remove(std::string);
};

#endif