#pragma once

#include <cstdio>
#include <stdexcept>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file enum_cast.h
//
// \brief "enum_cast" algorithm: converts integer to a specified enum-type
//
//////////////////////////////////////////////////////////////////////////////

namespace algorithms
{

    //! \brief Convert integer to type T, if possible
    //
    //         T must be an enum-type.
    //
    //         The base template is left unimplemented so as to generate
    //         a compile error if the conversion is not well-defined.
    //
    //         If conversion from size_t to T is supported but the value
    //         of integer is not a legal value for T, then EnumCastException
    //         should be thrown via  throw_enum_cast_exception().
    template <typename T> T enum_cast(size_t integer);


    //! \brief Exception thrown by the "enum_cast" algorithm if
    //         integer->T is a valid conversion, but the value of integer
    //         is not defined for T.
    //
    //         Use throw_enum_cast_exception() to instantiate and throw
    //         an instance of this class.
    class EnumCastException : public std::range_error
    {
    private:
        //! \brief Constructs the error message of the form:
        //         Cannot convert <value> to <typename_t>\n
        //         <optional_error_text>
        EnumCastException(
            const char* typename_t,
            const char* value,
            const char* optional_error_text
        );

    private:
        //! \brief Function to use to construct and throw this object
        template <typename T, typename ValueType>
        friend void throw_enum_cast_exception(
            ValueType   value,
            const char* optional_error_text
        );
    };

    //! \brief Function used to throw an EnumCastException
    //
    //         T is the type that the integer was being converted to;
    //         value can either be the actual value that was trying to
    //         be converted, or some type for which operator<< is
    //         well-defined.  Eg:
    //
    //             std::stringstream ss;
    //             ss << value;
    //
    //         compiles and does something useful.  Note that
    //         if ValueType is char, unsigned char, uint8_t, int8_t, or
    //         any other synonym, the value is output as decimal, not
    //         as a character as operator<<(std::ostream&, uint8_t) would
    //         normally do.
    //
    template <typename T, typename ValueType>
    void throw_enum_cast_exception(
        ValueType   value,
        const char* optional_error_text
    );

} // namespace algorithms

#include "enum_cast.inl"
