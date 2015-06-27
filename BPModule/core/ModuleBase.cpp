#include "BPModule/core/ModuleBase.hpp"
#include "BPModule/core/ModuleStore.hpp"
#include "BPModule/core/Output.hpp"

namespace bpmodule {

ModuleBase::ModuleBase(unsigned long id, ModuleStore & mstore, const ModuleInfo & minfo)
    : id_(id), key_(minfo.key), name_(minfo.name),
      version_(minfo.version), options_(minfo.options),
      mstore_(mstore)
{
    output::Debug("Constructed module [%1%] : %2% v%3%\n", id_, name_, version_);
}

ModuleBase::~ModuleBase()
{
    output::Debug("Destructed module [%1%] : %2% v%3%\n", id_, name_, version_);
}

unsigned long ModuleBase::ID(void) const
{
    return id_;
}

const std::string & ModuleBase::Key(void) const
{
    return key_;
}

const std::string & ModuleBase::Name(void) const
{
    return name_;
}

const std::string & ModuleBase::Version(void) const
{
    return version_;
}

ModuleStore & ModuleBase::MStore(void)
{
    return mstore_;
}


} // close namespace bpmodule
