#ifndef SYMBOL_H
#define SYMBOL_H

#include <wish.h>

class Symbol
{
public:
    wish_unicode    sym;
    int             color;
    int             bcolor;
    int             flags;

    Symbol() : sym(' '), color(0), bcolor(0), flags(0)
    {
    }
};

#endif
