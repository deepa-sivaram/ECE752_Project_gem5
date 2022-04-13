#ifndef __CPU_PRED_BRB_HH__
#define __CPU_PRED_BRB_HH__

namespace gem5
{

namespace branch_prediction
{

class BRB
{
  private:
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

  private:
    std::vector<BRBEntry> brb;

};

} // namespace branch_prediction
} // namespace gem5

#endif // __CPU_PRED_BRB_HH__
