

#ifndef LTE_TEST_PATHLOSS_MODEL_H
#define LTE_TEST_PATHLOSS_MODEL_H

#include "ns3/spectrum-value.h"

#include "ns3/test.h"

#include <ns3/buildings-propagation-loss-model.h>


using namespace ns3;


class LtePathlossModelTestSuite : public TestSuite
{
public:
  LtePathlossModelTestSuite ();
};


class LtePathlossModelSystemTestCase : public TestCase
{
  public:
    LtePathlossModelSystemTestCase (std::string name, double snrDb, double dist, uint16_t mcsIndex);
    LtePathlossModelSystemTestCase ();
    virtual ~LtePathlossModelSystemTestCase ();
    
    void DlScheduling (uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                       uint8_t mcsTb1, uint16_t sizeTb1, uint8_t mcsTb2, uint16_t sizeTb2);
                       
  private:
    virtual void DoRun (void);
    
    double m_snrDb;
    double m_distance;
    uint16_t m_mcsIndex;
};

#endif /* LTE_TEST_PATHLOSS_MODEL_H */

