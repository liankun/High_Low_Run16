#include<fstream>
#include<set>

void ana_fit(){
  ifstream in_txt("fit_sigma_result_all_runs.txt");
  ifstream in_txt1("../split_list.txt");
  int key;
  double par0;
  double error0;
  double par1;
  double error1;
  double par2;
  double error2;
  double chi2;
  int ndf;
  
  set<int> bad_set;
  while(in_txt1>>key){
    bad_set.insert(key);
  }

  TH3D* hmean_sigma[2];
  hmean_sigma[0] = new TH3D("hmean_sigma0","Mean vs Sigma South",400,0,100,200,-1,1,200,-5,5);
  hmean_sigma[0]->GetXaxis()->SetTitle("chi2/ndf");
  hmean_sigma[0]->GetYaxis()->SetTitle("Mean");
  hmean_sigma[0]->GetZaxis()->SetTitle("Sigma");

  hmean_sigma[1] = new TH3D("hmean_sigma1","Mean vs Sigma North",400,0,100,200,-1,1,200,-5,5);
  hmean_sigma[1]->GetXaxis()->SetTitle("chi2/ndf"); 
  hmean_sigma[1]->GetYaxis()->SetTitle("Mean");
  hmean_sigma[1]->GetZaxis()->SetTitle("Sigma");

  TH3D* hsigma_layer[2];
  hsigma_layer[0] = new TH3D("hsigma_layer0","Layer Dependence South",8,-0.5,7.5,200,-1,1,200,-5,5);
  hsigma_layer[0]->GetXaxis()->SetTitle("Layer");
  hsigma_layer[0]->GetYaxis()->SetTitle("Mean");
  hsigma_layer[0]->GetZaxis()->SetTitle("Sigma");


  hsigma_layer[1] = new TH3D("hsigma_layer1","Layer Dependence North",8,-0.5,7.5,200,-1,1,200,-5,5);
  hsigma_layer[1]->GetXaxis()->SetTitle("Layer");
  hsigma_layer[1]->GetYaxis()->SetTitle("Mean");
  hsigma_layer[1]->GetZaxis()->SetTitle("Sigma");


  while(in_txt>>key>>par0>>error0>>par1>>error1>>par2>>error2>>chi2>>ndf){
    if(bad_set.find(key)!=bad_set.end())continue;  
    if(key<128*24*8){
      hmean_sigma[0]->Fill(chi2/ndf,par1,fabs(par2));
      int layer=key/(128*24);
//      if(layer!=2 && layer!=6)
      hsigma_layer[0]->Fill(layer,par1,fabs(par2));
    }
    else{
      hmean_sigma[1]->Fill(chi2/ndf,par1,fabs(par2));
      int layer=(key-128*24*8)/(128*24);
//      if(layer!=2 && layer!=6)
      hsigma_layer[1]->Fill(layer,par1,fabs(par2));
    }
  }

  TFile* ofile = new TFile("output_ana_fit_all_runs_update_split.root","RECREATE");
  for(int iarm=0;iarm<2;iarm++){
    hmean_sigma[iarm]->Write();
    hsigma_layer[iarm]->Write();
  }
}
