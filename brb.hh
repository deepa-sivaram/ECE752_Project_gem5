#ifndef __CPU_PRED_BRB_HH__
#define __CPU_PRED_BRB_HH__

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
    DefaultBTB(unsigned numEntries);

    //Updating/Storing btable during context switch
    void update(Thread tid);

    //Initialize BRB
    void init();

    //
    void evict();


  private:
    //The actual BRB
    std::vector<BRBEntry> brb;

    //Number of entries in BRB
    unsigned numEntries;

};

} // namespace branch_prediction
} // namespace gem5

#endif // __CPU_PRED_BRB_HH__
