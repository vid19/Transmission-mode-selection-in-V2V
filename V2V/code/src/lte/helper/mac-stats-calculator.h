
#ifndef MAC_STATS_CALCULATOR_H_
#define MAC_STATS_CALCULATOR_H_

#include "ns3/lte-stats-calculator.h"
#include "ns3/nstime.h"
#include "ns3/uinteger.h"
#include <string>
#include <fstream>

namespace ns3 {

class MacStatsCalculator : public LteStatsCalculator
{
public:
 
  MacStatsCalculator ();

  virtual ~MacStatsCalculator ();

  
  static TypeId GetTypeId (void);

  void SetUlOutputFilename (std::string outputFilename);

  
  std::string GetUlOutputFilename (void);

  void SetDlOutputFilename (std::string outputFilename);

  
  std::string GetDlOutputFilename (void);

  void DlScheduling (uint16_t cellId, uint64_t imsi, uint32_t frameNo, uint32_t subframeNo,
                     uint16_t rnti, uint8_t mcsTb1, uint16_t sizeTb1, uint8_t mcsTb2, uint16_t sizeTb2);

  
  void UlScheduling (uint16_t cellId, uint64_t imsi,uint32_t frameNo, uint32_t subframeNo,
                     uint16_t rnti, uint8_t mcsTb, uint16_t sizeTb);

  static void DlSchedulingCallback (Ptr<MacStatsCalculator> macStats,
                             std::string path, uint32_t frameNo, uint32_t subframeNo,
                             uint16_t rnti, uint8_t mcsTb1, uint16_t sizeTb1,
                             uint8_t mcsTb2, uint16_t sizeTb2);

  static void UlSchedulingCallback (Ptr<MacStatsCalculator> macStats, std::string path,
                             uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                             uint8_t mcs, uint16_t size);


private:
  
  bool m_dlFirstWrite;

  
  bool m_ulFirstWrite;

};

} // namespace ns3

#endif /* MAC_STATS_CALCULATOR_H_ */
