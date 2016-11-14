//check the asymmetry as high gain 
//or low gain for fixed value

void check_asy(){
  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  TH2D* hexam = (TH2D*)ifile->Get("hhigh_low_key47641");
  double point[6]={10,15,20,25,30,35};
  TCanvas* c = new TCanvas();
  for(int i=0;i<6;i=i+1){
    hexam->SetAxisRange(point[i],point[i],"x");
    TH1D* htemp=hexam->ProjectionY();
    char hname[500];
    sprintf(hname,"htemp%d",i);
    htemp->SetName(hname);
    htemp->SetLineColor(i+2);
    cout<<htemp->GetMean()<<endl;
    if(i==0)htemp->DrawNormalized();
    else htemp->DrawNormalized("same");
    TLine* line = new TLine(htemp->GetMean(),0,htemp->GetMean(),0.1);
    line->Draw("same");
//    TMarker* marker=new TMarker(htemp->GetMean(),0.1,23);
//    marker->Draw("same");
  }
}
