#ifndef POSITIONMAPPER_H
#define POSITIONMAPPER_H

#include "xycontrol.h"

class PositionMapper
{
public:
    PositionMapper();

    void moveToPosition(int x , int y);


private:
    [[nodiscard]] constexpr int xStepEquivalent() const noexcept {return 1;}
    [[nodiscard]] constexpr int yStepEquivalent() const noexcept {return 1;}

private:
    XyControl m_xyc;

    int m_frameSizeX{800};
    int m_frameSizeY{600};
};

#endif // POSITIONMAPPER_H
