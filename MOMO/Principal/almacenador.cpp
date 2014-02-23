#include "almacenador.h"
#include <QString>
#include <Simbolos.h>
#include <iostream>
#include <QtDebug>
#include "mainwindow.h"


generadorVariables gen;
using namespace std;

almacenador::almacenador(){
    gen = generadorVariables();
}

LBinaryTree almacenador::almacenar(QString formula){
    formula = parentesisInnecesarios(formula);
    qDebug() << formula;
    int pos = siguienteOp(formula);
    LBinaryTree x;
    if(pos == -1){
        if(formula.at(0)==QString(SimbNOT)
                ||formula.at(0)==QString(SimbEVENTUALLY)
                ||formula.at(0)==QString(SimbNEXT)
                ||formula.at(0)==QString(SimbALWAYS)){
            BinaryTreeNode *nodoPadre = new BinaryTreeNode(formula.at(0));
            x = LBinaryTree(nodoPadre);
            QString izq = formula.right(formula.size()-1);
            BinaryTreeNode *nodoIzq = new BinaryTreeNode(izq);
            nodoPadre->SetLeftChild(nodoIzq);
            almacenarInterno(izq, nodoIzq);
        }
        else{
            BinaryTreeNode *nodoPadre = new BinaryTreeNode(formula);
            x = LBinaryTree(nodoPadre);
        }
    }else if(pos == -2){
        BinaryTreeNode *nodoPadre = new BinaryTreeNode("");
        x = LBinaryTree(nodoPadre);
    }else{
        BinaryTreeNode *nodoPadre = new BinaryTreeNode(formula.at(pos));
        x = LBinaryTree(nodoPadre);        
        QString izq = formula.left(pos);
        QString der = formula.right(formula.size()-1-pos);
        BinaryTreeNode *nodoIzq = new BinaryTreeNode(izq);
        BinaryTreeNode *nodoDer = new BinaryTreeNode(der);
        nodoPadre->SetLeftChild(nodoIzq);
        cout<< nodoPadre->GetLeftChild()->GetChar().toLocal8Bit().data()<< endl;
        nodoPadre->SetRightChild(nodoDer);
        almacenarInterno(izq, nodoIzq);
        almacenarInterno(der, nodoDer);
    }
    return x;
}

void almacenador::almacenarInterno(QString formula,BinaryTreeNode *nodoActual){
    formula = parentesisInnecesarios(formula);
    cout << "Esto es lo que voy a dividir:" << formula.toLocal8Bit().data() << endl;
    int pos = siguienteOp(formula);
    if(pos==-1){
        if(formula.at(0)==QString(SimbNOT)
                ||formula.at(0)==QString(SimbEVENTUALLY)
                ||formula.at(0)==QString(SimbNEXT)
                ||formula.at(0)==QString(SimbALWAYS)){
            nodoActual->setChar(formula.at(0));
            QString izq = formula.right(formula.size()-1);
            BinaryTreeNode *nodoIzq = new BinaryTreeNode(izq);
            nodoActual->SetLeftChild(nodoIzq);
            almacenarInterno(izq, nodoIzq);
        }
        else{
            nodoActual->setChar(formula);
        }
    }else if(pos > 0){
        nodoActual->setChar(formula.at(pos));
        QString izq = formula.left(pos);
        cout << "Izquierda:" << izq.toLocal8Bit().data() << endl;
        QString der = formula.right(formula.size()-1-pos);
        cout << "Derecha:" << der.toLocal8Bit().data() << endl;
        BinaryTreeNode *nodoIzq = new BinaryTreeNode(izq);
        BinaryTreeNode *nodoDer = new BinaryTreeNode(der);
        nodoActual->SetLeftChild(nodoIzq);
        nodoActual->SetRightChild(nodoDer);
        almacenarInterno(izq, nodoIzq);
        almacenarInterno(der, nodoDer);
    }
}

LBinaryTree almacenador::nnf(LBinaryTree arbol){
    BinaryTreeNode * primero = arbol.getFirst();
    arbol.setFirst(nnfInterno(primero));
    return arbol;
}

BinaryTreeNode * almacenador::nnfInterno(BinaryTreeNode *nodo){
    //cout<<nodo->GetChar().toLocal8Bit().data()<<endl;
    if(nodo->GetChar()==QString(SimbNOT)){
        nodo->SetLeftChild(nnfInterno(nodo->GetLeftChild()));
        cout<<"Entro"<<endl;
        if(nodo->GetLeftChild()->GetChar()==QString(SimbNOT)){
            return nnfInterno(nodo->GetLeftChild()->GetLeftChild());
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbNEXT)){
            BinaryTreeNode * nuevo= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * aux = nodo->GetLeftChild();
            nodo->SetLeftChild(nuevo);
            aux->SetLeftChild(nnfInterno(nodo));
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbEVENTUALLY)){
            BinaryTreeNode * nuevo= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * aux = nodo->GetLeftChild();
            nodo->SetLeftChild(nuevo);
            aux->SetLeftChild(nnfInterno(nodo));
            aux->setChar(SimbALWAYS);
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbALWAYS)){
            BinaryTreeNode * nuevo= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * aux = nodo->GetLeftChild();
            nodo->SetLeftChild(nuevo);
            aux->SetLeftChild(nnfInterno(nodo));
            aux->setChar(SimbEVENTUALLY);
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbAND)){
            BinaryTreeNode * derecha= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda);
            derechaNuev->SetLeftChild(derecha);
            aux->SetLeftChild(nnfInterno(izquierdaNuev));
            aux->SetRightChild(nnfInterno(derechaNuev));
            aux->setChar(SimbOR);
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbOR)){
            BinaryTreeNode * derecha= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda);
            derechaNuev->SetLeftChild(derecha);
            aux->SetLeftChild(nnfInterno(izquierdaNuev));
            aux->SetRightChild(nnfInterno(derechaNuev));
            aux->setChar(SimbAND);
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbRELEASE)){
            BinaryTreeNode * derecha= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda);
            derechaNuev->SetLeftChild(derecha);
            aux->SetLeftChild(nnfInterno(izquierdaNuev));
            aux->SetRightChild(nnfInterno(derechaNuev));
            aux->setChar(SimbUNTIL);
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbUNTIL)){
            BinaryTreeNode * derecha= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbNOT);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda);
            derechaNuev->SetLeftChild(derecha);
            aux->SetLeftChild(nnfInterno(izquierdaNuev));
            aux->SetRightChild(nnfInterno(derechaNuev));
            aux->setChar(SimbRELEASE);
            return aux;
        }else{
            cout<<"Entro"<<endl;
            cout<<nodo->GetLeftChild()->GetChar().toLocal8Bit().data()<<endl;
            nodo->SetLeftChild(nnfInterno(nodo->GetLeftChild()));
            return nodo;
        }
    }else{
        switch (nodo->nHijos()) {
        case 0:
            return nodo;
            break;
        case 1:
            nodo->SetLeftChild(nnfInterno(nodo->GetLeftChild()));
            return nodo;
            break;
        case 2:
            nodo->SetLeftChild(nnfInterno(nodo->GetLeftChild()));
            nodo->SetRightChild(nnfInterno(nodo->GetRightChild()));
            return nodo;
            break;
        default:
            return nodo;
            break;
        }
    }
}

LBinaryTree almacenador::dtnf(LBinaryTree arbol){
    BinaryTreeNode * primero = arbol.getFirst();
    arbol.setFirst(dtnfInterno(primero));
    return arbol;
}

BinaryTreeNode * almacenador::dtnfInterno(BinaryTreeNode *nodo){
    //cout<<nodo->GetChar().toLocal8Bit().data()<<endl;
    if(nodo->GetChar()==QString(SimbNEXT)){
        nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
        if(nodo->GetLeftChild()->GetChar()==QString(SimbAND)||nodo->GetLeftChild()->GetChar()==QString(SimbOR)){
            BinaryTreeNode * derecha= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbNEXT);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbNEXT);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda);
            derechaNuev->SetLeftChild(derecha);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else{
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            return nodo;
        }
    }else if(nodo->GetChar()==QString(SimbEVENTUALLY)){
        nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
        if(nodo->GetLeftChild()->GetChar()==QString(SimbOR)){
            BinaryTreeNode * derecha= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbEVENTUALLY);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbEVENTUALLY);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda);
            derechaNuev->SetLeftChild(derecha);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbEVENTUALLY)){
            return dtnfInterno(nodo->GetLeftChild());
        }else{
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            return nodo;
        }
    }else if(nodo->GetChar()==QString(SimbALWAYS)){
        nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
        if(nodo->GetLeftChild()->GetChar()==QString(SimbAND)){
            BinaryTreeNode * derecha= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbALWAYS);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbALWAYS);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda);
            derechaNuev->SetLeftChild(derecha);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbALWAYS)){
            return dtnfInterno(nodo->GetLeftChild());
        }else{
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            return nodo;
        }
    }else if(nodo->GetChar()==QString(SimbOR)){
        nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
        nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
        if(nodo->GetLeftChild()->GetChar()==QString(SimbAND)){
            BinaryTreeNode * izquierda2= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda1= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derecha= nodo->GetRightChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbOR);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbOR);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda1);
            izquierdaNuev->SetRightChild(derecha);
            derechaNuev->SetLeftChild(izquierda2);
            derechaNuev->SetRightChild(derecha);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else if(nodo->GetRightChild()->GetChar()==QString(SimbAND)){
            BinaryTreeNode * izquierda= nodo->GetLeftChild();
            BinaryTreeNode * derecha1= nodo->GetRightChild()->GetLeftChild();
            BinaryTreeNode * derecha2= nodo->GetRightChild()->GetRightChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbOR);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbOR);
            BinaryTreeNode * aux = nodo->GetRightChild();
            izquierdaNuev->SetLeftChild(izquierda);
            izquierdaNuev->SetRightChild(derecha1);
            derechaNuev->SetLeftChild(izquierda);
            derechaNuev->SetRightChild(derecha2);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else{
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
            return nodo;
        }
    }else if(nodo->GetChar()==QString(SimbUNTIL)){
        nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
        nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
        if(nodo->GetRightChild()->GetChar()==QString(SimbOR)){
            BinaryTreeNode * izquierda= nodo->GetLeftChild();
            BinaryTreeNode * derecha1= nodo->GetRightChild()->GetLeftChild();
            BinaryTreeNode * derecha2= nodo->GetRightChild()->GetRightChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbUNTIL);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbUNTIL);
            BinaryTreeNode * aux = nodo->GetRightChild();
            izquierdaNuev->SetLeftChild(izquierda);
            izquierdaNuev->SetRightChild(derecha1);
            derechaNuev->SetLeftChild(izquierda);
            derechaNuev->SetRightChild(derecha2);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbAND)){
            BinaryTreeNode * izquierda2= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda1= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derecha= nodo->GetRightChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbUNTIL);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbUNTIL);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda1);
            izquierdaNuev->SetRightChild(derecha);
            derechaNuev->SetLeftChild(izquierda2);
            derechaNuev->SetRightChild(derecha);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else if(nodo->GetRightChild()->GetChar()==QString(SimbUNTIL)){
            if(comparanodos(nodo->GetLeftChild(), nodo->GetRightChild()->GetLeftChild())){
                BinaryTreeNode * izquierda= nodo->GetLeftChild();
                BinaryTreeNode * derecha= nodo->GetRightChild()->GetRightChild();
                nodo->SetLeftChild(dtnfInterno(izquierda));
                nodo->SetRightChild(dtnfInterno(derecha));
                return nodo;
            }else{
                nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
                nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
                return nodo;
            }
        }else{
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
            return nodo;
        }
    }else if(nodo->GetChar()==QString(SimbRELEASE)){
        nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
        nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
        if(nodo->GetRightChild()->GetChar()==QString(SimbAND)){
            BinaryTreeNode * izquierda= nodo->GetLeftChild();
            BinaryTreeNode * derecha1= nodo->GetRightChild()->GetLeftChild();
            BinaryTreeNode * derecha2= nodo->GetRightChild()->GetRightChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbRELEASE);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbRELEASE);
            BinaryTreeNode * aux = nodo->GetRightChild();
            izquierdaNuev->SetLeftChild(izquierda);
            izquierdaNuev->SetRightChild(derecha1);
            derechaNuev->SetLeftChild(izquierda);
            derechaNuev->SetRightChild(derecha2);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else if(nodo->GetLeftChild()->GetChar()==QString(SimbOR)){
            BinaryTreeNode * izquierda2= nodo->GetLeftChild()->GetRightChild();
            BinaryTreeNode * izquierda1= nodo->GetLeftChild()->GetLeftChild();
            BinaryTreeNode * derecha= nodo->GetRightChild();
            BinaryTreeNode * derechaNuev= new BinaryTreeNode(SimbRELEASE);
            BinaryTreeNode * izquierdaNuev= new BinaryTreeNode(SimbRELEASE);
            BinaryTreeNode * aux = nodo->GetLeftChild();
            izquierdaNuev->SetLeftChild(izquierda1);
            izquierdaNuev->SetRightChild(derecha);
            derechaNuev->SetLeftChild(izquierda2);
            derechaNuev->SetRightChild(derecha);
            aux->SetLeftChild(dtnfInterno(izquierdaNuev));
            aux->SetRightChild(dtnfInterno(derechaNuev));
            return aux;
        }else if(nodo->GetRightChild()->GetChar()==QString(SimbRELEASE)){
            if(comparanodos(nodo->GetLeftChild(), nodo->GetRightChild()->GetLeftChild())){
                BinaryTreeNode * izquierda= nodo->GetLeftChild();
                BinaryTreeNode * derecha= nodo->GetRightChild()->GetRightChild();
                nodo->SetLeftChild(dtnfInterno(izquierda));
                nodo->SetRightChild(dtnfInterno(derecha));
                return nodo;
            }else{
                nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
                nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
                return nodo;
            }
        }else{
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
            return nodo;
        }
    }else{
        switch (nodo->nHijos()) {
        case 0:
            return nodo;
            break;
        case 1:
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            return nodo;
            break;
        case 2:
            nodo->SetLeftChild(dtnfInterno(nodo->GetLeftChild()));
            nodo->SetRightChild(dtnfInterno(nodo->GetRightChild()));
            return nodo;
            break;
        default:
            return nodo;
            break;
        }
    }
}

LBinaryTree almacenador::cnf(LBinaryTree arbol){
    BinaryTreeNode * primero = arbol.getFirst();
    arbol.setFirst(cnfInterno(primero, arbol).getPrimero().getFirst());
    return arbol;
}

EstructuraAuxiliarCNF almacenador::cnfInterno(BinaryTreeNode *nodo, LBinaryTree arbol){
    return cnfInterno2(nodo, arbol);
}

EstructuraAuxiliarCNF almacenador::cnfInterno2(BinaryTreeNode *nodo, LBinaryTree arbol){
    EstructuraAuxiliarCNF aux = EstructuraAuxiliarCNF();
    if(nodo->GetChar()==QString(SimbUNTIL) || nodo->GetChar()==QString(SimbRELEASE)){
        BinaryTreeNode * izq = nodo->GetLeftChild();
        BinaryTreeNode * der = nodo->GetRightChild();
        QString nuevaVar1 = gen.generarVariable();
        QString nuevaVar2 = gen.generarVariable();
        nodo->SetLeftChild(new BinaryTreeNode(nuevaVar1));
        nodo->SetRightChild(new BinaryTreeNode(nuevaVar2));
        BinaryTreeNode * nuevaForm1 = crearSubArbol(izq, nuevaVar1);
        nuevaForm1=nnfInterno(nuevaForm1);
        nuevaForm1=dtnfInterno(nuevaForm1);
        aux=cnfInterno2(nuevaForm1,arbol);
        arbol.setFirst(aux.getPrimero().unir(aux.getACtual()));
        BinaryTreeNode * nuevaForm2 = crearSubArbol(der, nuevaVar2);
        nuevaForm2=nnfInterno(nuevaForm2);
        nuevaForm2=dtnfInterno(nuevaForm2);
        aux=cnfInterno2(nuevaForm2,arbol);
        arbol.setFirst(aux.getPrimero().unir(aux.getACtual()));
        aux.setAct(nodo);
        aux.setPrim(arbol);
        return aux;
    }else if(nodo->GetChar()==QString(SimbALWAYS)&&nodo->GetLeftChild()->GetChar()==QString(SimbOR)&&
             (nodo->GetLeftChild()->GetLeftChild()->GetChar()==QString(SimbALWAYS)||nodo->GetLeftChild()->GetRightChild()->GetChar()==QString(SimbALWAYS))){
        if(nodo->GetLeftChild()->GetLeftChild()->GetChar()==QString(SimbALWAYS)){
            BinaryTreeNode * izq = nodo->GetLeftChild()->GetLeftChild()->GetLeftChild();
            QString nuevaVar1 = gen.generarVariable();
            nodo->GetLeftChild()->GetLeftChild()->SetLeftChild(new BinaryTreeNode(nuevaVar1));
            BinaryTreeNode * nuevaForm1 = crearSubArbol(izq, nuevaVar1);
            nuevaForm1=nnfInterno(nuevaForm1);
            nuevaForm1=dtnfInterno(nuevaForm1);
            aux=cnfInterno2(nuevaForm1->GetLeftChild(),arbol);
            nuevaForm1->SetLeftChild(aux.getACtual());
            arbol.setFirst(aux.getPrimero().unir(nuevaForm1));
            aux.setAct(nodo);
            aux.setPrim(arbol);
            return aux;
        }else{
            BinaryTreeNode * izq = nodo->GetLeftChild()->GetRightChild()->GetLeftChild();
            QString nuevaVar1 = gen.generarVariable();
            nodo->GetLeftChild()->GetRightChild()->SetLeftChild(new BinaryTreeNode(nuevaVar1));
            BinaryTreeNode * nuevaForm1 = crearSubArbol(izq, nuevaVar1);
            nuevaForm1=nnfInterno(nuevaForm1);
            nuevaForm1=dtnfInterno(nuevaForm1);
            aux=cnfInterno2(nuevaForm1->GetLeftChild(),arbol);
            nuevaForm1->SetLeftChild(aux.getACtual());
            arbol.setFirst(aux.getPrimero().unir(nuevaForm1));
            aux.setAct(nodo);
            aux.setPrim(arbol);
            return aux;
        }
    }else if(nodo->GetChar()==QString(SimbEVENTUALLY) || nodo->GetChar()==QString(SimbALWAYS)&& isDistributed(nodo->GetLeftChild())){
        BinaryTreeNode * izq = nodo->GetLeftChild();
        QString nuevaVar1 = gen.generarVariable();
        nodo->SetLeftChild(new BinaryTreeNode(nuevaVar1));
        BinaryTreeNode * nuevaForm1 = crearSubArbol(izq, nuevaVar1);
        nuevaForm1=nnfInterno(nuevaForm1);
        nuevaForm1=dtnfInterno(nuevaForm1);
        aux=cnfInterno2(nuevaForm1->GetLeftChild(),arbol);
        nuevaForm1->SetLeftChild(aux.getACtual());
        arbol.setFirst(aux.getPrimero().unir(nuevaForm1));
        aux.setAct(nodo);
        aux.setPrim(arbol);
        return aux;
    }else{
        switch (nodo->nHijos()) {
        case 0:
            aux.setAct(nodo);
            aux.setPrim(arbol);
            return aux;
            break;
        case 1:
            aux=cnfInterno(nodo->GetLeftChild(), arbol);
            aux.setAct(nodo);
            aux.setPrim(aux.getPrimero());
            return aux;
            break;
        case 2:
            aux=cnfInterno(nodo->GetLeftChild(), arbol);
            nodo->SetLeftChild(aux.getACtual());
            arbol=aux.getPrimero();
            aux=(cnfInterno(nodo->GetRightChild(), arbol));
            nodo->SetRightChild(aux.getACtual());
            arbol=aux.getPrimero();
            aux.setAct(nodo);
            aux.setPrim(arbol);
            return aux;
            break;
        default:
            aux.setAct(nodo);
            aux.setPrim(arbol);
            return aux;
            break;
        }
        //return arbol.getFirst();
    }
}


int almacenador::siguienteOp(QString formula){
    if(formula.size()==0)
        return -2;
    int i = 0;
    int parentesis = 0;
    while(i!=formula.size()-1){
        if(formula.at(i)=='(')
            parentesis++;
        else if(formula.at(i)==')')
            parentesis--;
        else if(parentesis==0 && (formula.at(i)== QString(SimbUNTIL)))
            return i;
        i++;
    }
    i=0;
    parentesis = 0;
    while(i!=formula.size()-1){
        if(formula.at(i)=='(')
            parentesis++;
        else if(formula.at(i)==')')
            parentesis--;
        else if(parentesis==0 && (formula.at(i)== QString(SimbRELEASE)))
            return i;
        i++;
    }
    i=0;
    parentesis = 0;
    while(i!=formula.size()-1){
        if(formula.at(i)=='(')
            parentesis++;
        else if(formula.at(i)==')')
            parentesis--;
        else if(parentesis==0 && (formula.at(i)== QString(SimbAND)))
            return i;
        i++;
    }
    i=0;
    parentesis = 0;
    while(i!=formula.size()-1){
        if(formula.at(i)=='(')
            parentesis++;
        else if(formula.at(i)==')')
            parentesis--;
        else if(parentesis==0 && (formula.at(i)== QString(SimbOR)))
            return i;
        i++;
    }
    i=0;
    parentesis = 0;
    while(i!=formula.size()-1){
        if(formula.at(i)=='(')
            parentesis++;
        else if(formula.at(i)==')')
            parentesis--;
        else if(parentesis==0 && (formula.at(i)== QString(SimbINPDER)))
            return i;
        i++;
    }
    i=0;
    parentesis = 0;
    while(i!=formula.size()-1){
        if(formula.at(i)=='(')
            parentesis++;
        else if(formula.at(i)==')')
            parentesis--;
        else if(parentesis==0 && (formula.at(i)== QString(SimbSSS)))
            return i;
        i++;
    }
    return -1;
}

QString almacenador::parentesisInnecesarios(QString formula){
    while(formula.at(0)=='(' && formula.at(formula.size()-1)==')'){
        int aux =0;
        int parentesis=0;
        while(aux<formula.size()-1){
            if(formula.at(aux)=='(')
                parentesis++;
            else if(formula.at(aux)==')'){
                parentesis--;
                if(parentesis==0)
                   return formula;
            }
            aux++;
        }
        formula = formula.mid(1,formula.size()-2);
    }
    return formula;
}


bool almacenador::comparanodos(BinaryTreeNode * nodo1, BinaryTreeNode * nodo2){
    if(nodo1->GetChar()!=nodo2->GetChar())
        return false;
    else{
        int nNodos1= nodo1->nHijos();
        if(nNodos1!=nodo2->nHijos())
            return false;
        else{
            switch (nNodos1) {
            case 0:
                return true;
                break;
            case 1:
                return comparanodos(nodo1->GetLeftChild(),nodo2->GetLeftChild());
                break;
            case 2:
                return (comparanodos(nodo1->GetLeftChild(),nodo2->GetLeftChild())&comparanodos(nodo1->GetRightChild(),nodo2->GetRightChild()));
                break;
            default:
                break;
            }
        }
    }
}

bool almacenador::isDistributed(BinaryTreeNode * actual){
    if(actual->GetChar()==QString(SimbNEXT)){
        while (actual->GetChar()==QString(SimbNEXT)){
            actual=actual->GetLeftChild();
        }
    }
    if(actual->GetChar()==QString(SimbAND)||actual->GetChar()==QString(SimbOR)||
            actual->GetChar()==QString(SimbINPDER)||actual->GetChar()==QString(SimbSSS))
        return false;
    else if((actual->GetChar()==QString(SimbAND)||actual->GetChar()==QString(SimbOR))&& comparanodos(actual->GetLeftChild(),actual->GetRightChild()))
        return false;
    else
        return true;
}

BinaryTreeNode * almacenador::crearSubArbol(BinaryTreeNode * actual, QString var){
    BinaryTreeNode * nuevoPadre = new BinaryTreeNode(SimbALWAYS);
    BinaryTreeNode * o = new BinaryTreeNode(SimbOR);
    BinaryTreeNode * no = new BinaryTreeNode(SimbNOT);
    no->SetLeftChild(new BinaryTreeNode(var));
    o->SetLeftChild(no);
    o->SetRightChild(actual);
    nuevoPadre->SetLeftChild(o);
    return nuevoPadre;
}
