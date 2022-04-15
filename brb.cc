#include "cpu/pred/brb.hh"
#include "debug/ECE&52_BPred.hh"

namespace gem5
{
namespace branch_prediction
{
BRB::BRB(unsigned _numEntries) : numEntries(_numEntries)
{
	brb.resize(numEntries);
}

void
BRB::update(Thread tid, std::vector<bool> btablePred, std::vector<bool> btableHyst, unsigned brb_index) 
{
    assert(brb_index < numEntries);

    brb[brb_index].tid = tid;
    brb[brb_index].valid = true;
    brb[brb_index].retainedBtablePrediction = btablePred;
    brb[brb_index].retainedBtableHysteresis = btableHyst;
}

bool
BRB::getPrediction(unsigned brb_index, std::vector<struct> brb, Thread tid, BranchInfo* bi)
{
	if(brb[brb_index].valid && (brb[brb_index].tid == tid)) 
		return {brb[brb_index].retainedBtablePrediction[bi->bimodalIndex], brb[brb_index].retainedBtableHysteresis[bi->bimodalIndex]};
}

void
BRB::getIndex()
{
}

void 
BRB::evict()
{
}
} // namespace branch_prediction
} // namespace gem5
                   
