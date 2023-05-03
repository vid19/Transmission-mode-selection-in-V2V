
#ifndef RADIO_BEARER_STATS_CONNECTOR_H
#define RADIO_BEARER_STATS_CONNECTOR_H


#include <ns3/traced-callback.h>
#include <ns3/config.h>
#include <ns3/simple-ref-count.h>
#include <ns3/ptr.h>

#include <set>
#include <map>

namespace ns3 {

class RadioBearerStatsCalculator;


class RadioBearerStatsConnector
{
public:
  /// Constructor
  RadioBearerStatsConnector ();

  
  void EnableRlcStats (Ptr<RadioBearerStatsCalculator> rlcStats);

  
  void EnablePdcpStats (Ptr<RadioBearerStatsCalculator> pdcpStats);

  /**
   * Connects trace sinks to appropriate trace sources
   */
  void EnsureConnected ();

  static void NotifyRandomAccessSuccessfulUe (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  static void NotifyConnectionSetupUe (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  static void NotifyConnectionReconfigurationUe (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  
  static void NotifyHandoverStartUe (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti, uint16_t targetCellId);

  static void NotifyHandoverEndOkUe (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  static void NotifyNewUeContextEnb (RadioBearerStatsConnector* c, std::string context, uint16_t cellid, uint16_t rnti);

  static void NotifyConnectionReconfigurationEnb (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

 
  static void NotifyHandoverStartEnb (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti, uint16_t targetCellId);

  static void NotifyHandoverEndOkEnb (RadioBearerStatsConnector* c, std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

private:
  
  void StoreUeManagerPath (std::string ueManagerPath, uint16_t cellId, uint16_t rnti);

  
  void ConnectSrb0Traces (std::string ueRrcPath, uint64_t imsi, uint16_t cellId, uint16_t rnti);

  void ConnectSrb1TracesUe (std::string ueRrcPath, uint64_t imsi, uint16_t cellId, uint16_t rnti);

  void ConnectTracesUeIfFirstTime (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  void ConnectTracesEnbIfFirstTime (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  void ConnectTracesUe (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  
  void DisconnectTracesUe (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

 
  void ConnectTracesEnb (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  
  void DisconnectTracesEnb (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);


  Ptr<RadioBearerStatsCalculator> m_rlcStats; //!< Calculator for RLC Statistics
  Ptr<RadioBearerStatsCalculator> m_pdcpStats; //!< Calculator for PDCP Statistics

  bool m_connected; //!< true if traces are connected to sinks, initially set to false
  std::set<uint64_t> m_imsiSeenUe; //!< stores all UEs for which RLC and PDCP traces were connected
  std::set<uint64_t> m_imsiSeenEnb; //!< stores all eNBs for which RLC and PDCP traces were connected
  
  /**
   * Struct used as key in m_ueManagerPathByCellIdRnti map
   */
  struct CellIdRnti
  {
    uint16_t cellId; //!< cellId
    uint16_t rnti; //!< rnti
  };

  /**
   * Less than operator for CellIdRnti, because it is used as key in map
   */
  friend bool operator < (const CellIdRnti &a, const CellIdRnti &b);

  /**
   * List UE Manager Paths by CellIdRnti
   */
  std::map<CellIdRnti, std::string> m_ueManagerPathByCellIdRnti;

};



} // namespace ns3


#endif // RADIO_BEARER_STATS_CONNECTOR_H
