#include "generadorvariables.h"

generadorVariables::generadorVariables()
{
        nVariablesgeneradas=0;
}

QString generadorVariables::generarVariable(){
    QString variable = "_p"+QString::number(nVariablesgeneradas);
    nVariablesgeneradas++;
    return variable;
}
