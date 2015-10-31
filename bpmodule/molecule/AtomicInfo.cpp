#include "bpmodule/molecule/AtomicInfo.hpp"
#include "bpmodule/molecule/AtomicInfo_LUT.hpp"
#include "bpmodule/exception/MoleculeException.hpp"

namespace bpmodule {
namespace molecule {

// global LUT:
// Maps Z to symbol
using lut::atomic_Z_sym_;

// Maps symbol to Z
using lut::atomic_sym_Z_;

// Maps Z to data
using lut::atomic_Z_data_;


int AtomicZNumber(const std::string & sym)
{
    if(atomic_sym_Z_.count(sym))
        return atomic_sym_Z_.at(sym);
    else
        throw exception::MoleculeException("No Z number for this atomic symbol",
                                           "symbol", sym);
}



std::string AtomicSymbol(int Z)
{
    if(atomic_Z_sym_.count(Z))
        return atomic_Z_sym_.at(Z);
    else
        throw exception::MoleculeException("No symbol for this Z number",
                                           "Z", std::to_string(Z));
}



AtomicData AtomicInfo(int Z)
{
    if(atomic_Z_data_.count(Z))
        return atomic_Z_data_.at(Z);
    else
        throw exception::MoleculeException("No atomic data for this Z number",
                                           "Z", std::to_string(Z));
}



AtomicData AtomicInfo(const std::string & sym)
{
    return AtomicInfo(AtomicZNumber(sym));
}



IsotopeData IsotopeInfo(int Z, int isonum)
{
    AtomicData ad = AtomicInfo(Z);
    
    for(const auto & it : ad.isotopes)
        if(it.isonum == isonum)
            return it;

    throw exception::MoleculeException("No isotope data for this Z and isotope number",
                                           "Z", std::to_string(Z),
                                           "isotope", std::to_string(isonum));
}



IsotopeData IsotopeInfo(const std::string & sym, int isonum)
{
    return IsotopeInfo(AtomicZNumber(sym), isonum); 
}



double AtomicMass(int Z)
{
    return AtomicInfo(Z).mass;
}



double AtomicMass(const std::string & sym)
{
    return AtomicInfo(sym).mass;
}



double IsotopeMass(int Z, int isonum)
{
    return IsotopeInfo(Z, isonum).mass;
}



double IsotopeMass(const std::string & sym, int isonum)
{
    return IsotopeInfo(sym, isonum).mass;
}



std::string AtomicName(int Z)
{
    return AtomicInfo(Z).name;
}



std::string AtomicName(const std::string & sym)
{
    return AtomicInfo(sym).name;
}



} // closing namespace molecule
} // closing namespace bpmodule

