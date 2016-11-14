#include<fstream>
void slope_row(){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);
  MpcExMapper* mapper = MpcExMapper::instance();

  TH1D* hslope_new_key[2];
  TH1D* hintercept_new_key[2];

  for(int iarm=0;iarm<2;iarm++){
    char hname[500];
    sprintf(hname,"hslope_new_key_arm%d",iarm);
    hslope_new_key[iarm] = new TH1D(hname,hname,24576,24576*iarm-0.5,24576*(iarm+1)-0.5);
    hslope_new_key[iarm]->GetXaxis()->SetTitle("New Key");    
    sprintf(hname,"hintercept_new_key_arm%d",iarm);
    hintercept_new_key[iarm] = new TH1D(hname,hname,24576,24576*iarm-0.5,24576*(iarm+1)-0.5);
    hintercept_new_key[iarm]->GetXaxis()->SetTitle("New Key");
  }

  ifstream in_txt_file("fitting_information_50_200.txt");
  int key;
  double slope;
  double intercept;
  double chi2;
  int ndf;
  while(in_txt_file>>key>>slope>>intercept>>chi2>>ndf){
    int arm = mapper->get_arm(key);
    int layer = mapper->get_layer(key);
    int quadrant = mapper->get_quadrant(key);
    int sensor = mapper->get_sensor_in_quadrant(key);
    int index = 6*quadrant+sensor;
    int ly = mapper->get_ly(key);
    int lx = mapper->get_lx(key);
    int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
    hslope_new_key[arm]->Fill(new_key,slope);
    hintercept_new_key[arm]->Fill(new_key,intercept);
  }
  
  TFile* ofile = new TFile("fitting_vs_key.root","RECREATE");
  for(int iarm=0;iarm<2;iarm++){
    hslope_new_key[iarm]->Write();
    hintercept_new_key[iarm]->Write();
  }
}
