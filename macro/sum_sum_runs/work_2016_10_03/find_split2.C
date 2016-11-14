#include<fstream>
void find_split2(){
  ifstream in_fit_txt("fitting_information_50_150.txt");
  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;

  while(in_fit_txt>>key>>slope>>intercept>>chi2>>ndf){
//    cout<<key<<slope<<intercept<<chi2<<ndf<<endl;
    slope[key]=slope;
    intercept[key]=intercept;
  }

  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  int exam_key=3450;
  double slope[24*128*16];
  double intercept[24*128*16];


  char hname[400];
  TH1D* hdiff = new TH1D("hdiff","diff",200,-50,50);
  hdiff->GetXaxis()->SetTitle("diff");


  TF1* ff = new TF1("ff",fitf,0,250,2);
  ff->SetParameter(0,intercept[exam_key]);
  ff->SetParameter(1,slope[exam_key]);
  cout<<intercept[exam_key]<<" "<<slope[exam_key]<<endl;
  sprintf(hname,"hhigh_low_key%d",exam_key);
  TH2D* hexam = (TH2D*)ifile->Get(hname);
  int NbinsX = hexam->GetNbinsX();
  int NbinsY = hexam->GetNbinsY();
  for(int ix=0;ix<NbinsX;ix++){
    for(int iy=0;iy<NbinsY;iy++){
      double x=hexam->GetXaxis()->GetBinCenter(ix+1);
      double y=hexam->GetYaxis()->GetBinCenter(iy+1);
      if(y<50 || y>200 || x < 0) continue;
      double content=hexam->GetBinContent(ix+1,iy+1);
      if(content<10)continue;
      double x_eval = ff->Eval(y);
//      cout<<x_eval<<endl;
      double diff=(x-x_eval)/x_eval;
//      cout<<chi2<<endl;
      hdiff->Fill(diff,content);
    }
  }
  
  TFile* ofile = new TFile("output_diff3450.root","RECREATE");
  hdiff->Write();
}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}

