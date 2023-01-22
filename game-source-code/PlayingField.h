#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <vector>
#include "FieldBlock.h"

using std::vector;

class PlayingField //The playing field is made up of 100 vertical blocks to determine positions of units and structures
{
    public:
        PlayingField();

    private:
        vector<FieldBlock> fieldBlocks;
};

#endif // PLAYINGFIELD_H
