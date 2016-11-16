//
// Created by Fran on 16/11/2016.
//

#ifndef UNTITLED_LISTA_H
#define UNTITLED_LISTA_H

/**
 * Clase que define un nodo de la lista enlazada
 */
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
    Nodo2<T> * getSiguiente(){return siguiente;}
    Nodo2<T> * getAnterior(){return anterior;}
    T & getDato(){return dato;}
    void setSiguiente(Nodo2<T> *orig){siguiente= orig;}
    void setAnterior(Nodo2<T> *orig){anterior= orig;}
    bool operator ==(const Nodo2<T> &orig){return dato==orig.dato;}
    bool operator !=(const Nodo2<T> &orig){return dato!=orig.dato;}
};

template<typename T>
class IteradorL{
private:
    Nodo2<T> * nodoapuntado;
    IteradorL():nodoapuntado(0){}
    IteradorL(IteradorL<T> &orig):nodoapuntado(orig.nodoapuntado){}

};

class Lista {


};


#endif //UNTITLED_LISTA_H
