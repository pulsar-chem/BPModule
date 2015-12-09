/*! \file
 *
 * \brief Two-electron integral implementation (header)
 * \author Ben Pritchard (ben@bennyp.org)
 */ 


#ifndef _GUARD_TWOELECTRONINTEGRALIMPL_HPP_
#define _GUARD_TWOELECTRONINTEGRALIMPL_HPP_

#include "bpmodule/modulebase/ModuleBase.hpp"


namespace bpmodule {
namespace modulebase {

/*! \brief Two-electron integral implementation new module
 *
 */
class TwoElectronIntegralIMPL : public ModuleBase
{
    public:
        TwoElectronIntegralIMPL(unsigned long id);

        TwoElectronIntegralIMPL(PyObject * self, unsigned long id);


        /*! \brief Set the basis sets for the integrals
         * 
         * \param [in] ncenter The number of centers for the integrals (ie, 3-center, 2-center)
         */
        virtual void SetBases(int ncenter,
                              datastore::UIDPointer<basisset::BasisSet> bs1,
                              datastore::UIDPointer<basisset::BasisSet> bs2,
                              datastore::UIDPointer<basisset::BasisSet> bs3,
                              datastore::UIDPointer<basisset::BasisSet> bs4);

    private:
        virtual boost::python::object MoveToPyObject_(std::function<void(modulebase::ModuleBase *)> deleter);

};

} // close namespace modulebase
} // close namespace bpmodule

#endif
