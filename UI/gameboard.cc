#include "gameboard.hh"

using Common::CubeCoordinate;
using Common::Hex;
using std::shared_ptr;
using std::map;

namespace Student {

bool GameBoard::isWaterTile(CubeCoordinate tileCoord) const {
    shared_ptr<Hex> hex = getHexOnCoordinatesOrNull(tileCoord);
    if(hex == nullptr){
        return false;
    }
    else{
        return hex->isWaterTile();
    }
}

shared_ptr<Hex> GameBoard::getHexOnCoordinatesOrNull(const Common::CubeCoordinate coordinates) const
{
    auto hexIterator = _hexMap.find(coordinates);
    if(hexIterator == _hexMap.end()){
        return nullptr;
    }
    else{
        return hexIterator->second;
    }
}

} // namespace Student
