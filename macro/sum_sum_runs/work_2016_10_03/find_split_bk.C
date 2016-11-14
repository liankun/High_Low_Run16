//use ratio to find the split
#include<TSpectrum.h>
void find_split(){
  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  if(!ifile){
    cout<<"open file failled !!!"<<endl;
    return;
  }
  TH2D* hexam = (TH2D*)ifile->Get("hhigh_low_key3450");
//  hexam->Draw("colz");
  int NbinsX = hexam->GetNbinsX();
  int NbinsY = hexam->GetNbinsY();

/*
  TF1* ff = new TF1("ff",fitf,50,200,2);
  ff->SetParameter(0,5.86121);
  ff->SetParameter(1,0.228503);
*/
  
  TH1D* hratio = new TH1D("hratio","Ratio",200,-20,20);
  hratio->GetXaxis()->SetName("ratio");

  TH1D* hphi = new TH1D("hphi","Phi",800,0,3.14);
  hphi->GetXaxis()->SetName("phi");

  for(int ix=0;ix<NbinsX;ix++){
    for(int iy=0;iy<NbinsY;iy++){
      double x=hexam->GetXaxis()->GetBinCenter(ix+1);
      double y=hexam->GetYaxis()->GetBinCenter(iy+1);
      if(y<5 || x < 0 || y>200) continue;
      double content=hexam->GetBinContent(ix+1,iy+1);
      if(content<10) continue;
      hratio->Fill(y/x,content);
      hphi->Fill(atan2(y,x),content);
    }
  }

  TSpectrum *s = new TSpectrum(2);
  Int_t nfound = s->Search(hratio,2,"",0.10);
  TFile* ofile = new TFile("output_ratio_example3450_cut.root","RECREATE");
  hratio->Write();
  hphi->Write();
}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}

