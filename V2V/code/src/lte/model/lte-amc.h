
#ifndef AMCMODULE_H
#define AMCMODULE_H

#include <vector>
#include <ns3/ptr.h>
#include <ns3/object.h>

namespace ns3 {

class SpectrumValue;


class LteAmc : public Object
{

public:
  static TypeId GetTypeId (void);
  
  LteAmc ();
  virtual ~LteAmc();
  
  enum AmcModel
    {
      
      PiroEW2010,
      
      MiErrorModel
    };
  
 int GetMcsFromCqi (int cqi);

 int GetTbSizeFromMcs (int mcs, int nprb);

   double GetSpectralEfficiencyFromCqi (int cqi);
 std::vector<int> CreateCqiFeedbacks (const SpectrumValue& sinr,
                                                  uint8_t rbgSize = 0);

  int GetCqiFromSpectralEfficiency (double s);
  
private:
  
  double m_ber;

  AmcModel m_amcModel;

}; 


}

#endif /* AMCMODULE_H */
