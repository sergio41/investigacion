#include "simbolos.h"
#include <QString>
//#include <string>

simbolos::simbolos()
{
}

QString simbolos::pasarDeTextoATextoConSimbolos(QString text){
    text = text.replace("G", SimbALWAYS);
    text = text.replace("&", SimbAND);
    text = text.replace("F", SimbEVENTUALLY);
    text = text.replace(">", SimbINPDER);
    text = text.replace("<", SimbINPIZQ);
    text = text.replace("X", SimbNEXT);
    text = text.replace("-", SimbNOT);
    text = text.replace("|", SimbOR);
    text = text.replace("=", SimbSSS);
    text = text.replace("R", SimbRELEASE);
    text = text.replace("U", SimbUNTIL);
    return text;
}


/*QString simbolos::pasaASimbolos(QString text){
    std::string aux;
    aux = text.replace(SimbALWAYS, CSimbALWAYS);
    text = text.replace(SimbAND, CSimbAND);
    text = text.replace(SimbEVENTUALLY, CSimbEVENTUALLY);
    text = text.replace(SimbINPDER, CSimbINPDER);
    text = text.replace(SimbINPIZQ, CSimbINPIZQ);
    text = text.replace(SimbNEXT, CSimbNEXT);
    text = text.replace(SimbNOT, CSimbNOT);
    text = text.replace(SimbOR, CSimbOR);
    text = text.replace(SimbSSS, CSimbSSS);
    text = text.replace(SimbRELEASE, CSimbRELEASE);
    text = text.replace(SimbUNTIL, CSimbUNTIL);
    return text;
}*/
