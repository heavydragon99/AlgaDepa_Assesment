#include "controller.h"

controller::controller() {
}

void controller::createLevel() {
    mModel.createLevel(mPersons, mGrid);
}