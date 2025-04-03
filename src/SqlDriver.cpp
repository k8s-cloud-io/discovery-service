#include "SqlDriver.h"

SqlDriver::SqlDriver()
:driverState(STATE_NONE) {
}
SqlDriver::State SqlDriver::state() const {
    return driverState;
}

void SqlDriver::setState(const State s) {
    driverState = s;
}

bool SqlDriver::isOpen() const {
    return driverState == STATE_OPEN;
}

bool SqlDriver::isClosed() const {
    return driverState == STATE_CLOSED || driverState == STATE_NONE;
}
