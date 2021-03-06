{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Oct 11 14:28:05 2016) by ROOT version5.30/03
/*   TCanvas *c1 = new TCanvas("c1", "c1",12,61,700,500);
   c1->Range(0.06225,-0.792664,0.43975,4.123675);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
*/   
   TH1D *hslope = new TH1D("hslope1","fitting slope",500,0,1);
   hslope->SetBinContent(73,2);
   hslope->SetBinContent(74,7);
   hslope->SetBinContent(75,10);
   hslope->SetBinContent(76,18);
   hslope->SetBinContent(77,26);
   hslope->SetBinContent(78,39);
   hslope->SetBinContent(79,64);
   hslope->SetBinContent(80,88);
   hslope->SetBinContent(81,128);
   hslope->SetBinContent(82,181);
   hslope->SetBinContent(83,200);
   hslope->SetBinContent(84,242);
   hslope->SetBinContent(85,383);
   hslope->SetBinContent(86,448);
   hslope->SetBinContent(87,530);
   hslope->SetBinContent(88,624);
   hslope->SetBinContent(89,731);
   hslope->SetBinContent(90,842);
   hslope->SetBinContent(91,1012);
   hslope->SetBinContent(92,1107);
   hslope->SetBinContent(93,1291);
   hslope->SetBinContent(94,1550);
   hslope->SetBinContent(95,1749);
   hslope->SetBinContent(96,1963);
   hslope->SetBinContent(97,2016);
   hslope->SetBinContent(98,2093);
   hslope->SetBinContent(99,2054);
   hslope->SetBinContent(100,2116);
   hslope->SetBinContent(101,2170);
   hslope->SetBinContent(102,2244);
   hslope->SetBinContent(103,2241);
   hslope->SetBinContent(104,2118);
   hslope->SetBinContent(105,2262);
   hslope->SetBinContent(106,2242);
   hslope->SetBinContent(107,2044);
   hslope->SetBinContent(108,2171);
   hslope->SetBinContent(109,1923);
   hslope->SetBinContent(110,1641);
   hslope->SetBinContent(111,1308);
   hslope->SetBinContent(112,1005);
   hslope->SetBinContent(113,793);
   hslope->SetBinContent(114,498);
   hslope->SetBinContent(115,340);
   hslope->SetBinContent(116,199);
   hslope->SetBinContent(117,101);
   hslope->SetBinContent(118,66);
   hslope->SetBinContent(119,16);
   hslope->SetBinContent(120,11);
   hslope->SetBinContent(121,4);
   hslope->SetBinContent(122,5);
   hslope->SetBinContent(123,1);
   hslope->SetBinContent(124,1);
   hslope->SetBinContent(129,1);
   hslope->SetBinContent(134,1);
   hslope->SetBinContent(142,1);
   hslope->SetBinContent(146,1);
   hslope->SetEntries(46922);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("hslope");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 46922  ");
   text = ptstats->AddText("Mean  = 0.2008");
   text = ptstats->AddText("RMS   = 0.01518");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   hslope->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hslope->GetListOfFunctions());

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   hslope->SetLineColor(ci);
   hslope->GetXaxis()->SetTitle("slope");
   hslope->GetXaxis()->SetRange(51,201);
   hslope->GetXaxis()->SetLabelFont(42);
   hslope->GetXaxis()->SetLabelSize(0.035);
   hslope->GetXaxis()->SetTitleSize(0.035);
   hslope->GetXaxis()->SetTitleFont(42);
   hslope->GetYaxis()->SetLabelFont(42);
   hslope->GetYaxis()->SetLabelSize(0.035);
   hslope->GetYaxis()->SetTitleSize(0.035);
   hslope->GetYaxis()->SetTitleFont(42);
   hslope->GetZaxis()->SetLabelFont(42);
   hslope->GetZaxis()->SetLabelSize(0.035);
   hslope->GetZaxis()->SetTitleSize(0.035);
   hslope->GetZaxis()->SetTitleFont(42);
   hslope->SetLineColor(kGreen);
   hslope->Draw("same");
   
   TPaveText *pt = new TPaveText(0.3922989,0.9339831,0.6077011,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextFont(42);
   text = pt->AddText("fitting slope");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
