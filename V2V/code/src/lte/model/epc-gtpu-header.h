

#ifndef EPS_GTPU_V1_H
#define EPS_GTPU_V1_H

#include <ns3/ptr.h>
#include <ns3/header.h>
#include <ns3/ipv4-header.h>

namespace ns3 {

class Packet;


/**
 * \ingroup lte
 *
 * Implementation of the GTPv1-U Release 10 as per 3Gpp TS 29.281 document
 */
class GtpuHeader : public Header
{
public:
  static TypeId GetTypeId (void);
  GtpuHeader ();
  virtual ~GtpuHeader ();
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
  virtual void Print (std::ostream &os) const;

  bool GetExtensionHeaderFlag () const;
  uint16_t GetLength () const;
  uint8_t GetMessageType () const;
  uint8_t GetNPduNumber () const;
  bool GetNPduNumberFlag () const;
  uint8_t GetNextExtensionType () const;
  bool GetProtocolType () const;
  uint16_t GetSequenceNumber () const;
  bool GetSequenceNumberFlag () const;
  uint32_t GetTeid () const;
  uint8_t GetVersion () const;
  void SetExtensionHeaderFlag (bool m_extensionHeaderFlag);
  void SetLength (uint16_t m_length);
  void SetMessageType (uint8_t m_messageType);
  void SetNPduNumber (uint8_t m_nPduNumber);
  void SetNPduNumberFlag (bool m_nPduNumberFlag);
  void SetNextExtensionType (uint8_t m_nextExtensionType);
  void SetProtocolType (bool m_protocolType);
  void SetSequenceNumber (uint16_t m_sequenceNumber);
  void SetSequenceNumberFlag (bool m_sequenceNumberFlag);
  void SetTeid (uint32_t m_teid);
  void SetVersion (uint8_t m_version);

  bool operator == (const GtpuHeader& b) const;


private:

  uint8_t m_version;   // really a 3 uint3_t


  bool m_protocolType;

 
  bool m_extensionHeaderFlag;

 
  bool m_sequenceNumberFlag;
 
  bool m_nPduNumberFlag;
 
  uint8_t m_messageType;
 
  uint16_t m_length;

 
  uint32_t m_teid;
 
  uint16_t m_sequenceNumber;
  
  uint8_t m_nPduNumber;
  
  uint8_t m_nextExtensionType;

};

} // namespace ns3

#endif /* EPS_GTPU_V1_H */
