#ifndef ESTRUCTURAAUXILIARCNF_H
#define ESTRUCTURAAUXILIARCNF_H
#include "binarytree.h"

class EstructuraAuxiliarCNF
{
public:
    EstructuraAuxiliarCNF();
    EstructuraAuxiliarCNF(BinaryTreeNode * ac, LBinaryTree pr);
    void setPrim(LBinaryTree pr);
    void setAct(BinaryTreeNode * ac);
    BinaryTreeNode * getACtual();
    LBinaryTree getPrimero();
private:
    BinaryTreeNode * actual;
    LBinaryTree primero;
};

#endif // ESTRUCTURAAUXILIARCNF_H
