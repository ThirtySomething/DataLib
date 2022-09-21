#pragma once
// *****************************************************************************
#include <stddef.h>
// *****************************************************************************
#include "parameterdata.h"
// *****************************************************************************
#define P_MaxName 32 //!< Maximum length of parameter name
// *****************************************************************************
/**
 * @struct _Parameter
 * @typedef Parameter
 * @brief Definition of a parameter
 *
 * The list of parameter is build up on this base except the paramPosition;
 */
typedef struct _Parameter
{
    size_t paramID;                //!< External reference ID of parameter
    size_t paramIndex;             //!< Internal index of parameter
    size_t paramPosition;          //!< Inernal position of parameter
    ParameterType paramType;       //!< Type of parameter
    char paramName[P_MaxName + 1]; //!< Name of parameter
} Parameter;
// *****************************************************************************
