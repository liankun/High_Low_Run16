#include<fstream>
#include<set>
void get_deadhot_hl(int group=0){
  ifstream high_deadhot_txt("high_bad_list_merge.txt");
  ifstream low_deadhot_txt("low_bad_list_merge.txt");

  ifstream high_discrete_txt("high_discrete.txt");
  ifstream low_discrete_txt("low_discrete.txt");

  set<int> high_deadhot_set;
  set<int> low_deadhot_set;
  set<int> high_discrete_set;
  set<int> low_discrete_set;

  int key;
  while(high_deadhot_txt>>key){
    high_deadhot_set.insert(key);
  }
  
  while(low_deadhot_txt>>key){
    low_deadhot_set.insert(key);
  }
  
  while(high_discrete_txt>>key){
    high_discrete_set.insert(key);
  }
  
  while(low_discrete_txt>>key){
    low_discrete_set.insert(key);
  }


  char file_name[500];
  sprintf(file_name,"%d/sum_sum.root",group);
  TFile* ifile = new TFile(file_name,"READONLY");
  TFile* ofile = new TFile("high_only_deadhot.root","RECREATE");
  for(set<int>::iterator it=high_deadhot_set.begin();it!=high_deadhot_set.end();++it){
    char hname[500];
    int key=(*it);
    if(low_deadhot_set.find(key)==low_deadhot_set.end()){
      sprintf(hname,"hhigh_low_key%d",key);
      TH2D* htemp=(TH2D*)ifile->Get(hname);
      ofile->cd();
      htemp->Write();
      delete htemp;
    }
  }
  ofile->Close();
  
  ofile = new TFile("low_only_deadhot.root","RECREATE");
  for(set<int>::iterator it=low_deadhot_set.begin();it!=low_deadhot_set.end();++it){
    char hname[500];
    int key=(*it);
    if(high_deadhot_set.find(key)==high_deadhot_set.end()){
      sprintf(hname,"hhigh_low_key%d",key);
      TH2D* htemp=(TH2D*)ifile->Get(hname);
      ofile->cd();
      htemp->Write();
      delete htemp;
    }
  }
  ofile->Close();

  ofile = new TFile("both_high_low_deadhot.root","RECREATE");
  for(set<int>::iterator it=low_deadhot_set.begin();it!=low_deadhot_set.end();++it){
    char hname[500];
    int key=(*it);
    if(high_deadhot_set.find(key)!=high_deadhot_set.end()){
      sprintf(hname,"hhigh_low_key%d",key);
      TH2D* htemp=(TH2D*)ifile->Get(hname);
      ofile->cd();
      htemp->Write();
      delete htemp;
    }
  }
  ofile->Close();
}
