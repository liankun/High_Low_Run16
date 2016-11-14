#include<fstream>
void compare_fit(){
  ifstream in_txt0("../work_2016_10_17/fit_sigma_result_all_runs.txt");
  ifstream in_txt1("../work_2016_10_17/fit_sigma_result_all_runs_81_150.txt");

  double sigma0[128*24*16]={0.};
  double mean0[128*24*16]={0.};
  double sigma1[128*24*16]={0.};
  double mean1[128*24*16]={0.};

  int key;
  double par0;
  double par1;
  double par2;
  double error0;
  double error1;
  double error2;
  double chi2;
  int ndf;

  while(in_txt0>>key>>par0>>error0>>par1>>error1>>par2>>error2>>chi2>>ndf){
    sigma0[key]=par2;
    mean0[key]=par1;
  }

  while(in_txt1>>key>>par0>>error0>>par1>>error1>>par2>>error2>>chi2>>ndf){
    sigma1[key]=par2;
    mean1[key]=par1;
  }

  TH2D* hmean_sigma[2];
  hmean_sigma[0] = new TH2D("hmean_sigma0","Sigma vs Mean South",200,-2,2,200,-2,2);
  hmean_sigma[0]->GetXaxis()->SetTitle("Mean");
  hmean_sigma[0]->GetYaxis()->SetTitle("Sigma");

  hmean_sigma[1] = new TH2D("hmean_sigma1","Sigma vs Mean North",200,-2,2,200,-2,2);
  hmean_sigma[1]->GetXaxis()->SetTitle("Mean");
  hmean_sigma[1]->GetYaxis()->SetTitle("Sigma");
  
//  ofstream out_txt0("big_diff_mean.txt");
//  ofstrema out_txt1("big_diff_sigma.txt");
  for(int i=0;i<128*24*16;i++){
    if(fabs(sigma0[i])>0){
      if(i<128*24*8){
        hmean_sigma[0]->Fill(mean1[i]-mean0[i],fabs(sigma1[i]/sigma0[i])-1);
//	if(fabs(mean1[i]-mean0[i])>0.1)big_diff_mean.txt<<i<<endl;
//	if(fabs(sigma1[i]/sigma0[i]-1)>)
      }
      else{
        hmean_sigma[1]->Fill(mean1[i]-mean0[i],fabs(sigma1[i]/sigma0[i])-1);
      }
    }
  }

  TFile* ofile = new TFile("output_compare_81_150.root","RECREATE");
  for(int iarm=0;iarm<2;iarm++){
    hmean_sigma[iarm]->Write();
  }

}
