#include<fstream>
void fit_sigma(){
  TFile* ifile = new TFile("../work_2016_10_16/output_dist_all_runs.root","READONLY");
  if(!ifile){
    cout<<"open file failed "<<endl;
    return;
  }
  TFile* ofile = new TFile("sigma_fit_all_runs_81_150.root","RECREATE");
  ofstream out_txt("fit_sigma_result_all_runs_81_150.txt"); 
  for(int i=0;i<128*24*16;i++){
    char hname[500];
    sprintf(hname,"hdst_key%d",i);
    TH2D* htemp = (TH2D*)ifile->Get(hname);
    if(!htemp) continue;
    htemp->SetAxisRange(81,150,"x");
    TH1D* htemp1 = htemp->ProjectionY();
    sprintf(hname,"fitfun%d",i);
    TF1* ff = new TF1(hname,fitf,-10,10,3);
    double mean = htemp1->GetMean();
    double rms = htemp1->GetRMS();
    ff->SetParameter(1,mean);
    ff->SetParameter(2,rms);
    htemp1->Fit(ff,"QR+");
    double par0 = ff->GetParameter(0);
    double error0 = ff->GetParError(0);
    double par1 = ff->GetParameter(1);
    double error1 = ff->GetParError(1);
    double par2 = ff->GetParameter(2);
    double error2 = ff->GetParError(2);
    double chi2 = ff->GetChisquare();
    int ndf = ff->GetNDF();
    out_txt<<i<<" "
           <<par0<<" "<<error0<<" "
           <<par1<<" "<<error1<<" "
	   <<par2<<" "<<error2<<" "
	   <<chi2<<" "<<ndf
	   <<endl;
    ofile->cd();
    htemp1->Write();
    delete htemp1;
    delete htemp;
  }
}

Double_t fitf(Double_t *x,Double_t *par){
  Double_t arg = 0;
  if(par[2]!=0) arg = (x[0] - par[1])/par[2];
  Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
  return fitval;
}
