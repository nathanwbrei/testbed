
#include <thread>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

// A single mutex to apply context locks during execution;
static std::mutex mymutex;

static void worker(TList *hlist)
{
  static int counter = -1;

  TString hh; hh.Form("hvl%08u", (unsigned)pthread_self());
  auto *hvl = new TH1D(hh.Data(), "", 1000, -10., 10.);

  TFile fin("events.root");
  auto *tree = dynamic_cast<TTree*>(fin.Get("tree")); 
  int nEvents = tree->GetEntries();

  double value;
  tree->SetBranchAddress("value", &value);

  {
    std::lock_guard<std::mutex> lock(mymutex);
    hlist->Add(hvl);
  }

  for( ; ; ) {
    // Yes, need an extra variable: 1) avoid tree->GetEntry() under lock, 
    // 2) can not safely call tree->GetEntry(counter) outside of the 
    // guarded context;
    unsigned current;
    {
      std::lock_guard<std::mutex> lock(mymutex);
      if (++counter >= nEvents) return;

      current = counter;
    }

    tree->GetEntry(current);
    hvl->Fill(value);
  } //for inf
} // worker()

int main( void )
{
  ROOT::EnableThreadSafety();

  TFile fout("histograms.root", "RECREATE");

  auto *hlist = new TList();

  // Launch N std::thread threads and merge their output afterwards;
  { 
    unsigned nThreads = 4;
    std::thread th[nThreads];

    for(unsigned iq=0; iq<nThreads; iq++) 
      th[iq] = std::thread(worker, hlist);

    for(unsigned iq=0; iq<nThreads; iq++) 
      th[iq].join();
  }

  auto *hv = new TH1D("hv", "hv", 1000, -10., 10.);
  hv->Merge(hlist);

  fout.cd(); hv->Write(); fout.Close();
} // main()
