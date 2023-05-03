

#ifndef PHY_RX_STATS_CALCULATOR_H_
#define PHY_RX_STATS_CALCULATOR_H_

#include "ns3/lte-stats-calculator.h"
#include "ns3/nstime.h"
#include "ns3/uinteger.h"
#include <string>
#include <fstream>
#include <ns3/lte-common.h>

namespace ns3 {


class PhyRxStatsCalculator : public LteStatsCalculator
{
public:
  /**
   * Constructor
   */
  PhyRxStatsCalculator ();

  /**
   * Destructor
   */
  virtual ~PhyRxStatsCalculator ();

  
  static TypeId GetTypeId (void);

  
  void SetUlRxOutputFilename (std::string outputFilename);

  
  std::string GetUlRxOutputFilename (void);

  
  void SetDlRxOutputFilename (std::string outputFilename);

 
  std::string GetDlRxOutputFilename (void);

  void DlPhyReception (PhyReceptionStatParameters params);

  void UlPhyReception (PhyReceptionStatParameters params);

 
  static void DlPhyReceptionCallback (Ptr<PhyRxStatsCalculator> phyRxStats,
                               std::string path, PhyReceptionStatParameters params);

 
  static void UlPhyReceptionCallback (Ptr<PhyRxStatsCalculator> phyRxStats,
                               std::string path, PhyReceptionStatParameters params);
private:

 
  bool m_dlRxFirstWrite;

   bool m_ulRxFirstWrite;

};

} // namespace ns3

#endif /* PHY_RX_STATS_CALCULATOR_H_ */
