// *****************************************************************************
#include "acutest.h"
#include "datalib_test.h"
#include "parameterdata_test.h"
#include "parametertype_test.h"
#include "storage_test.h"
#include "storage_i8_test.h"
#include "storage_i16_test.h"
#include "storage_i32_test.h"
#include "storage_i64_test.h"
#include "storage_ui8_test.h"
#include "storage_ui16_test.h"
#include "storage_ui32_test.h"
#include "storage_ui64_test.h"
#include "converter_test.h"
// *****************************************************************************
/**
 * @brief Perform unit tests
 *
 * This is the test program. Main function comes with the include of acutest.h.
 * The called functions come with the other includes.
 */
TEST_LIST = {
    //--------------------------------------------------------------------------
    // Test of 1 byte storage
    {"int8_t", t_parameterdata_i8},
    {"uint8_t", t_parameterdata_ui8},
    //--------------------------------------------------------------------------
    // Test of 2 byte storage
    {"int16_t", t_parameterdata_i16},
    {"uint16_t", t_parameterdata_ui16},
    //--------------------------------------------------------------------------
    // Test of 4 byte storage
    {"int32_t", t_parameterdata_i32},
    {"uint32_t", t_parameterdata_ui32},
    //--------------------------------------------------------------------------
    // Test of 8 byte storage
    {"int64_t", t_parameterdata_i64},
    {"uint64_t", t_parameterdata_ui64},
    //--------------------------------------------------------------------------
    // Test order of enum type
    {"enum ParameterType", t_parametertype},
    //--------------------------------------------------------------------------
    // Test of storage endianness
    {"endianess of system", t_storageEndianness},
    //--------------------------------------------------------------------------
    // Test of other endianness
    {"other endianness", t_storageEndiannessToggle},
    //--------------------------------------------------------------------------
    // Test of storage initialization
    {"storage size", t_storageGetTotalSize},
    //--------------------------------------------------------------------------
    // Test of storage element access
    {"storage get element", t_storageXetElement},
    //--------------------------------------------------------------------------
    // Test of storage element access
    {"storage init, resize and release", t_storageSize},
    //--------------------------------------------------------------------------
    // Test of 8 byte storage
    {"read/write int64_t", t_storage_i64},
    {"read/write uint64_t", t_storage_ui64},
    //--------------------------------------------------------------------------
    // Test of 4 byte storage
    {"read/write int32_t", t_storage_i32},
    {"read/write uint32_t", t_storage_ui32},
    //--------------------------------------------------------------------------
    // Test of 2 byte storage
    {"read/write int16_t", t_storage_i16},
    {"read/write uint16_t", t_storage_ui16},
    //--------------------------------------------------------------------------
    // Test of 1 byte storage
    {"read/write int8_t", t_storage_i8},
    {"read/write uint8_t", t_storage_ui8},
    //--------------------------------------------------------------------------
    // Test of conversion little/big endian
    {"conversion little/big endian", t_converter},
    //--------------------------------------------------------------------------
    // Test of datalib public API
    {"datalib API", t_datalib_api},
    {NULL, NULL}};
