/*! \file
 *
 * \brief Various test for options (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#ifndef _GUARD_TESTOPTIONS_HPP_
#define _GUARD_TESTOPTIONS_HPP_

#include <string>

#include "bpmodule/options/OptionMap.hpp"
#include "bpmodule/python_helper/Convert.hpp"


namespace bpmodule {
namespace testing {


template<typename T>
void TestOptionMap_Get(const options::OptionMap & opt, const std::string & key)
{
    // ignore return value
    opt.Get<T>(key);
}


template<typename T>
void TestOptionMap_Change(options::OptionMap & opt, const std::string & key, boost::python::object & value)
{
    // ignore return value
    const T tmp = python_helper::ConvertToCpp<T>(value);
    opt.Change<T>(key, tmp);
}



} // close namespace testing
} // close namespace bpmodule



#endif
