#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
#include <QString>

class BinaryTreeNode
{
public:
        BinaryTreeNode(QString symbol);
        void setDepth(int depth);
        int GetDepth(){return (m_Depth);}
        BinaryTreeNode * GetLeftChild(){return(m_pLeftChild);}
        BinaryTreeNode * GetRightChild(){return(m_pRightChild);}
        void SetLeftChild(BinaryTreeNode * pNode);
        void SetRightChild(BinaryTreeNode * pNode);
        BinaryTreeNode * GetParent(){return(m_pParentNode);}
        void SetParent(BinaryTreeNode * pNode);
        void setChar(QString symbol);
        QString GetChar(){return (m_Char);}
        //void imprimir();
        int nHijos();

private:
        BinaryTreeNode * m_pParentNode;
        int m_Depth; //this node's depth in the BST
        QString m_Char;
        BinaryTreeNode *m_pLeftChild; //node's left child
        BinaryTreeNode *m_pRightChild; //node's right child
};

#endif // BINARYTREENODE_H
