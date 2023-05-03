
#ifndef LTE_CONTROL_MESSAGES_H
#define LTE_CONTROL_MESSAGES_H

#include <ns3/ptr.h>
#include <ns3/simple-ref-count.h>
#include <ns3/ff-mac-common.h>
#include <ns3/lte-rrc-sap.h>
#include <list>

namespace ns3 {

class LteNetDevice;


class LteControlMessage : public SimpleRefCount<LteControlMessage>
{
public:
 
  enum MessageType
  {
    DL_DCI, UL_DCI, 
    DL_CQI, UL_CQI, 
    BSR, 
    DL_HARQ, 
    RACH_PREAMBLE, 
    RAR, 
    MIB, 
    SIB1, 
  };

  LteControlMessage (void);
  virtual ~LteControlMessage (void);

 
  void SetMessageType (MessageType type);
  
  MessageType GetMessageType (void);

private:
  MessageType m_type;
};

class DlDciLteControlMessage : public LteControlMessage
{
public:
  DlDciLteControlMessage (void);
  virtual ~DlDciLteControlMessage (void);

  void SetDci (DlDciListElement_s dci);

  DlDciListElement_s GetDci (void);

private:
  DlDciListElement_s m_dci;
};


class UlDciLteControlMessage : public LteControlMessage
{
public:
  UlDciLteControlMessage (void);
  virtual ~UlDciLteControlMessage (void);

 
  void SetDci (UlDciListElement_s dci);

  
  UlDciListElement_s GetDci (void);

private:
  UlDciListElement_s m_dci;
};


class DlCqiLteControlMessage : public LteControlMessage
{
public:
  DlCqiLteControlMessage (void);
  virtual ~DlCqiLteControlMessage (void);

  void SetDlCqi (CqiListElement_s dlcqi);

  CqiListElement_s GetDlCqi (void);

private:
  CqiListElement_s m_dlCqi;
};


class BsrLteControlMessage : public LteControlMessage
{
public:
  BsrLteControlMessage (void);
  virtual ~BsrLteControlMessage (void);

  void SetBsr (MacCeListElement_s bsr);

  MacCeListElement_s GetBsr (void);

private:
  MacCeListElement_s m_bsr;

};


class DlHarqFeedbackLteControlMessage : public LteControlMessage
{
public:
  DlHarqFeedbackLteControlMessage (void);
  virtual ~DlHarqFeedbackLteControlMessage (void);

  void SetDlHarqFeedback (DlInfoListElement_s m);

  DlInfoListElement_s GetDlHarqFeedback (void);

private:
  DlInfoListElement_s m_dlInfoListElement;

};



class RachPreambleLteControlMessage : public LteControlMessage
{
public:
  RachPreambleLteControlMessage (void);
  
 
  void SetRapId (uint32_t rapid);
  
  
  uint32_t GetRapId () const;

private:
  uint32_t m_rapId;

};



class RarLteControlMessage : public LteControlMessage
{
public:
  RarLteControlMessage (void);

  /** 
   * 
   * \param raRnti the RA-RNTI, see 3GPP TS 36.321 5.1.4
   */
  void SetRaRnti (uint16_t raRnti);

  /** 
   * 
   * \return  the RA-RNTI, see 3GPP TS 36.321 5.1.4
   */
  uint16_t GetRaRnti () const;

  /**
   * a MAC RAR and the corresponding RAPID subheader 
   * 
   */
  struct Rar
  {
    uint8_t rapId;
    BuildRarListElement_s rarPayload;
  };

  /** 
   * add a RAR to the MAC PDU, see 3GPP TS 36.321 6.2.3
   * 
   * \param rar the rar
   */
  void AddRar (Rar rar);

  /** 
   * 
   * \return a const iterator to the beginning of the RAR list
   */
  std::list<Rar>::const_iterator RarListBegin () const;
  
  /** 
   * 
   * \return a const iterator to the end of the RAR list
   */
  std::list<Rar>::const_iterator RarListEnd () const;

private:
  std::list<Rar> m_rarList;
  uint16_t m_raRnti;

};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * \brief Abstract model for broadcasting the Master Information Block (MIB)
 *        within the control channel (BCCH).
 *
 * MIB is transmitted by eNodeB RRC and received by UE RRC at every radio frame,
 * i.e., every 10 milliseconds.
 *
 * \sa LteEnbRrc::ConfigureCell, LteEnbPhy::StartFrame,
 *     LteUeRrc::DoRecvMasterInformationBlock
 */
class MibLteControlMessage : public LteControlMessage
{
public:
  /**
   * \brief Create a new instance of MIB control message.
   */
  MibLteControlMessage (void);

  /**
   * \brief Replace the MIB content of this control message.
   * \param mib the desired MIB content
   */
  void SetMib (LteRrcSap::MasterInformationBlock mib);

  /**
   * \brief Retrieve the MIB content from this control message.
   * \return the current MIB content that this control message holds
   */
  LteRrcSap::MasterInformationBlock GetMib () const;

private:
  LteRrcSap::MasterInformationBlock m_mib;

}; // end of class MibLteControlMessage


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * \brief Abstract model for broadcasting the System Information Block Type 1
 *        (SIB1) within the control channel (BCCH).
 *
 * SIB1 is transmitted by eNodeB RRC and received by UE RRC at the 6th subframe
 * of every odd-numbered radio frame, i.e., every 20 milliseconds.
 *
 * \sa LteEnbRrc::SetSystemInformationBlockType1, LteEnbPhy::StartSubFrame,
 *     LteUeRrc::DoRecvSystemInformationBlockType1
 */
class Sib1LteControlMessage : public LteControlMessage
{
public:
  /**
   * \brief Create a new instance of SIB1 control message.
   */
  Sib1LteControlMessage (void);

  /**
   * \brief Replace the SIB1 content of this control message.
   * \param sib1 the desired SIB1 content
   */
  void SetSib1 (LteRrcSap::SystemInformationBlockType1 sib1);

  /**
   * \brief Retrieve the SIB1 content from this control message.
   * \return the current SIB1 content that this control message holds
   */
  LteRrcSap::SystemInformationBlockType1 GetSib1 () const;

private:
  LteRrcSap::SystemInformationBlockType1 m_sib1;

}; // end of class Sib1LteControlMessage


} // namespace ns3

#endif  // LTE_CONTROL_MESSAGES_H
