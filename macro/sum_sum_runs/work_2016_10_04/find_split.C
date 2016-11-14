//use ratio to find the split
#include<TSpectrum.h>
#include<fstream>
#include<set>

void find_split(){
  ifstream high_deadhot_txt("../high_bad_list_merge_final.txt");
  ifstream low_deadhot_txt("../low_bad_list_merge.txt");
  set<int> deadhot_set;
  int key;
  while(high_deadhot_txt>>key){
    deadhot_set.insert(key);
  }

  while(low_deadhot_txt>>key){
    deadhot_set.insert(key);
  }

  TFile* ifile = new TFile("../sum_all_runs.root","READONLY");
  if(!ifile){
    cout<<"open file failled !!!"<<endl;
    return;  
  }

  TFile* ofile = new TFile("output_ratio_sigma3.root","RECREATE");
  ofstream out_txt("split_channel.txt");
  for(int i=0;i<128*24*16;i++){ 
    if(deadhot_set.find(i)!=deadhot_set.end()) continue;
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",i);
    TH2D* hexam = (TH2D*)ifile->Get(hname);
    double entries = hexam->GetEntries();
    if(entries<5){
      delete hexam;
      continue;
    }
    int NbinsX = hexam->GetNbinsX();
    int NbinsY = hexam->GetNbinsY();
    
    sprintf(hname,"hratio_key%d",i);
    TH1D* hratio = new TH1D(hname,hname,200,-20,20);
    hratio->GetXaxis()->SetTitle("ratio");

    for(int ix=0;ix<NbinsX;ix++){
      for(int iy=0;iy<NbinsY;iy++){
        double x=hexam->GetXaxis()->GetBinCenter(ix+1);
        double y=hexam->GetYaxis()->GetBinCenter(iy+1);
        if(y<10 || x < 0 || y>200) continue;
        double content=hexam->GetBinContent(ix+1,iy+1);
        if(content<5) continue;
        hratio->Fill(y/x,content);
      }
    }

    TSpectrum *s = new TSpectrum(2);
    Int_t nfound = s->Search(hratio,2,"",0.30);
    if(nfound>1){
      hratio->Write();
      hexam->Write();
      out_txt<<i<<endl;
    }
    delete s;
    delete hratio;
    delete hexam;
  }
}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}

