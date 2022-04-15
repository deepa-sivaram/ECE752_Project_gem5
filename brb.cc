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
    btb[brb_index].valid = true;
    brb[brb_index].retainedBtablePrediction = btablePred;
    brb[brb_index].retainedBtableHysteresis = btableHyst;
}

unsigned
BRB::getPrediction()
{
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
                   
