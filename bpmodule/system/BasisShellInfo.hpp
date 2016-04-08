/*! \file
 *
 * \brief Standalone class for basis shell information (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */

#ifndef BPMODULE_GUARD_SYSTEM__BASISSHELLINFO_HPP_
#define BPMODULE_GUARD_SYSTEM__BASISSHELLINFO_HPP_

#include "bpmodule/system/BasisShellBase.hpp"


namespace bpmodule {
namespace system {


/*! \brief Standalone shell information
 *
 * This class is self contained (ie, does not share data with other objects).
 * This is meant to be stored in System or to be otherwise used by developers
 * without fear of aliasing with other objects.
 *
 * As such, is would generally be "slow" (for some value of slow).
 * In addition, information about the coordinates are not stored here.
 *
 * Data is accessed through the BasisShellBase base class.
 */
class BasisShellInfo : public BasisShellBase
{
    public:
        BasisShellInfo(ShellType type, int am, bool cart, int nprim, int ngen);


        /*! \brief For serialization only
         * 
         * \warning NOT FOR USE OUTSIDE OF SERIALIZATION
         * \todo Replace if cereal fixes this
         */
        BasisShellInfo() = default;


        // compiler generated NOT ok
        // Will leave dangling pointers in the base class
        BasisShellInfo(const BasisShellInfo &);
        BasisShellInfo & operator=(const BasisShellInfo &);

        // These are ok though
        BasisShellInfo(BasisShellInfo &&)                  = default;
        BasisShellInfo & operator=(BasisShellInfo &&)      = default;

        bool operator==(const BasisShellInfo & rhs) const;


    private:
        std::vector<double> alphas_; //!< Exponents (storage)
        std::vector<double> coefs_;  //!< Coefficients (storage)



        //! \name Serialization
        ///@{

        DECLARE_SERIALIZATION_FRIENDS


        template<class Archive>
        void serialize(Archive & ar)
        {
            // we aren't serializing the base class, so we do this manually
            ar(cereal::base_class<BasisShellBase>(this), alphas_, coefs_);

            // if we are unserializing
            BasisShellBase::SetPtrs_(alphas_.data(), coefs_.data());
        }

        ///@}
};


/// A vector of shell information
typedef std::vector<BasisShellInfo> BasisShellInfoVector;


} // close namespace system
} // close namespace bpmodule


#endif