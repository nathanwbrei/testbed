
#include <TFile.h>
#include <ROOT/RDataFrame.hxx>

int main( void )
{
  ROOT::EnableImplicitMT(4);

  TFile fout("histograms.root", "RECREATE");

  ROOT::RDataFrame rdf("tree", "events.root");
  auto hv = rdf.Histo1D({"hv", "hv", 1000, -10., 10.}, "value");

  fout.cd(); hv->Write(); fout.Close();
} // main()
