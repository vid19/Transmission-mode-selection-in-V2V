

#ifndef LTE_TEST_CQI_GENERATION_H
#define LTE_TEST_CQI_GENERATION_H

#include "ns3/test.h"

using namespace ns3;

class LteCqiGenerationTestSuite : public TestSuite
{
public:
  LteCqiGenerationTestSuite ();
};

class LteCqiGenerationTestCase : public TestCase
{
public:
  LteCqiGenerationTestCase (std::string name, bool usePdcchForCqiGeneration,
                            uint16_t dlMcs, uint16_t ulMcs);
  virtual ~LteCqiGenerationTestCase ();

  void DlScheduling (uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                     uint8_t mcsTb1, uint16_t sizeTb1, uint8_t mcsTb2, uint16_t sizeTb2);

  void UlScheduling (uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                     uint8_t mcs, uint16_t sizeTb);

private:
  virtual void DoRun (void);

  bool m_usePdcchForCqiGeneration;
  uint16_t m_dlMcs;
  uint16_t m_ulMcs;

};

class LteCqiGenerationDlPowerControlTestCase : public TestCase
{
public:
  LteCqiGenerationDlPowerControlTestCase (std::string name, uint8_t cell0Pa, uint8_t cell1Pa,
                                          uint16_t dlMcs, uint16_t ulMcs);
  virtual ~LteCqiGenerationDlPowerControlTestCase ();

  void DlScheduling (uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                     uint8_t mcsTb1, uint16_t sizeTb1, uint8_t mcsTb2, uint16_t sizeTb2);

  void UlScheduling (uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                     uint8_t mcs, uint16_t sizeTb);

private:
  virtual void DoRun (void);

  uint8_t m_cell0Pa;
  uint8_t m_cell1Pa;

  uint16_t m_dlMcs;
  uint16_t m_ulMcs;

};

#endif /* LTE_TEST_CQI_GENERATION_H */
