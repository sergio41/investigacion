#include "ventana.h"

Ventana *depurador;
bool state;

void iniciarDepurador(){
    if (!state){
        state = true;
        depurador = new Ventana();
        depurador->show();
    }
}

void terminarDepurador(){
    if (state){
        delete depurador;
        state = false;
    }
}

void anadirADepurador(QString texto){
    if (state) depurador->Anadir(texto);
}

bool getEstado(){
    return state;
}
