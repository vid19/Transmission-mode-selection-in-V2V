

#ifndef LTE_TEST_INTERFERENCE_FR_H
#define LTE_TEST_INTERFERENCE_FR_H

#include "ns3/test.h"

using namespace ns3;

/**
 * Test Interference level with FR algorithms
 */
class LteInterferenceFrTestSuite : public TestSuite
{
public:
  LteInterferenceFrTestSuite ();
};


class LteInterferenceHardFrTestCase : public TestCase
{
public:
  LteInterferenceHardFrTestCase (std::string name, double d1, double d2, double dlSinr, double ulSinr);
  virtual ~LteInterferenceHardFrTestCase ();

private:
  virtual void DoRun (void);

  double m_d1;
  double m_d2;
  double m_expectedDlSinrDb;
  double m_expectedUlSinrDb;
};

class LteInterferenceStrictFrTestCase : public TestCase
{
public:
  LteInterferenceStrictFrTestCase (std::string name, double d1, double d2,
                                   double commonDlSinr, double commonUlSinr, double edgeDlSinr, double edgeUlSinr,
                                   uint32_t rspqThreshold);
  virtual ~LteInterferenceStrictFrTestCase ();

private:
  virtual void DoRun (void);

  double m_d1;
  double m_d2;
  double m_commonDlSinrDb;
  double m_commonUlSinrDb;
  double m_edgeDlSinrDb;
  double m_edgeUlSinrDb;

  uint32_t m_rspqThreshold;
};

#endif /* LTE_TEST_INTERFERENCE_FR_H */
