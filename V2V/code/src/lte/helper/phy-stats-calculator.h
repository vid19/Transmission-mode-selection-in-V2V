

#ifndef PHY_STATS_CALCULATOR_H_
#define PHY_STATS_CALCULATOR_H_

#include "ns3/lte-stats-calculator.h"
#include "ns3/nstime.h"
#include "ns3/uinteger.h"
#include "ns3/spectrum-value.h"
#include <string>
#include <fstream>

namespace ns3 {

class PhyStatsCalculator : public LteStatsCalculator
{
public:
  /**
   * Constructor
   */
  PhyStatsCalculator ();

  /**
   * Destructor
   */
  virtual ~PhyStatsCalculator ();

 
  static TypeId GetTypeId (void);


  void SetCurrentCellRsrpSinrFilename (std::string filename);

 
  std::string GetCurrentCellRsrpSinrFilename  (void);

  
  void SetUeSinrFilename (std::string filename);

  
  std::string GetUeSinrFilename (void);

  
  void SetInterferenceFilename (std::string filename);

 
  std::string GetInterferenceFilename (void);

  void ReportCurrentCellRsrpSinr (uint16_t cellId, uint64_t imsi, uint16_t rnti, double rsrp, double sinr);

  void ReportUeSinr (uint16_t cellId, uint64_t imsi, uint16_t rnti, double sinrLinear);

 
  void ReportInterference (uint16_t cellId, Ptr<SpectrumValue> interference);

  static void ReportCurrentCellRsrpSinrCallback (Ptr<PhyStatsCalculator> phyStats,
                                          std::string path, uint16_t cellId, uint16_t rnti,
                                          double rsrp, double sinr);
  
  
  static void ReportUeSinr (Ptr<PhyStatsCalculator> phyStats, std::string path,
                     uint16_t cellId, uint16_t rnti, double sinrLinear);

  static void ReportInterference (Ptr<PhyStatsCalculator> phyStats, std::string path,
                           uint16_t cellId, Ptr<SpectrumValue> interference);


private:
  
  bool m_RsrpSinrFirstWrite;

  
  bool m_UeSinrFirstWrite;

 
  bool m_InterferenceFirstWrite;

  std::string m_RsrpSinrFilename;

  std::string m_ueSinrFilename;

  
  std::string m_interferenceFilename;

};

} // namespace ns3

#endif /* PHY_STATS_CALCULATOR_H_ */
