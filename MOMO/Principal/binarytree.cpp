#include "binarytree.h"
#include <QString>
using namespace std;


LBinaryTree::LBinaryTree(BinaryTreeNode *nodo)
{
    ID="identificador";
    firstNode=nodo;
}
LBinaryTree::LBinaryTree()
{
}
void LBinaryTree::setID(QString id){
    ID=id;
}
void LBinaryTree::setFirst(BinaryTreeNode *binNod){
    firstNode=binNod;
}

BinaryTreeNode * LBinaryTree::unir(BinaryTreeNode * nuevo){
    BinaryTreeNode * nuevoPrimero = new BinaryTreeNode(SimbAND);
    nuevoPrimero->SetLeftChild(firstNode);
    nuevoPrimero->SetRightChild(nuevo);
    setFirst(nuevoPrimero);
    return firstNode;
}
