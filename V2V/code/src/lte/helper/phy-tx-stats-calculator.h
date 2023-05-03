

#ifndef PHY_TX_STATS_CALCULATOR_H_
#define PHY_TX_STATS_CALCULATOR_H_

#include "ns3/lte-stats-calculator.h"
#include "ns3/nstime.h"
#include "ns3/uinteger.h"
#include <string>
#include <fstream>
#include <ns3/lte-common.h>

namespace ns3 {


class PhyTxStatsCalculator : public LteStatsCalculator
{
public:
  /**
   * Constructor
   */
  PhyTxStatsCalculator ();

  /**
   * Destructor
   */
  virtual ~PhyTxStatsCalculator ();

  static TypeId GetTypeId (void);


  void SetUlTxOutputFilename (std::string outputFilename);

 
  std::string GetUlTxOutputFilename (void);

 
  void SetDlTxOutputFilename (std::string outputFilename);

  
  std::string GetDlTxOutputFilename (void);


  void DlPhyTransmission (PhyTransmissionStatParameters params);


  void UlPhyTransmission (PhyTransmissionStatParameters params);

  static void DlPhyTransmissionCallback (Ptr<PhyTxStatsCalculator> phyTxStats,
                                  std::string path, PhyTransmissionStatParameters params);

  static void UlPhyTransmissionCallback (Ptr<PhyTxStatsCalculator> phyTxStats,
                                  std::string path, PhyTransmissionStatParameters params);

private:
 
  bool m_dlTxFirstWrite;

  bool m_ulTxFirstWrite;

};

} // namespace ns3

#endif /* PHY_TX_STATS_CALCULATOR_H_ */
