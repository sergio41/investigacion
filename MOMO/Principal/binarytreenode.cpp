#include "binarytreenode.h"
#include "mainwindow.h"
using namespace std;
#include <iostream>
#include <QString>

BinaryTreeNode::BinaryTreeNode(QString symbol)
{   m_Char = symbol;
    m_Depth = 0;
    m_pParentNode = NULL;
    m_pLeftChild = NULL;
    m_pRightChild = NULL;
}

void BinaryTreeNode::setDepth(int depth){
    m_Depth = depth;
}

void BinaryTreeNode::setChar(QString symbol){
    m_Char = symbol;
}

void BinaryTreeNode::SetLeftChild(BinaryTreeNode *pNode){
    m_pLeftChild = pNode;
}

void BinaryTreeNode::SetRightChild(BinaryTreeNode *pNode){
    m_pRightChild = pNode;
}

void BinaryTreeNode::SetParent(BinaryTreeNode *pNode){
    m_pParentNode = pNode;
}

int BinaryTreeNode::nHijos(){
    if(m_pRightChild==NULL){
        if(m_pLeftChild==NULL)
            return 0;
        return 1;
    }
    return 2;
}

/*void BinaryTreeNode::imprimirNodo(MainWindow *ventana){
    ventana->imprimir(m_Char);
    //cout << m_Char.toUtf8().constData() << endl;
    if(m_pLeftChild!=NULL){
        ventana->imprimir("izq");
        GetLeftChild()->imprimirNodo(ventana);
    }
    if(m_pRightChild!=NULL){
        ventana->imprimir("der");
        GetRightChild()->imprimirNodo(ventana);
    }
}*/
