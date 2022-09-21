// *****************************************************************************
#include <stddef.h>
// *****************************************************************************
#include "parameterdefinition.h"
// *****************************************************************************
Parameter parameterDefinition[] = {
    // Parameter ID     Parameter Index     Parameter Position      Parameter Type      Parameter Name
    // int64_t and uint64_t using each 8 bytes, allowed position range 0 - 3
    {   0,              0,                  1,                      PT_BYTE8,           "int64_t"},
    {   1,              1,                  0,                      PT_BYTE8,           "uint64_t"},
    // int32_t and uint32_t using each 4 bytes, allowed position range 0 - 7
    {   2,              1,                  2,                      PT_BYTE4,           "int32_t"},
    {   3,              1,                  3,                      PT_BYTE4,           "uint32_t"},
    // int16_t and uint16_t using each 2 bytes, allowed position range 0 - 15
    {   4,              2,                  0,                      PT_BYTE2,           "int16_t"},
    {   5,              2,                  1,                      PT_BYTE2,           "uint16_t"},
    // int8_t and uint8_t using each 1 bytes, allowed position range 0 - 31
    {   6,              2,                  6,                      PT_BYTE1,           "int8_t"},
    {   7,              2,                  7,                      PT_BYTE1,           "uint8_t"},
};
// *****************************************************************************
#define SIZE_OF_PARAMETER_DEFINITION_TABLE (sizeof(parameterDefinition) / sizeof(parameterDefinition[0]))
// *****************************************************************************
size_t sizeParameterList = SIZE_OF_PARAMETER_DEFINITION_TABLE;
// *****************************************************************************

/*
                                                    1   1   1   1   1   1
int8_t      0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5
int16_t     0       1       2       3       4       5       6       7
int32_t     0               1               2               3
int64_t     0                               1
*/
