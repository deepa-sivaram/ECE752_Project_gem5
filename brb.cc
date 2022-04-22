
#include "cpu/pred/brb.hh"
#include "debug/ECE752_BPred.hh"
#include "base/types.hh"
#include "base/trace.hh"

namespace gem5
{
namespace branch_prediction
{
BRB::BRB()
{
	brb.resize(numEntries);
}

void
BRB::update(Thread tid, std::vector<bool> btablePred, std::vector<bool> btableHyst, unsigned brb_index) 
{
    assert(brb_index < numEntries);
    if (brb_index >= numEntries) {
	    insert_index = evict();
    } else {
	    insert_index = brb_index;
    }
    brb[insert_index].tid = tid;
    brb[insert_index].valid = true;
    brb[insert_index].retainedBtablePrediction = btablePred;
    brb[insert_index].retainedBtableHysteresis = btableHyst;
}

bool
BRB::getPrediction(Addr instPC, Thread tid, BranchInfo* bi)
{
	//unsigned current_indx = (instPC >> instShiftAmt) ^ (tid << (tagShiftAmt - instShiftAmt - log2NumThreads))) & idxMask;
	for (unsigned current_indx = 0; current_indx <= brb_index; current_indx++)
	{
	if(brb[current_indx].valid && (brb[current_indx].tid == tid)) 
		return {brb[current_indx].retainedBtablePrediction[bi->bimodalIndex], brb[current_indx].retainedBtableHysteresis[bi->bimodalIndex]};
	}
}

unsigned
BRB::getIndex()
{
	return brb_index++;
}

unsigned
BRB::evict()
{
	unsigned i = rand[0, numEntries-1];
	brb[i].valid = false;
	return i;
}
} // namespace branch_prediction
} // namespace gem5
                   
