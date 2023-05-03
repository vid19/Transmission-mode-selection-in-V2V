
#ifndef LTE_TEST_FADING_H
#define LTE_TEST_FADING_H

#include "ns3/spectrum-value.h"

#include "ns3/test.h"

#include <ns3/buildings-mobility-model.h>
#include <ns3/buildings-propagation-loss-model.h>
#include <ns3/spectrum-value.h>

#include <ns3/trace-fading-loss-model.h>

using namespace ns3;



class LteFadingTestSuite : public TestSuite
{
  public:
    LteFadingTestSuite ();
};


class LteFadingTestCase : public TestCase
{
  public:
    LteFadingTestCase (Ptr<BuildingsMobilityModel> m1, Ptr<BuildingsMobilityModel> m2, double refValue, std::string name);
    virtual ~LteFadingTestCase ();
    
  private:
    virtual void DoRun (void);
    
    void GetFadingSample ();
    
    Ptr<BuildingsMobilityModel> m_node1;
    Ptr<BuildingsMobilityModel> m_node2;
    Ptr<TraceFadingLossModel> m_fadingModule;
    double m_lossRef;
    std::vector<SpectrumValue> m_fadingSamples;
     
    
};

class LteFadingSystemTestCase : public TestCase
{
  public:
    LteFadingSystemTestCase (std::string name, double snrDb, double dist, uint16_t mcsIndex);
    LteFadingSystemTestCase ();
    virtual ~LteFadingSystemTestCase ();
    
    void DlScheduling (uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                       uint8_t mcsTb1, uint16_t sizeTb1, uint8_t mcsTb2, uint16_t sizeTb2);
                       
  private:
    virtual void DoRun (void);
    
    double m_snrDb;
    double m_distance;
    uint16_t m_mcsIndex;
};

#endif /*LTE_TEST_FADING_H*/
