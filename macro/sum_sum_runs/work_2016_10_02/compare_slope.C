#include<fstream>
#include<map>
void compare_slope(){
  ifstream in_txt0("fitting_information_50_150.txt");
  ifstream in_txt1("fitting_information_150_200.txt");
  ifstream in_txt2("fitting_information_30_50.txt");

  map<int,double> slope_set0;
  map<int,double> slope_set1;
  map<int,double> slope_set2;

  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;
  
  while(in_txt0>>key>>slope>>intercept>>chi2>>ndf){   
    slope_set0.insert(pair<int,double>(key,slope));
  }

  while(in_txt1>>key>>slope>>intercept>>chi2>>ndf){
    if(ndf >0 && chi2/ndf > 10) continue;
    slope_set1.insert(pair<int,double>(key,slope));
  }

  while(in_txt2>>key>>slope>>intercept>>chi2>>ndf){
    if(ndf >0 && chi2/ndf > 10) continue;
    slope_set2.insert(pair<int,double>(key,slope));
  }

  TH1D* hdiff0 = new TH1D("hdiff0","Diff",400,-2,2);
  hdiff0->GetXaxis()->SetTitle("diff");

  TH1D* hdiff1 = new TH1D("hdiff1","Diff",400,-2,2);
  hdiff1->GetXaxis()->SetTitle("diff");

  for(map<int,double>::iterator it=slope_set1.begin();it!=slope_set1.end();it++){
    int key=it->first;
    double slope=it->second;
    if(slope_set0.find(key)!=slope_set0.end()){
      double slope0=slope_set0.find(key)->second;
      hdiff0->Fill((slope-slope0)/slope0);
    }
  }
  
  for(map<int,double>::iterator it=slope_set2.begin();it!=slope_set2.end();it++){
    int key=it->first;
    double slope=it->second;
    if(slope_set0.find(key)!=slope_set0.end()){
      double slope0=slope_set0.find(key)->second;
      hdiff1->Fill((slope-slope0)/slope0);
    }
  }

  TFile* ofile = new TFile("out_diff_chi2_over10.root","RECREATE");
  hdiff0->Write();
  hdiff1->Write();

}
