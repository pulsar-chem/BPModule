/*! \file
 *
 * \brief Basis shell from a basis set object (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */

#ifndef PULSAR_GUARD_SYSTEM__BASISSETSHELL_HPP_
#define PULSAR_GUARD_SYSTEM__BASISSETSHELL_HPP_

#include "pulsar/types.h"
#include "pulsar/system/BasisShellBase.hpp"
#include "pulsar/system/CoordType.hpp"
#include "bphash/Hasher.hpp"

namespace pulsar{

// for friend
class BasisSet;


/*! \brief Shell information stored in a BasisSet object
 *
 * This class is not self contained. Instead, the data for
 * alpha, etc, are held elsewhere (in the BasisSet object). As such,
 * it is generally "faster", for various reasons. However,
 * Different objects can share data, so modifying data should probably
 * never be done.
 *
 * \todo Could make non-const stuff protected, and then forward...
 */
class BasisSetShell : public BasisShellBase
{
    /*
     * Since this class is meant to be paired with a basis set, it is not
     * meant to be serialized by itself
     * 
     * RMR- Should the main constructor be made protected/private ?  I'm under
     * the impression noone besides the basis set should be making instances of
     * this class
     */
    public:

        /*! \brief Constructor
         *
         * Will NOT copy data from \p bshell to the new storage space
         * 
         * \param [in] bshell Another shell to copy
         * \param [in] alphaptr Pointer to where this shell's exponents are
         * \param [in] coefptr Pointer to where this shell's coefficients are
         * \param [in] xyzptr Pointer to where this shell's coordinates are
         */
        BasisSetShell(const BasisShellBase & bshell,
                      double * alphaptr, double * coefptr, double * xyzptr) ASSERTIONS_ONLY
            : BasisShellBase(bshell.get_type(), bshell.am(), bshell.n_primitives(), bshell.n_general_contractions())
        {
            set_ptrs_(alphaptr, coefptr, xyzptr);
        }


        // compiler generated ok for move only
        BasisSetShell(const BasisSetShell & rhs)             = delete;
        BasisSetShell(BasisSetShell && rhs)                  = default;
        BasisSetShell & operator=(const BasisSetShell & rhs) = delete;
        BasisSetShell & operator=(BasisSetShell && rhs)      = default;

        bool operator==(const BasisSetShell & rhs) const
        {
            if(this == &rhs)
                return true;

            // this is done manually (rather than "using")
            // prevent implicit comparison between one type and another
            return (
                      std::equal(xyz_, xyz_+3, rhs.xyz_) &&
                      BasisShellBase::base_compare_(rhs)
                   );
        }


        bool operator!=(const BasisSetShell & rhs) const
        {
            return !((*this) == rhs);
        }

        ///@{ Safe, slow access to data

        /// Get the coordinates of the shell
        CoordType get_coords(void) const ASSERTIONS_ONLY
        {
            assert_xyz_ptr_();
            return CoordType{xyz_[0], xyz_[1], xyz_[2]};
        }

        /* Set the coordinates of the shell
         RMR-If you only get thes from BasisSets you can't change the coords
         * 
         void set_coords(const CoordType coords) const
        {
            xyz_[0] = coords[0];
            xyz_[1] = coords[1];
            xyz_[2] = coords[2];
        }
         
        /// Set a single coordinate of the shell
        void set_coord(unsigned int i, double val)
        {
            assert_xyz_ptr_();
            validate_xyz_idx_(i);
            xyz_[i] = val;
        } 
          
         

        */ 
        /// Get a single coordinate of the shell
        double get_coord(unsigned int i) const
        {
            assert_xyz_ptr_();
            validate_xyz_idx_(i);
            return xyz_[i];
        }



        ///@}




        ///@{ Raw, unsafe, fast

        /// Get a pointer to the coordinates of the shell
        const double * coords_ptr(void) const ASSERTIONS_ONLY
        {
            assert_xyz_ptr_();
            return xyz_;
        }

        /// Get a pointer to the coordinates of the shell
        double * coords_ptr(void) ASSERTIONS_ONLY
        {
            assert_xyz_ptr_();
            return xyz_;
        }

        double coord(unsigned int i) const ASSERTIONS_ONLY
        {
            assert_xyz_ptr_();
            assert_xyz_idx_(i);
            return xyz_[i];
        }

        ///@}




        /*! \brief For serialization only
         * 
         * \warning NOT FOR USE OUTSIDE OF SERIALIZATION
         * \todo Replace if cereal fixes this
         */
        BasisSetShell() = default;

        bphash::HashValue my_hash(void) const
        {
            return bphash::make_hash(bphash::HashType::Hash128, *this);
        } 


    private:
        friend class BasisSet;

        double * xyz_;     //!< XYZ coordindates of this center


        void assert_xyz_ptr_(void) const
        {
            
            psr_assert(xyz_ != nullptr, "Null pointers in BasisSetShell");
        }

        void validate_xyz_idx_(unsigned int i) const
        {
            
            if(i > 2)
                throw PulsarException("Attempt to access coordinate direction that does not exist",
                                        "i", i);
        }

        void assert_xyz_idx_(unsigned int i) const
        {
            
            psr_assert(i < 3, "Attempt to access coordinate direction that does not exist",
                                             "i", i);
        }


        void set_ptrs_(double * alphaptr, double * coefptr, double * xyzptr)
        {
            BasisShellBase::set_ptrs_(alphaptr, coefptr); 
            xyz_ = xyzptr;
        }


        //! \name Serialization
        ///@{

        DECLARE_SERIALIZATION_FRIENDS
        BPHASH_DECLARE_HASHING_FRIENDS

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(cereal::base_class<BasisShellBase>(this));
        }

       
        void hash(bphash::Hasher & h) const
        {
            h(static_cast<const BasisShellBase &>(*this),
              bphash::hash_pointer(xyz_, 3));
        }
 
        ///@}
    
};

} // close namespace pulsar


#endif
