#include "estructuraauxiliarcnf.h"

EstructuraAuxiliarCNF::EstructuraAuxiliarCNF(BinaryTreeNode * ac, LBinaryTree pr)
{
    actual=ac;
    primero=pr;
}

EstructuraAuxiliarCNF::EstructuraAuxiliarCNF()
{
}

void EstructuraAuxiliarCNF::setPrim(LBinaryTree pr){
    primero=pr;
}
void EstructuraAuxiliarCNF::setAct(BinaryTreeNode * ac){
    actual=ac;
}

BinaryTreeNode * EstructuraAuxiliarCNF::getACtual(){
    return actual;
}

LBinaryTree EstructuraAuxiliarCNF::getPrimero(){
    return primero;
}
