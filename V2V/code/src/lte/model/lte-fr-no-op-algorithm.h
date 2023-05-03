

#ifndef LTE_FR_NO_OP_ALGORITHM_H
#define LTE_FR_NO_OP_ALGORITHM_H

#include <ns3/lte-ffr-algorithm.h>
#include <ns3/lte-ffr-sap.h>
#include <ns3/lte-ffr-rrc-sap.h>
#include <ns3/lte-rrc-sap.h>

namespace ns3 {


class LteFrNoOpAlgorithm : public LteFfrAlgorithm
{
public:
 
  LteFrNoOpAlgorithm ();

  virtual ~LteFrNoOpAlgorithm ();

  // inherited from Object
  static TypeId GetTypeId ();

  // inherited from LteFfrAlgorithm
  virtual void SetLteFfrSapUser (LteFfrSapUser* s);
  virtual LteFfrSapProvider* GetLteFfrSapProvider ();

  virtual void SetLteFfrRrcSapUser (LteFfrRrcSapUser* s);
  virtual LteFfrRrcSapProvider* GetLteFfrRrcSapProvider ();

  // let the forwarder class access the protected and private members
  friend class MemberLteFfrSapProvider<LteFrNoOpAlgorithm>;
  friend class MemberLteFfrRrcSapProvider<LteFrNoOpAlgorithm>;

protected:
  // inherited from Object
  virtual void DoInitialize ();
  virtual void DoDispose ();

  virtual void Reconfigure ();

  // FFR SAP PROVIDER IMPLEMENTATION
  virtual std::vector <bool> DoGetAvailableDlRbg ();
  virtual bool DoIsDlRbgAvailableForUe (int i, uint16_t rnti);
  virtual std::vector <bool> DoGetAvailableUlRbg ();
  virtual bool DoIsUlRbgAvailableForUe (int i, uint16_t rnti);
  virtual void DoReportDlCqiInfo (const struct FfMacSchedSapProvider::SchedDlCqiInfoReqParameters& params);
  virtual void DoReportUlCqiInfo (const struct FfMacSchedSapProvider::SchedUlCqiInfoReqParameters& params);
  virtual void DoReportUlCqiInfo ( std::map <uint16_t, std::vector <double> > ulCqiMap );
  virtual uint8_t DoGetTpc (uint16_t rnti);
  virtual uint8_t DoGetMinContinuousUlBandwidth ();

  // FFR SAP RRC PROVIDER IMPLEMENTATION
  virtual void DoReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults);
  virtual void DoRecvLoadInformation (EpcX2Sap::LoadInformationParams params);

private:
  // FFR SAP
  LteFfrSapUser* m_ffrSapUser;
  LteFfrSapProvider* m_ffrSapProvider;

  // FFR RRF SAP
  LteFfrRrcSapUser* m_ffrRrcSapUser;
  LteFfrRrcSapProvider* m_ffrRrcSapProvider;

}; // end of class LteFrNoOpAlgorithm


} // end of namespace ns3


#endif /* LTE_FFR_NO_OP_ALGORITHM_H */
