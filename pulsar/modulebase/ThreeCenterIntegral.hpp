#pragma once

/*! \file
 *
 * \brief Two-electron integral implementation (header)
 * \author Ben Pritchard (ben@bennyp.org)
 */

#include "pulsar/modulebase/ModuleBase.hpp"
#include "pulsar/system/BasisSet.hpp"
#include "pulsar/util/PythonIntegralHelper.hpp"


namespace pulsar{

/*! \brief Two-electron, three cneter integral implementation
 *
 */
class ThreeCenterIntegral : public ModuleBase
{
protected:
    PythonIntegralHelper helper_;
    public:
        typedef ThreeCenterIntegral BaseType;
        typedef std::string HashType;
        ThreeCenterIntegral(ID_t id)
            : ModuleBase(id, "ThreeCenterIntegral"), initialized_(false)
        { }


        /*! \brief initialize the integral computation
         *
         * \param [in] deriv Derivative to calculate
         * \param [in] wfn Wavefunction to use to calculate integrals
         * \param [in] bs1 Basis set tag to use for the first center
         * \param [in] bs2 Basis set tag to use for the second center
         * \param [in] bs3 Basis set tag to use for the third center
         */
        void initialize(unsigned int deriv,
                        const Wavefunction & wfn,
                        const BasisSet & bs1,
                        const BasisSet & bs2,
                        const BasisSet & bs3)
        {
            ModuleBase::call_function(&ThreeCenterIntegral::uninitialized_or_throw_);
            ModuleBase::call_function(&ThreeCenterIntegral::initialize_, deriv, wfn, bs1, bs2, bs3);
            helper_.initialize(bs1,bs2,bs3);
            initialized_ = true;
        }

        HashType my_hash(unsigned int deriv,
                        const Wavefunction & wfn,
                        const BasisSet & bs1,
                        const BasisSet & bs2,
                        const BasisSet & bs3)
        {
            return ModuleBase::call_function(&ThreeCenterIntegral::my_hash_,deriv,wfn,bs1,bs2,bs3);
        }

        /*! Return the number of components calculated by this module
         *
         * For example, something that calculates x,y,z component would return 3
         */
        unsigned int n_components(void) const
        {
            return ModuleBase::call_function(&ThreeCenterIntegral::n_components_);
        }


        /*! \brief calculate an integral
         *
         * \param [in] shell1 Shell index on the first center
         * \param [in] shell2 Shell index on the second center
         * \param [in] shell3 Shell index on the third center
         * \param [in] outbuffer Where to place the completed integrals
         * \param [in] bufsize Size of \p outbuffer (as the number of doubles)
         * \return A pointer to the beginning of the integral buffer
         */
        const double* calculate(uint64_t shell1, uint64_t shell2,
                           uint64_t shell3)
        {
            ModuleBase::call_function(&ThreeCenterIntegral::initialized_or_throw_);
            return ModuleBase::call_function(&ThreeCenterIntegral::calculate_,
                                                shell1, shell2, shell3);
        }

        /*! \brief calculate multiple integrals
         *
         * \param [in] shells1 Shell indicies on the first center
         * \param [in] shells2 Shell indicies on the second center
         * \param [in] shells3 Shell indicies on the third center
         * \param [in] outbuffer Where to place the completed integrals
         * \param [in] bufsize Size of \p outbuffer (as the number of doubles)
         * \return Number of integrals calculated
         */
        const double* calculate_multi(const std::vector<uint64_t> & shells1,
                                 const std::vector<uint64_t> & shells2,
                                 const std::vector<uint64_t> & shells3)
        {
            ModuleBase::call_function(&ThreeCenterIntegral::initialized_or_throw_);
            return ModuleBase::call_function(&ThreeCenterIntegral::calculate_multi_,
                                                  shells1, shells2, shells3);
        }


        /*! \brief calculate an integral (for use from python)
         *
         * \param [in] shell1 Shell index on the first center
         * \param [in] shell2 Shell index on the second center
         * \param [in] shell3 Shell index on the third center
         * \return Integrals in a Python list
         */
        pybind11::list calculate_py(uint64_t shell1, uint64_t shell2,uint64_t shell3)
        {
               const double* ints =
                ModuleBase::call_function(&ThreeCenterIntegral::calculate_,
                                              shell1, shell2, shell3);
               return helper_.int_2_py(ints,shell1,shell2,shell3);
        }


        /*! \brief calculate multiple integrals (for use from python)
         *
         * \param [in] shells1 Shell indicies on the first center
         * \param [in] shells2 Shell indicies on the second center
         * \param [in] shells3 Shell indicies on the third center
         * \return The integrals in a Python list
         */
        pybind11::list calculate_multi_py(const std::vector<uint64_t> & shells1,
                                    const std::vector<uint64_t> & shells2,
                                    const std::vector<uint64_t> & shells3)
        {
            const double* ints=
              ModuleBase::call_function(&ThreeCenterIntegral::calculate_multi_,
                                           shells1, shells2, shells3);
            return helper_.multi_int_2_py(ints,shells1,shells2,shells3);
        }


        /////////////////////////////////////////
        // To be implemented by derived classes
        /////////////////////////////////////////
        //! \copydoc initialize
        virtual void initialize_(unsigned int deriv,
                                 const Wavefunction & wfn,
                                 const BasisSet & bs1,
                                 const BasisSet & bs2,
                                 const BasisSet & bs3) = 0;

        virtual HashType my_hash_(unsigned int deriv,
                                  const Wavefunction& wfn,
                                  const BasisSet & bs1,
                                  const BasisSet & bs2,
                                  const BasisSet & bs3)=0;

        //! \copydoc n_components
        virtual unsigned int n_components_(void) const
        {
            return 1;
        }


        //! \copydoc calculate
        virtual const double* calculate_(uint64_t shell1, uint64_t shell2,
                                    uint64_t shell3) = 0;

        //! \copydoc calculate_multi
        virtual const double* calculate_multi_(const std::vector<uint64_t> & /*shells1*/,
                                          const std::vector<uint64_t> & /*shells2*/,
                                          const std::vector<uint64_t> & /*shells3*/)
        {
//            //////////////////////////////////////////////////////////
//            // default implementation - just loop over and do them all
//            //////////////////////////////////////////////////////////

//            uint64_t ntotal = 0;

//            for(uint64_t s1 : shells1)
//            for(uint64_t s2 : shells2)
//            for(uint64_t s3 : shells3)
//            for(uint64_t s4 : shells4)
//            {
//                uint64_t nbatch = calculate_(s1, s2, s3, s4);
//                ntotal += nbatch;
//                outbuffer += nbatch;

//                // be safe with unsigned types
//                bufsize = ( (nbatch >= bufsize) ? 0 : (bufsize - nbatch) );
//            }

            return nullptr;
        }



    private:
        bool initialized_; //!< Has initialize() been called


        void initialized_or_throw_(void) const
        {
            if(!initialized_)
                throw PulsarException("Module is not yet initialized");
        }

        void uninitialized_or_throw_(void) const
        {
            if(initialized_)
                throw PulsarException("Module has already been initialized");
        }
};


class ThreeCenterIntegral_Py : public ThreeCenterIntegral
{
    public:
        using ThreeCenterIntegral::ThreeCenterIntegral;

        MODULEBASE_FORWARD_PROTECTED_TO_PY

        virtual void initialize_(unsigned int deriv,
                                 const Wavefunction & wfn,
                                 const BasisSet & bs1,
                                 const BasisSet & bs2,
                                 const BasisSet & bs3)

        {
            return call_py_override<void>(this, "initialize_", deriv, wfn, bs1, bs2, bs3);
        }


        virtual unsigned int n_components_(void) const
        {
            if(has_py_override<ThreeCenterIntegral>(this, "n_components_"))
                return call_py_override<unsigned int>(this, "n_components_");
            else
                return ThreeCenterIntegral::n_components_();
        }

        virtual HashType my_hash_(unsigned int deriv,
                                  const Wavefunction &wfn,
                                  const BasisSet &bs1,
                                  const BasisSet &bs2,
                                  const BasisSet &bs3)
        {
            return call_py_override<HashType>(this,"my_hash_", deriv, wfn,bs1, bs2,bs3);
        }
        virtual const double* calculate_(uint64_t shell1, uint64_t shell2,
                                    uint64_t shell3)
        {
                pybind11::list ints =
                    call_py_override<pybind11::list>(this,"calculate_",shell1,shell2,shell3);

                return helper_.py_2_int(ints);
        }


        virtual const double* calculate_multi_(const std::vector<uint64_t> & shells1,
                                          const std::vector<uint64_t> & shells2,
                                          const std::vector<uint64_t> & shells3)
        {

              if(has_py_override<ThreeCenterIntegral>(this, "calculate_multi_"))
              {
                  pybind11::list ints=
                          call_py_override<pybind11::list>(this,"calculate_multi_",shells1,shells2,shells3);
                  return helper_.py_2_int(ints);
              }

              return ThreeCenterIntegral::calculate_multi_(shells1, shells2, shells3);
        }

};

} // close namespace pulsar
