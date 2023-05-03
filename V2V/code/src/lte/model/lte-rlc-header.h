
#ifndef LTE_RLC_HEADER_H
#define LTE_RLC_HEADER_H

#include "ns3/header.h"
#include "ns3/lte-rlc-sequence-number.h"

#include <list>

namespace ns3 {


class LteRlcHeader : public Header
{
public:


  LteRlcHeader ();
  ~LteRlcHeader ();

  void SetFramingInfo (uint8_t framingInfo);
  void SetSequenceNumber (SequenceNumber10 sequenceNumber);

  uint8_t GetFramingInfo () const;
  SequenceNumber10 GetSequenceNumber () const;

  void PushExtensionBit (uint8_t extensionBit);
  void PushLengthIndicator (uint16_t lengthIndicator);

  uint8_t PopExtensionBit (void);
  uint16_t PopLengthIndicator (void);

  typedef enum {
    DATA_FIELD_FOLLOWS  = 0,
    E_LI_FIELDS_FOLLOWS = 1
  } ExtensionBit_t;

  typedef enum {
    FIRST_BYTE    = 0x00,
    NO_FIRST_BYTE = 0x02
  } FramingInfoFirstByte_t;

  typedef enum {
    LAST_BYTE    = 0x00,
    NO_LAST_BYTE = 0x01
  } FramingInfoLastByte_t;


  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual void Print (std::ostream &os) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);

private:
  uint16_t m_headerLength;
  uint8_t  m_framingInfo;      //  2 bits
  SequenceNumber10 m_sequenceNumber;

  std::list <uint8_t> m_extensionBits; // Includes extensionBit of the fixed part
  std::list <uint16_t> m_lengthIndicators;

};

}; // namespace ns3

#endif // LTE_RLC_HEADER_H
