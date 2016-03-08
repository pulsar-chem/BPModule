/*\file
 *
 * \brief Atoms and atomic centers (header)
*/


#ifndef BPMODULE_GUARD_SYSTEM__ATOM_HPP_
#define BPMODULE_GUARD_SYSTEM__ATOM_HPP_

#include "bpmodule/system/CoordType.hpp"
#include "bpmodule/system/BasisShellInfo.hpp"


namespace bpmodule {
namespace system {



/*! \brief A center in a molecule
 *
 * Atoms contain a unique index, which must be set on construction.
 * This would generally be the input ordering, but is otherwise arbitrary.
 *
 * Generally, Atoms would be created by one of the CreateAtom
 * free functions, which fill in much of the information with defaults
 * given a Z number (and optionally an isotope number).
 *
 * Many values which are traditionally integers are instead represented
 * as doubles, which allows for fractional occupation.
 *
 * Data is stored within the Atom object, therefore copying will not
 * create aliases.
 *
 * Follows PointConcept via derivation from math::Point
 */
class Atom : public math::Point
{
    private:
        size_t idx_;   //!< Unique index of the atom
        int Z_;        //!< Atomic Z number (as integer. Also stored as a (double) weight)
        int isonum_;   //!< Isotope number

        double mass_;           //!< Atomic mass (abundance-weighted isotope masses)
        double isotopemass_;    //!< Mass of the selected isotope
        double charge_;         //!< Charge on the center
        double multiplicity_;   //!< Electronic multiplicity
        double nelectrons_;     //!< Number of assigned electrons

        BasisShellInfoMap bshells_; //!< Basis functions associated with this atom/center

    public:
        /*! \brief Constructor
         */
        Atom(size_t idx,  CoordType xyz, int Z, int isonum,
             double charge, double multiplicity, double nelectrons)
        {
            // we do it this way in case we change where the info is stored
            idx_ = idx;
            SetCoords(xyz);
            SetZ(Z);
            SetIsonum(isonum);
            SetCharge(charge);
            SetMultiplicity(multiplicity);
            SetNElectrons(nelectrons);
        }


        Atom(const Atom &)             = default;
        Atom & operator=(const Atom &) = default;
        Atom(Atom &&)                  = default;
        Atom & operator=(Atom &&)      = default;


        /* \brief Equality comparison
         *
         * This compares all components individually
         */
        bool operator==(const Atom & rhs) const;

        /* \brief Inequality comparison
         *
         * This compares all components individually
         */
        bool operator!=(const Atom & rhs) const;



        /*! \name General properties
         */ 
        ///@{ 

        /*
         * I'm aware that a class with lots of getters/setters is bad
         * form. However, we are leaving it open to future optimizations,
         * such as storing the data elsewhere
         */

        /*! \brief Get the unique index of this atom
         *
         * Typically, the index will represent the input ordering
         */
        size_t GetIdx(void) const noexcept
        {
            return idx_;
        }

        /*! \brief Get the atomic Z number (number of protons) */
        int GetZ(void) const noexcept
        {
            return Z_;
        }

        /*! \brief Set the atomic Z number (number of protons) */
        void SetZ(int Z) noexcept
        {
            Z_ = Z;
        }


        /*! \brief Get the isotope number (number of protons + neutrons) */
        int GetIsonum(void) const noexcept
        {
            return isonum_;
        }

        /*! \brief Set the isotope number (number of protons + neutrons) */
        void SetIsonum(int isonum) noexcept
        {
            isonum_ = isonum;
        }


        /*! \brief Get the atomic mass (isotope masses weighted by abundance) */
        double GetMass(void) const
        {
            return mass_;
        }

        /*! \brief Set the atomic mass (isotope masses weighted by abundance) */
        void SetMass(double mass)
        {
            mass_ = mass;
        };


        /*! \brief Get the mass of the isotope */
        double GetIsotopeMass(void) const
        {
            return isotopemass_;
        }

        /*! \brief Set the mass of the isotope */
        void SetIsotopeMass(double isotopemass)
        {
            isotopemass_ = isotopemass;
        };


        /*! \brief Get the charge on this atom/center */
        double GetCharge(void) const noexcept
        {
            return charge_;
        }

        /*! \brief Set the charge on this atom/center */
        void SetCharge(double charge) noexcept
        {
            charge_ = charge;
        }


        /*! \brief Get the electronic multiplicity of this atom/center  */
        double GetMultiplicity(void) const noexcept
        {
            return charge_;
        }

        /*! \brief Set the electronic multiplicity of this atom/center  */
        void SetMultiplicity(double m) noexcept
        {
            multiplicity_ = m;
        }


        /*! \brief Get the number of electrons assigned to this atom/center */
        double GetNElectrons(void) const noexcept
        {
            return nelectrons_;
        }

        /*! \brief Set the number of electrons assigned to this atom/center */
        void SetNElectrons(double n) noexcept
        {
            nelectrons_ = n;
        }

        /*! \brief Get the name of the element */
        std::string GetName(void) const;

        /*! \brief Get the symbol of the element */
        std::string GetSymbol(void) const;


        ///@}



        /*! \name Basis Set information
         */ 
        ///@{ 

        /*! \brief See is this atom has a basis set assigned with the given label
         */
        bool HasShells(const std::string & label) const
        {
            return bshells_.count(label);
        }

        /*! \brief Number of shells with this label on this atom
         */
        int NShell(const std::string & label) const
        {
            if(!HasShells(label))
                return 0;
            return bshells_.at(label).size();
        }

        /*! \brief Get all basis set information for this atom
         * 
         * Returns all the shells for all the different assigned basis sets
         */
        BasisShellInfoMap GetAllShells(void) const
        {
            return bshells_;
        }

        /*! \brief Get information for a particular assigned basis set
         * 
         * If a basis set with the given label doesn't exist on this center, an
         * empty BasisShellInfoVector is returned
         */
        BasisShellInfoVector GetShells(const std::string & label) const
        {
            if(HasShells(label))
                return bshells_.at(label);
            else
                return BasisShellInfoVector();
        }

        /*! \brief Set all the shells for a basis set with a given label
         * 
         * Existing basis set information (for that label) is overwritten
         */
        void SetShells(const std::string & label, const BasisShellInfoVector & shells)
        {
            bshells_[label] = shells;
        }

        /*! \brief Append a shell to a basis set with a given label
         */
        void AddShell(const std::string & label, const BasisShellInfo & shell)
        {
            bshells_[label].push_back(shell);
        }

        ///@}

};

//! \todo What to do about printing
std::ostream& operator<<(std::ostream& os,const Atom& A);


/* \brief Create an atom given an ID, coordinates, and atomic number
 *
 * The rest of the data is filled in automatically
 */
Atom CreateAtom(size_t idx, CoordType xyz, int Z);


/*! \copydocs CreateAtom(size_t,size_t, CoordType, int) */
Atom CreateAtom(size_t idx, double x, double y, double z, int Z);



/* \brief Create an atom given an ID, coordinates, atomic number, and isotope number
 *
 * The rest of the data is filled in automatically
 */
Atom CreateAtom(size_t idx, CoordType xyz, int Z, int isonum);


/*! \copydocs CreateAtom(size_t,size_t, CoordType, int, int) */
Atom CreateAtom(size_t idx, double x, double y, double z, int Z, int isonum);




} // close namespace system
} // close namespace bpmodule

#endif

