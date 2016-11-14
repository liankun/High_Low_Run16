#include<fstream>
#include<set>
#include<map>
void  classify_channel(){
  ifstream in_txt_file("fitting_information_50_200.txt");
//  ofstream out_txt_file("chi2_over90.txt");
  TFile* ifile = new TFile("output_fit_all_runs_50_200_exclude_deadhot.root","READONLY");
  TFile* ofile = new TFile("fitting_50_200_intercept_less0_dot_1.root","RECREATE");
  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;
  while(in_txt_file>>key>>slope>>intercept>>chi2>>ndf){
    if(fabs(intercept)<0.1){
      char hname[400];
      sprintf(hname,"hhigh_low_key%d_switch_pfx",key);
      TProfile* ptemp = (TProfile*)ifile->Get(hname);
      ofile->cd();
      ptemp->Write();
      delete ptemp;
    }
  }
}
