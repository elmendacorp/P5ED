//
// Created by Fran on 03/11/2016.
//

#ifndef UNTITLED_ABB_H
#define UNTITLED_ABB_H

#include<cassert>
#include<vector>


template<typename T>
class NodoA {
private:
    T dato;
    NodoA<T> *izquierda;
    NodoA<T> *derecha;
public:
    NodoA() : izquierda(0), derecha(0) {}

    NodoA(const T &orig) : izquierda(0), derecha(0), dato(orig) {}

    void setDato(const T &dato) { this->dato = dato; }

    T &getDato() { return dato; }

    bool tieneDerecha() { return derecha != 0; }

    bool tieneIzquierda() { return izquierda != 0; }

    NodoA<T> *getIzquierda() { return izquierda; }

    NodoA<T> *getDerecha() { return derecha; }

    void setIzquierda(NodoA<T> *orig) { izquierda = orig; }

    void setDerecha(NodoA<T> *orig) { derecha = orig; }
};

template<typename T>
class ABB {
private:

    NodoA<T> *raiz;

    NodoA<T> *inserta( T &dato);

    NodoA<T> *buscaClave(const T &ele);

    NodoA<T> *borraDato(const T &ele, NodoA<T> *p);

    NodoA<T> *buscaPadre(NodoA<T> *p);

    NodoA<T> *borraMin(NodoA<T> *p);

    std::vector<NodoA<T> *> anchura(NodoA<T> *p);


public:
    ABB();

    ~ABB();

    ABB(const ABB<T> &orig);

    bool buscar(const T &ele);

    bool insertar(T &ele);

    bool eliminar(const T &ele);

    int numElementos();

    int altura();

    int numHojas();


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
NodoA<T> *ABB<T>::inserta(T &dato) {

    if (raiz == 0) {
        NodoA<T> *tmp = new NodoA<T>(); //En este caso es el de que la raiz es nula
        tmp->setDato(dato);
        raiz = tmp;
        return tmp;
    }
    NodoA<T> *actual = raiz;
    bool insertado = false;
    while (!insertado) {
        if (actual->getDato() < dato) {//rama de la izquierda
            if (actual->tieneIzquierda()) {
                actual = actual->getIzquierda();//si no esta vacio iteramos a la izquierda y repetimos el proceso
            } else {
                NodoA<T> *tmp = new NodoA<T>();
                tmp->setDato(dato);
                actual->setIzquierda(tmp);
                actual = tmp;
                insertado = true;
            }
        } else if (actual->getDato() > dato) {
            if (actual->tieneDerecha()) {
                actual = actual->getDerecha();
            } else {
                NodoA<T> *tmp = new NodoA<T>();
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
 * @return NodoA en el que se encuentra, 0 en otro caso
 */
template<typename T>
NodoA<T> *ABB<T>::buscaClave(const T &ele) {
    NodoA<T> *actual = raiz;
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
            } else if (actual->getDato() > ele) {
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
 * @param resultado NodoA de vuelta
 * @return true si se ha encontrado, false en otro caso
 */
template<typename T>
bool ABB<T>::buscar(const T &ele) {
    NodoA<T>* resultado = buscaClave(ele);
    return (resultado != 0);
}

/**
 * Construcctor de copia, usa un recorrido en anchura y luego una insercion ordenada para mantener la estructura
 * @param orig
 * @return
 */
template<typename T>
ABB<T>::ABB(const ABB<T> &orig) {
    if (orig.raiz != 0) {
        *this = ABB<T>();
        NodoA<T> *actual = orig.raiz;
        std::vector<NodoA<T> *> tmp = this->anchura(actual);
        for (int i = 0; i < tmp.size(); ++i) {
            this->inserta(tmp[i]);
        }
    }
}

/**
 * Funcion auxiliar que busca el padre un NodoA, se supone el NodoA existente
 * @param p NodoA a buscar
 * @return
 */
template<typename T>
NodoA<T> *ABB<T>::buscaPadre(NodoA<T> *p) {
    NodoA<T> *tmp = raiz;
    bool encontrado = false;
    if (p == raiz) {
        return 0; //en el caso de que la raiz sea el NodoA buscado no tiene padre
    }
    while (!encontrado) {
        if (tmp->getIzquierda() == p || tmp->getDerecha() == p) {
            return tmp;
        } else if (p->getDato() < p->getIzquierda()->getDato()) {
            tmp = tmp->getIzquierda();
        } else if (p->getDato() > p->getDerecha()->getDato()) {
            tmp = tmp->getDerecha();
        }
    }
}

/**
 * Borrado de un elemento y el subarbol que cuelga de el
 * @param ele dato a comparar
 * @param p subarbol de partida
 * @return NodoA del elemento buscado
 */
template<typename T>
NodoA<T> *ABB<T>::borraDato(const T &ele, NodoA<T> *p) {
    NodoA<T> *actual = this->buscaClave(ele);
    std::vector<NodoA<T> *> tmp = this->anchura(actual);
    for (int i = (int) tmp.size() - 1; i >= 0; --i) {//borrado completo del subarbol
        actual = tmp[i];
        if (actual->tieneDerecha()) {
            delete actual->getDerecha();
        }
        if (actual->tieneIzquierda()) {
            delete actual->getIzquierda();
        }
    }

    NodoA<T> *padre = buscaPadre(p);//aqui elimino la referencia del padre al NodoA que borramos
    if (padre->tieneDerecha()) {
        if (padre->getDerecha() == p) {
            delete padre->getDerecha();
        }
    } else {
        delete padre->getIzquierda();
    }
    return actual;
}

/**
 * Borra un elemento en el arbol
 * @param ele elemento a borrar
 * @return resultado del borrado
 */
template<typename T>
bool ABB<T>::eliminar(const T &ele) {
    NodoA<T> *tmp ;
    if (this->buscar(ele)) {
        tmp=this->borraDato(ele, tmp);
        return true;
    }
    return false;
}

/**
 * Calcula el numero de elementos del arbol
 * @return
 */
template<typename T>
int ABB<T>::numElementos() {
    std::vector<NodoA<T> *> tmp = this->anchura(raiz);
    return (int) tmp.size();
}

/**
 * Calcula la altura maxima del arbol
 * @return
 */
template<typename T>
int ABB<T>::altura() {
    int altura = 1;
    std::vector<NodoA<T> *> tmp = this->anchura(raiz);
    NodoA<T> *minimo = tmp[tmp.size() - 1];
    NodoA<T> *actual = minimo;
    while (actual != raiz) {
        actual = this->buscaPadre(actual);
        ++altura;
    }

    return altura;
}

/**
 * funcion auxiliar pasa el arbol a un vector en modo anchura
 * @param p
 * @return vector con el recorrido en anchura
 */
template<typename T>
std::vector<NodoA<T> *> ABB<T>::anchura(NodoA<T> *p) {
    std::vector<NodoA<T> *> tmp;
    NodoA<T> *actual = p;
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
    return tmp;
}

/**
 * devuelve el numero de hojas del arbol
 * @return
 */
template<typename T>
int ABB<T>::numHojas() {
    int hojas = 0;
    NodoA<T> *aux;
    std::vector<NodoA<T> *> tmp = this->anchura(raiz);
    for (int i = 0; i < tmp.size(); ++i) {
        aux = tmp[i];
        if (!aux->tieneDerecha() && !aux->tieneIzquierda()) {
            ++hojas;
        }
    }
    return hojas;
}

/**
 * borra el hijo mas a la izquierda del NodoA que se le indica
 * @param p NodoA de inicio
 * @return NodoA borrado
 */
template<typename T>
NodoA<T> *ABB<T>::borraMin(NodoA<T> *p) {
    NodoA<T> *tmp = p;
    while (p->tieneIzquierda()) {
        tmp = p->getIzquierda();
    }
    if (tmp != 0) {
        this->borraDato(tmp->getDato(), tmp);
    }
    return tmp;
}


template<typename T>
ABB<T>::~ABB() {
    this->borraDato(raiz->getDato(),raiz);
}


#endif //UNTITLED_ABB_H
