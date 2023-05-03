
#ifndef LENA_TEST_PHY_ERROR_MODEL_H
#define LENA_TEST_PHY_ERROR_MODEL_H

#include <ns3/simulator.h>
#include <ns3/test.h>
#include <ns3/nstime.h>


using namespace ns3;



class LenaDataPhyErrorModelTestCase : public TestCase
{
public:
  LenaDataPhyErrorModelTestCase (uint16_t nUser, uint16_t dist,
                                 double blerRef, uint16_t toleranceRxPackets,
                                 Time statsStartTime, uint32_t rngRun);
  virtual ~LenaDataPhyErrorModelTestCase ();

private:
  virtual void DoRun (void);
  static std::string BuildNameString (uint16_t nUser, uint16_t dist, uint32_t rngRun);
  uint16_t m_nUser;
  uint16_t m_dist;
  double m_blerRef;
  uint16_t m_toleranceRxPackets;
  Time m_statsStartTime; ///< Extra time in the beginning of simulation to allow RRC connection establishment + SRS
  uint32_t m_rngRun;

};



class LenaDlCtrlPhyErrorModelTestCase : public TestCase
{
public:
  LenaDlCtrlPhyErrorModelTestCase (uint16_t nEnb, uint16_t dist,
                                   double blerRef, uint16_t toleranceRxPackets,
                                   Time statsStartTime, uint32_t rngRun);
  virtual ~LenaDlCtrlPhyErrorModelTestCase ();

private:
  virtual void DoRun (void);
  static std::string BuildNameString (uint16_t nUser, uint16_t dist, uint32_t rngRun);
  uint16_t m_nEnb;
  uint16_t m_dist;
  double m_blerRef;
  uint16_t m_toleranceRxPackets;
  Time m_statsStartTime; ///< Extra time in the beginning of simulation to allow RRC connection establishment + SRS
  uint32_t m_rngRun;

};



class LenaTestPhyErrorModelSuite : public TestSuite
{
public:
  LenaTestPhyErrorModelSuite ();
};

#endif /* LENA_TEST_PHY_ERROR_MODEL_H */
