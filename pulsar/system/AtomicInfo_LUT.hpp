/*! \file
 *
 * \brief LUTs for Atomic Information (header)
*/


/**************************************************************
THIS FILE IS GENERATED VIA SCRIPTS. IF YOU WANT
EVERYONE TO STAY SANE, DO NOT EDIT THIS FILE DIRECTLY

Generated via:
    ../../scripts/generate_atomicinfo.py AtomicInfo_LUT

CREATED: 2016-04-24 10:41:52.913532
**************************************************************/


#ifndef PULSAR_GUARD_SYSTEM__ATOMICINFO_LUT_HPP_
#define PULSAR_GUARD_SYSTEM__ATOMICINFO_LUT_HPP_


#include <map>
#include "pulsar/system/AtomicInfo.hpp"
#include "pulsar/util/StringUtil.hpp"



namespace pulsar {
namespace system {
namespace lut {



//////////////////////////////////////////////////
// Various data maps. Stored in LUT source file
//////////////////////////////////////////////////
extern const std::map<int, std::string> atomic_Z_sym_;

extern const std::map<std::string, int, util::CaseInsensitiveLess> atomic_sym_Z_;

extern const std::map<int, AtomicData> atomic_Z_data_;




} // closing namespace lut
} // closing namespace system
} // closing namespace pulsar



#endif
