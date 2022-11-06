# DataLib

A C library for reading/writing/updating parameters in a specified data area. Primary goal is to store numeric parameters. There may be limitations with respect to floating point numbers. This library is not designed to work with strings.

## [Converter][converter]

Contains functions to determine and to change the endianness.

## [DataLib][datalib]

Contains the functions to access the storage via the defined parameters as in [ParameterDefinition][parameterdefinition].

## [Endianness][endianness1]

Enum definition of little and big endianness.

## [Parameter][parameter]

Definition of a structure of a parameter. This structure describes a parameter and it's details:

```c
typedef struct _Parameter
{
    unsigned int paramID;          //!< External reference ID of parameter
    unsigned int paramIndex;       //!< Internal index of parameter
    unsigned short paramPosition;  //!< Inernal position of parameter
    ParameterType paramType;       //!< Type of parameter
    char paramName[P_MaxName + 1]; //!< Name of parameter
} Parameter;
```

At the moment name of a parameter is defined with a size of 32 bytes.

## [ParameterDefinition][parameterdefinition]

Sourcefile containing the user defined parameters. See predefined example.

## [ParameterData][parameterdata]

The [ParameterData][parameterdata] is an union which defines the used memory of a segment. The type is based on an array of 2 64-bit values and results in 16 bytes. The other values are also arrays based on these 16 bytes. See the size of C [datatypes][datatypes] for more details and better understanding. Keep in mind that the [`int`/`unsigned int`][sizeint] and [`long`/`unsigned long`][sizelong] datatype is depending on the compiler and/or operating system. So the available types are `int8_t`, `int16_t`, `int32_t`, `int64_t` and their unsigned counterparts.

## [ParameterType][parametertype]

The [ParameterType][parametertype] is an enum which defines the number of bytes used for the parameter.

## [Storage][storage]

Contains functions to access the [storage][storage].

## Hints from internet

- [Compiler flags][hcompileflags] used in the project makefile
- [Datatypes][hlimits] in C and their limits used in tests
- [Datatypes][hstdint] in C and their size in bits/bytes
- [Datatypes][hdatatypes] in C and their sizes and printf mask
- [Determination][hendianness] of system's endianness
- [Endian swap macros][hendianswap] used to ensure always little endian
- [First compiler target][hfirsttarget] of makefile
- [Reverse array][hrevertarray] used to change endianness
- [Variables][hmakevar] used in makefile

## Open source usage

This project uses other open source projects. Thanks to

- [Acutest][acutest]: Used for the tests in the project. This project uses the [MIT][mit] license.

[acutest]: https://github.com/mity/acutest
[converter]: ./prog/include/converter.h
[datalib]: ./prog/include/datalib.h
[datatypes]: https://www.geeksforgeeks.org/data-types-in-c/
[endianness1]: ./prog/include/endianness.h
[endianness]: https://en.wikipedia.org/wiki/Endianness
[hcompileflags]: https://interrupt.memfault.com/blog/best-and-worst-gcc-clang-compiler-flags
[hdatatypes]: https://www.geeksforgeeks.org/data-types-in-c/
[hendianness]: https://www.geeksforgeeks.org/little-and-big-endian-mystery/
[hendianswap]: https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
[hfirsttarget]: https://stackoverflow.com/questions/2057689/how-does-make-app-know-default-target-to-build-if-no-target-is-specified
[hlimits]: https://www.tutorialspoint.com/c_standard_library/limits_h.htm
[hmakevar]: https://www.cmcrossroads.com/article/dumping-every-makefile-variable
[hrevertarray]: https://www.techiedelight.com/reverse-array-c/
[hstdint]: https://en.wikibooks.org/wiki/C_Programming/stdint.h
[mit]: https://opensource.org/licenses/MIT
[parameter]: ./prog/include/parameter.h
[parameterdata]: ./prog/include/parameterdata.h
[parameterdefinition]: ./prog/src/parameterdefinition.c
[parametertype]: ./prog/include/parametertype.h
[sizeint]: https://retrocomputing.stackexchange.com/questions/16351/when-if-ever-was-the-c-language-int-size-altered-from-the-host-machine-word-r
[sizelong]: https://www.tutorialspoint.com/cprogramming/c_data_types.htm
[storage]: ./prog/include/storage.h
