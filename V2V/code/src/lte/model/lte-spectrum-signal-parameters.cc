

#include <ns3/log.h>
#include <ns3/packet-burst.h>
#include <ns3/ptr.h>
#include <ns3/lte-spectrum-signal-parameters.h>
#include <ns3/lte-control-messages.h>


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteSpectrumSignalParameters");

LteSpectrumSignalParameters::LteSpectrumSignalParameters ()
{
  NS_LOG_FUNCTION (this);
}

LteSpectrumSignalParameters::LteSpectrumSignalParameters (const LteSpectrumSignalParameters& p)
  : SpectrumSignalParameters (p)
{
  NS_LOG_FUNCTION (this << &p);
  packetBurst = p.packetBurst->Copy ();
}

Ptr<SpectrumSignalParameters>
LteSpectrumSignalParameters::Copy ()
{
  NS_LOG_FUNCTION (this);
  Ptr<LteSpectrumSignalParameters> lssp (new LteSpectrumSignalParameters (*this), false);  
  return lssp;
}



LteSpectrumSignalParametersDataFrame::LteSpectrumSignalParametersDataFrame ()
{
  NS_LOG_FUNCTION (this);
}

LteSpectrumSignalParametersDataFrame::LteSpectrumSignalParametersDataFrame (const LteSpectrumSignalParametersDataFrame& p)
: SpectrumSignalParameters (p)
{
  NS_LOG_FUNCTION (this << &p);
  cellId = p.cellId;
  if (p.packetBurst)
    {
      packetBurst = p.packetBurst->Copy ();
    }
  ctrlMsgList = p.ctrlMsgList;
}

Ptr<SpectrumSignalParameters>
LteSpectrumSignalParametersDataFrame::Copy ()
{
  NS_LOG_FUNCTION (this);
  Ptr<LteSpectrumSignalParametersDataFrame> lssp (new LteSpectrumSignalParametersDataFrame (*this), false);  
  return lssp;
}



LteSpectrumSignalParametersDlCtrlFrame::LteSpectrumSignalParametersDlCtrlFrame ()
{
  NS_LOG_FUNCTION (this);
}

LteSpectrumSignalParametersDlCtrlFrame::LteSpectrumSignalParametersDlCtrlFrame (const LteSpectrumSignalParametersDlCtrlFrame& p)
: SpectrumSignalParameters (p)
{
  NS_LOG_FUNCTION (this << &p);
  cellId = p.cellId;
  pss = p.pss;
  ctrlMsgList = p.ctrlMsgList;
}

Ptr<SpectrumSignalParameters>
LteSpectrumSignalParametersDlCtrlFrame::Copy ()
{
  NS_LOG_FUNCTION (this);
  Ptr<LteSpectrumSignalParametersDlCtrlFrame> lssp (new LteSpectrumSignalParametersDlCtrlFrame (*this), false);  
  return lssp;
}


LteSpectrumSignalParametersUlSrsFrame::LteSpectrumSignalParametersUlSrsFrame ()
{
  NS_LOG_FUNCTION (this);
}

LteSpectrumSignalParametersUlSrsFrame::LteSpectrumSignalParametersUlSrsFrame (const LteSpectrumSignalParametersUlSrsFrame& p)
: SpectrumSignalParameters (p)
{
  NS_LOG_FUNCTION (this << &p);
  cellId = p.cellId;
}

Ptr<SpectrumSignalParameters>
LteSpectrumSignalParametersUlSrsFrame::Copy ()
{
  NS_LOG_FUNCTION (this);
  Ptr<LteSpectrumSignalParametersUlSrsFrame> lssp (new LteSpectrumSignalParametersUlSrsFrame (*this), false);  
  return lssp;
}







} // namespace ns3
