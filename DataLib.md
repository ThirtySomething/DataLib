# DataLib

A C library for reading/writing/updating parameters in a specified data area. Primary goal is to store numeric parameters. There may be limitations with respect to floating point numbers. This library is not designed to work with strings.

## [Converter][Converter]

Contains functions to determine and to change the endianness.

## [DataLib][DataLib]

Contains the functions to access the storage via the defined parameters as in [ParameterDefinition][ParameterDefinition].

## [Endianness][Endianness1]

Enum definition of little and big endianness.

## [Parameter][Parameter]

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

## [ParameterDefinition][ParameterDefinition]

Sourcefile containing the user defined parameters. See predefined example.

## [ParameterData][ParameterData]

The [ParameterData][ParameterData] is an union which defines the used memory of a segment. The type is based on an array of 2 64-bit values and results in 16 bytes. The other values are also arrays based on these 16 bytes. See the size of C [datatypes][DataTypes] for more details and better understanding. Keep in mind that the  [`int`/`unsigned int`][SizeInt] and [`long`/`unsigned long`][SizeLong] datatype is depending on the compiler and/or operating system. So the available types are `int8_t`, `int16_t`, `int32_t`, `int64_t` and their unsigned counterparts.

## [ParameterType][ParameterType]

The [ParameterType][ParameterType] is an enum which defines the number of bytes used for the parameter.

## [Storage][Storage]

Contains functions to access the [storage][Storage].

## Hints from internet

* [Compiler flags][hcompileflags] used in the project makefile
* [Datatypes][hlimits] in C and their limits used in tests
* [Datatypes][hstdint] in C and their size in bits/bytes
* [Datatypes][hdatatypes] in C and their sizes and printf mask
* [Determination][hendianness] of system's endianness
* [Endian swap macros][hendianswap] used to ensure always little endian
* [First compiler target][hfirsttarget] of makefile
* [Reverse array][hrevertarray] used to change endianness
* [Variables][hmakevar] used in makefile

## Open source usage

This project uses other open source projects. Thanks to

* [Acutest][Acutest]: Used for the tests in the project. This project uses the [MIT][MIT] license.

[Acutest]: https://github.com/mity/acutest
[BSD]: http://troydhanson.github.io/tpl/license.html
[Converter]: ./prog/include/converter.h
[DataTypes]: https://www.geeksforgeeks.org/data-types-in-c/
[DataLib]: ./prog/include/datalib.h
[Endianness1]: ./prog/include/endianness.h
[Endianness]: https://en.wikipedia.org/wiki/Endianness
[MIT]: https://opensource.org/licenses/MIT
[ParameterData]: ./prog/include/parameterdata.h
[ParameterDefinition]: ./prog/src/parameterdefinition.c
[ParameterType]: ./prog/include/parametertype.h
[Parameter]: ./prog/include/parameter.h
[SizeInt]: https://retrocomputing.stackexchange.com/questions/16351/when-if-ever-was-the-c-language-int-size-altered-from-the-host-machine-word-r
[SizeLong]: https://www.tutorialspoint.com/cprogramming/c_data_types.htm
[Storage]: ./prog/include/storage.h
[hcompileflags]: https://interrupt.memfault.com/blog/best-and-worst-gcc-clang-compiler-flags
[hdatatypes]: https://www.geeksforgeeks.org/data-types-in-c/
[hendianness]: https://www.geeksforgeeks.org/little-and-big-endian-mystery/
[hendianswap]: https://ecs-network.serv.pacific.edu/past-courses/2013-fall-ecpe-170/lab/endian-byte-swap-macros/view
[hfirsttarget]: https://stackoverflow.com/questions/2057689/how-does-make-app-know-default-target-to-build-if-no-target-is-specified
[hlimits]: https://www.tutorialspoint.com/c_standard_library/limits_h.htm
[hmakevar]: https://www.cmcrossroads.com/article/dumping-every-makefile-variable
[hrevertarray]: https://www.techiedelight.com/reverse-array-c/
[hstdint]: https://en.wikibooks.org/wiki/C_Programming/stdint.h
