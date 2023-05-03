
#ifndef LTE_TEST_RLC_AM_E2E_H
#define LTE_TEST_RLC_AM_E2E_H

#include "ns3/test.h"


using namespace ns3;



class LteRlcAmE2eTestSuite : public TestSuite
{
public:
  LteRlcAmE2eTestSuite ();
};


class LteRlcAmE2eTestCase : public TestCase
{
  public:
  LteRlcAmE2eTestCase (std::string name, uint32_t seed, double losses, bool bulkSduArrival);
    LteRlcAmE2eTestCase ();
    virtual ~LteRlcAmE2eTestCase ();

  private:
    virtual void DoRun (void);

    void DlDropEvent (Ptr<const Packet> p);
    void UlDropEvent (Ptr<const Packet> p);

    uint32_t m_run;
    double   m_losses;
    bool m_bulkSduArrival;

    uint32_t m_dlDrops;
    uint32_t m_ulDrops;

};

#endif // LTE_TEST_RLC_AM_E2E_H
