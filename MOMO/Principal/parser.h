#include <QString>

#ifndef PARSER_H
#define PARSER_H

class parser
{
public:
    parser();
    bool comprobarParser(QString formula);

private:
    bool comprobarParserInterno(QString formula);
};

#endif // PARSER_H
