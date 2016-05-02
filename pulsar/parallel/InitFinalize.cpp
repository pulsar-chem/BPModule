/*! \file
 *
 * \brief Parallelization functionality (source)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 
#include <memory>
#include "pulsar/parallel/InitFinalize.hpp"
#include "pulsar/output/GlobalOutput.hpp"
#include "pulsar/util/Cmdline.hpp"
#include "LibTaskForce.hpp"

namespace pulsar{
namespace parallel {

typedef LibTaskForce::Environment Env_t;
static std::unique_ptr<Env_t> Env_;

const Env_t& GetEnv(){return *Env_;}
 


void Init(size_t NThreads)
{
    output::GlobalOutput("Calling MPI Init\n");
    Env_=std::unique_ptr<Env_t>(new Env_t(NThreads));
    
    //madness::initialize(*(util::GetArgc()), *(util::GetArgv()));
    output::GlobalOutput("Initialized Process %? of %?\n", GetProcID(), GetNProc());
}


void Finalize(void)
{
    output::GlobalOutput("Finalizing Process %? of %?\n", GetProcID(), GetNProc());
    Env_.reset();
    //madness::finalize();
}


long GetProcID(void)
{
    return static_cast<long>(Env_->Comm().Rank());
}


long GetNProc(void)
{
    return static_cast<long>(Env_->Comm().NProcs());
}

} // close namespace parallel
} // close namespace pulsar