
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>

int main( void )
{
  TFile ff("events.root", "RECREATE");

  auto tree = new TTree("tree", "tree");

  double value;
  tree->Branch("value", &value);

  for(unsigned ev=0; ev<1000000; ev++) {
    value = gRandom->Gaus(0., 1.);
    tree->Fill();
  } //for ev

  tree->Write(); ff.Close();
} // main()
