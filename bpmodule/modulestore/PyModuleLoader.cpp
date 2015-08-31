#include "bpmodule/output/Output.hpp"
#include "bpmodule/modulestore/PyModuleLoader.hpp"
#include "bpmodule/modulestore/ModuleStore.hpp"
#include "bpmodule/modulebase/ModuleBase.hpp"

using bpmodule::modulebase::ModuleBase;

namespace bpmodule {
namespace modulestore {



PyModuleLoader::PyModuleLoader(ModuleStore * mst)
    : mst_(mst)
{
}



PyModuleLoader::~PyModuleLoader()
{
    UnloadAll();
}



ModuleBase * PyModuleLoader::CreateWrapper_(boost::python::object fn, const std::string & key,
                                            unsigned long id,
                                            const ModuleInfo & minfo)
{
    boost::python::object newobj = fn(key, id, boost::ref(*mst_), boost::ref(minfo));
    objects_[id] = newobj;
    return boost::python::extract<ModuleBase *>(newobj);
}



void PyModuleLoader::DeleteWrapper_(unsigned long id)
{
    DeleteObject_(id);
}



void PyModuleLoader::AddPyModule(const std::string & key,
                                 boost::python::object func, const ModuleInfo & minfo)
{

    ModuleStore::ModuleGeneratorFunc cfunc = std::bind(&PyModuleLoader::CreateWrapper_, this, func,
                                                       std::placeholders::_1,
                                                       std::placeholders::_2,
                                                       std::placeholders::_3);

    ModuleStore::ModuleRemoverFunc dfunc = std::bind(&PyModuleLoader::DeleteWrapper_, this, std::placeholders::_1);
    mst_->AddModule(key, cfunc, dfunc, minfo);
}



void PyModuleLoader::DeleteObject_(unsigned long id)
{
    objects_.erase(id);
}



void PyModuleLoader::UnloadAll(void)
{
    objects_.clear();
}



} // close namespace modulestore
} // close namespace bpmodule