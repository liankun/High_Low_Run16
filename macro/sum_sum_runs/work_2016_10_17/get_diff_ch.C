#include<fstream>
void get_diff_ch(){
  ifstream in_txt("fit_sigma_result_all_runs.txt");
  int key;
  double par0;
  double error0;
  double par1;
  double error1;
  double par2;
  double error2;
  double chi2;
  int ndf;
  
  ofstream out_txt("big_diff_ch_mean2.txt");
  while(in_txt>>key>>par0>>error0>>par1>>error1>>par2>>error2>>chi2>>ndf){
    if(fabs(par1)>0.19){
      out_txt<<key<<endl;
    }
  }

}
