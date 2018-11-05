#ifndef IGAMECONTROLLER_HH
#define IGAMECONTROLLER_HH

#include "cubecoordinate.hh"

namespace Student {

class IGameController{
public:
    virtual void handleHexagonClick(Common::CubeCoordinate hexCoordinates) = 0;
};
}


#endif // IGAMECONTROLLER_HH
