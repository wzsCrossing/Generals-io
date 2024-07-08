#include "MapInfo.h"

CellType Cell::getType() {
    return type_;
}

int Cell::getOwner() {
    return owner_;
}

int Cell::getArmy() {
    return army_;
}

void Cell::setType(CellType type) {
    type_ = type;
}

void Cell::setOwner(int owner) {
    owner_ = owner;
}

void Cell::setArmy(int army) {
    army_ = army;
}

void Cell::addArmy(int army) {
    army_ += army;
}

