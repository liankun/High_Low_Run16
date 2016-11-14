#include<fstream>
void compare_hl_lh(){
  ifstream in_txt("../work_2016_10_02/fitting_information_50_150.txt");
  double slope_list[128*24*16]={0.};
  double intercept_list[128*24*16]={0.};
  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;

  while(in_txt>>key>>slope>>intercept>>chi2>>ndf){
    slope_list[key]=slope;
    intercept_list[key]=intercept;
  }

  TH2D* hdiff[2];
  hdiff[0] = new TH2D("hdiff0","Slope diff vs intercept diff South",100,-2,2,100,-2,2);
  hdiff[0]->GetXaxis()->SetTitle("Slope Diff");
  hdiff[0]->GetYaxis()->SetTitle("Intercept Diff");

  hdiff[1] = new TH2D("hdiff1","Slope diff vs intercept diff North",100,-2,2,100,-2,2);
  hdiff[1]->GetXaxis()->SetTitle("Slope Diff");
  hdiff[1]->GetYaxis()->SetTitle("Intercept Diff");


  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  TFile* ofile = new TFile("compare_hl_lh.root","RECREATE");
  for(int i = 0;i < 128*24*16;i++){
    if(slope_list[i] < 0.000001) continue;
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",i);
    int arm=1;
    if(i<128*24*8) arm=0;
    TH2D* htemp = (TH2D*)ifile->Get(hname);
    TF1* ff=new TF1("ff",fitf,0,200,2); 
    ff->SetParameter(0,intercept_list[i]);
    ff->SetParameter(1,slope_list[i]);
    double x0 = ff->Eval(50);
    double x1 = ff->Eval(150);
    delete ff;
    sprintf(hname,"ff_key%d",i);
    ff = new TF1(hname,fitf,x0,x1,2);
    TProfile* ptemp=htemp->ProfileX();
    ptemp->Fit(ff,"RQ+");
    ofile->cd();
    ptemp->Write();

    double slope2=ff->GetParameter(1);
    double intercept2=ff->GetParameter(0);
    double slope_inv = 1/slope2;
    double intercept_inv = -intercept2/slope2;
    double slope_diff=(slope_inv-slope_list[i])/slope_list[i];
    double intercept_diff=(intercept_inv-intercept_list[i])/(intercept_list[i]);
    hdiff[arm]->Fill(slope_diff,intercept_diff);
    delete htemp;
    delete ptemp;
    delete ff;
    
  }

  for(int iarm=0;iarm<2;iarm++){
    hdiff[iarm]->Write();
  }

}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}

