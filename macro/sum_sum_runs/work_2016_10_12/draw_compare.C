//draw big diff of slope and intercept
//compare with reference
#include<fstream>
#include<set>
void draw_compare(){
  ifstream in_txt0("big_diff_slope_series4.txt");
  ifstream in_txt1("big_diff_intercept_series4.txt");
  set<int> slope_set;
  set<int> intercept_set;
  int key;
  while(in_txt0>>key){
    slope_set.insert(key);
  }
  while(in_txt1>>key){
    intercept_set.insert(key);
  }

  TFile* ifile0 = new TFile("output_fit_switch_50_150_exclude_deadhot.root","READONLY");
  TFile* ifile1 = new TFile("output_fit_switch_50_150_exclude_deadhot4.root","READONLY");
  
  TFile* ofile = new TFile("output_compare_series4.root","RECREATE");

  for(set<int>::iterator it=slope_set.begin();it!=slope_set.end();++it){
    int key=*it;
    char hname[500];
    sprintf(hname,"hhigh_low_key%d_pfy",key);
    TProfile* ptemp0 = (TProfile*)ifile0->Get(hname);
    TProfile* ptemp1 = (TProfile*)ifile1->Get(hname);
    sprintf(hname,"fit_fun_key%d",key);
    ptemp0->GetFunction(hname)->SetLineColor(kBlack);
    ptemp1->SetLineColor(kRed);
    ptemp1->GetFunction(hname)->SetLineColor(kGreen);
    sprintf(hname,"c_slope_%d",key);
    TCanvas* c = new TCanvas(hname,hname);
    ptemp0->Draw("");
    ptemp1->Draw("same");
    ofile->cd();
    c->Write();
    delete ptemp0;
    delete ptemp1;
    delete c;
  }

  for(set<int>::iterator it=intercept_set.begin();it!=intercept_set.end();++it){
    int key=*it;
    char hname[500];
    sprintf(hname,"hhigh_low_key%d_pfy",key);
    TProfile* ptemp0 = (TProfile*)ifile0->Get(hname);
    TProfile* ptemp1 = (TProfile*)ifile1->Get(hname);
    sprintf(hname,"fit_fun_key%d",key);
    ptemp0->GetFunction(hname)->SetLineColor(kBlack);
    ptemp1->SetLineColor(kRed);
    ptemp1->GetFunction(hname)->SetLineColor(kGreen);
    sprintf(hname,"c_intercept_%d",key);
    TCanvas* c = new TCanvas(hname,hname);
    ptemp0->Draw("");
    ptemp1->Draw("same");
    ofile->cd();
    c->Write();
    delete ptemp0;
    delete ptemp1;
    delete c;
  }
}
