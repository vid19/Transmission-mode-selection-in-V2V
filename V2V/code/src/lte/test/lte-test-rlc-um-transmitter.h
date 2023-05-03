
#ifndef LTE_TEST_RLC_UM_TRANSMITTER_H
#define LTE_TEST_RLC_UM_TRANSMITTER_H

#include "ns3/test.h"

namespace ns3 {

class LteTestRrc;
class LteTestMac;
class LteTestPdcp;

}

using namespace ns3;


class LteRlcUmTransmitterTestSuite : public TestSuite
{
  public:
    LteRlcUmTransmitterTestSuite ();
};

class LteRlcUmTransmitterTestCase : public TestCase
{
  public:
    LteRlcUmTransmitterTestCase (std::string name);
    LteRlcUmTransmitterTestCase ();
    virtual ~LteRlcUmTransmitterTestCase ();

    void CheckDataReceived (Time time, std::string shouldReceived, std::string assertMsg);

  protected:
    virtual void DoRun (void);

    Ptr<LteTestPdcp> txPdcp;
    Ptr<LteRlc> txRlc;
    Ptr<LteTestMac> txMac;

  private:
    void DoCheckDataReceived (std::string shouldReceived, std::string assertMsg);

};


class LteRlcUmTransmitterOneSduTestCase : public LteRlcUmTransmitterTestCase
{
  public:
    LteRlcUmTransmitterOneSduTestCase (std::string name);
    LteRlcUmTransmitterOneSduTestCase ();
    virtual ~LteRlcUmTransmitterOneSduTestCase ();

  private:
    virtual void DoRun (void);

};

/**
 * Test 4.1.1.2 Segmentation (One SDU => n PDUs)
 */
class LteRlcUmTransmitterSegmentationTestCase : public LteRlcUmTransmitterTestCase
{
  public:
    LteRlcUmTransmitterSegmentationTestCase (std::string name);
    LteRlcUmTransmitterSegmentationTestCase ();
    virtual ~LteRlcUmTransmitterSegmentationTestCase ();

  private:
    virtual void DoRun (void);

};

/**
 * Test 4.1.1.3 Concatenation (n SDUs => One PDU)
 */
class LteRlcUmTransmitterConcatenationTestCase : public LteRlcUmTransmitterTestCase
{
  public:
    LteRlcUmTransmitterConcatenationTestCase (std::string name);
    LteRlcUmTransmitterConcatenationTestCase ();
    virtual ~LteRlcUmTransmitterConcatenationTestCase ();

  private:
    virtual void DoRun (void);

};

/**
 * Test 4.1.1.4 Report Buffer Status (test primitive parameters)
 */
class LteRlcUmTransmitterReportBufferStatusTestCase : public LteRlcUmTransmitterTestCase
{
  public:
    LteRlcUmTransmitterReportBufferStatusTestCase (std::string name);
    LteRlcUmTransmitterReportBufferStatusTestCase ();
    virtual ~LteRlcUmTransmitterReportBufferStatusTestCase ();

  private:
    virtual void DoRun (void);

};

#endif /* LTE_TEST_RLC_UM_TRANSMITTER_H */
