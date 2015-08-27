#ifndef TEST_BASE_H
#define TEST_BASE_H

#include "BPModule/core/ModuleBase.hpp"

using namespace bpmodule;


namespace bpmodule {

class Test_Base : public ModuleBase
{
    public:
        Test_Base(unsigned long id, ModuleStore & mstore, const ModuleInfo & minfo);

        virtual void RunTest(void) = 0;
        virtual void CallRunTest(const std::string & other) = 0;
        virtual void Throw(void) = 0;
        virtual void CallThrow(const std::string & other) = 0;

        virtual CalcData CalcTest(CalcData inputs) = 0;
};

}

#endif