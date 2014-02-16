#include <QString>
#ifndef SIMBOLOS_H
#define SIMBOLOS_H

//SIMBOLOS
#define SimbALL         "¬◊○□← →  ↔ ∧∨"
#define SimbNOT         "¬"
#define SimbEVENTUALLY  "◊"
#define SimbNEXT        "○"
#define SimbALWAYS      "□"
#define SimbINPDER      "→"
#define SimbSSS         "↔"
#define SimbAND         "∧"
#define SimbOR          "∨"
#define SimbUNTIL       "U"
#define SimbRELEASE     "R"

#define CSimbALL         '¬◊○□← →  ↔ ∧∨'
#define CSimbNOT         '¬'
#define CSimbEVENTUALLY  '◊'
#define CSimbNEXT        '○'
#define CSimbALWAYS      '□'
#define CSimbINPDER      '→'
#define CSimbSSS         '↔'
#define CSimbAND         '∧'
#define CSimbOR          '∨'
#define CSimbUNTIL       'U'
#define CSimbRELEASE     'R'


class simbolos
{
public:
    simbolos();
    QString pasarDeTextoATextoConSimbolos(QString text);
    //QString pasaASimbolos(QString text);
};

#endif // SIMBOLOS_H
