//check the asymmetry as high gain 
//or low gain for fixed value

void check_asy_high(){
  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  TH2D* hexam = (TH2D*)ifile->Get("hhigh_low_key47641");
  double point[6]={20,50,80,110,140,170};
  TCanvas* c = new TCanvas();
  for(int i=0;i<6;i=i+1){
    hexam->SetAxisRange(point[i],point[i],"y");
    TH1D* htemp=hexam->ProjectionX();
    char hname[500];
    sprintf(hname,"htemp%d",i);
    htemp->SetName(hname);
    htemp->SetLineColor(i+2);
    cout<<htemp->GetMean()<<endl;
    if(i==0)htemp->DrawNormalized();
    else htemp->DrawNormalized("same");
    TLine* line = new TLine(htemp->GetMean(),0,htemp->GetMean(),0.6);
    line->Draw("same");
//    TMarker* marker=new TMarker(htemp->GetMean(),0.1,23);
//    marker->Draw("same");
  }
}
