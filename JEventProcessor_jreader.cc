
#include <JEventProcessor_jreader.h>

TList *JEventProcessor_jreader::mList = new TList();

thread_local TH1D  *JEventProcessor_jreader::mHist = 0;

void JEventProcessor_jreader::Init(void) {
  mFout = new TFile("histograms.root", "RECREATE");
} // JEventProcessor_jreader::Init()

void JEventProcessor_jreader::Finish(void) {
  TH1D hsum("hv", "hv", 1000, -10., 10.);

  hsum.Merge(mList);
  
  mFout->cd(); hsum.Write(); mFout->Close(); 
} // JEventProcessor_jreader::Finish()
