#ifndef __CPU_PRED_BRB_HH__
#define __CPU_PRED_BRB_HH__

#include "base/types.hh"
#include <vector>
#include "base/statistics.hh"
#include "debug/ECE752_BPred.hh"
#include "base/trace.hh"

namespace gem5
{

namespace branch_prediction
{

class BRB
{
  private:
    //Each BRB Entry
    struct BRBEntry
    {
        /** The entry's thread id. */
        ThreadID tid;
        
	/** Whether or not the entry is valid. */
        bool valid;

	/*Retained Btable*/
	std::vector<bool> retainedBtablePrediction;
     	std::vector<bool> retainedBtableHysteresis;

	BRBEntry() 
	{
	    DPRINTF(ECE752_BPred, "Deepa: Initializing BRBEntry");
	    tid = 3;
	    valid = false;
	    const uint64_t bimodalTableSize = 1ULL << 13;
	    retainedBtablePrediction.resize(bimodalTableSize, false);
	    retainedBtableHysteresis.resize(bimodalTableSize >> 2, true);
	}
    };

    //The actual BRB
    std::vector<BRBEntry> brb;

    //Number of entries in BRB
    static const unsigned numEntries = 4;

    //Index pointer that points to the tail of BRB
    unsigned brb_tail_index_ptr;

  public:
    //Constructor
    BRB();

    //Updating/Storing btable during context switch
    void update(ThreadID tid, std::vector<bool> btablePred, std::vector<bool> btableHyst);

    //Evict entries from BRB when full
    unsigned evict();

    //Return index of BRB
    unsigned getIndex(ThreadID tid);

    //Return Prediction from BRB
    bool getPrediction(Addr pc, int biModalIndex, ThreadID tid);

    //Update the bimodal predictor in BRB
    void basePredUpdate(Addr pc, bool taken, int biModalIndex, ThreadID tid, unsigned logRatioBiModalHystEntries);
};

} // namespace branch_prediction
} // namespace gem5

#endif // __CPU_PRED_BRB_HH__
