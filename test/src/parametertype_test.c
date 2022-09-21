// *****************************************************************************
#include "parametertype.h"
#include "testinc.h"
// *****************************************************************************
void t_parametertype(void)
{
    unsigned int i_enum = 0;
    unsigned int i_shift = 0;

    i_enum = 1 << i_shift++;
    do
    {
        switch (i_enum)
        {
            break;
        case 1:
            TEST_CHECK(i_enum == PT_BYTE1);
            break;
        case 2:
            TEST_CHECK(i_enum == PT_BYTE2);
            break;
        case 4:
            TEST_CHECK(i_enum == PT_BYTE4);
            break;
        case 8:
            TEST_CHECK(i_enum == PT_BYTE8);
            break;
        case 16:
            TEST_CHECK(i_enum == PT_BYTE16);
            break;
            break;
        case 32:
            TEST_CHECK(i_enum == PT_LAST);
            break;
        default:
            TEST_MSG("Missing/invalid enum value [%d]", i_enum);
            break;
        }
        i_enum = 1 << i_shift++;
    } while (i_enum <= PT_LAST);
}
// *****************************************************************************
