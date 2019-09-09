
#include "JEventSource_jreader.h"

static std::mutex mymutex;

bool WithProcessor = false;

TList *JEventSource_jreader::mList = 0;
thread_local TH1D  *JEventSource_jreader::mHist = 0;

void JEventSource_jreader::Open(void)
{
  SetNumEventsToGetAtOnce(100, 100);

  mFout = new TFile("histograms.root", "RECREATE");

  mHistSum = new TH1D("hv", "hv", 1000, -10., 10.);

  mList = new TList();

  mFin = new TFile("events.root");
  mTree = dynamic_cast<TTree*>(mFin->Get("tree")); 
  
  mTree->SetBranchAddress("value", &mValue);
  mEventsTotal = mTree->GetEntries();
}

void JEventSource_jreader::InitializeLocalHistogram( void )
{
  TString hh; hh.Form("hvl%08u", (unsigned)pthread_self());
  mHist = new TH1D(hh.Data(), "", 1000, -10., 10.);
    
  // Basically the only place, which requires extra lock;
  {
    std::lock_guard<std::mutex> lock(mymutex);

    mList->Add(mHist);
  }
} // JEventSource_jreader::InitializeLocalHistogram()

void JEventSource_jreader::GetEvent(std::shared_ptr<JEvent> jevent)
{
  if (++mEvCurrent >= mEventsTotal) throw JEventSource::RETURN_STATUS::kNO_MORE_EVENTS;

  mTree->GetEntry(mEvCurrent);
  
  if (WithProcessor) 
    jevent->Insert(new MyDouble(mValue), "value");
  else {
    // There is no race condition here, since this call can not happen 
    // concurrently from the processor in this default mode;
    if (!mHist) InitializeLocalHistogram();
    mHist->Fill(mValue);
  } //if
}


