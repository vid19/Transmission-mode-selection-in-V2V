
#ifndef LTE_FFR_ALGORITHM_H
#define LTE_FFR_ALGORITHM_H

#include <ns3/object.h>
#include <ns3/lte-rrc-sap.h>
#include <ns3/epc-x2-sap.h>
#include <ns3/ff-mac-sched-sap.h>
#include <map>

namespace ns3 {

class LteFfrSapUser;
class LteFfrSapProvider;

class LteFfrRrcSapUser;
class LteFfrRrcSapProvider;


class LteFfrAlgorithm : public Object
{
public:
  LteFfrAlgorithm ();
  virtual ~LteFfrAlgorithm ();

  static TypeId GetTypeId ();

 
  virtual void SetLteFfrSapUser (LteFfrSapUser* s) = 0;

  virtual void SetLteFfrRrcSapUser (LteFfrRrcSapUser* s) = 0;

  virtual LteFfrSapProvider* GetLteFfrSapProvider () = 0;

  virtual LteFfrRrcSapProvider* GetLteFfrRrcSapProvider () = 0;

  uint8_t GetUlBandwidth () const;

  void SetUlBandwidth (uint8_t bw);

  
  uint8_t GetDlBandwidth () const;

  void SetDlBandwidth (uint8_t bw);

  void SetFrCellTypeId (uint8_t cellTypeId);

  /**
   * \return cellTypeId which is used for automatic FR configuration
   */
  uint8_t GetFrCellTypeId () const;

protected:

  // inherited from Object
  virtual void DoDispose ();

  /**
   * \brief Automatic FR reconfiguration
   */
  virtual void Reconfigure () = 0;

  
  virtual std::vector <bool> DoGetAvailableDlRbg () = 0;

  
  virtual bool DoIsDlRbgAvailableForUe (int rbId, uint16_t rnti) = 0;

  virtual std::vector <bool> DoGetAvailableUlRbg () = 0;

  virtual bool DoIsUlRbgAvailableForUe (int rbId, uint16_t rnti) = 0;

  
  virtual void DoReportDlCqiInfo (const struct FfMacSchedSapProvider::SchedDlCqiInfoReqParameters& params) = 0;

  virtual void DoReportUlCqiInfo (const struct FfMacSchedSapProvider::SchedUlCqiInfoReqParameters& params) = 0;

  
  virtual void DoReportUlCqiInfo ( std::map <uint16_t, std::vector <double> > ulCqiMap ) = 0;

  virtual uint8_t DoGetTpc (uint16_t rnti) = 0;

  virtual uint8_t DoGetMinContinuousUlBandwidth () = 0;

 
  virtual void DoSetCellId (uint16_t cellId);

  virtual void DoSetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth);

  virtual void DoReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults) = 0;

  virtual void DoRecvLoadInformation (EpcX2Sap::LoadInformationParams params) = 0;

  int GetRbgSize (int dlbandwidth);


  uint16_t m_cellId;

  uint8_t m_dlBandwidth; 
  uint8_t m_ulBandwidth; 

  uint8_t m_frCellTypeId;

  bool m_enabledInUplink;

  bool m_needReconfiguration;

}; // end of class LteFfrAlgorithm


} // end of namespace ns3


#endif /* LTE_FFR_ALGORITHM_H */
