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
BRB::getPrediction(Addr instPC, std::vector<struct> brb, Thread tid, BranchInfo* bi)
{
	unsigned current_indx = (instPC >> instShiftAmt) ^ (tid << (tagShiftAmt - instShiftAmt - log2NumThreads))) & idxMask;
	if(brb[current_indx].valid && (brb[current_indx].tid == tid)) 
		return {brb[current_indx].retainedBtablePrediction[bi->bimodalIndex], brb[current_indx].retainedBtableHysteresis[bi->bimodalIndex]};
}

unsigned
BRB::getIndex(unsigned brb_index)
{
	return brb_index++;
}

void 
BRB::evict(std::vector<struct> brb)
{
	int i = rand[0, numEntries-1];
	brb[i].valid = false;		
}
} // namespace branch_prediction
} // namespace gem5
                   
