/*! \file
 *
 * \brief Storage of generic data (inner class)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef _GUARD_OPTIONHOLDER_HPP_
#define _GUARD_OPTIONHOLDER_HPP_

#include <functional>

#include "bpmodule/datastore/OptionBase.hpp"
#include "bpmodule/python_helper/Pybind11.hpp"

namespace bpmodule {
namespace datastore {
namespace detail {



/*! \brief Holds the value and default for an option
 *
 * \note This is a template class, but definitions are in the
 *       cpp file. This class is then defined for the
 *       allowed option types.
 */
template<typename T>
class OptionHolder : public OptionBase
{
    public:
        //! A function that can validate an object of type T
        typedef std::function<OptionIssues (const OptionHolder<T> &)> ValidatorFunc;


        /*! \brief Constructs via pointers
         *
         * This object will take ownership of the value and def pointers.
         * The default value will be validated (if given).
         *
         * The value is not set on construction, only the default
         *
         * \throw bpmodule::exception::OptionException
         *        If the default value is invalid, or
         *        there is a default argument supplied for a 'required' option.
         *
         * \throw bpmodule::exception::PythonCallException
         *       If there is a problem calling the validation function
         *
         * \param [in] key The key of this option
         * \param [in] def The default value
         * \param [in] validator A validator function for this object
         * \param [in] required True if this option is required
         * \param [in] pytype The python type of this option
         * \param [in] help A help string for this option
         *
         */
        OptionHolder(const std::string & key, T * def,
                     ValidatorFunc validator, bool required,
                     python_helper::PythonType pytype,
                     const std::string & help);



        /*! \brief Copy constructor
         *
         * Data will be deep copied
         */
        OptionHolder(const OptionHolder & oph);




        OptionHolder(void)                                  = delete;
        OptionHolder(OptionHolder && oph)                   = delete;
        OptionHolder & operator=(const OptionHolder & oph)  = delete;
        OptionHolder & operator=(OptionHolder && oph)       = delete;
        virtual ~OptionHolder()                             = default;



        /*! \brief Change the stored value
         *
         * This object will copy construct a new value
         *
         * \exstrong
         */
        void Change(const T & value);



        /*! \brief Get the current value
         *
         * If the value is not set, but a default exists, the default is returned.
         *
         * \throw bpmodule::exception::OptionException
         *        If the option does not have a value or a default
         */
        const T & Get(void) const;




        /*! \brief Get the default value
         *
         * \throw bpmodule::exception::OptionException
         *        If the option does not have a default
         */
        const T & GetDefault(void) const;



        ////////////////////////////////////////
        // Virtual functions from OptionBase
        ////////////////////////////////////////

        virtual OptionBasePtr Clone(void) const;

        virtual const char * Type(void) const noexcept;

        const std::type_info & TypeInfo(void) const noexcept;

        virtual std::string DemangledType(void) const;

        virtual bool HasValue(void) const noexcept;

        virtual bool HasDefault(void) const noexcept;

        virtual bool IsDefault(void) const;

        virtual void ResetToDefault(void) noexcept;

        virtual void Print(void) const;

        virtual OptionIssues GetIssues(void) const;

        virtual bool Compare(const OptionBase & rhs) const;

        /////////////////////////////////////////
        // Python-related functions
        /////////////////////////////////////////
        virtual pybind11::object GetPy(void) const;

        virtual void ChangePy(pybind11::object obj);


    private:
        //! A set value for the option
        std::unique_ptr<T> value_;

        //! The default for the option
        std::unique_ptr<T> default_;

        //! Validation function object
        ValidatorFunc validator_;
};





/*! \brief Create an OptionHolder from a python object
 *
 * \throw bpmodule::exception::OptionException
 *        If there is a problem with the option (validation or python conversion problems)
 *
 * \throw bpmodule::exception::PythonCallException
 *        If there is a problem calling the validation function (in validating the default)
 */
OptionBasePtr OptionHolderFactory(const std::string & key, pybind11::object obj);




} //closing namespace detail
} //closing namespace datastore
} //closing namespace bpmodule


#endif
