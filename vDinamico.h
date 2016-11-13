/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vDinamico.h
 * Author: Fran
 *
 * Created on 1 de octubre de 2016, 17:44
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <stdexcept>
#include <cmath>

template<typename T>
class vDinamico {
public:
    vDinamico();

    vDinamico(unsigned tam, const T &dato);

    vDinamico(const vDinamico<T> &orig);

    vDinamico(const vDinamico<T> &orig, unsigned inicio, unsigned fin);

    T lee(unsigned pos);

    void escribe(unsigned pos, T &dato);


    /**
     * COnstructor de copia
     * @param orig
     * @return 
     */
    vDinamico<T> &operator=(const vDinamico<T> &orig) {
        if (orig.tamal > tamaf) {
            tamaf = orig.tamaf;
            delete[] v;
            v = new T[tamaf];
        }
        tamal = orig.tamal;
        for (unsigned i = 0; i < tamal; ++i) {
            v[i] = orig.v[i];
        }
    }

    /**
     * operador cochete
     * @param pos
     * @return 
     */
    T &operator[](unsigned pos);

    void inserta(unsigned pos, T &dato);

    T &elimina(unsigned pos);

    void aumenta(T &dato);

    T disminuye();

    unsigned tama() {
        return tamal;
    }


    T busca(const T &dato);

    virtual ~vDinamico();

private:
    int tamal, tamaf;
    T *v;
};

/**
 * constructor por defecto
 */
template<typename T>
vDinamico<T>::vDinamico() {
    tamal = 0;
    tamaf = 1;
    v = new T[tamaf];
}

/**
 * constructor con valot por defecto
 * @param tam
 * @param dato
 */
template<typename T>
vDinamico<T>::vDinamico(unsigned tam, const T &dato) {
    tamaf = pow(2, ((unsigned) log2(tam)) + 1);
    v = new T[tamaf];
    tamal = 0;
    for (unsigned i = 0; i < tamaf; ++i) {
        v[i] = dato;
    }
}

/**
 * constructor de copia
 * @param orig
 */
template<typename T>
vDinamico<T>::vDinamico(const vDinamico<T> &orig) {
    if (tamaf < orig.tamal) {
        tamaf = orig.tamaf;
    }
    delete[] v;
    v = new T[tamaf];
    tamal = orig.tamal;
    for (unsigned i = 0; i < orig.tamal; ++i) {
        v[i] = orig.v[i];
    }
}

/**
 * constructor de copia por rango
 * @param orig
 * @param inicio
 * @param fin
 */
template<typename T>
vDinamico<T>::vDinamico(const vDinamico<T> &orig, unsigned inicio, unsigned fin) {
    if (inicio < 0 || inicio > tamal || fin < 0 || fin > tamal || inicio > fin) {
        throw (std::out_of_range("Fuera de rango"));
    }
    if (tamaf < (fin - inicio)) {
        tamaf = pow(2, ((unsigned) log2((fin - inicio))) + 1);
        delete[] v;
        v = new T[tamaf];
    }
    tamal = fin - inicio;
    for (unsigned i = 0; i < (fin - inicio); ++i) {
        v[i] = orig.v[inicio + i];
    }
}

/**
 * insercion de un elemento en mitad del vector
 * @param pos
 * @param dato
 */
template<typename T>
void vDinamico<T>::inserta(unsigned pos, T &dato) {
    if (pos > tamal || pos < 0) {
        throw std::out_of_range("Fuera de rango");
    }
    if (tamal == tamaf - 1) {
        vDinamico<T> temp(*this);
        tamaf *= 2;
        delete[] v;
        v= new T [tamaf];
        v= temp.v;

    }
    ++tamal;
    for (unsigned i = tamal - 1; i < pos; --i) {
        v[i] = v[i - 1];
    }
    v[pos] = dato;
}

/**
 * insercion de un elemento al final del vector
 * @param dato
 */
template<typename T>
void vDinamico<T>::aumenta(T &dato) {
    if (tamal == tamaf) {
        vDinamico<T> temp;
        for (unsigned i = 0; i < temp.tamal; ++i) {
            temp.v[i] = v[i];
        }
        tamaf *= 2;
        delete[] v;
        v = new T[tamaf];
        for (unsigned i = 0; i < temp.tamal; ++i) {
            v[i] = temp.v[i];
        }
    }
    v[tamal] = dato;
    ++tamal;

}

/**
 * eliminacion del elemento en la posicion iesima
 * @param pos
 * @return 
 */
template<typename T>
T &vDinamico<T>::elimina(unsigned pos) {
    if (pos > tamal || pos < 0) {
        throw std::out_of_range("Fuera de rango");
    }
    T temp = v[pos];
    for (unsigned i = pos; pos < tamal; ++i) {
        v[i] = v[i + 1];
    }
    --tamal;
    return temp;
}

template<typename T>
T &vDinamico<T>::operator[](unsigned pos) {
    if (pos > tamal) {
        throw std::out_of_range("Fuera de rango");
    }
    return v[pos];
}

/**
 * Destructor de la clase
 */
template<typename T>
vDinamico<T>::~vDinamico() {
    delete[] v;
}

/**
     * Devuelve el objeto en la posicion iesima
     * @param pos
     * @return
     */
template<typename T>
T vDinamico<T>::lee(unsigned pos) {
    if (pos > tamal) {
        throw std::out_of_range("Fuera de rango");
    }
    return v[pos];
}

/**
     * Sobreescribir una posicion existente en el vector logico
     * @param pos
     * @param dato
     */
template<typename T>
void vDinamico<T>::escribe(unsigned pos, T &dato) {
    if (pos > tamal) {
        throw std::out_of_range("Fuera de rango");
    }
    v[pos] = dato;
}

template<typename T>
T vDinamico<T>::busca(const T &dato) {
    for(unsigned i=0;i<tamal;++i){
        if(v[i]== dato){
            return v[i];
        }
    }
}

#endif /* VDINAMICO_H */

