

#ifndef LTE_STATS_CALCULATOR_H_
#define LTE_STATS_CALCULATOR_H_

#include "ns3/object.h"
#include "ns3/string.h"
#include <map>

namespace ns3 {



class LteStatsCalculator : public Object
{
public:
 
  LteStatsCalculator ();

  
  virtual ~LteStatsCalculator ();

  
  static TypeId GetTypeId (void);

  void SetUlOutputFilename (std::string outputFilename);

  
  std::string GetUlOutputFilename (void);

 
  void SetDlOutputFilename (std::string outputFilename);

  std::string GetDlOutputFilename (void);

  bool ExistsImsiPath (std::string path);

  
  void SetImsiPath (std::string path, uint64_t imsi);

  
  uint64_t GetImsiPath (std::string path);

  
  bool ExistsCellIdPath (std::string path);

  void SetCellIdPath (std::string path, uint16_t cellId);

 
  uint16_t GetCellIdPath (std::string path);

protected:

  static uint64_t FindImsiFromEnbRlcPath (std::string path);

  
  static uint64_t FindImsiFromUePhy (std::string path);

 
  static uint64_t FindImsiFromLteNetDevice (std::string path);

 
  static uint16_t FindCellIdFromEnbRlcPath (std::string path);

  static uint64_t FindImsiFromEnbMac (std::string path, uint16_t rnti);

  static uint16_t FindCellIdFromEnbMac (std::string path, uint16_t rnti);

  
  static uint64_t FindImsiForEnb (std::string path, uint16_t rnti);

  
  static uint64_t FindImsiForUe (std::string path, uint16_t rnti);

private:
  
  std::map<std::string, uint64_t> m_pathImsiMap;

  
  std::map<std::string, uint16_t> m_pathCellIdMap;

  
  std::string m_dlOutputFilename;

  
  std::string m_ulOutputFilename;
};

} // namespace ns3

#endif /* LTE_STATS_CALCULATOR_H_ */
