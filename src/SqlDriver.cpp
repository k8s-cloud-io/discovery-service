#include "SqlDriver.h"

SqlDriver::SqlDriver()
:driverState(SqlDriver::STATE_NONE) {
}
SqlDriver::State SqlDriver::state() const {
    return driverState;
}

void SqlDriver::setState(SqlDriver::State s) {
    driverState = s;
}

bool SqlDriver::isOpen() const {
    return driverState == SqlDriver::STATE_OPEN;
}

bool SqlDriver::isClosed() const {
    return driverState == SqlDriver::STATE_CLOSED || driverState == SqlDriver::STATE_NONE;
}
