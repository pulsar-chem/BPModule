/*! \file
 *
 * \brief Various test for the ModuleInfo class (source)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 

#include "bpmodule/testing/TestingBase.hpp"
#include "bpmodule/testing/TestModuleInfo.hpp"
#include "bpmodule/modulestore/ModuleInfo.hpp"

#include <boost/python.hpp>

using bpmodule::modulestore::ModuleInfo;

namespace bpmodule {
namespace testing {


int TestModuleInfo_Construct(int itest, const std::string & desc, bool expected, const boost::python::dict & mi)
{
    return TestConstruct<ModuleInfo>(itest, desc, expected, mi);
}


} // close namespace testing
} // close namespace bpmodule
