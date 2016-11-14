
void fit_sigma(){
  TFile* ifile = new TFile("output_dist_bk.root","READONLY");
  for(int i=0;i<128*24*16;i++){
    char hname[500];
    sprintf(hname,"hdst_key%d",i);
    TH2D* htemp=(TH2D*)ifile->Get(hname);
    if(!htemp) continue;
    TH1D* htemp1 = htemp->ProjectionY();
    htemp1->Fit("gaus");

  }
}
