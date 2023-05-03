


#ifndef EPC_TFT_CLASSIFIER_H
#define EPC_TFT_CLASSIFIER_H


#include "ns3/ptr.h"
#include "ns3/simple-ref-count.h"
#include "ns3/epc-tft.h"

#include <map>


namespace ns3 {

class EpcTft;
class Packet;


class EpcTftClassifier : public SimpleRefCount<EpcTftClassifier>
{
public:
  
  EpcTftClassifier ();
  

  void Add (Ptr<EpcTft> tft, uint32_t id);

 
  void Delete (uint32_t id);
  
  uint32_t Classify (Ptr<Packet> p, EpcTft::Direction direction);
  
protected:
  
  std::map <uint32_t, Ptr<EpcTft> > m_tftMap;
  
};



} // namespace ns3
  
#endif /* TFT_CLASSIFIER_H */ 
