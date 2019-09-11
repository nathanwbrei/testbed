
void plotter( void )
{
  auto ff = new TFile("histograms.root");
  auto hv = dynamic_cast<TH1D*>(ff->Get("hv"));

  auto cv = new TCanvas("cv", "cv", 1000, 500);
  cv->Divide(2, 1);

  auto tree = dynamic_cast<TTree*>(ff->Get("tree")); 
  auto hh   = new TH1D("hh", "", 1000, -10., 10.);
  tree->Project("hh", "value");

  cv->cd(1);
  hv->Fit("gaus");
  cv->cd(2);
  hh->Fit("gaus");
} // plotter()
