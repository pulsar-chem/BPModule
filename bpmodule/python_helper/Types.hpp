/*! \file
 *
 * \brief Handling and detection of python types (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef _GUARD_TYPES_HPP_
#define _GUARD_TYPES_HPP_

#include <string>
#include "bpmodule/python_helper/BoostPython_fwd.hpp"


namespace bpmodule {
namespace python_helper {


//! Types defined in python that are available in BPModule
enum class PythonType
{
    Bool,
    Int,
    Float,
    String,
    ListBool,
    ListInt,
    ListFloat,
    ListString,
    ListEmpty,
    ListHetero,
    ListUnknown,
    Tuple,
    Dict,
    None,
    Unknown
};




/*! \brief Convert a string to a PythonType
 */
PythonType StrToPythonType(const std::string & str);


/*! \brief Convert a PythonType to a string
 */
const char * PythonTypeToStr(PythonType pytype);


/*! \brief Determine the type of a boost python object
 */
PythonType DeterminePyType(const boost::python::object & obj);


/*! \brief Get the class of a python object as a string
 */
std::string GetPyClass(const boost::python::object & obj);


/*! \brief Check if a python object has a given attribute
 */
bool HasAttr(const boost::python::object & obj, const std::string & attr);


/*! \brief Check if a python object is callable
 */ 
bool IsCallable(const boost::python::object & obj);


/*! \brief Check if a python object is callable taking the given number of arguments
 */ 
bool IsCallable(const boost::python::object & obj, int narg);


/*! \brief Check if a python object has a given callable attribute
 */
bool HasCallableAttr(const boost::python::object & obj, const std::string & attr);


/*! \brief Check if a python object has a given callable attribute taking the given number of arguments
 */
bool HasCallableAttr(const boost::python::object & obj, const std::string & attr, int narg);



} // close namespace python_helper
} // close namespace bpmodule

#endif
