

#ifndef LTE_UE_CMAC_SAP_H
#define LTE_UE_CMAC_SAP_H

#include <ns3/packet.h>
#include <ns3/ff-mac-common.h>
#include <ns3/eps-bearer.h>
#include <ns3/lte-common.h>

namespace ns3 {



class LteMacSapUser;


class LteUeCmacSapProvider
{
public:
  virtual ~LteUeCmacSapProvider ();

  struct RachConfig
  {
    uint8_t numberOfRaPreambles;
    uint8_t preambleTransMax;
    uint8_t raResponseWindowSize;
  };
  
  virtual void ConfigureRach (RachConfig rc) = 0;


  virtual void StartContentionBasedRandomAccessProcedure () = 0;


  virtual void StartNonContentionBasedRandomAccessProcedure (uint16_t rnti, uint8_t rapId, uint8_t prachMask) = 0;


  struct LogicalChannelConfig
  {
    uint8_t priority;
    uint16_t prioritizedBitRateKbps;
    uint16_t bucketSizeDurationMs;
    uint8_t logicalChannelGroup;
  };
  
  /** 
   * add a new Logical Channel (LC) 
   * 
   * \param lcId the ID of the LC
   * \param lcConfig the LC configuration provided by the RRC
   * \param msu the corresponding LteMacSapUser
   */
  virtual void AddLc (uint8_t lcId, LogicalChannelConfig lcConfig, LteMacSapUser* msu) = 0;

  /** 
   * remove an existing LC
   * 
   * \param lcId 
   */
  virtual void RemoveLc (uint8_t lcId) = 0;

  /** 
   * reset the MAC
   * 
   */
  virtual void Reset () = 0;
  
};



/**
 * Service Access Point (SAP) offered by the UE MAC to the UE RRC
 *
 * This is the MAC SAP User, i.e., the part of the SAP that contains the RRC methods called by the MAC
 */
class LteUeCmacSapUser
{
public:

  virtual ~LteUeCmacSapUser ();

  /** 
   * 
   * 
   * \param rnti the T-C-RNTI, which will eventually become the C-RNTI after contention resolution
   */
  virtual void SetTemporaryCellRnti (uint16_t rnti) = 0;

  /** 
   * Notify the RRC that the MAC Random Access procedure completed successfully
   * 
   */
  virtual void NotifyRandomAccessSuccessful () = 0;

  /** 
   * Notify the RRC that the MAC Random Access procedure failed
   * 
   */
  virtual void NotifyRandomAccessFailed () = 0;
};




} // namespace ns3


#endif // LTE_UE_CMAC_SAP_H
