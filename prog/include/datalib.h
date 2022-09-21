#pragma once
// *****************************************************************************
#include <stddef.h>
#include <stdbool.h>
// *****************************************************************************
#include "parameterdefinition.h"
// *****************************************************************************
bool isValidParamID(size_t const paramID);
// *****************************************************************************
bool getParameter(size_t const paramID, void *value);
// *****************************************************************************
bool setParameter(size_t const paramID, const void *value);
// *****************************************************************************