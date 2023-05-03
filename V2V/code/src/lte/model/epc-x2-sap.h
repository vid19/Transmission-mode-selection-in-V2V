

#ifndef EPC_X2_SAP_H
#define EPC_X2_SAP_H

#include "ns3/packet.h"
#include "ns3/eps-bearer.h"
#include "ns3/ipv4-address.h"

#include <bitset>

namespace ns3 {


class Node;


class EpcX2Sap
{
public:
  virtual ~EpcX2Sap ();
  
 
  struct ErabToBeSetupItem
  {
    uint16_t    erabId;
    EpsBearer   erabLevelQosParameters;
    bool        dlForwarding;
    Ipv4Address transportLayerAddress;
    uint32_t    gtpTeid;

    ErabToBeSetupItem ();
  };

  struct ErabAdmittedItem
  {
    uint16_t    erabId;
    uint32_t    ulGtpTeid;
    uint32_t    dlGtpTeid;
  };


  struct ErabNotAdmittedItem
  {
    uint16_t    erabId;
    uint16_t    cause;
  };


  static const uint16_t m_maxPdcpSn = 4096;
  struct ErabsSubjectToStatusTransferItem
  {
    uint16_t            erabId;
    std::bitset<m_maxPdcpSn> receiveStatusOfUlPdcpSdus;
    uint16_t            ulPdcpSn;
    uint32_t            ulHfn;
    uint16_t            dlPdcpSn;
    uint32_t            dlHfn;
  };

 
  enum UlInterferenceOverloadIndicationItem
  {
    HighInterference,
    MediumInterference,
    LowInterference
  };

  struct UlHighInterferenceInformationItem
  {
    uint16_t    targetCellId;
    std::vector <bool> ulHighInterferenceIndicationList;
  };

  struct RelativeNarrowbandTxBand
  {
    std::vector <bool> rntpPerPrbList;
    int16_t     rntpThreshold;
    uint16_t    antennaPorts;
    uint16_t    pB;
    uint16_t    pdcchInterferenceImpact;
  };

  struct CellInformationItem
  {
    uint16_t    sourceCellId;
    std::vector <UlInterferenceOverloadIndicationItem> ulInterferenceOverloadIndicationList;
    std::vector <UlHighInterferenceInformationItem> ulHighInterferenceInformationList;
    RelativeNarrowbandTxBand relativeNarrowbandTxBand;
  };

  enum LoadIndicator
  {
    LowLoad,
    MediumLoad,
    HighLoad,
    Overload
  };

  struct CompositeAvailCapacity
  {
    uint16_t    cellCapacityClassValue;
    uint16_t    capacityValue;
  };

  struct CellMeasurementResultItem
  {
    uint16_t        sourceCellId;

    LoadIndicator   dlHardwareLoadIndicator;
    LoadIndicator   ulHardwareLoadIndicator;

    LoadIndicator   dlS1TnlLoadIndicator;
    LoadIndicator   ulS1TnlLoadIndicator;

    uint16_t        dlGbrPrbUsage;
    uint16_t        ulGbrPrbUsage;
    uint16_t        dlNonGbrPrbUsage;
    uint16_t        ulNonGbrPrbUsage;
    uint16_t        dlTotalPrbUsage;
    uint16_t        ulTotalPrbUsage;

    CompositeAvailCapacity  dlCompositeAvailableCapacity;
    CompositeAvailCapacity  ulCompositeAvailableCapacity;
  };


  enum IdCause
  {
    HandoverDesirableForRadioReason,
    TimeCriticalHandover
  };

  struct HandoverRequestParams
  {
    uint16_t            oldEnbUeX2apId;
    uint16_t            cause;
    uint16_t            sourceCellId;
    uint16_t            targetCellId;
    uint32_t            mmeUeS1apId;
    uint64_t            ueAggregateMaxBitRateDownlink;
    uint64_t            ueAggregateMaxBitRateUplink;
    std::vector <ErabToBeSetupItem> bearers;
    Ptr<Packet>         rrcContext;
  };

  struct HandoverRequestAckParams
  {
    uint16_t            oldEnbUeX2apId;
    uint16_t            newEnbUeX2apId;
    uint16_t            sourceCellId;
    uint16_t            targetCellId;
    std::vector <ErabAdmittedItem> admittedBearers;
    std::vector <ErabNotAdmittedItem> notAdmittedBearers;
    Ptr<Packet>         rrcContext;
  };

  struct HandoverPreparationFailureParams
  {
    uint16_t            oldEnbUeX2apId;
    uint16_t            sourceCellId;
    uint16_t            targetCellId;
    uint16_t            cause;
    uint16_t            criticalityDiagnostics;
  };

  struct SnStatusTransferParams
  {
    uint16_t            oldEnbUeX2apId;
    uint16_t            newEnbUeX2apId;
    uint16_t            sourceCellId;
    uint16_t            targetCellId;
    std::vector <ErabsSubjectToStatusTransferItem> erabsSubjectToStatusTransferList;
  };

  struct UeContextReleaseParams
  {
    uint16_t            oldEnbUeX2apId;
    uint16_t            newEnbUeX2apId;
    uint16_t            sourceCellId;
    uint16_t            targetCellId;
  };

  struct LoadInformationParams
  {
    uint16_t            targetCellId;
    std::vector <CellInformationItem> cellInformationList;
  };

  struct ResourceStatusUpdateParams
  {
    uint16_t            targetCellId;
    uint16_t            enb1MeasurementId;
    uint16_t            enb2MeasurementId;
    std::vector <CellMeasurementResultItem> cellMeasurementResultList;
  };

  struct UeDataParams
  {
    uint16_t    sourceCellId;
    uint16_t    targetCellId;
    uint32_t    gtpTeid;
    Ptr<Packet> ueData;
  };

};

class EpcX2SapProvider : public EpcX2Sap
{
public:
  virtual ~EpcX2SapProvider ();

  /**
   * Service primitives
   */

  virtual void SendHandoverRequest (HandoverRequestParams params) = 0;

  virtual void SendHandoverRequestAck (HandoverRequestAckParams params) = 0;

  virtual void SendHandoverPreparationFailure (HandoverPreparationFailureParams params) = 0;

  virtual void SendSnStatusTransfer (SnStatusTransferParams params) = 0;

  virtual void SendUeContextRelease (UeContextReleaseParams params) = 0;

  virtual void SendLoadInformation (LoadInformationParams params) = 0;

  virtual void SendResourceStatusUpdate (ResourceStatusUpdateParams params) = 0;

  virtual void SendUeData (UeDataParams params) = 0;
};

class EpcX2SapUser : public EpcX2Sap
{
public:
  virtual ~EpcX2SapUser ();

  /**
   * Service primitives
   */

  virtual void RecvHandoverRequest (HandoverRequestParams params) = 0;

  virtual void RecvHandoverRequestAck (HandoverRequestAckParams params) = 0;

  virtual void RecvHandoverPreparationFailure (HandoverPreparationFailureParams params) = 0;

  virtual void RecvSnStatusTransfer (SnStatusTransferParams params) = 0;

  virtual void RecvUeContextRelease (UeContextReleaseParams params) = 0;

  virtual void RecvLoadInformation (LoadInformationParams params) = 0;
  
  virtual void RecvResourceStatusUpdate (ResourceStatusUpdateParams params) = 0;

  virtual void RecvUeData (UeDataParams params) = 0;
};

///////////////////////////////////////

template <class C>
class EpcX2SpecificEpcX2SapProvider : public EpcX2SapProvider
{
public:
  EpcX2SpecificEpcX2SapProvider (C* x2);

  //
  // Interface implemented from EpcX2SapProvider
  //

  virtual void SendHandoverRequest (HandoverRequestParams params);

  virtual void SendHandoverRequestAck (HandoverRequestAckParams params);

  virtual void SendHandoverPreparationFailure (HandoverPreparationFailureParams params);

  virtual void SendSnStatusTransfer (SnStatusTransferParams params);

  virtual void SendUeContextRelease (UeContextReleaseParams params);

  virtual void SendLoadInformation (LoadInformationParams params);

  virtual void SendResourceStatusUpdate (ResourceStatusUpdateParams params);

  virtual void SendUeData (UeDataParams params);

private:
  EpcX2SpecificEpcX2SapProvider ();
  C* m_x2;
};

template <class C>
EpcX2SpecificEpcX2SapProvider<C>::EpcX2SpecificEpcX2SapProvider (C* x2)
  : m_x2 (x2)
{
}

template <class C>
EpcX2SpecificEpcX2SapProvider<C>::EpcX2SpecificEpcX2SapProvider ()
{
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendHandoverRequest (HandoverRequestParams params)
{
  m_x2->DoSendHandoverRequest (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendHandoverRequestAck (HandoverRequestAckParams params)
{
  m_x2->DoSendHandoverRequestAck (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendHandoverPreparationFailure (HandoverPreparationFailureParams params)
{
  m_x2->DoSendHandoverPreparationFailure (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendSnStatusTransfer (SnStatusTransferParams params)
{
  m_x2->DoSendSnStatusTransfer (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendUeContextRelease (UeContextReleaseParams params)
{
  m_x2->DoSendUeContextRelease (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendLoadInformation (LoadInformationParams params)
{
  m_x2->DoSendLoadInformation (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendResourceStatusUpdate (ResourceStatusUpdateParams params)
{
  m_x2->DoSendResourceStatusUpdate (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapProvider<C>::SendUeData (UeDataParams params)
{
  m_x2->DoSendUeData (params);
}

///////////////////////////////////////

template <class C>
class EpcX2SpecificEpcX2SapUser : public EpcX2SapUser
{
public:
  EpcX2SpecificEpcX2SapUser (C* rrc);

  //
  // Interface implemented from EpcX2SapUser
  //

  virtual void RecvHandoverRequest (HandoverRequestParams params);

  virtual void RecvHandoverRequestAck (HandoverRequestAckParams params);

  virtual void RecvHandoverPreparationFailure (HandoverPreparationFailureParams params);

  virtual void RecvSnStatusTransfer (SnStatusTransferParams params);

  virtual void RecvUeContextRelease (UeContextReleaseParams params);

  virtual void RecvLoadInformation (LoadInformationParams params);

  virtual void RecvResourceStatusUpdate (ResourceStatusUpdateParams params);

  virtual void RecvUeData (UeDataParams params);

private:
  EpcX2SpecificEpcX2SapUser ();
  C* m_rrc;
};

template <class C>
EpcX2SpecificEpcX2SapUser<C>::EpcX2SpecificEpcX2SapUser (C* rrc)
  : m_rrc (rrc)
{
}

template <class C>
EpcX2SpecificEpcX2SapUser<C>::EpcX2SpecificEpcX2SapUser ()
{
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvHandoverRequest (HandoverRequestParams params)
{
  m_rrc->DoRecvHandoverRequest (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvHandoverRequestAck (HandoverRequestAckParams params)
{
  m_rrc->DoRecvHandoverRequestAck (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvHandoverPreparationFailure (HandoverPreparationFailureParams params)
{
  m_rrc->DoRecvHandoverPreparationFailure (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvSnStatusTransfer (SnStatusTransferParams params)
{
  m_rrc->DoRecvSnStatusTransfer (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvUeContextRelease (UeContextReleaseParams params)
{
  m_rrc->DoRecvUeContextRelease (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvLoadInformation (LoadInformationParams params)
{
  m_rrc->DoRecvLoadInformation (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvResourceStatusUpdate (ResourceStatusUpdateParams params)
{
  m_rrc->DoRecvResourceStatusUpdate (params);
}

template <class C>
void
EpcX2SpecificEpcX2SapUser<C>::RecvUeData (UeDataParams params)
{
  m_rrc->DoRecvUeData (params);
}

} // namespace ns3

#endif // EPC_X2_SAP_H
