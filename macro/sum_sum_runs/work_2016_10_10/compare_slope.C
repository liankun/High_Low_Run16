#include<fstream>
void compare_slope(){
  ifstream in_txt0("../work_2016_10_09/fitting_information_50_150.txt");
  ifstream in_txt1("../work_2016_10_09/fitting_information_50_150_serious1.txt");
  
  TH1D* hdiff_slope[2];
  TH1D* hdiff_intercept[2];
  
  hdiff_slope[0] = new TH1D("hdiff_slope0","slope diff arm 0",200,-1,1);
  hdiff_slope[0]->GetXaxis()->SetTitle("Different");

  hdiff_slope[1] = new TH1D("hdiff_slope1","slope diff arm 1",200,-1,1);
  hdiff_slope[1]->GetXaxis()->SetTitle("Different");

  hdiff_intercept[0] = new TH1D("hdiff_intercept0","intercept diff arm 0",200,-5,5);
  hdiff_intercept[0]->GetXaxis()->SetTitle("Different");

  hdiff_intercept[1] = new TH1D("hdiff_intercept1","intercept diff arm 1",200,-5,5);
  hdiff_intercept[1]->GetXaxis()->SetTitle("Different");


  double slope0[128*24*16]={0.};
  double intercept0[128*24*16]={0.};
  double slope1[128*24*16]={0.};
  double intercept1[128*24*16]={0.};

  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;
  
  while(in_txt0>>key>>slope>>intercept>>chi2>>ndf){
    slope0[key]=slope;
    intercept0[key]=intercept;
  }
  
  while(in_txt1>>key>>slope>>intercept>>chi2>>ndf){
    slope1[key]=slope;
    intercept1[key]=intercept;
  }

  ofstream out_txt("big_diff_channel1.txt");
  for(int i=0;i<128*24*16;i++){
    if((slope0[i]>0)&&(slope1[i]>0)){
      double diff=(slope0[i]-slope1[i])/slope0[i];
      if(i<128*24*8) hdiff_slope[0]->Fill(diff);
      else hdiff_slope[1]->Fill(diff);

      if(fabs(diff)>0.1) out_txt<<i<<endl;
    }
    
    if((intercept0[i]>0)&&(intercept1[i]>0)){
      double diff=(intercept0[i]-intercept1[i]);
      if(i<128*24*8) hdiff_intercept[0]->Fill(diff);
      else hdiff_intercept[1]->Fill(diff);
    }

  }

  TFile* ofile = new TFile("compare_fit1.root","RECREATE");
  for(int iarm=0;iarm<2;iarm++){
    hdiff_slope[iarm]->Write();
    hdiff_intercept[iarm]->Write();
  }
}
