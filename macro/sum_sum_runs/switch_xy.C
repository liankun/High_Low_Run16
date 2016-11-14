void switch_xy(){
  TFile* ifile = new TFile("sum_all_runs.root","READONLY");
  TFile* ofile = new TFile("sum_all_runs_xy_switch.root","RECREATE");

  for(int i=0;i<128*24*16;i++){
    char hname[500];
    sprintf(hname,"hhigh_low_key%d",i);
    TH2D* htemp = (TH2D*)ifile->Get(hname);
    if(!htemp) cout<<"get "<<i<<" failed !"<<endl;
    
    sprintf(hname,"hhigh_low_key%d_switch",i);
    TH2D* htemp_switch = new TH2D(hname,hname,230,-0.5,230-0.5,230,-0.5,230-0.5);
    htemp_switch->GetXaxis()->SetTitle("High Gain ADC");
    htemp_switch->GetYaxis()->SetTitle("Low Gain ADC");
    for(int ix=0;ix<230;ix++){
      for(int iy=0;iy<230;iy++){
        double content = htemp->GetBinContent(ix+1,iy+1);
	if(content>0) htemp_switch->SetBinContent(iy+1,ix+1,content);
      }
    }
    ofile->cd();
    htemp_switch->Write();
    delete htemp;
    delete htemp_switch;
  }
}
