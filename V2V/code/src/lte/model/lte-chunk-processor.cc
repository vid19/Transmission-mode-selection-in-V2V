


#include <ns3/log.h>
#include <ns3/spectrum-value.h>
#include "lte-chunk-processor.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteChunkProcessor");

LteChunkProcessor::LteChunkProcessor ()
{
  NS_LOG_FUNCTION (this);
}

LteChunkProcessor::~LteChunkProcessor ()
{
  NS_LOG_FUNCTION (this);
}

void
LteChunkProcessor::AddCallback (LteChunkProcessorCallback c)
{
  NS_LOG_FUNCTION (this);
  m_lteChunkProcessorCallbacks.push_back (c);
}

void
LteChunkProcessor::Start ()
{
  NS_LOG_FUNCTION (this);
  m_sumValues = 0;
  m_totDuration = MicroSeconds (0);
}


void
LteChunkProcessor::EvaluateChunk (const SpectrumValue& sinr, Time duration)
{
  NS_LOG_FUNCTION (this << sinr << duration);
  if (m_sumValues == 0)
    {
      m_sumValues = Create<SpectrumValue> (sinr.GetSpectrumModel ());
    }
  (*m_sumValues) += sinr * duration.GetSeconds ();
  m_totDuration += duration;
}

void
LteChunkProcessor::End ()
{
  NS_LOG_FUNCTION (this);
  if (m_totDuration.GetSeconds () > 0)
    {
      std::vector<LteChunkProcessorCallback>::iterator it;
      for (it = m_lteChunkProcessorCallbacks.begin (); it != m_lteChunkProcessorCallbacks.end (); it++)
        {
          (*it)((*m_sumValues) / m_totDuration.GetSeconds ());
        }
    }
  else
    {
      NS_LOG_WARN ("m_numSinr == 0");
    }
}


  
void
LteSpectrumValueCatcher::ReportValue (const SpectrumValue& value)
{
  m_value = value.Copy ();
}

Ptr<SpectrumValue> 
LteSpectrumValueCatcher::GetValue ()
{
  return m_value;
}


} // namespace ns3
