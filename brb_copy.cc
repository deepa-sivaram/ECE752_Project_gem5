#include "cpu/pred/brb.hh"
#include "debug/ECE752_BPred.hh"
#include "base/types.hh"
#include "base/trace.hh"

namespace gem5
{
namespace branch_prediction
{
BRB::BRB() : brb_tail_index_ptr(0) 
{
	DPRINTF(ECE752_BPred, "Deepa: Initializing BRB\n");
	brb.resize(numEntries);
	for (unsigned i = 1; i <= numEntries; ++i) {
            brb[i].valid = false;
        }
}

void
BRB::update(ThreadID tid, std::vector<bool> btablePred, std::vector<bool> btableHyst)
{
    unsigned insert_index;
    unsigned brb_index = getIndex();
    if (brb_index == 0)
	    insert_index = evict();
    else 
	    insert_index = brb_index;

    brb[insert_index].tid = tid;
    brb[insert_index].valid = true;
    brb[insert_index].retainedBtablePrediction = btablePred;
    brb[insert_index].retainedBtableHysteresis = btableHyst;
}

bool
BRB::getPrediction(Addr pc, int biModalIndex, ThreadID tid)
{
    for (unsigned current_index = 1; current_index <= brb_tail_index_ptr; current_index++) {
	if(brb[current_index].valid && (brb[current_index].tid == tid))
	    return brb[current_index].retainedBtablePrediction[biModalIndex];
    }
    return 0;
}

void
BRB::basePredUpdate(Addr pc, bool taken, int biModalIndex, ThreadID tid, unsigned logRatioBiModalHystEntries)
{
    for (unsigned current_index = 1; current_index <= brb_tail_index_ptr; current_index++) {
        if(brb[current_index].valid && (brb[current_index].tid == tid)) {
	    int inter = (brb[current_index].retainedBtablePrediction[biModalIndex] << 1) 
		    + brb[current_index].retainedBtableHysteresis[biModalIndex >> logRatioBiModalHystEntries];
	    if (taken) {
		if (inter < 3)
		    inter++;
	    } else if (inter > 0) {
		inter--;
	    }
	    const bool pred = inter >> 1;
	    const bool hyst = inter & 1;
	    brb[current_index].retainedBtablePrediction[biModalIndex] = pred;
	    brb[current_index].retainedBtableHysteresis[biModalIndex >> logRatioBiModalHystEntries] = hyst;
	    DPRINTF(ECE752_BPred, "Deepa: BRB: Updating branch %lx, pred:%d, hyst:%d\n", pc, pred, hyst);
	}
    }
}

unsigned
BRB::getIndex()
{
    if(brb_tail_index_ptr <= numEntries)
	return ++brb_tail_index_ptr;
    else {
	DPRINTF(ECE752_BPred, "BRB Full!! Calling evict func\n");
	return 0;
    }
}

unsigned
BRB::evict()
{
    unsigned evict_index = 1 + (rand() % numEntries);
    DPRINTF(ECE752_BPred, "Evicting data at index %d \n", evict_index);
    brb[evict_index].valid = false;
    return evict_index;
}

} // namespace branch_prediction
} // namespace gem5
                   
