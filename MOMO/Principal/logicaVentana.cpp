#include "ventana.h"

Ventana *depurador;

void iniciarDepurador(){
    depurador = new Ventana();
    depurador->show();
}
