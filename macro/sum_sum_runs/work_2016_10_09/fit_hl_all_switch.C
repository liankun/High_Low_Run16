#include<fstream>
#include<set>

void fit_hl_all_switch(int group=0){
  ifstream high_deadhot_txt("../high_bad_list_merge_final.txt");
  ifstream low_deadhot_txt("../low_bad_list_merge.txt");
  ifstream split_list_txt("split_list.txt");

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
 
  while(split_list_txt>>key){
    deadhot_set.insert(key);
  }

  char fpath[500];
  TFile* ifile = new TFile("../sum_all_runs4.root","READONLY");
  TFile* ofile = new TFile("output_fit_switch_50_150_exclude_deadhot4.root","RECREATE");

  TH1D* hslope = new TH1D("hslope","fitting slope",500,0,1);
  hslope->GetXaxis()->SetTitle("slope");
  
  TH2D* hslope_chi2 = new TH2D("hslope_chi2","slope vs  chi2",400,0,100,500,0,1);
  hslope_chi2->GetXaxis()->SetTitle("chi2");
  hslope_chi2->GetYaxis()->SetTitle("slope");

  TH3D* hfit_info0 = new TH3D("hfit_info0","fit information arm 0",400,0,100,500,0,1,500,-5,5);
  hfit_info0->GetXaxis()->SetTitle("chi2");
  hfit_info0->GetYaxis()->SetTitle("slope");
  hfit_info0->GetZaxis()->SetTitle("intercept");

  TH3D* hfit_info1 = new TH3D("hfit_info1","fit information arm 1",400,0,100,500,0,1,500,-5,5);
  hfit_info1->GetXaxis()->SetTitle("chi2");
  hfit_info1->GetYaxis()->SetTitle("slope");
  hfit_info1->GetZaxis()->SetTitle("intercept");


//  gStyle->SetOptFit(111);
  ofstream out_txt("fitting_information_50_150_serious4.txt");
  for(int i=0;i<128*24*16;i++){
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",i);
    TH2D* htemp = (TH2D*)ifile->Get(hname);
    if(!htemp){
      delete htemp;
      continue;
    }
    TProfile* hprof = htemp->ProfileY();
    sprintf(hname,"fit_fun_key%d",i);
    TF1* ff=new TF1(hname,fitf,50,150,2); 

    double entries = htemp->GetEntries();
    if(deadhot_set.find(i)==deadhot_set.end()){      
      hprof->Fit(ff,"QR+");
      double slope = ff->GetParameter(1);
      double intercept = ff->GetParameter(0);
      double chi2 = ff->GetChisquare();
      int ndf = ff->GetNDF();
      hslope->Fill(slope);
      out_txt<<i<<" "<<slope<<" "<<intercept<<" "<<chi2<<" "<<ndf<<endl;
      if(ndf>0){
        hslope_chi2->Fill(chi2/ndf,slope);
	if(i<128*24*8)hfit_info0->Fill(chi2/ndf,slope,intercept);
	else hfit_info1->Fill(chi2/ndf,slope,intercept);
        ofile->cd();
        hprof->Write();
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
