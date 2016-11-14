#include<fstream>
void count_hist_num0(){
  ifstream in_txt("run_list.txt");
  int runNumber;
  ofstream out_txt("hist_key_num0.txt");
  while(in_txt>>runNumber){
    if(runNumber>455073) continue; 
    cout<<"Process "<<runNumber<<endl;
    char fpath[500];
    sprintf(fpath,"%d/sum.root",runNumber);
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
    cout<<runNumber<<" "<<num_hist<<endl;
    out_txt<<runNumber<<" "<<num_hist<<endl; 
  }
}
