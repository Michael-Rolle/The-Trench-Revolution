#ifndef FIELDBLOCK_H
#define FIELDBLOCK_H

#include <memory>
#include <vector>
#include "Unit.h"

using std::vector;
using std::shared_ptr;

class FieldBlock
{
    public:
        FieldBlock();
        void addUnit(shared_ptr<Unit> unit) { units.push_back(unit); }
        void removeUnit(shared_ptr<Unit> unit);
        bool containsUnits();

    private:
        vector<shared_ptr<Unit>> units; //The units within one block
};

#endif // FIELDBLOCK_H
