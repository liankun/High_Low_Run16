#include<fstream>
#include<set>
void draw_canvas(){
  ifstream in_txt("big_diff_ch_sigma_big.txt");
  set<int> split_set;
  int key;
  while(in_txt>>key){
    split_set.insert(key);
  }
  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  for(set<int>::iterator it=split_set.begin();it!=split_set.end();it++){
    int key=*it;
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",key);
    TH2D* htemp = (TH2D*)ifile->Get(hname);
    sprintf(hname,"c_high_low_key%d",key);
    TCanvas* c = new TCanvas();
    c->SetLogz();
    htemp->Draw("colz");
    sprintf(hname,"all_runs_sigma/c_high_low_key%d.gif",key);
    c->Print(hname,"gif");
    delete c;
  }
}
