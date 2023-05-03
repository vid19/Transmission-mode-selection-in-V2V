
#ifndef LTE_TEST_LINK_ADAPTATION_H
#define LTE_TEST_LINK_ADAPTATION_H

#include "ns3/test.h"


using namespace ns3;


class LteLinkAdaptationTestSuite : public TestSuite
{
public:
  LteLinkAdaptationTestSuite ();
};


class LteLinkAdaptationTestCase : public TestCase
{
public:
  LteLinkAdaptationTestCase (std::string name, double snrDb, double loss, uint16_t mcsIndex);
  LteLinkAdaptationTestCase ();
  virtual ~LteLinkAdaptationTestCase ();

  void DlScheduling (uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                     uint8_t mcsTb1, uint16_t sizeTb1, uint8_t mcsTb2, uint16_t sizeTb2);

private:
  virtual void DoRun (void);

  double m_snrDb;
  double m_loss;
  uint16_t m_mcsIndex;
};

#endif /* LTE_TEST_LINK_ADAPTATION_H */
