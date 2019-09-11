
#include <JEventProcessor_jreader.h>

TList *JEventProcessor_jreader::mList = new TList();
thread_local TH1D  *JEventProcessor_jreader::mHist = 0;

std::vector<std::vector<MyDouble>*> JEventProcessor_jreader::mOutputQueueArray;
thread_local std::vector<MyDouble> *JEventProcessor_jreader::mOutputQueue = 
  new std::vector<MyDouble>;

void JEventProcessor_jreader::Init(void) {
  mFout = new TFile("histograms.root", "RECREATE");

  mOutputTree = new TTree("tree", "tree");
  mOutputTree->Branch("value", &mOutputValue);
} // JEventProcessor_jreader::Init()

void JEventProcessor_jreader::Finish(void) {
  auto hsum = new TH1D("hv", "hv", 1000, -10., 10.);

  hsum->Merge(mList); mList->Delete();

  // Flush thread queues;
  for(auto queue: mOutputQueueArray) 
    FlushOutputQueue(queue);
  
  mOutputTree->Write(); hsum->Write(); mFout->Close(); 
} // JEventProcessor_jreader::Finish()
