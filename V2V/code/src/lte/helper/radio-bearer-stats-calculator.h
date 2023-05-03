

#ifndef RADIO_BEARER_STATS_CALCULATOR_H_
#define RADIO_BEARER_STATS_CALCULATOR_H_

#include "ns3/lte-stats-calculator.h"
#include "ns3/lte-common.h"
#include "ns3/uinteger.h"
#include "ns3/object.h"
#include "ns3/basic-data-calculators.h"
#include "ns3/lte-common.h"
#include <string>
#include <map>
#include <fstream>

namespace ns3
{
/// Container: (IMSI, LCID) pair, uint32_t
typedef std::map<ImsiLcidPair_t, uint32_t> Uint32Map;
/// Container: (IMSI, LCID) pair, uint64_t
typedef std::map<ImsiLcidPair_t, uint64_t> Uint64Map;
/// Container: (IMSI, LCID) pair, uint32_t calculator
typedef std::map<ImsiLcidPair_t, Ptr<MinMaxAvgTotalCalculator<uint32_t> > > Uint32StatsMap;
/// Container: (IMSI, LCID) pair, uint64_t calculator
typedef std::map<ImsiLcidPair_t, Ptr<MinMaxAvgTotalCalculator<uint64_t> > > Uint64StatsMap;
/// Container: (IMSI, LCID) pair, double
typedef std::map<ImsiLcidPair_t, double> DoubleMap;
/// Container: (IMSI, LCID) pair, LteFlowId_t
typedef std::map<ImsiLcidPair_t, LteFlowId_t> FlowIdMap;


class RadioBearerStatsCalculator : public LteStatsCalculator
{
public:
  /**
   * Class constructor
   */
  RadioBearerStatsCalculator ();

  /**
    * Class constructor
    */
  RadioBearerStatsCalculator (std::string protocolType);

  /**
   * Class destructor
   */
  virtual
  ~RadioBearerStatsCalculator ();

  // Inherited from ns3::Object
  /**
   *  Register this type.
   *  \return The object TypeId.
   */
  static TypeId GetTypeId (void);
  void DoDispose ();


  std::string GetUlOutputFilename (void);

 
  std::string GetDlOutputFilename (void);

 
  void SetUlPdcpOutputFilename (std::string outputFilename);

 
  std::string GetUlPdcpOutputFilename (void);

  
  void SetDlPdcpOutputFilename (std::string outputFilename);

  /**
   * Get the name of the file where the downlink PDCP statistics will be stored.
   * @return the name of the file where the downlink PDCP statistics will be stored
   */
  std::string GetDlPdcpOutputFilename (void);


  /** 
   * 
   * \param t the value of the StartTime attribute
   */
  void SetStartTime (Time t);

  /** 
   * 
   * \return the value of the StartTime attribute
   */
  Time GetStartTime () const;

  /** 
   * 
   * \param e the epoch duration
   */
  void SetEpoch (Time e);

  /** 
   * 
   * \return the epoch duration
   */
  Time GetEpoch () const;


  void
  UlTxPdu (uint16_t cellId, uint64_t imsi, uint16_t rnti, uint8_t lcid, uint32_t packetSize);


  void
  UlRxPdu (uint16_t cellId, uint64_t imsi, uint16_t rnti, uint8_t lcid, uint32_t packetSize, uint64_t delay);


  void
  DlTxPdu (uint16_t cellId, uint64_t imsi, uint16_t rnti, uint8_t lcid, uint32_t packetSize);

 
  void
  DlRxPdu (uint16_t cellId, uint64_t imsi, uint16_t rnti, uint8_t lcid, uint32_t packetSize, uint64_t delay);

  
  uint32_t
  GetUlTxPackets (uint64_t imsi, uint8_t lcid);

  
  uint32_t
  GetUlRxPackets (uint64_t imsi, uint8_t lcid);

  
  uint64_t
  GetUlTxData (uint64_t imsi, uint8_t lcid);

  uint64_t
  GetUlRxData (uint64_t imsi, uint8_t lcid);


  uint32_t
  GetUlCellId (uint64_t imsi, uint8_t lcid);

 
  double
  GetUlDelay (uint64_t imsi, uint8_t lcid);


  std::vector<double>
  GetUlDelayStats (uint64_t imsi, uint8_t lcid);


  std::vector<double>
  GetUlPduSizeStats (uint64_t imsi, uint8_t lcid);


  uint32_t
  GetDlTxPackets (uint64_t imsi, uint8_t lcid);


  uint32_t
  GetDlRxPackets (uint64_t imsi, uint8_t lcid);

  uint64_t
  GetDlTxData (uint64_t imsi, uint8_t lcid);

  uint64_t
  GetDlRxData (uint64_t imsi, uint8_t lcid);

  uint32_t
  GetDlCellId (uint64_t imsi, uint8_t lcid);

  double
  GetDlDelay (uint64_t imsi, uint8_t lcid);

  std::vector<double>
  GetDlDelayStats (uint64_t imsi, uint8_t lcid);

  std::vector<double>
  GetDlPduSizeStats (uint64_t imsi, uint8_t lcid);

private:
  
  void
  ShowResults (void);

  void
  WriteUlResults (std::ofstream& outFile);

  void
  WriteDlResults (std::ofstream& outFile);

  void
  ResetResults (void);

  void RescheduleEndEpoch ();

  void EndEpoch (void);

  EventId m_endEpochEvent; 

  FlowIdMap m_flowId;

  Uint32Map m_dlCellId; 
  Uint32Map m_dlTxPackets; 
  Uint32Map m_dlRxPackets; 
  Uint64Map m_dlTxData; 
  Uint64Map m_dlRxData; 
  Uint64StatsMap m_dlDelay; 
  Uint32StatsMap m_dlPduSize; 

  Uint32Map m_ulCellId; 
  Uint32Map m_ulTxPackets; 
  Uint32Map m_ulRxPackets; 
  Uint64Map m_ulTxData; 
  Uint64Map m_ulRxData; 
  Uint64StatsMap m_ulDelay; 
  Uint32StatsMap m_ulPduSize; 

  /**
   * Start time of the on going epoch
   */
  Time m_startTime;

  /**
   * Epoch duration
   */
  Time m_epochDuration;

  /**
   * true if output files have not been opened yet
   */
  bool m_firstWrite;

  /**
   * true if any output is pending
   */
  bool m_pendingOutput;

  /**
   * Protocol type, by default RLC
   */
  std::string m_protocolType;

  /**
   * Name of the file where the downlink PDCP statistics will be saved
   */
  std::string m_dlPdcpOutputFilename;

  /**
   * Name of the file where the uplink PDCP statistics will be saved
   */
  std::string m_ulPdcpOutputFilename;

};

} // namespace ns3

#endif /* RADIO_BEARER_STATS_CALCULATOR_H_ */
