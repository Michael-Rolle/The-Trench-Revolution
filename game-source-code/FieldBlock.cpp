#include "FieldBlock.h"

FieldBlock::FieldBlock()
{
    //ctor
}

bool FieldBlock::containsUnits()
{
    return units.empty() ? false : true;
}
