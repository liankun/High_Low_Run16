#include<fstream>
void count_hist_num(){
//  ifstream in_txt("MPC-EX_Physics_Run_List.txt");
//  int runNumber=455056;
  ofstream out_txt("hist_number.txt"); 
  for(int j=0;j<44;j++){   
    cout<<"Process "<<j<<endl;
    char fpath[500];
    sprintf(fpath,"%d/sum_sum.root",j);
    TFile* ifile = new TFile(fpath,"READONLY");
    int num_hist=0;
    for(int i=0;i<128*24*16;i++){
      char hname[500];
      sprintf(hname,"hhigh_low_key%d",i);
      TH2D* htemp = (TH2D*)ifile->Get(hname);
      if(!htemp) continue;
      else{
        num_hist++;
	delete htemp;
      }
    }
    ifile->Close();
    cout<<j<<" "<<num_hist<<endl;
    out_txt<<j<<" "<<num_hist<<endl;
  }
}
