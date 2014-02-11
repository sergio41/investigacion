#ifndef ALMACENADOR_H
#define ALMACENADOR_H

#include <QString>
#include "binarytreenode.h"
#include "binarytree.h"


class almacenador
{
public:
    almacenador();
    LBinaryTree almacenar(QString formula);
    LBinaryTree nnf(LBinaryTree arbol);
    LBinaryTree dtnf(LBinaryTree arbol);

private:
    void almacenarInterno(QString formula,BinaryTreeNode *nodoActual);
    int siguienteOp(QString formula);
    QString parentesisInnecesarios(QString formula);
    BinaryTreeNode *nnfInterno(BinaryTreeNode *nodo);
    BinaryTreeNode *dtnfInterno(BinaryTreeNode *nodo);
    bool comparanodos(BinaryTreeNode * nodo1, BinaryTreeNode * nodo2);
};

#endif // ALMACENADOR_H