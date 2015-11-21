#ifndef _GUARD_INITFINALIZE_HPP_
#define _GUARD_INITFINALIZE_HPP_

#include "bpmodule/python_helper/BoostPython_fwd.hpp"


namespace bpmodule {
namespace tensor {

void Init(const boost::python::list & argv);
void Finalize(void);


} // close namespace tensor
} // close namespace bpmodule


#endif