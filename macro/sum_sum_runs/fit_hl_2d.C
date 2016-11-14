#include<fstream>
#include<set>

void fit_hl_2d(int group=44){
  ifstream high_deadhot_txt("high_bad_list_merge_final.txt");
  ifstream low_deadhot_txt("low_bad_list_merge.txt");

  set<int> high_deadot_set;
  set<int> low_deadhot_set;
  set<int> deadhot_set;

  int key;
  while(high_deadhot_txt>>key){
    high_deadot_set.insert(key);
    deadhot_set.insert(key);
  }

  while(low_deadhot_txt>>key){
    low_deadhot_set.insert(key);
    deadhot_set.insert(key);
  }
  
  char fpath[500];
  sprintf(fpath,"%d/sum_sum.root",group);
  TFile* ifile = new TFile(fpath,"READONLY");
  sprintf(fpath,"%d/output_fit_more_info_2d.root",group);
  TFile* ofile = new TFile(fpath,"RECREATE");

  TH1D* hslope = new TH1D("hslope","fitting slope",100,-5,20);
  hslope->GetXaxis()->SetTitle("slope");
  
  TH2D* hslope_chi2 = new TH2D("hslope_chi2","slope vs  chi2",100,0,50,100,-5,20);
  hslope_chi2->GetXaxis()->SetTitle("chi2");
  hslope_chi2->GetYaxis()->SetTitle("slope");

  TH3D* hfit_info0 = new TH3D("hfit_info0","fit information arm 0",100,0,50,100,-5,20,100,-30,30);
  hfit_info0->GetXaxis()->SetTitle("chi2");
  hfit_info0->GetYaxis()->SetTitle("slope");
  hfit_info0->GetZaxis()->SetTitle("intercept");

  TH3D* hfit_info1 = new TH3D("hfit_info1","fit information arm 1",100,0,50,100,-5,20,100,-30,30);
  hfit_info1->GetXaxis()->SetTitle("chi2");
  hfit_info1->GetYaxis()->SetTitle("slope");
  hfit_info1->GetZaxis()->SetTitle("intercept");


  gStyle->SetOptFit(111);
//  ofstream out_txt("fitting_over_5chi2_new.txt");
  for(int i=0;i<128*24*16;i++){
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",i);
    TH2D* htemp = (TH2D*)ifile->Get(hname);
    TProfile* hprof = htemp->ProfileX();
    sprintf(hname,"fit_fun_key%d",i);
    TF1* ff; 
    if(i<128*24*8)ff= new TF1(hname,fitf,9,38,2);
    else ff=new TF1(hname,fitf,6,33,2);
    double entries = htemp->GetEntries();
    if(deadhot_set.find(i)==deadhot_set.end()){
      hprof->Fit(ff,"QR+");
      double slope = ff->GetParameter(1);
      double intercept = ff->GetParameter(0);
      double chi2 = ff->GetChisquare();
      int ndf = ff->GetNDF();
      hslope->Fill(slope);
      if(ndf>0){
        hslope_chi2->Fill(chi2/ndf,slope);
	if(i<128*24*8)hfit_info0->Fill(chi2/ndf,slope,intercept);
	else hfit_info1->Fill(chi2/ndf,slope,intercept);
//	if(chi2/ndf<2 && fabs(intercept)<1){
	  sprintf(hname,"c_key%d",i);
	  TCanvas* c = new TCanvas(hname,hname);
          htemp->Draw("colz");
          ff->Draw("same");
          ofile->cd();
          c->Write();
//	  out_txt<<i<<endl;
//	}
      }
      if(slope < 1){
        cout<<i<<endl;
      }
    }
    delete htemp;
    delete hprof;
    delete ff;
  }
  ofile->cd();
  hslope->Write();
  hslope_chi2->Write();
  hfit_info0->Write();
  hfit_info1->Write();
}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}
