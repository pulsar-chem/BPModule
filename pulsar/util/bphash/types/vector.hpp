/*! \file
 *
 * \brief A class that hashes objects
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef PULSAR_GUARD_TYPES__VECTOR_HPP_
#define PULSAR_GUARD_TYPES__VECTOR_HPP_

#include <vector>
#include "pulsar/util/bphash/types/ContainerHelper.hpp"

namespace pulsar{
namespace util {
namespace detail {


///////////////
// vector
///////////////
template<typename T, typename Alloc>
struct ObjectHasher<std::vector<T, Alloc>>
    : public ContainerHasher<std::vector<T, Alloc>> { };


} // close namespace detail
} // close namespace util
} // close namespace pulsar

#endif
