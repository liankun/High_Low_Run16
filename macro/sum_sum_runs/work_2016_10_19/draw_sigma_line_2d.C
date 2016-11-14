//testing the sigma 
void draw_sigma_line_2d(){
  TFile* ifile = new TFile("../sum_all_runs.root");
  if(!ifile){
    cout<<"open file failed !!!"<<endl;
    return;
  }
  TH2D* htemp=(TH2D*)ifile->Get("hhigh_low_key3585");
  if(!htemp){
    cout<<"no 2d hist !"<<endl;
    return;
  }

  int NbinsX=htemp->GetNbinsX();
  int NbinsY=htemp->GetNbinsY();


  double slope=0.2151;
  double intercept=1.188;
  double sigma=0.9753;

  TF1* ff = new TF1("fun",fitf,0,250,2);
  ff->SetParameter(0,intercept);
  ff->SetParameter(1,slope);
  ff->SetLineColor(kRed);

/*
  for(int ix=0;ix<NbinsX;ix++){
    for(int iy=0;iy<NbinsY;iy++){
      double y=htemp->GetYaxis()->GetBinCenter(iy+1);
      double x=htemp->GetXaxis()->GetBinCenter(ix+1);
      double eval_x = ff->Eval(y);
      double dist = (eval_x-x)/sqrt(slope*slope+1);
      if(fabs(dist)>5*sigma){
        htemp->SetBinContent(ix+1,iy+1,0);
      }
    }
  }
*/
  htemp->ResetStats();

  ff->SetParameter(0,-intercept/slope);
  ff->SetParameter(1,1/slope);


  TF1* ff0 = new TF1("fun0",fitf,0,200,2);
  ff0->SetParameter(0,-intercept/slope-5*sigma*sqrt(1+1/(slope*slope)));
  ff0->SetParameter(1,1/slope);
  ff0->SetLineColor(kRed);

  TF1* ff1 = new TF1("fun1",fitf,0,200,2);
  ff1->SetParameter(0,-intercept/slope+5*sigma*sqrt(1+1/(slope*slope)));
  ff1->SetParameter(1,1/slope);
  ff1->SetLineColor(kRed);

  TCanvas* c;
  htemp->Draw("colz");
  ff->Draw("same");
  ff0->Draw("same");
  ff1->Draw("same");

}

Double_t fitf(Double_t* x,Double_t* par){
  double result=0;
  result += par[0]+par[1]*x[0];
  return result;
}

