#ifndef PULSAR_GUARD_MATH__EXACTCAST_HPP_
#define PULSAR_GUARD_MATH__EXACTCAST_HPP_

#include <limits>

#include "pulsar/pragma.h"
#include "pulsar/math/Checking.hpp"
#include "pulsar/exception/PulsarException.hpp"
#include "pulsar/util/Mangle.hpp"



namespace pulsar{
namespace detail {


/*! \brief Perform a cast between types that preserves precision
 *
 * Can be used for integer <-> integer or floating point <-> floating point, and exact
 * integer <-> floating point
 */
template<typename Target, typename Source>
struct ExactCast
{
    static Target cast(const Source & s)
    {
        static_assert(  ( std::is_integral<Source>::value || std::is_floating_point<Source>::value ) &&
                        ( std::is_integral<Target>::value || std::is_floating_point<Target>::value ),
                         "Attempting to perform conversion between two unknown types");

        static_assert(  ( std::is_arithmetic<Source>::value && std::is_arithmetic<Target>::value ),
                        "Attempting to perform numeric cast on non-arithmetic types");

        // These are disabled function wide. Intel seems to
        // complain about stuff in branches that should
        // be optimized out
        PRAGMA_WARNING_PUSH
        PRAGMA_WARNING_IGNORE_FP_CONVERT
        PRAGMA_WARNING_IGNORE_POINTLESS_COMPARISON_UINT_0
        PRAGMA_WARNING_IGNORE_STATEMENT_UNREACHABLE


        ////////////////////////////////////////////////////////////////////////////////
        // this is written with branching so that the limits checking isn't always done
        // (ie, going from short->int should be pretty much optimized out)
        //
        // Actually, most branching shown here should be optimized out at compile time
        ////////////////////////////////////////////////////////////////////////////////

        ///////////////////
        // for integers
        ///////////////////
        if(std::is_integral<Source>::value && std::is_integral<Target>::value)
        {
            // both are signed or unsigned
            if(std::is_signed<Source>::value == std::is_signed<Target>::value)
            {
                // going from smaller to larger type - ok
                if(std::numeric_limits<Target>::digits >= std::numeric_limits<Source>::digits)
                    return static_cast<Target>(s);
                else
                {
                    // source is larger type than target. check limits
                    Source tmax = static_cast<Source>(std::numeric_limits<Target>::max());
                    Source tmin = static_cast<Source>(std::numeric_limits<Target>::lowest());
                    if(s > tmax)
                        throw PulsarException("Error in numeric_cast",
                                                       "desc", "source value overflows target type",
                                                       "ifrom", demangle_cpp_type<Source>(),
                                                       "ito", demangle_cpp_type<Target>());
                    else if(s < tmin)
                        throw PulsarException("Error in numeric_cast",
                                                       "desc", "source value underflows target type",
                                                       "ifrom", demangle_cpp_type<Source>(),
                                                       "ito", demangle_cpp_type<Target>());

                    else // safe!
                        return static_cast<Target>(s);

                }
            }
            else if(std::is_signed<Source>::value) // Source is signed, Target is unsigned
            {
                if(s < 0)
                    throw PulsarException("Error in numeric_cast",
                                                   "desc", "source value underflows target type",
                                                   "ifrom", demangle_cpp_type<Source>(),
                                                   "ito", demangle_cpp_type<Target>());

                
                // going from smaller to larger type - ok (since s >= 0)
                if(std::numeric_limits<Target>::digits >= std::numeric_limits<Source>::digits)
                    return static_cast<Target>(s);
                else
                {
                    // source is larger type than target. check other limit
                    // casting to Source type should be ok since sizeof(Source) > sizeof(Target)
                    Source tmax = static_cast<Source>(std::numeric_limits<Target>::max());
                    if(s > tmax)
                        throw PulsarException("Error in numeric_cast",
                                                       "desc", "source value overflows target type",
                                                       "ifrom", demangle_cpp_type<Source>(),
                                                       "ito", demangle_cpp_type<Target>());

                    else // safe!
                        return static_cast<Target>(s);

                }
            }
            else  // Source is unsigned, target is signed
            {
                // going from smaller to larger type - ok
                // (since numeric_limits::digits reports bits without sign bit)
                if(std::numeric_limits<Target>::digits >= std::numeric_limits<Source>::digits)
                    return static_cast<Target>(s);
                else
                {
                    // source is larger type than target. check max limit
                    // casting to Source type should be ok since sizeof(Source) > sizeof(Target)
                    Source tmax = static_cast<Source>(std::numeric_limits<Target>::max());
                    if(s > tmax)
                        throw PulsarException("Error in numeric_cast",
                                                       "desc", "source value overflows target type",
                                                       "ifrom", demangle_cpp_type<Source>(),
                                                       "ito", demangle_cpp_type<Target>());

                    else // safe!
                        return static_cast<Target>(s);

                }
            }
        }



        // if both are floating point
        // we have to check that the conversion is valid
        else if(std::is_floating_point<Source>::value && std::is_floating_point<Target>::value)
        {
            // Hackish way, but convert to target and back, then compare
            // check for overflow and underflow
            Target t = static_cast<Target>(s);
            Source s2 = static_cast<Source>(t);

            // ignore this warning -- we are doing it on purpose
            PRAGMA_WARNING_PUSH
            PRAGMA_WARNING_IGNORE_FP_EQUALITY
            if(s == s2)
                return t;
            else
                throw PulsarException("Error in numeric_cast",
                                               "desc", "Floating point conversion results in loss of precision",
                                               "fpfrom", demangle_cpp_type<Source>(),
                                               "fpto", demangle_cpp_type<Target>());
            PRAGMA_WARNING_POP
        }

        else if(std::is_floating_point<Source>::value && std::is_integral<Target>::value)
        {
            // Check validity (ie does the FP source have exactly an integer?)
            if(!is_integer(s))
                throw PulsarException("Error in numeric_cast",
                                               "desc", "Floating point conversion to integer results in loss of information",
                                               "fpfrom", demangle_cpp_type<Source>(),
                                               "ito", demangle_cpp_type<Target>());
            else
                return static_cast<Target>(s);
        }

        else if(std::is_integral<Source>::value && std::is_floating_point<Target>::value)
        {
            // Can the floating point handle the integer?
            Target t = static_cast<Target>(s);

            if(!is_integer(s))
                throw PulsarException("Error in numeric_cast",
                                               "desc", "Floating point type cannot exactly handle this integer",
                                               "ifrom", demangle_cpp_type<Source>(),
                                               "fpto", demangle_cpp_type<Target>());

            Source s2 = static_cast<Source>(s);
            PRAGMA_WARNING_PUSH
            PRAGMA_WARNING_IGNORE_FP_EQUALITY
            if(s != s2)
                throw PulsarException("Error in numeric_cast",
                                               "desc", "Floating point type cannot exactly handle this integer",
                                               "ifrom", demangle_cpp_type<Source>(),
                                               "fpto", demangle_cpp_type<Target>());
            else
                return t;
            PRAGMA_WARNING_POP

        }

        else
            throw std::logic_error("numeric_cast unhandled types");


        PRAGMA_WARNING_POP
    }
};





/*! \copydoc ExactCast
 *
 * Specialization for no conversion
 */
template<typename Source>
struct ExactCast<Source, Source>
{
    static Source cast(const Source & s)
    {
        return s;
    }
};




} // close namespace detail
} // close namespace pulsar



#endif
