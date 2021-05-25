#include "positionmapper.h"

PositionMapper::PositionMapper()
{
    std::thread ioThread(&XyControl::run, &m_xyc);
}

void PositionMapper::moveToPosition(int x, int y)
{

}
