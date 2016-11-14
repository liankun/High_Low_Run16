#include<fstream>
#include<set>
#include<map>
void  classify_channel(){
  ifstream in_txt_file("fitting_information_30_50.txt");
//  ofstream out_txt_file("chi2_over90.txt");
  TFile* ifile = new TFile("output_fit_switch_30_50_exclude_deadhot.root","READONLY");
  TFile* ofile = new TFile("fitting_30_50_chi2_over_north10_south15.root","RECREATE");
  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;
  while(in_txt_file>>key>>slope>>intercept>>chi2>>ndf){
    double cut=10;
    if(key<128*24*8) cut=15;
    if((ndf>0) && (chi2/ndf>cut)){
      char hname[400];
      sprintf(hname,"hhigh_low_key%d_pfy",key);
      TProfile* ptemp = (TProfile*)ifile->Get(hname);
      ofile->cd();
      ptemp->Write();
      delete ptemp;
    }
  }
}
