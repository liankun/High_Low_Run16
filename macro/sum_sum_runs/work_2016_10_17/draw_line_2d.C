#include<fstream>
#include<set>
void draw_line_2d(){
  ifstream in_txt("../work_2016_10_12/fitting_information_50_150.txt");
  ifstream in_txt1("big_diff_ch_mean.txt");
  double slope[128*24*16]={0.};
  double intercept[128*24*16]={0.};

  int key;
  double par0;
  double err0;
  double par1;
  double err1;
  double chi2;
  int ndf;

  while(in_txt>>key>>par0>>err0>>par1>>err1>>chi2>>ndf){
    slope[key]=par0;
    intercept[key]=par1;
  }

  set<int> bad_set;
  while(in_txt1>>key){
    bad_set.insert(key);
  }

  TFile* ifile0= new TFile("../sum_all_runs.root","READONLY");
  TFile* ofile = new TFile("line_2d.root","RECREATE");
  for(set<int>::iterator it=bad_set.begin();it!=bad_set.end();++it){
    int index=*it;
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",index);
    TH2D* htemp = (TH2D*)ifile0->Get(hname);
    sprintf(hname,"fit_key%d",index);
    TF1* ff = new TF1(hname,fitf,0,200,2);
    ff->SetParameter(0,-intercept[index]/slope[index]);
    ff->SetParameter(1,1/slope[index]);
    ff->SetLineColor(kRed);
    sprintf(hname,"c_key%d",index);
    TCanvas* c = new TCanvas(hname,hname);
    htemp->Draw("colz");
    c->cd();
    ff->Draw("same");
    ofile->cd();
    c->Write();
    delete htemp;
    delete ff;
    delete c;
  }
}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}

