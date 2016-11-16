//
// Created by Fran on 16/11/2016.
//

#ifndef UNTITLED_LISTA_H
#define UNTITLED_LISTA_H




template<typename T>
class Nodo2{
private:
    T dato;
    Nodo2<T> * siguiente;
    Nodo2<T> * anterior;
public:
    Nodo2():siguiente(0), anterior(0){}
    Nodo2(const Nodo2<T> &orig):siguiente(orig.siguiente), anterior(orig.anterior), dato(orig.dato){}
    bool haySiguiente(){return siguiente!=0;}
    bool hayAnterior(){return anterior!=0;}
    bool operator ==(const Nodo2<T> &orig){return dato==orig.dato;}
    bool operator !=(const Nodo2<T> &orig){return dato!=orig.dato;}
};

class Lista {


};


#endif //UNTITLED_LISTA_H
