#include "parser.h"
#include <QString>
#include <Simbolos.h>

#include <iostream>
using namespace std;

int parentesis = 0;
bool parentesisAbrir = true;
bool parentesisCerrar = false;
bool unarios = true;
bool binarios = false;
bool letra = true;
bool fin = false;

parser::parser()
{
}

bool parser::comprobarParser(QString formula){
    parentesis = 0;
    parentesisAbrir = true;
    parentesisCerrar = false;
    unarios = true;
    binarios = false;
    letra = true;
    fin = false;

    return comprobarParserInterno(formula);
}

bool parser::comprobarParserInterno(QString formula){
    if (formula.length()==0){
        return (fin && parentesis == 0);
    } else if (formula.at(0) == '('){
        if (parentesisAbrir){
            parentesis++;
            parentesisAbrir = true;
            parentesisCerrar = true;
            unarios = true;
            binarios = false;
            letra = true;
            fin = false;
            return (comprobarParserInterno(formula.right(formula.length()-1)));
        } else return false;
    } else if (formula.at(0) == ')'){
        if (parentesisCerrar && parentesis>0){
            parentesis--;
            parentesisAbrir = false;
            parentesisCerrar = true;
            unarios = false;
            binarios = true;
            letra = false;
            fin = true;
            return (comprobarParserInterno(formula.right(formula.length()-1)));
        } else return false;
    } else if (formula.at(0) == QString(SimbNOT) || formula.at(0) == QString(SimbEVENTUALLY) || formula.at(0) == QString(SimbNEXT) || formula.at(0) == QString(SimbALWAYS)){
        if (unarios){
            parentesisAbrir = true;
            parentesisCerrar = false;
            unarios = true;
            binarios = false;
            letra = true;
            fin = false;
            return (comprobarParserInterno(formula.right(formula.length()-1)));
        } else return false;
    } else if (formula.at(0) == QString(SimbAND) || formula.at(0) == QString(SimbOR) || formula.at(0) == QString(SimbRELEASE) || formula.at(0) == QString(SimbUNTIL) || formula.at(0) == QString(SimbINPDER)  || formula.at(0) == QString(SimbSSS)){
        if (binarios){
            parentesisAbrir = true;
            parentesisCerrar = false;
            unarios = true;
            binarios = false;
            letra = true;
            fin = false;
            return (comprobarParserInterno(formula.right(formula.length()-1)));
        } else return false;
    } else if (formula.at(0) >= 'a' && formula.at(0) <= 'z'){
        if (letra) {
            parentesisAbrir = false;
            parentesisCerrar = true;
            unarios = false;
            binarios = true;
            letra = false;
            fin = true;
            return (comprobarParserInterno(formula.right(formula.length()-1)));
        } else return false;
    }
    return false;
}
