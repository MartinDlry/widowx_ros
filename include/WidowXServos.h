#ifndef WIDOWXSERVOS_H
#define WIDOWXSERVOS_H

#include <array>

#include "ServoGroup.h"

class WidowXServos : public ServoGroup
{
    public:
        std::array<int,6> positions;
        std::array<int,6> speeds;

        WidowXServos();
        WidowXServos( std::array<int,6> positions );
        
        bool validPositions();
        
        const static std::array<int,6> basePositions;

    private:
        const static std::array<int,12> boundaries;
};
#endif