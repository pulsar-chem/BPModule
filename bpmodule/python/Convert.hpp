/*! \file
 *
 * \brief Conversion between python and C++ (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef _GUARD_CONVERT_HPP_
#define _GUARD_CONVERT_HPP_

#include "bpmodule/output/Output.hpp"

#include "bpmodule/python/Pybind11.hpp"
#include "bpmodule/python/Pybind11_stl.hpp"
#include "bpmodule/python/Types.hpp"
#include "bpmodule/python/Errors.hpp"
#include "bpmodule/exception/PythonConvertException.hpp"
#include "bpmodule/util/Mangle.hpp"


namespace bpmodule {
namespace python {



/*! \brief Convert a python object to a C++ object
 *
 * \throw bpmodule::exception::PythonConvertException on error
 *
 * \tparam T The C++ type to convert to
 * \param [in] obj The python object to convert
 */
template<typename T>
T ConvertToCpp(pybind11::object obj)
{
    using bpmodule::exception::PythonConvertException;


    //! \todo more restrictive?

    // throws if there is an issue
    //! \todo exception handling
    try {
        return obj.cast<T>();
    }
    catch(const std::exception & ex)
    {
        throw PythonConvertException("Cannot convert from python to C++: Conversion failed",
                                     GetPyClass(obj), util::DemangleCppType<T>(),
                                     "what", ex.what());
    }
    catch(...)
    {
        throw PythonConvertException("Cannot convert from python to C++: Conversion failed",
                                     GetPyClass(obj), util::DemangleCppType<T>(),
                                     "what", "unknown exception type");
    }
}




/*! \brief Convert a C++ object to a python object
 *
 * \throw bpmodule::exception::PythonConvertException on error
 *
 * \tparam T The C++ type to convert from
 * \param [in] obj The python object to convert
 */
template<typename T>
pybind11::object ConvertToPy(const T & obj)
{
    using bpmodule::exception::PythonConvertException;


    // may NOT throw if there is an issue
    try {
        pybind11::object pyobj = pybind11::cast(obj);

        //! \todo fix if this is fixed in pybind11
        if(pyobj.ptr() == nullptr)
        {
            throw PythonConvertException(detail::GetPyException(),
                                         util::DemangleCppType<T>(), "python object",
                                         "info", "Resulting object pointer is null");
        }
        else
            return pyobj;
        
    }
    catch (const std::exception & ex)
    {
        throw PythonConvertException(ex.what(), 
                                     util::DemangleCppType<T>(), "python object",
                                     "info", "In converting from C++ to python object");
    }
    catch(...)
    {
        throw PythonConvertException("Caught unknown exception", 
                                     util::DemangleCppType<T>(), "python object",
                                     "info", "In converting from C++ to python object");
    }
}


/*! \brief Convert a plain array of C++ objects to a python object
 *
 * \throw exception::PythonConvertException if the
 *        data could not be converted
 *
 * \tparam T The C++ type to convert from
 *
 * \param [in] obj An array of objects
 * \param [in] n Length of the array
 * \return Converted data as a python object
 */
template<typename T>
pybind11::object ConvertToPy(const T * const obj, size_t n)
{
    std::vector<T> v(obj, obj+n);

    return ConvertToPy(v);
}



} // close namespace python
} // close namespace bpmodule

#endif
