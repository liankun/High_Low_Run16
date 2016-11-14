#include<fstream>
void run_by_run_check(){
  TH2D* hslope[2];
  TH2D* hintercept[2];
  TH2D* hchi2[2];

  for(int iarm = 0;iarm < 2;iarm++){
    char hname[500];
    sprintf(hname,"hslope_arm%d",iarm);
    hslope[iarm] = new TH2D(hname,hname,24576,24576*iarm-0.5,24576*(iarm+1)-0.5,500,0,1);
    hslope[iarm]->GetXaxis()->SetTitle("Key");
    hslope[iarm]->GetYaxis()->SetTitle("Slope");
    sprintf(hname,"hintercept_arm%d",iarm);
    hintercept[iarm] = new TH2D(hname,hname,24576,24576*iarm-0.5,24576*(iarm+1)-0.5,500,-5,5);
    hintercept[iarm]->GetXaxis()->SetTitle("Key");
    hintercept[iarm]->GetYaxis()->SetTitle("Intercept");
    sprintf(hname,"hchi2_arm%d",iarm);
    hchi2[iarm] = new TH2D(hname,hname,24576,24576*iarm-0.5,24576*(iarm+1)-0.5,200,0,50);
    hchi2[iarm]->GetXaxis()->SetTitle("Key");
    hchi2[iarm]->GetYaxis()->SetTitle("Chi2/Ndf");
  }

  char fpath[500];
  for(int i=0;i<44;i++){
    sprintf(fpath,"../%d/fitting_information.txt",i);
    int key;
    double slope;
    double intercept;
    double chi2;
    int ndf;
    ifstream in_txt_file(fpath);
    while(in_txt_file>>key>>slope>>intercept>>chi2>>ndf){
      if(key<24576){
        hslope[0]->Fill(key,slope);
	hintercept[0]->Fill(key,intercept);
	if(ndf > 0)hchi2[0]->Fill(key,chi2/ndf);
      }
      else{
        hslope[1]->Fill(key,slope);
	hintercept[1]->Fill(key,intercept);
	if(ndf > 0)hchi2[1]->Fill(key,chi2/ndf);
      }
    }
  }
  TFile* ofile = new TFile("run_by_run_check.root","RECREATE");
  for(int iarm =0;iarm < 2;iarm++){
    hslope[iarm]->Write();
    hintercept[iarm]->Write();
    hchi2[iarm]->Write();
  }
}
