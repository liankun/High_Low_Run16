#include<fstream>
void compare_slope(){
  ifstream in_txt0("fitting_information_50_150.txt");
  ifstream in_txt1("fitting_information_50_150_serious4.txt");
  
  TH1D* hdiff_slope[2];
  TH1D* hdiff_intercept[2];
  TH1D* hdiff_slope_er[2];
  TH1D* hdiff_intercept_er[2];
  TH1D* hslope_error[2];
  TH1D* hinterept_error[2];
  
  hdiff_slope[0] = new TH1D("hdiff_slope0","slope diff arm 0",400,-2,2);
  hdiff_slope[0]->GetXaxis()->SetTitle("Different");

  hdiff_slope[1] = new TH1D("hdiff_slope1","slope diff arm 1",400,-2,2);
  hdiff_slope[1]->GetXaxis()->SetTitle("Different");

  hslope_error[0] = new TH1D("hslope_error0","hslope error arm 0",200,-0.1,0.1);
  hslope_error[0]->GetXaxis()->SetTitle("error");

  hslope_error[1] = new TH1D("hslope_error1","hslope error arm 1",200,-0.1,0.1);
  hslope_error[1]->GetXaxis()->SetTitle("error");


  hdiff_slope_er[0] = new TH1D("hdiff_slope_er0","slope diff in error arm 0",200,-50,50);
  hdiff_slope_er[0]->GetXaxis()->SetTitle("Different in error");

  hdiff_slope_er[1] = new TH1D("hdiff_slope_er1","slope diff in error arm 1",200,-50,50);
  hdiff_slope_er[1]->GetXaxis()->SetTitle("Different in error");


  hdiff_intercept[0] = new TH1D("hdiff_intercept0","intercept diff arm 0",200,-5,5);
  hdiff_intercept[0]->GetXaxis()->SetTitle("Different");

  hdiff_intercept[1] = new TH1D("hdiff_intercept1","intercept diff arm 1",200,-5,5);
  hdiff_intercept[1]->GetXaxis()->SetTitle("Different");

  hdiff_intercept_er[0] = new TH1D("hdiff_intercept_er0","intercept diff in error arm 0",200,-50,50);
  hdiff_intercept_er[0]->GetXaxis()->SetTitle("Different in error");

  hdiff_intercept_er[1] = new TH1D("hdiff_intercept_er1","intercept diff in error arm 1",200,-50,50);
  hdiff_intercept_er[1]->GetXaxis()->SetTitle("Different in error");

  hinterept_error[0] = new TH1D("hinterept_error0","Intercept error arm 0",200,-0.1,0.1);
  hinterept_error[0]->GetXaxis()->SetTitle("error");

  hinterept_error[1] = new TH1D("hinterept_error1","Intercept error arm 1",200,-0.1,0.1);
  hinterept_error[1]->GetXaxis()->SetTitle("error");

  double slope0[128*24*16]={0.};
  double slope_er0[128*24*16]={0.};
  double intercept0[128*24*16]={0.};
  double intercept_er0[128*24*16]={0.};
  double slope1[128*24*16]={0.};
  double slope_er1[128*24*16]={0.};
  double intercept1[128*24*16]={0.};
  double intercept_er1[128*24*16]={0.};

  int key;
  double slope;
  double slope_error;
  double intercept;
  double intercept_error;
  double chi2;
  int ndf;
  
  while(in_txt0>>key>>slope>>slope_error>>intercept>>intercept_error>>chi2>>ndf){
    slope0[key]=slope;
    slope_er0[key]=slope_error;
    intercept0[key]=intercept;
    intercept_er0[key]=intercept_error;
  }
  
  while(in_txt1>>key>>slope>>slope_error>>intercept>>intercept_error>>chi2>>ndf){
    slope1[key]=slope;
    slope_er1[key]=slope_error;
    intercept1[key]=intercept;
    intercept_er1[key]=intercept_error;
  }
  
  ofstream out_txt0("big_diff_slope_series4.txt");
  ofstream out_txt1("big_diff_intercept_series4.txt");
  for(int i=0;i<128*24*16;i++){
    if(slope0[i]>0){
      double diff=slope0[i]-slope1[i];
      double sum_er=fabs(slope_er0[i])+fabs(slope_er1[i]);
//      cout<<i<<" slope "<<sum_er<<endl;
      if(i<128*24*8){
        hdiff_slope[0]->Fill(diff/slope0[i]);
        hdiff_slope_er[0]->Fill(diff/sum_er);
	hslope_error[0]->Fill(sum_er/fabs(slope0[i]));
	if(fabs(diff/slope0[i])>0.03 || fabs(diff/sum_er) > 5){
          out_txt0<<i<<endl;
	}
      }
      else{
        hdiff_slope[1]->Fill(diff);
        hdiff_slope_er[1]->Fill(diff/sum_er);
	hslope_error[1]->Fill(sum_er/fabs(slope0[i]));
	if(fabs(diff)> 0.4 || fabs(diff/sum_er) > 5){
          out_txt1<<i<<endl;
	}
      }
    }
    
//    if(fabs(intercept0[i]>0)&&fabs(intercept1[i]>0)){
      double diff=(intercept0[i]-intercept1[i]);
      double sum_er=fabs(intercept_er0[i])+fabs(intercept_er1[i]);
//      cout<<i<<" intercept "<<sum_er<<endl;
      if(i<128*24*8){
        hdiff_intercept[0]->Fill(diff);
        hdiff_intercept_er[0]->Fill(diff/sum_er);
	hinterept_error[0]->Fill(sum_er/fabs(intercept0[i]));
      }
      else{
        hdiff_intercept[1]->Fill(diff);
        hdiff_intercept_er[1]->Fill(diff/sum_er);
	hinterept_error[1]->Fill(sum_er/fabs(intercept0[i]));
      }
//    }

  }

  TFile* ofile = new TFile("compare_fit4.root","RECREATE");
  for(int iarm=0;iarm<2;iarm++){
    hdiff_slope[iarm]->Write();
    hdiff_intercept[iarm]->Write();
    hdiff_slope_er[iarm]->Write();
    hdiff_intercept_er[iarm]->Write();
    hslope_error[iarm]->Write();
    hinterept_error[iarm]->Write();
  }
}
