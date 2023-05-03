

#ifndef ASN1_HEADER_H
#define ASN1_HEADER_H

#include "ns3/header.h"

#include <bitset>
#include <string>

namespace ns3 {

class Asn1Header : public Header
{
public:
  Asn1Header ();
  virtual ~Asn1Header ();

  
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  uint32_t GetSerializedSize (void) const;
  void Serialize (Buffer::Iterator bIterator) const;

 
  virtual uint32_t Deserialize (Buffer::Iterator bIterator) = 0;
  virtual void Print (std::ostream &os) const = 0;

  virtual void PreSerialize (void) const = 0;

protected:
  mutable uint8_t m_serializationPendingBits;
  mutable uint8_t m_numSerializationPendingBits;
  mutable bool m_isDataSerialized; 
  mutable Buffer m_serializationResult; 

 
  void WriteOctet (uint8_t octet) const;

  
  void SerializeBoolean (bool value) const;
 
  void SerializeInteger (int n, int nmin, int nmax) const;
  
  void SerializeSequenceOf (int numElems, int nMax, int nMin) const;
  
  void SerializeChoice (int numOptions, int selectedOption,
                        bool isExtensionMarkerPresent) const;
 
  void SerializeEnum (int numElems, int selectedElem) const;
  /**
   * Serialize nothing (null op)
   */
  void SerializeNull () const;
  /**
   * Finalizes an in progress serialization.
   */
  void FinalizeSerialization () const;

  /**
   * Serialize a bitset
   * \param data data to serialize
   */
  template <int N>
  void SerializeBitset (std::bitset<N> data) const;

  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  template <int N>
  void SerializeSequence (std::bitset<N> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<0> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<1> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<2> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<3> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<4> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<5> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<6> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<9> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<10> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;
  /**
   * Serialize a sequence
   * \param optionalOrDefaultMask Mask to serialize
   * \param isExtensionMarkerPresent true if Extension Marker is present
   */
  void SerializeSequence (std::bitset<11> optionalOrDefaultMask,
                          bool isExtensionMarkerPresent) const;

  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  template <int N>
  void SerializeBitstring (std::bitset<N> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<1> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<2> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<8> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<10> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<16> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<27> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<28> bitstring) const;
  /**
   * Serialize a bitstring
   * \param bitstring bitstring to serialize
   */
  void SerializeBitstring (std::bitset<32> bitstring) const;

  // Deserialization functions

  /**
   * Deserialize a bitset
   * \param data buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  template <int N>
  Buffer::Iterator DeserializeBitset (std::bitset<N> *data,
                                      Buffer::Iterator bIterator);
  /**
   * Deserialize a bitset
   * \param data buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitset (std::bitset<8> *data,
                                      Buffer::Iterator bIterator);

  /**
   * Deserialize a boolean
   * \param value buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBoolean (bool *value,
                                       Buffer::Iterator bIterator);
  /**
   * Deserialize an integer
   * \param n buffer to store the result
   * \param nmin min value to serialize
   * \param nmax max value to serialize
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeInteger (int *n, int nmin, int nmax,
                                       Buffer::Iterator bIterator);
  /**
   * Deserialize a Choice (set of options)
   * \param numOptions number of options
   * \param isExtensionMarkerPresent true if extension mark is present
   * \param selectedOption buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeChoice (int numOptions,
                                      bool isExtensionMarkerPresent,
                                      int *selectedOption,
                                      Buffer::Iterator bIterator);
  /**
   * Deserialize an Enum
   * \param numElems number of elements in the enum
   * \param selectedElem buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeEnum (int numElems, int *selectedElem,
                                    Buffer::Iterator bIterator);

  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  template <int N>
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<N> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<0> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<1> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<2> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<3> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<4> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<5> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<6> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<9> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<10> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);
  /**
   * Deserialize a sequence
   * \param optionalOrDefaultMask buffer to store the result
   * \param isExtensionMarkerPresent true if Extension Marker is present
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequence (std::bitset<11> *optionalOrDefaultMask,
                                        bool isExtensionMarkerPresent,
                                        Buffer::Iterator bIterator);

  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
 template <int N>
  Buffer::Iterator DeserializeBitstring (std::bitset<N> *bitstring,
                                         Buffer::Iterator bIterator);
 /**
  * Deserialize a bitstring
  * \param bitstring buffer to store the result
  * \param bIterator buffer iterator
  * \returns the modified buffer iterator
  */
  Buffer::Iterator DeserializeBitstring (std::bitset<1> *bitstring,
                                         Buffer::Iterator bIterator);
  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitstring (std::bitset<2> *bitstring,
                                         Buffer::Iterator bIterator);
  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitstring (std::bitset<8> *bitstring,
                                         Buffer::Iterator bIterator);
  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitstring (std::bitset<10> *bitstring,
                                         Buffer::Iterator bIterator);
  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitstring (std::bitset<16> *bitstring,
                                         Buffer::Iterator bIterator);
  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitstring (std::bitset<27> *bitstring,
                                         Buffer::Iterator bIterator);
  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitstring (std::bitset<28> *bitstring,
                                         Buffer::Iterator bIterator);
  /**
   * Deserialize a bitstring
   * \param bitstring buffer to store the result
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeBitstring (std::bitset<32> *bitstring,
                                         Buffer::Iterator bIterator);

  /**
   * Deserialize nothing (null op)
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeNull (Buffer::Iterator bIterator);
  /**
   * Deserialize a Sequence
   * \param numElems buffer to store the result
   * \param nMax max value to serialize
   * \param nMin min value to serialize
   * \param bIterator buffer iterator
   * \returns the modified buffer iterator
   */
  Buffer::Iterator DeserializeSequenceOf (int *numElems, int nMax, int nMin,
                                          Buffer::Iterator bIterator);
};

} // namespace ns3

#endif // ASN1_HEADER_H

