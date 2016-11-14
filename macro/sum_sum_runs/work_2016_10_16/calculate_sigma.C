#include<fstream>
#include<set>
void calculate_sigma(){
  TFile* ifile = new TFile("../sum_all_runs4.root","READONLY");
  ifstream in_txt0("../high_bad_list_merge_final.txt");
  ifstream in_txt1("../low_bad_list_merge.txt");
  ifstream in_txt2("../split_list.txt");
  ifstream fit_info("../work_2016_10_12/fitting_information_50_150.txt");
  
  set<int> bad_key_set;

  double slope_list[128*24*16]={0.};
  double intercept_list[128*24*16]={0.};


  int key;
  double slope;
  double slope_error;
  double intercept;
  double intercept_error;
  double chi2;
  int ndf;

  while(fit_info>>key>>slope>>slope_error>>intercept>>intercept_error>>chi2>>ndf){
    slope_list[key]=slope;
    intercept_list[key]=intercept;
  }

  while(in_txt0>>key){
    bad_key_set.insert(key);
  }

  while(in_txt1>>key){
    bad_key_set.insert(key);
  }

  while(in_txt2>>key){
    bad_key_set.insert(key);
  }

  TFile* ofile = new TFile("output_dist_series4.root","RECREATE");
  for(int i=0;i<128*24*16;i++){
    if(bad_key_set.find(i)!=bad_key_set.end()) continue;
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",i);
    TH2D* htemp = (TH2D*)ifile->Get(hname);
    if(!htemp) continue;
    if(slope_list[i]<0.00001){
      cout<<"No slope for key "<<i<<endl;
      delete htemp;
      continue;
    }
    sprintf(hname,"fit_fun%d",i);
    TF1* ff = new TF1(hname,fitf,0,250,2);
    ff->SetParameter(1,slope_list[i]);
    ff->SetParameter(0,intercept_list[i]);
    int NbinsX = htemp->GetNbinsX();
    int NbinsY = htemp->GetNbinsY();
    sprintf(hname,"hdst_key%d",i);
    TH2D* hdst = new TH2D(hname,hname,120,40-0.5,160-0.5,200,-20,20);
    for(int ix=0;ix<NbinsX;ix++){
      for(int iy=0;iy<NbinsY;iy++){
        double y=htemp->GetYaxis()->GetBinCenter(iy+1);
	double x=htemp->GetXaxis()->GetBinCenter(ix+1);
	if(y<50 || y >150) continue;
	double content=htemp->GetBinContent(ix+1,iy+1);
	if(content<1) continue;
	double eval_x = ff->Eval(y);
	double dist = (eval_x-x)/sqrt(slope_list[i]*slope_list[i]+1);
	hdst->Fill(y,dist,content);
      }
    }
    ofile->cd();
    hdst->Write();
    delete htemp;
    delete ff;
    delete hdst;
  }
}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}

