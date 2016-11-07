//
// Created by Fran on 03/11/2016.
//

#ifndef UNTITLED_ABB_H
#define UNTITLED_ABB_H

#include <cassert>
#include<vector>

template<typename T>
class Nodo {
private:
    Nodo<T> *izquierda;
    Nodo<T> *derecha;
    T dato;
public:
    Nodo() : izquierda(0), derecha(0) {}

    Nodo(const T &orig) : izquierda(0), derecha(0), dato(orig) {}

    void setDato(T &dato) { this->dato = dato; }

    T getDato() { return dato; }

    bool tieneDerecha() { return derecha != 0; }

    bool tieneIzquierda() { return izquierda != 0; }

    Nodo<T> *getIzquierda() { return izquierda; }

    Nodo<T> *getDerecha() { return derecha; }

    void setIzquierda(Nodo<T> *&nodo) { izquierda = nodo; }

    void setDerecha(Nodo<T> *&nodo) { derecha = nodo; }

    friend class ABB;
};

template<typename T>
class ABB {
private:
    Nodo<T> *raiz;

    Nodo<T> *inserta(const T &dato);

    Nodo<T> *buscaClave(T &ele);

    Nodo<T> *insertarDato(T &ele, Nodo<T> *p);

    Nodo<T> *borraMin(Nodo<T> *&p);

    void preorden(Nodo<T> *p, int nivel);

    void inorden(Nodo<T> *p, int nivel);

    void postorden(Nodo<T> *p, int nivel);


public:
    ABB();

    ABB(const ABB<T> &orig);

    bool buscar(T &ele, T &resultado);

    bool insertar(T &ele);

    bool eliminar(T &ele);

    int numElementos();

    int altura();

    int numHojas();

    void recorrerPreorden() { preorden(raiz, 0); }

    void recorrerInorden() { inorden(raiz, 0); }

    void recorrerPostorden() { postorden(raiz, 0); }


};

/**
 * Constructor por defecto inicializa la raiz a 0
 * @return null
 */
template<typename T>
ABB<T>::ABB() {
    raiz = 0;
}

/**
 * Insercion ordenada en el arbol
 * @param dato
 */
template<typename T>
Nodo<T> *ABB<T>::inserta(const T &dato) {
    Nodo<T> *actual = raiz;
    bool insertado = false;
    while (!insertado) {
        if (actual == 0) {
            Nodo<T> *tmp = new Nodo<T>(); //En este caso es el de que la raiz es nula
            tmp->setDato(dato);
            actual = tmp;
            insertado = true;
        } else {
            if (actual->getDato() < dato) {//rama de la izquierda
                if (actual->tieneIzquierda()) {
                    actual = actual->getIzquierda();//si no esta vacio iteramos a la izquierda y repetimos el proceso
                } else {
                    Nodo<T> *tmp = new Nodo<T>();
                    tmp->setDato(dato);
                    actual->setIzquierda(tmp);
                    actual = tmp;
                    insertado = true;
                }
            }
            if (actual->getDato() > dato) {
                if (actual->tieneDerecha()) {
                    actual = actual->getDerecha();
                } else {
                    Nodo<T> *tmp = new Nodo<T>();
                    tmp->setDato(dato);
                    actual->setDerecha(tmp);
                    actual = tmp;
                    insertado = true;
                }
            } else {
                insertado = true;
                actual = 0;
            }
        }
    }
    return actual;
}

/**
 * Insercion publica
 * @param ele elemento T que se quiere insertar
 * @return true su insertado, false en otro caso
 */
template<typename T>
bool ABB<T>::insertar(T &ele) {
    return (inserta(ele) != 0); //si no se inserta en el caso que el dato sea igual a un existente
}

/**
 * Busca un elemento T en el arbol
 * @param ele elemnto a buscar
 * @return Nodo en el que se encuentra, 0 en otro caso
 */
template<typename T>
Nodo<T> *ABB<T>::buscaClave(T &ele) {
    Nodo<T> *actual = raiz;
    bool encontrado = false;
    while (!encontrado) {
        if (actual == 0) {
            encontrado = true; //caso del arbol vacio
        } else {
            if (actual->getDato() < ele) {//rama de la izquierda
                if (actual->tieneIzquierda()) {
                    actual = actual->getIzquierda();//si no esta vacio iteramos a la izquierda y repetimos el proceso
                } else {
                    actual = 0;
                    encontrado = true;
                }
            }
            if (actual->getDato() > ele) {
                if (actual->tieneDerecha()) {
                    actual = actual->getDerecha();
                } else {
                    actual = 0;
                    encontrado = true;
                }
            } else {//caso de que el elemento sea igual
                encontrado = true;
            }
        }
    }
    return actual;
}

/**
 * Busqueda publica de un elemento en el arbol
 * @param ele elemento T a buscar
 * @param resultado Nodo de vuelta
 * @return true si se ha encontrado, false en otro caso
 */
template<typename T>
bool ABB<T>::buscar(T &ele, T &resultado) {
    resultado = buscaClave(ele);
    return (resultado != 0);
}

template<typename T>
ABB<T>::ABB(const ABB &orig) {
    if (orig.raiz != 0) {
        *this = ABB<T>();
        std::vector<Nodo<T> *> tmp;
        Nodo<T> *actual = orig.raiz;
        tmp.push_back(actual);
        int index = 0;
        while (actual->tieneIzquierda() || actual->tieneDerecha() || index < tmp.size()) {
            actual = tmp[index];
            if (actual->tieneDerecha()) {
                tmp.push_back(actual->getDerecha());
            }
            if (actual->tieneIzquierda()) {
                tmp.push_back(actual->getIzquierda());
            }
            ++index;
        }
        for (int i = 0; i < tmp.size(); ++i) {
            this->inserta(tmp[i]);
        }
    }
}

template<typename T>


#endif //UNTITLED_ABB_H
