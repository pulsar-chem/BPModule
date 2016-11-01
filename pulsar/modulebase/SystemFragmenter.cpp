/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include<limits>//for max of double
#include "pulsar/modulebase/SystemFragmenter.hpp"
#include "pulsar/datastore/OptionMap.hpp"
#include "pulsar/math/PowerSetItr.hpp"
#include "pulsar/math/Point.hpp"
#include "pulsar/modulebase/ModuleBase.hpp"

using Frag_t=pulsar::SystemMap::value_type;
using Thresh_t=std::map<size_t,double>;

namespace pulsar{

//Recursive function for establishing the weight of each nmer
//Note b/c we are possibly leaving some out we can't use the closed formulas
void GetCoef(bool Even,const SNType& SN,NMerSetType& NMers){
  /*  if(NMers.count(SN)==0)return;//We assumed this interaction is negligible
    NMers[SN].Weight+=(Even?1.0:-1.0);
    PowerSetItr<SNType> Frags(SN,1,(int)SN.size()-1);
    while(Frags){
        GetCoef(!Even,*Frags,NMers);
        ++Frags;
    }*/
}

NMerSetType SystemFragmenter::make_nmers(const NMerSetType& Frags){
    /*const size_t NEnd=
        std::min(options().get<size_t>("TRUNCATION_ORDER"),Frags.size());
    Thresh_t Dists=options().get<Thresh_t>("DISTANCE_THRESHOLDS");
    NMerSetType NMers;
    const double DaMax=std::numeric_limits<double>::max();


    //Make sure we work in two stupid base case scenarios
    if(NEnd==0)return NMers;//Empty set
    if(NEnd==1)return Frags;//The fragments we were given

    //Real scenarios follow...
    PowerSetItr<NMerSetType> Comb(Frags,1,(int)NEnd);
    while(Comb){
        const size_t N=Comb->size();
        const double DistN=(double)Dists.at(N);
        const double Thresh=(Dists.count(N)==1?(double)N*DistN*DistN:DaMax);
        NMerInfo DaNMer;
        for(const auto& Frag : *Comb){
            const NMerInfo& NMer=Frag.second;
            DaNMer.SN.insert(NMer.SN.begin(),NMer.SN.end());
            if(DaNMer.NMer.size()==0)DaNMer.NMer=NMer.NMer;
            else DaNMer.NMer.insert(NMer.NMer.begin(),NMer.NMer.end());
            DaNMer.Weight=0.0;
        }
        double RHS=0.0;
        const Point CoM=center_of_mass(DaNMer.NMer);
        for(const auto& Frag: *Comb){//We needed the CoM, hence the two loops
            const double Dist=center_of_mass(Frag.second.NMer).distance(CoM);
            RHS+=Dist*Dist;
        }
        if(Thresh>=RHS)NMers.insert({DaNMer.SN,DaNMer});
        ++Comb;
    }
    for(const typename NMerSetType::value_type& NMerI: NMers)
        GetCoef(true,NMerI.first,NMers);
    return NMers;*/
}


}//end namespaces
