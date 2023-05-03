

#ifndef A2_A4_RSRQ_HANDOVER_ALGORITHM_H
#define A2_A4_RSRQ_HANDOVER_ALGORITHM_H

#include <ns3/lte-handover-algorithm.h>
#include <ns3/lte-handover-management-sap.h>
#include <ns3/lte-rrc-sap.h>
#include <ns3/simple-ref-count.h>
#include <ns3/ptr.h>
#include <map>

namespace ns3 {



class A2A4RsrqHandoverAlgorithm : public LteHandoverAlgorithm
{
public:
  /// Creates an A2-A4-RSRQ handover algorithm instance.
  A2A4RsrqHandoverAlgorithm ();

  virtual ~A2A4RsrqHandoverAlgorithm ();

  // inherited from Object
  static TypeId GetTypeId ();

  // inherited from LteHandoverAlgorithm
  virtual void SetLteHandoverManagementSapUser (LteHandoverManagementSapUser* s);
  virtual LteHandoverManagementSapProvider* GetLteHandoverManagementSapProvider ();

  // let the forwarder class access the protected and private members
  friend class MemberLteHandoverManagementSapProvider<A2A4RsrqHandoverAlgorithm>;

protected:
  // inherited from Object
  virtual void DoInitialize ();
  virtual void DoDispose ();

  // inherited from LteHandoverAlgorithm as a Handover Management SAP implementation
  void DoReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults);

private:
  
  void EvaluateHandover (uint16_t rnti, uint8_t servingCellRsrq);

  bool IsValidNeighbour (uint16_t cellId);

  void UpdateNeighbourMeasurements (uint16_t rnti, uint16_t cellId,
                                    uint8_t rsrq);

  /// The expected measurement identity for A2 measurements.
  uint8_t m_a2MeasId;
  /// The expected measurement identity for A4 measurements.
  uint8_t m_a4MeasId;

  
  class UeMeasure : public SimpleRefCount<UeMeasure>
  {
  public:
    uint16_t m_cellId; 
    uint8_t m_rsrp;    
    uint8_t m_rsrq;    
  };

  typedef std::map<uint16_t, Ptr<UeMeasure> > MeasurementRow_t;

 
  typedef std::map<uint16_t, MeasurementRow_t> MeasurementTable_t;

  /// Table of measurement reports from all UEs.
  MeasurementTable_t m_neighbourCellMeasures;

  uint8_t m_servingCellThreshold;

  uint8_t m_neighbourCellOffset;

  /// Interface to the eNodeB RRC instance.
  LteHandoverManagementSapUser* m_handoverManagementSapUser;
  /// Receive API calls from the eNodeB RRC instance.
  LteHandoverManagementSapProvider* m_handoverManagementSapProvider;

}; // end of class A2A4RsrqHandoverAlgorithm


} // end of namespace ns3


#endif /* A2_A4_RSRQ_HANDOVER_ALGORITHM_H */
