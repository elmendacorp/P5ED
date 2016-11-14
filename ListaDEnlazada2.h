/* 
 * File:   ListaDEnlazada.
 * Author: Fran
 *
 * Created on 19 de octubre de 2016, 17:05
 */

#ifndef LISTADENLAZADA_
#define    LISTADENLAZADA_

#include "cassert"

template<typename T>
class Nodo {
private:
    T elemento;
    Nodo<T> *anterior;
    Nodo<T> *siguiente;
public:

    Nodo() : anterior(0), siguiente(0) {
    };

    Nodo(const T &elem, Nodo<T> *&ant, Nodo<T> *&sig) : elemento(elem), anterior(ant), siguiente(sig) {
    }

    bool operator==(const Nodo<T> *&orig) {
        return *this == orig;
    }

    Nodo(const Nodo<T> *&orig) {
        this=new Nodo<T>();
        elemento = orig->elemento;
        anterior = orig->anterior;
        siguiente = orig->siguiente;
    }

    void SetSiguiente(Nodo<T> *sig) {
        siguiente = sig;
    }

    Nodo *GetSiguiente() const {
        return siguiente;
    }

    void SetAnterior(Nodo<T> *ant) {
        this->anterior = ant;
    }

    Nodo *GetAnterior() const {
        return anterior;
    }

    void SetElemento(T &elemento) {
        this->elemento = elemento;
    }

    const T GetElemento() {
        return elemento;
    }

    bool operator!=(const Nodo<T> *&orig) {
        return *this != orig;
    }
};

template<typename T>
class Iterador {
private:
    Nodo<T> *nodo;

    friend class ListaDEnlazada;

public:
    Iterador(Nodo<T> * &aNodo) : nodo(aNodo) {}

    bool hayAnterior() { return nodo->GetAnterior() != 0; }

    bool haySiguiente() { return nodo->GetSiguiente() != 0; }

    void anterior() { nodo = nodo->GetAnterior(); }

    void siguiente() { nodo = nodo->GetSiguiente(); }

    bool operator!=(const Iterador<T> &orig) { return this->nodo != orig.nodo; }

    bool operator==(const Iterador<T> &orig) { return this->nodo == orig.nodo; }

    T &dato() { return nodo->GetElemento(); }

    Nodo<T> * operator*(Iterador<T> &it) { return it.nodo; }


};

/**Clase Lista enlazada
 */
template<typename T>
class ListaDEnlazada {
private:
    Nodo<T> *cabecera;
    Nodo<T> *cola;

    Nodo<T> *inicio() {
        return cabecera;
    }

    Nodo<T> *final() {
        return cola;
    }

    void insertarInicio(T &dato);

    void insertarFinal(T &dato);

    void borrarInicio();

    void borrarFinal();

public:

    ListaDEnlazada();

    ~ListaDEnlazada();

    ListaDEnlazada(ListaDEnlazada<T> &orig);

    ListaDEnlazada<T> operator=(ListaDEnlazada<T> &orig);

    Iterador<T> iteradorInicio() { return Iterador<T>(cabecera); };

    Iterador<T> iteradorFin() { return Iterador<T>(cola); };

    void insertar(Iterador<T> &i, T &dato);

    void borrar(Iterador<T> &i);


};


template<typename T>
void ListaDEnlazada<T>::borrarFinal() {
    if (cola != 0) {
        cola = cola->GetAnterior();
        delete cola->GetSiguiente();
        cola->SetSiguiente(0);
    }
}

template<typename T>
void ListaDEnlazada<T>::borrarInicio() {
    if (cabecera != 0) {
        cabecera = cabecera->GetSiguiente();
        delete cabecera->GetAnterior();
    }
}

template<typename T>
void ListaDEnlazada<T>::insertarFinal(T &dato) {
    Nodo<T> *temporal = new Nodo<T>();
    temporal->SetElemento(dato);
    if(cola!=0) {
        temporal->SetAnterior(cola);
        cola->SetSiguiente(temporal);
    }
    if (cabecera == 0) {
        cabecera = temporal;
    }
    cola = temporal;

}

template<typename T>
void ListaDEnlazada<T>::insertarInicio(T &dato) {
    Nodo<T> *temporal = new Nodo<T>();
    temporal->SetElemento(dato);
    if (cabecera != 0) {
        temporal->SetSiguiente(cabecera);
        cabecera->SetAnterior(temporal);
    }
    temporal->SetAnterior(0);
    cabecera = temporal;
    if (cola == 0) {
        cola = cabecera;
    }
}

template<typename T>
void ListaDEnlazada<T>::insertar(Iterador<T> &i, T &dato) {
    assert(i.nodo != 0);
    if (i == this->iteradorInicio()) {
        this->insertarInicio(dato);
    } else if (i == this->iteradorFin()) {
        this->insertarFinal(dato);
    } else {
        Nodo<T> *temporal = new Nodo<T>();
        temporal->SetElemento(dato);
        if (i.haySiguiente()) {
            temporal->SetSiguiente(i.nodo->GetSiguiente());
            i.nodo->SetAnterior(temporal);
        }
        if (i.hayAnterior()) {
            temporal->SetAnterior(i.nodo->GetAnterior());
            i.nodo->SetSiguiente(temporal);
        }
    }
}

template<typename T>
void ListaDEnlazada<T>::borrar(Iterador<T> &i) {
    if(i==this->iteradorInicio()){
        this->borrarInicio();
    }else if(i==this->iteradorFin()){
        this->borrarFinal();
    }else {
        Nodo<T> *temporal(i.nodo);
        assert(temporal != 0);
        temporal->GetAnterior()->SetSiguiente(temporal->GetSiguiente());
        temporal->GetSiguiente()->SetAnterior(temporal->GetAnterior());
        delete temporal;
    }

}


template<typename T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator=(ListaDEnlazada<T> &orig) {
    ListaDEnlazada<T> tmp;
    Iterador<Nodo<T> *> aux = orig.iteradorInicio();
    while (aux != orig.iteradorFin()) {
        tmp.insertarFinal(aux.dato()->GetElemento());
        aux.siguiente();
    }
    return tmp;
}


template<typename T>
ListaDEnlazada<T>::ListaDEnlazada(ListaDEnlazada<T> &orig) {
    Iterador<T> it=orig.iteradorInicio();
    while(it!=orig.iteradorFin()){
        this->insertarFinal(it.dato());
        it.siguiente();
    }
}

template<typename T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    while (cabecera != cola) {
        cabecera = cabecera->GetSiguiente();
        delete cabecera->GetAnterior();
    }
    delete cabecera;
}


template<typename T>
ListaDEnlazada<T>::ListaDEnlazada() {
    cabecera = 0;
    cola=0;
}


#endif	/* LISTADENLAZADA_ */