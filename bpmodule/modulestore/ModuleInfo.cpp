/*! \file
 *
 * \brief Structure storing information about a module (source)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#include "bpmodule/modulestore/ModuleInfo.hpp"
#include "bpmodule/exception/MapException.hpp"
#include "bpmodule/python_helper/Convert.hpp"

using bpmodule::datastore::OptionMap;
using bpmodule::python_helper::ConvertListToVec;
using bpmodule::python_helper::ConvertToCpp;

namespace bpmodule {
namespace modulestore {


/*! \brief Converts types for ModuleInfo
 *
 * Catches exceptions in conversion and appends some information
 *
 * \tparam T Destination type
 *
 * \param [in] dict The dictionary containing the data
 * \param [in] key The key in the dictionary
 */
template<typename T>
static T DictConvertHelper(const boost::python::dict & dictionary, const char * key)
{
    if(!dictionary.has_key(key))
        throw bpmodule::exception::MapException("Python dictionary missing key", "ModuleInfo", key, typeid(T).name());


    try {
        return ConvertToCpp<T>(dictionary[key]);
    }
    catch(bpmodule::exception::GeneralException & ex)
    {
        ex.AppendInfo({ {"key", key}, {"location", "ModuleInfo"} });
        throw ex;
    }
}


/*! \brief Converts python lists to C++ vectors for ModuleInfo
 *
 * Catches exceptions in conversion and appends some information
 *
 * \tparam T Destination type
 *
 * \param [in] dict The dictionary containing the data
 * \param [in] key The key in the dictionary
 */
template<typename T>
static std::vector<T> DictConvertHelperVec(const boost::python::dict & dictionary, const char * key)
{
    // will make sure it can convert to list
    // and will append key to exception
    boost::python::list lst = DictConvertHelper<boost::python::list>(dictionary, key);


    // Actually convert the vector
    try {
        return ConvertListToVec<T>(lst);
    }
    catch(bpmodule::exception::GeneralException & ex)
    {
        ex.AppendInfo({ {"key", key}, {"location", "ModuleInfo"} });
        throw ex;
    }
}



ModuleInfo::ModuleInfo(const boost::python::dict & dictionary)
{
    try {
        key         = DictConvertHelper<std::string>(dictionary, "key");
        name        = DictConvertHelper<std::string>(dictionary, "name");
        type        = DictConvertHelper<std::string>(dictionary, "type");
        path        = DictConvertHelper<std::string>(dictionary, "path");
        version     = DictConvertHelper<std::string>(dictionary, "version");
        description = DictConvertHelper<std::string>(dictionary, "description");

        authors     = DictConvertHelperVec<std::string>(dictionary, "authors");
        refs        = DictConvertHelperVec<std::string>(dictionary, "refs");

        if(dictionary.has_key("passedoptions"))
        {
            try {
                // DictConvertHelper will make sure it is a list and that the key exists
                options = OptionMap(DictConvertHelper<boost::python::list>(dictionary, "passedoptions"));
            }
            catch(bpmodule::exception::GeneralException & ex)
            {
                ex.AppendInfo({ {"key", "passedoptions"} });
                throw ex;
            }
        }

        // soname is optional
        if(dictionary.has_key("soname"))
            soname = DictConvertHelper<std::string>(dictionary, "soname");
    }
    catch(bpmodule::exception::GeneralException & ex)
    {
        ex.AppendInfo({ {"module", name} }); // name may or may not be set
        throw ex;
    }
}


} // close namespace modulestore
} // close namespace bpmodule

