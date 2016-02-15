#include <sstream>
#include "bpmodule/system/Atom.hpp"
#include "bpmodule/system/AtomicInfo.hpp"

namespace bpmodule {

//    typedef std::set<const util::Enumeration<system::AtomProperty>*> Set_t;
//    Set_t util::Enumeration<system::AtomProperty>::Enums_=Set_t();
namespace system {


std::string Atom::GetName(void) const
{
    return AtomicNameFromZ(GetZ());

}

std::string Atom::GetSymbol(void) const
{
    return AtomicSymFromZ(GetZ());
}


Atom CreateAtom(size_t id, Atom::CoordType xyz, int Z)
{
    int isonum = MostCommonIsotopeFromZ(Z);
    return CreateAtom(id, xyz, Z, isonum);

}

Atom CreateAtom(size_t id, Atom::CoordType xyz, int Z, int isonum)
{
    return Atom(id,
                xyz,
                Z,
                isonum,
                AtomicMassFromZ(Z),
                IsotopeMassFromZ(Z, isonum),
                0,  //! \todo default charge
                AtomicMultiplicityFromZ(Z),
                Z); //! 0 charge, nelectrons = Z
}

Atom CreateAtom(size_t id, double x, double y, double z, int Z)
{
    return CreateAtom(id, {x,y,z}, Z);
}

Atom CreateAtom(size_t id, double x, double y, double z, int Z, int isonum)
{
    return CreateAtom(id, {x,y,z}, Z, isonum);
}


/*
size_t DefaultMult(size_t Z){
    switch(Z){
        case 0 :{return 1;}
        case 1:{return 2;}
        case 2:{return 1;}
        case 3:{return 2;}
        case 4:{return 1;}
        case 5:{return 2;}
        case 6:{return 3;}
        case 7:{return 4;}
        case 8:{return 3;}
        case 9:{return 2;}
        case 10:{return 1;}
        default:{return 0;}
    }
}    




const AtomProperty AtomProperty::Mass("MASS");
const AtomProperty AtomProperty::Z("ATOMIC NUMBER");
const AtomProperty AtomProperty::Charge("CHARGE");
const AtomProperty AtomProperty::Mult("MULTIPLICITY");
const AtomProperty AtomProperty::NElec("NUMBER OF ELECTRONS");


std::string Atom::Symbol() const{
    return AtomicSymFromZ((int)Z());
}

Atom::Atom(size_t ZIn,double x,double y,double z):
    Base_t(x,y,z){
        AddWeight(AtomProperty::Z,(double)ZIn);
        SetMass(AtomicMassFromZ((int)ZIn));
        SetChargeAndMult(0.0,DefaultMult((int)ZIn));
        SetNElec((double)ZIn);
}

bool Atom::operator==(const Atom& RHS)const{
            if(Z()!=RHS.Z())return false;
            if((*this)[0]!=RHS[0]||
               (*this)[1]!=RHS[1]||
               (*this)[2]!=RHS[2])return false;
            if(NElec()!=RHS.NElec()||Charge()!=RHS.NElec())return false;
            if(Mass()!=RHS.Mass())return false;
            return true;
}

std::string Atom::ToString() const{
    std::stringstream ss;
    ss<<Symbol()<<" "<<(*this)[0]<<" "<<(*this)[1]<<" "<<(*this)[2];
    return ss.str();
}
*/
    

/*
double & Atom::Mass(void)
{
    return Point_t.Weight(AtomWeights::Mass);
}


const double & Atom::Mass(void) const
{
    return Point_t.Weight(AtomWeights::Mass);
}


*/

} // close namespace system
} // close namespace bpmodule
