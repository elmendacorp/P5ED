//
// Created by Fran on 25/10/2016.
//

#ifndef CPPAPPLICATION_2_GITCODE_H
#define CPPAPPLICATION_2_GITCODE_H

#include "Fichero.h"
#include "Commit.h"
#include "fecha.h"
#include <list>
#include <vector>
#include "Abb.h"
#include "ListaDEnlazada2.h"

class Gitcode {
private:
    class refCommit {
    public:
        std::string codCommit;
        list<Commit>::iterator itc;
        refCommit(const std::string &cod,const list<Commit>::iterator &it) :codCommit(cod),itc(it){}
        refCommit(const refCommit &orig): codCommit(orig.codCommit),itc(orig.itc){}
    };

    list<Commit> commits;
    vector<Fichero *> ficheros;
    std::string fileFichero;
    std::string fileCommits;
    Fecha *fecha;
public:
    Commit getCommit(std::string &commi);

    vector<Commit> getCommitFechas(const Fecha &inicio, const Fecha &fin);

    vector<Commit> getCommitFichero(std::string fichero);

    Gitcode(const std::string &fich, const std::string &commi);

    void eliminaFichero(std::string &fichero);

    ~Gitcode();
};


#endif //CPPAPPLICATION_2_GITCODE_H
