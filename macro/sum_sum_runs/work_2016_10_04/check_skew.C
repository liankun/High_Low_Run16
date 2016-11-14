void check_skew(){
  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  TH2D* hexam = (TH2D*)ifile->Get("hhigh_low_key47641");
  TH1D* hskew = new TH1D("hskew","Skewness",100,-0.5,99.5);
  for(int i=5;i<50;i++){
    hexam->SetAxisRange(i-1,i+1,"x");
    TH1D* htemp = hexam->ProjectionY();
    hskew->Fill(i,htemp->GetSkewness(1));
  }
  hskew->Draw();
}
