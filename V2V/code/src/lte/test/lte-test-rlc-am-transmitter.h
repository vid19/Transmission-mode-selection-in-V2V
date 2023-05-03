
#ifndef LTE_TEST_RLC_AM_TRANSMITTER_H
#define LTE_TEST_RLC_AM_TRANSMITTER_H

#include "ns3/test.h"


namespace ns3 {

class LteTestRrc;
class LteTestMac;
class LteTestPdcp;

}

using namespace ns3;


class LteRlcAmTransmitterTestSuite : public TestSuite
{
  public:
    LteRlcAmTransmitterTestSuite ();
};

class LteRlcAmTransmitterTestCase : public TestCase
{
  public:
    LteRlcAmTransmitterTestCase (std::string name);
    LteRlcAmTransmitterTestCase ();
    virtual ~LteRlcAmTransmitterTestCase ();

    void CheckDataReceived (Time time, std::string shouldReceived, std::string assertMsg);

  protected:
    virtual void DoRun (void);

    Ptr<LteTestPdcp> txPdcp;
    Ptr<LteRlc> txRlc;
    Ptr<LteTestMac> txMac;

  private:
    void DoCheckDataReceived (std::string shouldReceived, std::string assertMsg);

};

/**
 * Test 4.1.1.1 One SDU, One PDU
 */
class LteRlcAmTransmitterOneSduTestCase : public LteRlcAmTransmitterTestCase
{
  public:
    LteRlcAmTransmitterOneSduTestCase (std::string name);
    LteRlcAmTransmitterOneSduTestCase ();
    virtual ~LteRlcAmTransmitterOneSduTestCase ();

  private:
    virtual void DoRun (void);

};

/**
 * Test 4.1.1.2 Segmentation (One SDU => n PDUs)
 */
class LteRlcAmTransmitterSegmentationTestCase : public LteRlcAmTransmitterTestCase
{
  public:
    LteRlcAmTransmitterSegmentationTestCase (std::string name);
    LteRlcAmTransmitterSegmentationTestCase ();
    virtual ~LteRlcAmTransmitterSegmentationTestCase ();

  private:
    virtual void DoRun (void);

};

/**
 * Test 4.1.1.3 Concatenation (n SDUs => One PDU)
 */
class LteRlcAmTransmitterConcatenationTestCase : public LteRlcAmTransmitterTestCase
{
  public:
    LteRlcAmTransmitterConcatenationTestCase (std::string name);
    LteRlcAmTransmitterConcatenationTestCase ();
    virtual ~LteRlcAmTransmitterConcatenationTestCase ();

  private:
    virtual void DoRun (void);

};

/**
 * Test 4.1.1.4 Report Buffer Status (test primitive parameters)
 */
class LteRlcAmTransmitterReportBufferStatusTestCase : public LteRlcAmTransmitterTestCase
{
  public:
    LteRlcAmTransmitterReportBufferStatusTestCase (std::string name);
    LteRlcAmTransmitterReportBufferStatusTestCase ();
    virtual ~LteRlcAmTransmitterReportBufferStatusTestCase ();

  private:
    virtual void DoRun (void);

};

#endif // LTE_TEST_RLC_AM_TRANSMITTER_H
