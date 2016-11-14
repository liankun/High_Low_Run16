#include<fstream>
void draw_compare_by_group(){
  ifstream in_txt0("../work_2016_10_12/fitting_information_50_150.txt");
  double slope0[128*24*16]={0.};
  double slope_er0[128*24*16]={0.};
  double intercept0[128*24*16]={0.};
  double intercept_er0[128*24*16]={0.};
  
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

  
  TH2D* hkey_slope_diff[2];
  TH2D* hkey_slope_diff_er[2];
  TH2D* hkey_itcp_diff[2];
  TH2D* hkey_itcp_diff_er[2];


  for(int iarm=0;iarm<2;iarm++){
    char hname[500];
    sprintf(hname,"hkey_slope_diff_arm%d",iarm);
    hkey_slope_diff[iarm] = new TH2D(hname,hname,24576,-0.5+24576*iarm,24576*(iarm+1)-0.5,500,-1,1);
    hkey_slope_diff[iarm]->GetXaxis()->SetTitle("Key");
    hkey_slope_diff[iarm]->GetYaxis()->SetTitle("diff");
    
    sprintf(hname,"hkey_slope_diff_er_arm%d",iarm);
    hkey_slope_diff_er[iarm] = new TH2D(hname,hname,24576,-0.5+24576*iarm,24576*(iarm+1)-0.5,200,-20,20);
    hkey_slope_diff_er[iarm]->GetXaxis()->SetTitle("Key");
    hkey_slope_diff_er[iarm]->GetYaxis()->SetTitle("diff in error");

    sprintf(hname,"hkey_itcp_diff_arm%d",iarm);
    hkey_itcp_diff[iarm] = new TH2D(hname,hname,24576,-0.5+24576*iarm,24576*(iarm+1)-0.5,200,-5,5);
    hkey_itcp_diff[iarm]->GetXaxis()->SetTitle("Key");
    hkey_itcp_diff[iarm]->GetYaxis()->SetTitle("diff");

    sprintf(hname,"hkey_itcp_diff_er_arm%d",iarm);
    hkey_itcp_diff_er[iarm] = new TH2D(hname,hname,24576,-0.5+24576*iarm,24576*(iarm+1)-0.5,200,-20,20);
    hkey_itcp_diff_er[iarm]->GetXaxis()->SetTitle("Key");
    hkey_itcp_diff_er[iarm]->GetYaxis()->SetTitle("diff in error");
  }


  char fpath[500];
  ofstream out_txt("bad_group_key.txt");
  for(int i=0;i<44;i++){
    sprintf(fpath,"../%d/fitting_information_50_150.txt",i);
    ifstream in_txt1(fpath);
    cout<<"process "<<fpath<<endl;
    while(in_txt1>>key>>slope>>slope_error>>intercept>>intercept_error>>chi2>>ndf){
 //     cout<<key<<endl;    
      int arm=1;
      if(key<24576) arm=0;
      if(slope0[key]>0){
        double diff = slope-slope0[key];
	double sum_er = fabs(slope_error)+fabs(slope_er0[key]);
        hkey_slope_diff[arm]->Fill(key,diff/slope0[key]);
	hkey_itcp_diff_er[arm]->Fill(key,diff/sum_er);
      
        if(fabs(diff/slope0[key]) > 0.4 || fabs(diff/sum_er) > 5){
          out_txt<<i<<" "<<key<<endl;
	}

        diff = intercept-intercept0[key];
	sum_er = fabs(intercept_error)+fabs(intercept_er0[key]);
	hkey_itcp_diff[arm]->Fill(key,diff);
	hkey_itcp_diff_er[arm]->Fill(key,diff/sum_er);
      }
    }//while
    in_txt1.close();
  }//for
  TFile* ofile = new TFile("output_compare_all.root","RECREATE");
  for(int iarm=0;iarm<2;iarm++){
    hkey_slope_diff[iarm]->Write();
    hkey_itcp_diff_er[iarm]->Write();
    hkey_itcp_diff[iarm]->Write();
    hkey_itcp_diff_er[iarm]->Write();
  }

}
