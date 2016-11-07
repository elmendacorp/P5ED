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

    Nodo<T> *borraDato(T &ele, Nodo<T> *&p);

    Nodo<T> *buscaPadre(Nodo<T> *&p);

    Nodo<T> *insertarDato(T &ele, Nodo<T> *p);

    Nodo<T> *borraMin(Nodo<T> *&p);

    void preorden(Nodo<T> *p, int nivel);

    void inorden(Nodo<T> *p, int nivel);

    void postorden(Nodo<T> *p, int nivel);

    std::vector<Nodo<T>*> anchura(Nodo<T> * &p);


public:
    ABB();

    ABB(const ABB<T> &orig);

    bool buscar(T &ele, Nodo<T>* &resultado);

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

    if (raiz == 0) {
        Nodo<T> *tmp = new Nodo<T>(); //En este caso es el de que la raiz es nula
        tmp->setDato(dato);
        raiz=tmp;
        return tmp;
    }
    Nodo<T> *actual = raiz;
    bool insertado = false;
    while (!insertado) {
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
            } else if (actual->getDato() > dato) {
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
 * @param resultado Nodo de vuelta
 * @return true si se ha encontrado, false en otro caso
 */
template<typename T>
bool ABB<T>::buscar(T &ele, Nodo<T>* &resultado) {
    resultado = buscaClave(ele);
    return (resultado != 0);
}

/**
 * Construcctor de copia, usa un recorrido en anchura y luego una insercion ordenada para mantener la estructura
 * @param orig
 * @return
 */
template<typename T>
ABB<T>::ABB(const ABB &orig) {
    if (orig.raiz != 0) {
        *this = ABB<T>();
        Nodo<T> *actual = orig.raiz;
        std::vector<Nodo<T> *> tmp = this->anchura(actual);
        for (int i = 0; i < tmp.size(); ++i) {
            this->inserta(tmp[i]);
        }
    }
}

/**
 * Funcion auxiliar que busca el padre un nodo, se supone el nodo existente
 * @param p Nodo a buscar
 * @return
 */
template<typename T>
Nodo<T> *ABB<T>::buscaPadre(Nodo<T> *&p) {
    Nodo<T> *tmp = raiz;
    bool encontrado = false;
    if (p == raiz) {
        return 0; //en el caso de que la raiz sea el nodo buscado no tiene padre
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
 * @return Nodo del elemento buscado
 */
template<typename T>
Nodo<T> *ABB<T>::borraDato(T &ele, Nodo<T> *&p) {
    Nodo<T> *actual = this->buscaClave(ele);
    std::vector<Nodo<T> *> tmp= this->anchura(actual);
    for (int i = tmp.size() - 1; i >= 0; --i) {//borrado completo del subarbol
        actual = tmp[i];
        if (actual->tieneDerecha()) {
            delete actual->getDerecha();
        }
        if (actual->tieneIzquierda()) {
            delete actual->getIzquierda();
        }
    }

    Nodo<T> *padre = buscaPadre(p);//aqui elimino la referencia del padre al nodo que borramos
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
bool ABB<T>::eliminar(T &ele) {
    Nodo<T>* tmp;
    if(this->buscar(ele,tmp)){
        this->borraDato(ele,tmp);
        delete tmp;
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
    std::vector<Nodo<T> *> tmp=this->anchura(raiz);
    return (int)tmp.size();
}
/**
 * Calcula la altura maxima del arbol
 * @return
 */
template<typename T>
int ABB<T>::altura() {
    int altura=0;
    std::vector<Nodo<T>*> tmp=this->anchura(raiz);
    Nodo<T> * minimo=tmp[tmp.size()-1];
    Nodo<T> * actual=minimo;
    while(actual!=raiz){
        actual=this->buscaPadre(actual);
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
std::vector<Nodo<T> *>  ABB<T>::anchura(Nodo<T> *&p) {
    std::vector<Nodo<T> *> tmp;
    Nodo<T> *actual = p;
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
    int hojas=0;
    Nodo<T>* aux;
    std::vector<Nodo<T>*> tmp=this->anchura(raiz);
    for(int i=0;i<tmp.size();++i){
        aux=tmp[i];
        if(!aux->tieneDerecha()&&!aux->tieneIzquierda()){
            ++hojas;
        }
    }
    return hojas;
}
template<typename T>
Nodo<T> *ABB::borraMin(Nodo<T> *&p) {
    Nodo<T> *tmp=p;
    while(p->tieneIzquierda()){
        tmp=p->getIzquierda();
    }
    if(tmp!=0){
        this->borraDato(tmp->getDato(),tmp);
    }
    return tmp;
}


#endif //UNTITLED_ABB_H
