#ifndef __CPU_PRED_BRB_HH__
#define __CPU_PRED_BRB_HH__

#include "base/types.hh"
#include <vector>
#include "base/statistics.hh"
#include "cpu/pred/tage_base.hh"

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
        bool valid = false;

	/*Retained Btable*/
	std::vector<bool> retainedBtablePrediction;
     	std::vector<bool> retainedBtableHysteresis;
    };
  public:
    //Constructor
    BRB();

    //Updating/Storing btable during context switch
    void update(Addr pc, Thread tid, BranchInfo *bi);

    //Evict entries from BRB when full
    void evict();

    //Return index of BRB
    void getIndex();

    //Return Prediction from BRB
    void getPrediction();


  private:
    //The actual BRB
    std::vector<BRBEntry> brb;

    //Number of entries in BRB
    const unsigned numEntries = 10;

    //Index pointer that points to the tail of BRB
    unsigned brb_index;

};

} // namespace branch_prediction
} // namespace gem5

#endif // __CPU_PRED_BRB_HH__
