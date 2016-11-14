#include<fstream>
#include<set>
#include<map>
void  classify_channel(){
  ifstream in_txt_file("fitting_information.txt");
//  ofstream out_txt_file("chi2_over90.txt");
  TFile* ifile = new TFile("output_fit.root","READONLY");
  TFile* ofile = new TFile("fitting_chi2_over30.root","RECREATE");
  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;
  while(in_txt_file>>key>>slope>>intercept>>chi2>>ndf){
    if(fabs(chi2/ndf)>30){
      char hname[400];
      sprintf(hname,"hhigh_low_key%d_pfx",key);
      TProfile* ptemp = (TProfile*)ifile->Get(hname);
      ofile->cd();
      ptemp->Write();
      delete ptemp;
    }
  }
}
