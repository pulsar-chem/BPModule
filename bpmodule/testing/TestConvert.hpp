/*! \file
 *
 * \brief Various test for the core (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#ifndef _GUARD_TESTCONVERT_HPP_
#define _GUARD_TESTCONVERT_HPP_

#include <string>

#include "bpmodule/python_helper/Convert.hpp"
#include "bpmodule/testing/TestingBase.hpp"


namespace bpmodule {
namespace testing {



/*! \brief Testing of python-to-C++ conversions
 *
 * \tparam T Type to convert to
 *
 * \param [in] itest A test number
 * \param [in] desc Some description
 * \param [in] expected True if this is supoosed to succeed, false if it should
 *                      throw an exception
 * \param [in] obj Object to convert
 */
template<typename T>
int TestConvertToCpp(int itest, const std::string & desc, bool expected, const boost::python::object & obj)
{
    return TestFunc(itest, desc, expected, bpmodule::python_helper::ConvertToCpp<T>, obj);
}



} // close namespace testing
} // close namespace bpmodule



#endif
