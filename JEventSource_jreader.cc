
#include "JEventSource_jreader.h"
#include "JEventProcessor_jreader.h"

void JEventSource_jreader::Open(void)
{
  //SetNumEventsToGetAtOnce(100, 100);

  mFin = new TFile("events.root");
  mTree = dynamic_cast<TTree*>(mFin->Get("tree")); 
  
  mTree->SetBranchAddress("value", &mValue);
  mEventsTotal = mTree->GetEntries();
} // JEventSource_jreader::Open()

void JEventSource_jreader::GetEvent(std::shared_ptr<JEvent> jevent)
{
  if (++mEvCurrent >= mEventsTotal) throw JEventSource::RETURN_STATUS::kNO_MORE_EVENTS;

  mTree->GetEntry(mEvCurrent);
  
  // Either populate the event or call TH1D::Fill() directly;
  if (WithProcessor) 
    jevent->Insert(new MyDouble(mValue), "value");
  else    
    JEventProcessor_jreader::FillThreadHistogram(mValue);
} // JEventSource_jreader::GetEvent()


