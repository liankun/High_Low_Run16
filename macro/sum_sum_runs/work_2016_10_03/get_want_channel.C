#include<fstream>
#include<set>

void get_want_channel(){
  ifstream in_txt("diff_over10_50_100_vs_50_150.txt");
  int key;
  set<int> want_set;
  while(in_txt>>key){
    want_set.insert(key);
  }

  TFile* ifile0 = new TFile("../work_2016_10_02/output_fit_switch_50_100_exclude_deadhot.root","READONLY");
  TFile* ifile1 = new TFile("../sum_all_runs.root","READONLY");
  TFile* ofile = new TFile("output_diff_channel_50_100.root","RECREATE");
  char name[500];
  for(set<int>::iterator it=want_set.begin();it!=want_set.end();++it){
    int key = *it;
    sprintf(name,"hhigh_low_key%d_pfy",key);
    TProfile* ptemp = (TProfile*)ifile0->Get(name);
    ofile->cd();
    ptemp->Write();
    sprintf(name,"hhigh_low_key%d",key);
    TH2D* htemp = (TH2D*)ifile1->Get(name);
    ofile->cd();
    htemp->Write();
    delete ptemp;
    delete htemp;
  }
}
