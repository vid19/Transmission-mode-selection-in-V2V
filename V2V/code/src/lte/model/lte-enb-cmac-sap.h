

#ifndef LTE_ENB_CMAC_SAP_H
#define LTE_ENB_CMAC_SAP_H

#include <ns3/packet.h>
#include <ns3/ff-mac-common.h>
#include <ns3/eps-bearer.h>
#include <ns3/lte-common.h>

namespace ns3 {


class LteMacSapUser;


class LteEnbCmacSapProvider
{
public:
  virtual ~LteEnbCmacSapProvider ();
  
  virtual void ConfigureMac (uint8_t ulBandwidth,
                             uint8_t dlBandwidth) = 0;


  virtual void AddUe (uint16_t rnti) = 0;


  virtual void RemoveUe (uint16_t rnti) = 0;

  struct LcInfo
  {
    uint16_t rnti;   
    uint8_t  lcId;   
    uint8_t  lcGroup;
    uint8_t  qci;    
    bool     isGbr;  
    uint64_t mbrUl;  
    uint64_t mbrDl;  
    uint64_t gbrUl;  
    uint64_t gbrDl;  
  };

  virtual void AddLc (LcInfo lcinfo, LteMacSapUser* msu) = 0;

  virtual void ReconfigureLc (LcInfo lcinfo) = 0;

  virtual void ReleaseLc (uint16_t rnti, uint8_t lcid) = 0;
  
  /**
   * \brief Parameters for [re]configuring the UE 
   */
  struct UeConfig
  {
    /**
     * UE id within this cell
     */
    uint16_t  m_rnti;
    /**
     * Transmission mode [1..7] (i.e., SISO, MIMO, etc.)
     */
    uint8_t   m_transmissionMode;
  };

  /** 
   * update the configuration of the UE
   * 
   * \param params 
   */
  virtual void UeUpdateConfigurationReq (UeConfig params) = 0;


  /**
   * struct defining the RACH configuration of the MAC
   * 
   */
  struct RachConfig
  {
    uint8_t numberOfRaPreambles;
    uint8_t preambleTransMax;
    uint8_t raResponseWindowSize;
  };

  /** 
   * 
   * \return the current RACH configuration of the MAC
   */
  virtual RachConfig GetRachConfig () = 0;

  /**
   * 
   * 
   */
  struct AllocateNcRaPreambleReturnValue
  {
    bool valid; ///< true if a valid RA config was allocated, false otherwise
    uint8_t raPreambleId; ///< random access preamble id
    uint8_t raPrachMaskIndex; /// PRACH mask index
  };

  virtual AllocateNcRaPreambleReturnValue AllocateNcRaPreamble (uint16_t rnti) = 0;

};


class LteEnbCmacSapUser
{
public:
  virtual ~LteEnbCmacSapUser ();

 
  virtual uint16_t AllocateTemporaryCellRnti () = 0;

  virtual void NotifyLcConfigResult (uint16_t rnti, uint8_t lcid, bool success) = 0;

 
  struct UeConfig
  {
    /**
     * UE id within this cell
     */
    uint16_t  m_rnti;
    /**
     * Transmission mode [1..7] (i.e., SISO, MIMO, etc.)
     */
    uint8_t   m_transmissionMode;
  };

 
  virtual void RrcConfigurationUpdateInd (UeConfig params) = 0;
};







} // namespace ns3


#endif // MAC_SAP_H
