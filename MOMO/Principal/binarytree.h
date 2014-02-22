#include <QString>
#include "binarytreenode.h"
#include <Simbolos.h>

#ifndef BINARYTREE_H
#define BINARYTREE_H

class LBinaryTree
{
public:
    LBinaryTree(BinaryTreeNode *nodo);
    LBinaryTree();
    QString getID(){return ID;}
    BinaryTreeNode *getFirst(){return firstNode;}
    void setID(QString id);
    void setFirst(BinaryTreeNode *binNod);
    BinaryTreeNode * unir (BinaryTreeNode * nuevo);

private:
    BinaryTreeNode *firstNode;
    QString ID;
};

#endif // BINARYTREE_H
