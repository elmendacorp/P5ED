//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_GITCODE_H
#define CPPAPPLICATION_2_GITCODE_H

#include "Fichero.h"
#include "Commit.h"
#include "fecha.h"
#include "vDinamico.h"
#include "Abb.h"
#include "Lista.h"

class Gitcode {
private:
    class refCommit {
    public:
        std::string codCommit;
        IteradorL<Commit> itc;
        refCommit(){}
        refCommit(const std::string &cod,const IteradorL<Commit> &it) :codCommit(cod),itc(it){}
        refCommit(const refCommit &orig): codCommit(orig.codCommit),itc(orig.itc){}
        bool operator <(const refCommit &orig){return codCommit<orig.codCommit;}
        bool operator >(const refCommit &orig){return codCommit>orig.codCommit;}
    };


    ABB<refCommit> ABBbuscar;
    Lista<Commit> commits;
    vDinamico<Fichero *> ficheros;
public:
    /**
     * Busca un commit por su  V1
     * @param commi
     * @return
     */
    Commit getCommit(std::string &commi);


    vDinamico<Commit*> getCommitFechas(const Fecha &inicio, const Fecha &fin);

    vDinamico<Commit*> getCommitFichero(std::string fichero);

    Gitcode(const std::string &fich, const std::string &commi);

    void eliminaFichero(std::string &fichero);

    void nuevoCommit(Commit &orig);

    bool borraCommit(const std::string &codigo);

    std::string getStatus();

};


#endif //CPPAPPLICATION_2_GITCODE_H
