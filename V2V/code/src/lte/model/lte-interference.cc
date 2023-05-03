

#include "lte-interference.h"
#include "lte-chunk-processor.h"

#include <ns3/simulator.h>
#include <ns3/log.h>


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteInterference");

LteInterference::LteInterference ()
  : m_receiving (false),
    m_lastSignalId (0),
    m_lastSignalIdBeforeReset (0)
{
  NS_LOG_FUNCTION (this);
}

LteInterference::~LteInterference ()
{
  NS_LOG_FUNCTION (this);
}

void 
LteInterference::DoDispose ()
{
  NS_LOG_FUNCTION (this);
  m_rsPowerChunkProcessorList.clear ();
  m_sinrChunkProcessorList.clear ();
  m_interfChunkProcessorList.clear ();
  m_rxSignal = 0;
  m_allSignals = 0;
  m_noise = 0;
  Object::DoDispose ();
} 


TypeId
LteInterference::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LteInterference")
    .SetParent<Object> ()
    .SetGroupName("Lte")
  ;
  return tid;
}


void
LteInterference::StartRx (Ptr<const SpectrumValue> rxPsd)
{ 
  NS_LOG_FUNCTION (this << *rxPsd);
  if (m_receiving == false)
    {
      NS_LOG_LOGIC ("first signal");
      m_rxSignal = rxPsd->Copy ();
      m_lastChangeTime = Now ();
      m_receiving = true;
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_rsPowerChunkProcessorList.begin (); it != m_rsPowerChunkProcessorList.end (); ++it)
        {
          (*it)->Start ();
        }
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_interfChunkProcessorList.begin (); it != m_interfChunkProcessorList.end (); ++it)
        {
          (*it)->Start ();
        }
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_sinrChunkProcessorList.begin (); it != m_sinrChunkProcessorList.end (); ++it)
        {
          (*it)->Start (); 
        }
    }
  else
    {
      NS_LOG_LOGIC ("additional signal" << *m_rxSignal);
      // receiving multiple simultaneous signals, make sure they are synchronized
      NS_ASSERT (m_lastChangeTime == Now ());
      // make sure they use orthogonal resource blocks
      NS_ASSERT (Sum ((*rxPsd) * (*m_rxSignal)) == 0.0);
      (*m_rxSignal) += (*rxPsd);
    }
}


void
LteInterference::EndRx ()
{
  NS_LOG_FUNCTION (this);
  if (m_receiving != true)
    {
      NS_LOG_INFO ("EndRx was already evaluated or RX was aborted");
    }
  else
    {
      ConditionallyEvaluateChunk ();
      m_receiving = false;
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_rsPowerChunkProcessorList.begin (); it != m_rsPowerChunkProcessorList.end (); ++it)
        {
          (*it)->End ();
        }
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_interfChunkProcessorList.begin (); it != m_interfChunkProcessorList.end (); ++it)
        {
          (*it)->End ();
        }
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_sinrChunkProcessorList.begin (); it != m_sinrChunkProcessorList.end (); ++it)
        {
          (*it)->End (); 
        }
    }
}


void
LteInterference::AddSignal (Ptr<const SpectrumValue> spd, const Time duration)
{
  NS_LOG_FUNCTION (this << *spd << duration);
  DoAddSignal (spd);
  uint32_t signalId = ++m_lastSignalId;
  if (signalId == m_lastSignalIdBeforeReset)
    {
     
      m_lastSignalIdBeforeReset += 0x10000000;
    }
  Simulator::Schedule (duration, &LteInterference::DoSubtractSignal, this, spd, signalId);
}


void
LteInterference::DoAddSignal  (Ptr<const SpectrumValue> spd)
{ 
  NS_LOG_FUNCTION (this << *spd);
  ConditionallyEvaluateChunk ();
  (*m_allSignals) += (*spd);
}

void
LteInterference::DoSubtractSignal  (Ptr<const SpectrumValue> spd, uint32_t signalId)
{ 
  NS_LOG_FUNCTION (this << *spd);
  ConditionallyEvaluateChunk ();   
  int32_t deltaSignalId = signalId - m_lastSignalIdBeforeReset;
  if (deltaSignalId > 0)
    {   
      (*m_allSignals) -= (*spd);
    }
  else
    {
      NS_LOG_INFO ("ignoring signal scheduled for subtraction before last reset");
    }
}


void
LteInterference::ConditionallyEvaluateChunk ()
{
  NS_LOG_FUNCTION (this);
  if (m_receiving)
    {
      NS_LOG_DEBUG (this << " Receiving");
    }
  NS_LOG_DEBUG (this << " now "  << Now () << " last " << m_lastChangeTime);
  if (m_receiving && (Now () > m_lastChangeTime))
    {
      NS_LOG_LOGIC (this << " signal = " << *m_rxSignal << " allSignals = " << *m_allSignals << " noise = " << *m_noise);

      SpectrumValue interf =  (*m_allSignals) - (*m_rxSignal) + (*m_noise);

      SpectrumValue sinr = (*m_rxSignal) / interf;
      Time duration = Now () - m_lastChangeTime;
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_sinrChunkProcessorList.begin (); it != m_sinrChunkProcessorList.end (); ++it)
        {
          (*it)->EvaluateChunk (sinr, duration);
        }
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_interfChunkProcessorList.begin (); it != m_interfChunkProcessorList.end (); ++it)
        {
          (*it)->EvaluateChunk (interf, duration);
        }
      for (std::list<Ptr<LteChunkProcessor> >::const_iterator it = m_rsPowerChunkProcessorList.begin (); it != m_rsPowerChunkProcessorList.end (); ++it)
        {
          (*it)->EvaluateChunk (*m_rxSignal, duration);
        }
      m_lastChangeTime = Now ();
    }
}

void
LteInterference::SetNoisePowerSpectralDensity (Ptr<const SpectrumValue> noisePsd)
{
  NS_LOG_FUNCTION (this << *noisePsd);
  ConditionallyEvaluateChunk ();
  m_noise = noisePsd;
  
  m_allSignals = Create<SpectrumValue> (noisePsd->GetSpectrumModel ());
  if (m_receiving == true)
    {
      // abort rx
      m_receiving = false;
    }
 
  m_lastSignalIdBeforeReset = m_lastSignalId;
}

void
LteInterference::AddRsPowerChunkProcessor (Ptr<LteChunkProcessor> p)
{
  NS_LOG_FUNCTION (this << p);
  m_rsPowerChunkProcessorList.push_back (p);
}

void
LteInterference::AddSinrChunkProcessor (Ptr<LteChunkProcessor> p)
{
  NS_LOG_FUNCTION (this << p);
  m_sinrChunkProcessorList.push_back (p);
}

void
LteInterference::AddInterferenceChunkProcessor (Ptr<LteChunkProcessor> p)
{
  NS_LOG_FUNCTION (this << p);
  m_interfChunkProcessorList.push_back (p);
}




} // namespace ns3


