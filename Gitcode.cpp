//
// Created by Fran on 25/10/2016.
//

#include "Gitcode.h"
#include <fstream>
#include <iostream>




Commit Gitcode::getCommit(std::string &commi) {
    Iterador<Commit> ite = commits.iteradorInicio();
    while (ite != commits.iteradorFin()) {
        Commit tm = ite.dato();
        if (tm.getCodigo() == commi) {
            return ite.dato();
        }
        ite.siguiente();

    }

}

vDinamico<Commit*> Gitcode::getCommitFechas(const Fecha &inicio, const Fecha &fin) {
    vDinamico<Commit*> tempo;
    Iterador<Commit> ite = commits.iteradorInicio();
    while (ite != commits.iteradorFin()) {
        if (ite.dato().getMarcaDeTiempo() < fin && ite.dato().getMarcaDeTiempo() > inicio) {
            Commit* t = &ite.dato();
            tempo.aumenta(t);
        }
        ite.siguiente();
    }

    return tempo;
}

vDinamico<Commit*> Gitcode::getCommitFichero(std::string fichero) {
    vDinamico<Commit*> temporal;
    Iterador<Commit> tempo = commits.iteradorInicio();
    while (tempo != commits.iteradorFin()) {
        Fichero *t = tempo.dato().buscaFichero(fichero);
        if (t->getTamaBytes() != 0) {
            Commit *d = &tempo.dato();
            temporal.aumenta(d);
        }
        tempo.siguiente();
    }

    return temporal;
}

Gitcode::Gitcode(const std::string &fich, const std::string &commi) {
    std::string lineaActual;
    try {
        std::ifstream inputStream;
        inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        inputStream.open(fich);

        inputStream >> lineaActual;

        while (!inputStream.eof()) {
            Fichero *f;
            std::getline(inputStream >> ws, lineaActual);

            auto pos = lineaActual.find(';');
            auto ruta = lineaActual.substr(0, pos);
            auto tama = lineaActual.substr(pos + 1, ruta.length() - 1);

            pos = ruta.find_last_of('/');
            auto ubicacion = ruta.substr(0, pos + 1);
            auto nombre = ruta.substr(pos + 1, ruta.length());
            auto tamaBytes = std::stoi(tama);
            f =new Fichero(nombre, ubicacion, tamaBytes);
            ficheros.aumenta(f);



        }
        inputStream.close();
    } catch (exception &e) {
        std::cerr << "Excepcion leyendo el fichero: " << e.what() << std::endl;
    }

    int ref;
    try {
        std::ifstream inputStream;

        inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        inputStream.open(commi);
        Commit *MiCommit;
        inputStream >> lineaActual;

        while (!inputStream.eof()) {
            std::getline(inputStream >> ws, lineaActual);

            auto pos = lineaActual.find_last_of(';');
            auto indice = lineaActual.substr(pos + 1, lineaActual.size());
            auto substr1 = lineaActual.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto mensaje = lineaActual.substr(pos + 1, substr1.size());
            substr1 = substr1.substr(0, pos);
            pos = substr1.find_last_of(';');
            auto marcaTiempo = substr1.substr(pos + 1, substr1.size());

            Fecha fch = Fecha();
            fch.anadirAnios(std::stoi(marcaTiempo.substr(0, 4)));
            fch.anadirMeses(std::stoi(marcaTiempo.substr(4, 6)));
            fch.anadirDias(std::stoi(marcaTiempo.substr(6, 8)));
            fch.anadirHoras(std::stoi(marcaTiempo.substr(8, 10)));
            fch.anadirMin(std::stoi(marcaTiempo.substr(10, 12)));

            auto codigo = substr1.substr(0, pos);
            Commit inserta = Commit(codigo, fch, mensaje);

            pos = 0;
            indice = indice.substr(0, (indice.size() - 1));
            while (pos != indice.find_first_of(',')) {
                pos = indice.find_last_of(',');
                ref = std::stoi(indice.substr(pos + 1, substr1.size()));
                inserta.anadeFichero(ficheros[ref]);
                indice = indice.substr(0, pos);
            }
            Iterador<Commit> in=commits.iteradorFin();
            commits.insertar(in,inserta);
            refCommit inserta2=refCommit(inserta.getCodigo(),commits.iteradorFin());
            ABBbuscar.insertar(inserta2);




        }
        inputStream.close();
    } catch (exception &e) {
        std::cerr << "Excepcion leyendo el fichero: " << e.what() << std::endl;
    }
}

void Gitcode::eliminaFichero(std::string &fichero) {
    Iterador<Commit> miIt = commits.iteradorInicio();
    while (miIt != commits.iteradorFin()) {
        miIt.dato().borraFichero(fichero);
        miIt.siguiente();
    }
}

Gitcode::~Gitcode() {
    ficheros.~vDinamico();
    commits.~ListaDEnlazada();

}

void Gitcode::nuevoCommit(Commit &orig) {
    refCommit b=refCommit(orig.getCodigo(),commits.iteradorInicio());
    if(!ABBbuscar.buscar(b)){
        commits.insertar(b.itc,orig);
        ABBbuscar.insertar(b);
    }

}

bool Gitcode::borraCommit(const std::string &codigo) {
    refCommit b=refCommit(codigo,commits.iteradorInicio());
    if(ABBbuscar.buscar(b)){

    }

}

std::string Gitcode::getStatus() {
    std::string mistr;
    mistr+= (char)ABBbuscar.altura();
    mistr+= (char)ABBbuscar.numElementos();
    mistr+= (char)ABBbuscar.numHojas();
    return mistr;
}

