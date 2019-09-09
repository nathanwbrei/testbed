
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

int main( void )
{
  TFile fin("events.root"), fout("histograms.root", "RECREATE");
  auto tree = dynamic_cast<TTree*>(fin.Get("tree")); 

  double value;
  tree->SetBranchAddress("value", &value);

  auto hv = new TH1D("hv", "hv", 1000, -10., 10.);

  // Loop through all events in a "usual" way;
  unsigned nEvents = tree->GetEntries();
  for(unsigned ev=0; ev<nEvents; ev++) {
    tree->GetEntry(ev);
    hv->Fill(value);
  } //for ev

  hv->Write(); fin.Close(); fout.Close();
} // main()
