

#include "root/TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TStopwatch.h"


void DetectorStabilityPlotMaker(){


  TChain *DetectorStabilityChain = new TChain("DetectorStabilityTree");
  // DetectorStabilityChain->Add("AnaTreeLoopDataStability.root");
  DetectorStabilityChain->Add("AnaTreeLoopDataStability_0.root");
  DetectorStabilityChain->Add("AnaTreeLoopDataStability_1.root");
  DetectorStabilityChain->Add("AnaTreeLoopDataStability_2.root");
  DetectorStabilityChain->Add("AnaTreeLoopDataStability_3.root");

  // TFile *f = new TFile("AnaTreeLoopDataStability.root");
  TCanvas *c1 = new TCanvas("c1","Tree test");
  // c1->SetGridx(1);
  c1->SetGridy(1);

  gStyle->SetOptStat(0);

  // TTree *DetectorStabilityChain = (TTree*)f->Get("DetectorStabilityChain");

  //
  // Plot averge number of hits per event as a function of run
  //

  TH2F *frameNumberHitsRun = new TH2F("frameNumberHitsRun","Average Number of Hits per Event", 1000, DetectorStabilityChain->GetMinimum("Run")-100, DetectorStabilityChain->GetMaximum("Run")+100, 1000, 0, 5e4);
  frameNumberHitsRun->GetXaxis()->SetTitle("Run Number");
  frameNumberHitsRun->GetYaxis()->SetTitle("Average Number of Hits");
  frameNumberHitsRun->GetYaxis()->SetTitleOffset(1.5);
  frameNumberHitsRun->Draw();

  TLegend *lNumberHitsRun = new TLegend(0.69,0.69,0.86,0.87);
  lNumberHitsRun->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NTotalHitsInPlaneAverage:Run","","SAME");
  TGraph *gNTotalHitsInPlaneAverage = (TGraph*)gPad->GetPrimitive("Graph");
  lNumberHitsRun->AddEntry(gNTotalHitsInPlaneAverage,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NUHitsAverage:Run","","SAME");
  TGraph *gNUHitsAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gNUHitsAverage ->SetMarkerStyle(8);
  gNUHitsAverage ->SetMarkerColor(4);
  lNumberHitsRun->AddEntry(gNUHitsAverage,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NVHitsAverage:Run","","SAME");
  TGraph *gNVHitsAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gNVHitsAverage->SetMarkerStyle(8);
  gNVHitsAverage->SetMarkerColor(3);
  lNumberHitsRun->AddEntry(gNVHitsAverage,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NYHitsAverage:Run","","SAME");
  TGraph *gNYHitsAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gNYHitsAverage->SetMarkerStyle(8);
  gNYHitsAverage->SetMarkerColor(2);
  lNumberHitsRun->AddEntry(gNYHitsAverage,"Y Plane","p");

  lNumberHitsRun->Draw();
  c1->Print("NumberHitsRun.png");




  //
  // Plot averge number of hits per event as a function of date
  //

  TH2F *frameNumberHitsDate = new TH2F("frameNumberHitsDate","Average Number of Hits per Event", 1000, DetectorStabilityChain->GetMinimum("EventTime")-100000, DetectorStabilityChain->GetMaximum("EventTime")+100000, 1000, 0, 5e4);
  frameNumberHitsDate->Draw();
  frameNumberHitsDate->GetXaxis()->SetTitle("Date/Time");
  frameNumberHitsDate->GetXaxis()->SetTimeDisplay(1);
  frameNumberHitsDate->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M}");
  frameNumberHitsDate->GetXaxis()->SetLabelOffset(0.025);
  frameNumberHitsDate->GetXaxis()->SetTitleOffset(1.5);
  frameNumberHitsDate->GetYaxis()->SetTitle("Average Number of Hits");
  frameNumberHitsDate->GetYaxis()->SetTitleOffset(1.5);

  TLegend *lNumberHitsDate = new TLegend(0.69,0.69,0.86,0.87);
  lNumberHitsDate->SetFillColor(0);
  // lNumberHitsDate->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NTotalHitsInPlaneAverage:EventTime","","SAME");
  TGraph *gNTotalHitsInPlaneAverageDate = (TGraph*)gPad->GetPrimitive("Graph");
  lNumberHitsDate->AddEntry(gNTotalHitsInPlaneAverageDate,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NUHitsAverage:EventTime","","SAME");
  TGraph *gNUHitsAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gNUHitsAverageDate->SetMarkerStyle(8);
  gNUHitsAverageDate->SetMarkerColor(4);
  lNumberHitsDate->AddEntry(gNUHitsAverageDate,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NVHitsAverage:EventTime","","SAME");
  TGraph *gNVHitsAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gNVHitsAverageDate->SetMarkerStyle(8);
  gNVHitsAverageDate->SetMarkerColor(3);
  lNumberHitsDate->AddEntry(gNVHitsAverageDate,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NYHitsAverage:EventTime","","SAME");
  TGraph *gNYHitsAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gNYHitsAverage->SetMarkerStyle(8);
  gNYHitsAverage->SetMarkerColor(2);
  lNumberHitsDate->AddEntry(gNYHitsAverageDate,"Y Plane","p");

  lNumberHitsRun->Draw();
  c1->Print("NumberHitsDate.png");




  //
  // Plot standard deviation of charge of hits per event in a run
  //

  TH2F *frameHitChargeRunStanDev = new TH2F("frameHitChargeRunStanDev","Standard Deviation of Hit Charge per Event", 1000, DetectorStabilityChain->GetMinimum("Run")-100, DetectorStabilityChain->GetMaximum("Run")+100, 1000, 0, 50);
  frameHitChargeRunStanDev->GetXaxis()->SetTitle("Run Number");
  frameHitChargeRunStanDev->GetYaxis()->SetTitle("ADC");
  // frameHitChargeRunStanDev->GetYaxis()->SetTitleOffset(1.5);
  frameHitChargeRunStanDev->Draw();

  TLegend *lHitChargeRunStanDev = new TLegend(0.69,0.69,0.86,0.87);
  lHitChargeRunStanDev ->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("TotalHitChargeInPlaneStanDev:Run","","SAME");
  TGraph *gTotalHitChargeInPlaneStanDevRun  = (TGraph*)gPad->GetPrimitive("Graph");
  lHitChargeRunStanDev->AddEntry(gTotalHitChargeInPlaneStanDevRun,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("UHitChargeStanDev :Run","","SAME");
  TGraph *gUHitChargeStanDevRun    = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gUHitChargeStanDevRun  ->SetMarkerStyle(8);
  gUHitChargeStanDevRun  ->SetMarkerColor(4);
  lHitChargeRunStanDev->AddEntry(gUHitChargeStanDevRun   ,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("VHitChargeStanDev:Run","","SAME");
  TGraph *gVHitChargeStanDevRun    = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gVHitChargeStanDevRun  ->SetMarkerStyle(8);
  gVHitChargeStanDevRun  ->SetMarkerColor(3);
  lHitChargeRunStanDev->AddEntry(gVHitChargeStanDevRun   ,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("YHitChargeStanDev:Run","","SAME");
  TGraph *gYHitChargeStanDevRun = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gYHitChargeStanDevRun->SetMarkerStyle(8);
  gYHitChargeStanDevRun->SetMarkerColor(2);
  lHitChargeRunStanDev->AddEntry(gYHitChargeStanDevRun  ,"Y Plane","p");

  lHitChargeRunStanDev ->Draw();

  c1->Print("HitChargeRunStanDevRun.png");


  //
  // Plot standard deviation of charge from hits as a function of date
  //

  TH2F *frameHitChargeDateStanDev = new TH2F("frameHitChargeDateStanDev","Standard Deviation of Hit Charge per Event", 1000, DetectorStabilityChain->GetMinimum("EventTime")-100000, DetectorStabilityChain->GetMaximum("EventTime")+100000, 1000, 0, 50);
  frameHitChargeDateStanDev->GetXaxis()->SetTitle("Run Number");
  frameHitChargeDateStanDev->GetYaxis()->SetTitle("ADC");
  // frameHitChargeDateStanDev->GetYaxis()->SetTitleOffset(1.5);
  frameHitChargeDateStanDev->GetXaxis()->SetTitle("Date/Time");
  frameHitChargeDateStanDev->GetXaxis()->SetTimeDisplay(1);
  frameHitChargeDateStanDev->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M}");
  frameHitChargeDateStanDev->GetXaxis()->SetLabelOffset(0.025);
  frameHitChargeDateStanDev->GetXaxis()->SetTitleOffset(1.5);
  frameHitChargeDateStanDev->Draw();

  TLegend *lHitChargeDateStanDevDate = new TLegend(0.69,0.69,0.86,0.87);
  lHitChargeDateStanDevDate ->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("TotalHitChargeInPlaneStanDev:EventTime","","SAME");
  TGraph *gTotalHitChargeInPlaneStanDevDate  = (TGraph*)gPad->GetPrimitive("Graph");
  lHitChargeDateStanDevDate->AddEntry(gTotalHitChargeInPlaneStanDevDate   ,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("UHitChargeStanDev:EventTime","","SAME");
  TGraph *gUHitChargeStanDevDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gUHitChargeStanDevDate->SetMarkerStyle(8);
  gUHitChargeStanDevDate->SetMarkerColor(4);
  lHitChargeDateStanDevDate->AddEntry(gUHitChargeStanDevDate,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("VHitChargeStanDev:EventTime","","SAME");
  TGraph *gVHitChargeStanDevDate  = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gVHitChargeStanDevDate->SetMarkerStyle(8);
  gVHitChargeStanDevDate->SetMarkerColor(3);
  lHitChargeDateStanDevDate->AddEntry(gVHitChargeStanDevDate,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("YHitChargeStanDev:EventTime","","SAME");
  TGraph *gYHitChargeStanDevDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gYHitChargeStanDevDate->SetMarkerStyle(8);
  gYHitChargeStanDevDate->SetMarkerColor(2);
  lHitChargeDateStanDevDate->AddEntry(gYHitChargeStanDevDate,"Y Plane","p");

  lHitChargeDateStanDevDate->Draw();

  c1->Print("HitChargeDateStanDevDate.png");












  //
  // Plot average charge of hits per event in a run
  //

  TH2F *frameHitChargeRun = new TH2F("frameHitChargeRun","Average Hit Charge per Event", 1000, DetectorStabilityChain->GetMinimum("Run")-100, DetectorStabilityChain->GetMaximum("Run")+100, 1000, 0, 500);
  frameHitChargeRun->GetXaxis()->SetTitle("Run Number");
  frameHitChargeRun->GetYaxis()->SetTitle("ADC");
  // frameHitChargeRun->GetYaxis()->SetTitleOffset(1.5);
  frameHitChargeRun->Draw();

  TLegend *lHitChargeRun = new TLegend(0.69,0.69,0.86,0.87);
  lHitChargeRun->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("TotalHitChargeInPlaneAverage:Run","","SAME");
  TGraph *gTotalHitChargeInPlaneAverage = (TGraph*)gPad->GetPrimitive("Graph");
  lHitChargeRun->AddEntry(gTotalHitChargeInPlaneAverage,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("UHitChargeAverage:Run","","SAME");
  TGraph *gUHitChargeAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gUHitChargeAverage->SetMarkerStyle(8);
  gUHitChargeAverage->SetMarkerColor(4);
  lHitChargeRun->AddEntry(gUHitChargeAverage,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("VHitChargeAverage:Run","","SAME");
  TGraph *gVHitChargeAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gVHitChargeAverage->SetMarkerStyle(8);
  gVHitChargeAverage->SetMarkerColor(3);
  lHitChargeRun->AddEntry(gVHitChargeAverage,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("YHitChargeAverage:Run","","SAME");
  TGraph *gYHitChargeAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gYHitChargeAverage->SetMarkerStyle(8);
  gYHitChargeAverage->SetMarkerColor(2);
  lHitChargeRun->AddEntry(gYHitChargeAverage,"Y Plane","p");

  lHitChargeRun->Draw();

  c1->Print("HitChargeRun.png");


  //
  // Plot average charge of hits as a function of date
  //

  TH2F *frameHitChargeDate = new TH2F("frameHitChargeDate","Average Hit Charge per Event", 1000, DetectorStabilityChain->GetMinimum("EventTime")-100000, DetectorStabilityChain->GetMaximum("EventTime")+100000, 1000, 0, 500);
  frameHitChargeDate->GetYaxis()->SetTitle("ADC");
  // frameHitChargeDate->GetYaxis()->SetTitleOffset(1.5);
  frameHitChargeDate->Draw();
  frameHitChargeDate->GetXaxis()->SetTitle("Date/Time");
  frameHitChargeDate->GetXaxis()->SetTimeDisplay(1);
  frameHitChargeDate->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M}");
  frameHitChargeDate->GetXaxis()->SetLabelOffset(0.025);
  frameHitChargeDate->GetXaxis()->SetTitleOffset(1.5);

  TLegend *lHitChargeDate = new TLegend(0.69,0.69,0.86,0.87);
  lHitChargeDate->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("TotalHitChargeInPlaneAverage:EventTime","","SAME");
  TGraph *gTotalHitChargeInPlaneAverageDate = (TGraph*)gPad->GetPrimitive("Graph");
  lHitChargeDate->AddEntry(gTotalHitChargeInPlaneAverageDate,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("UHitChargeAverage:EventTime","","SAME");
  TGraph *gUHitChargeAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gUHitChargeAverageDate->SetMarkerStyle(8);
  gUHitChargeAverageDate->SetMarkerColor(4);
  lHitChargeDate->AddEntry(gUHitChargeAverageDate,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("VHitChargeAverage:EventTime","","SAME");
  TGraph *gVHitChargeAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gVHitChargeAverageDate->SetMarkerStyle(8);
  gVHitChargeAverageDate->SetMarkerColor(3);
  lHitChargeDate->AddEntry(gVHitChargeAverageDate,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("YHitChargeAverage:EventTime","","SAME");
  TGraph *gYHitChargeAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gYHitChargeAverageDate->SetMarkerStyle(8);
  gYHitChargeAverageDate->SetMarkerColor(2);
  lHitChargeDate->AddEntry(gYHitChargeAverageDate,"Y Plane","p");

  lHitChargeDate->Draw();

  c1->Print("HitChargeDate.png");







  //
  // Plot average peak charge of hits per event in a run
  //

  TH2F *frameHitPeakChargeRun = new TH2F("frameHitPeakChargeRun","Average Hit Peak Charge per Event", 1000, DetectorStabilityChain->GetMinimum("Run")-100, DetectorStabilityChain->GetMaximum("Run")+100, 1000, 0, 75);
  frameHitPeakChargeRun->GetYaxis()->SetTitle("ADC");
  // frameHitPeakChargeRun->GetYaxis()->SetTitleOffset(1.5);
  frameHitPeakChargeRun->GetXaxis()->SetTitle("Run Number");
  frameHitPeakChargeRun->Draw();

  TLegend *lHitPeakChargeRun = new TLegend(0.69,0.69,0.86,0.87);
  lHitPeakChargeRun->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("TotalHitPeakChargeInPlaneAverage:Run","","SAME");
  TGraph *gTotalHitPeakChargeInPlaneAverage = (TGraph*)gPad->GetPrimitive("Graph");
  lHitPeakChargeRun->AddEntry(gTotalHitPeakChargeInPlaneAverage,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("UHitPeakChargeAverage:Run","","SAME");
  TGraph *gUHitPeakChargeAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gUHitPeakChargeAverage->SetMarkerStyle(8);
  gUHitPeakChargeAverage->SetMarkerColor(4);
  lHitPeakChargeRun->AddEntry(gUHitPeakChargeAverage,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("VHitPeakChargeAverage:Run","","SAME");
  TGraph *gVHitPeakChargeAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gVHitPeakChargeAverage->SetMarkerStyle(8);
  gVHitPeakChargeAverage->SetMarkerColor(3);
  lHitPeakChargeRun->AddEntry(gVHitPeakChargeAverage,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("YHitPeakChargeAverage:Run","","SAME");
  TGraph *gYHitPeakChargeAverage = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gYHitPeakChargeAverage->SetMarkerStyle(8);
  gYHitPeakChargeAverage->SetMarkerColor(2);
  lHitPeakChargeRun->AddEntry(gYHitPeakChargeAverage,"Y Plane","p");

  lHitPeakChargeRun->Draw();

  c1->Print("HitPeakChargeRun.png");







  //
  // Plot average peak charge of hits as a function of date
  //

  TH2F *frameHitPeakChargeDate = new TH2F("frameHitPeakChargeDate","Average Hit Peak Charge per Event", 1000, DetectorStabilityChain->GetMinimum("EventTime")-100000, DetectorStabilityChain->GetMaximum("EventTime")+100000, 1000, 0, 75);
  frameHitPeakChargeDate->GetYaxis()->SetTitle("ADC");
  // frameHitPeakChargeDate->GetYaxis()->SetTitleOffset(1.5);
  frameHitPeakChargeDate->Draw();
  frameHitPeakChargeDate->GetXaxis()->SetTitle("Date/Time");
  frameHitPeakChargeDate->GetXaxis()->SetTimeDisplay(1);
  frameHitPeakChargeDate->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M}");
  frameHitPeakChargeDate->GetXaxis()->SetLabelOffset(0.025);
  frameHitPeakChargeDate->GetXaxis()->SetTitleOffset(1.5);

  TLegend *lHitPeakChargeDate = new TLegend(0.69,0.69,0.86,0.87);
  lHitPeakChargeDate->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("TotalHitPeakChargeInPlaneAverage:EventTime","","SAME");
  TGraph *gTotalHitPeakChargeInPlaneAverageDate = (TGraph*)gPad->GetPrimitive("Graph");
  lHitPeakChargeDate->AddEntry(gTotalHitPeakChargeInPlaneAverageDate,"All Planes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(4);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("UHitPeakChargeAverage:EventTime","","SAME");
  TGraph *gUHitPeakChargeAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gUHitPeakChargeAverageDate->SetMarkerStyle(8);
  gUHitPeakChargeAverageDate->SetMarkerColor(4);
  lHitPeakChargeDate->AddEntry(gUHitPeakChargeAverageDate,"U Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(3);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("VHitPeakChargeAverage:EventTime","","SAME");
  TGraph *gVHitPeakChargeAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gVHitPeakChargeAverageDate->SetMarkerStyle(8);
  gVHitPeakChargeAverageDate->SetMarkerColor(3);
  lHitPeakChargeDate->AddEntry(gVHitPeakChargeAverageDate,"V Plane","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("YHitPeakChargeAverage:EventTime","","SAME");
  TGraph *gYHitPeakChargeAverageDate = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gYHitPeakChargeAverageDate->SetMarkerStyle(8);
  gYHitPeakChargeAverageDate->SetMarkerColor(2);
  lHitPeakChargeDate->AddEntry(gYHitPeakChargeAverageDate,"Y Plane","p");

  lHitPeakChargeDate->Draw();

  c1->Print("HitPeakChargeDate.png");





  //
  // Plot averge number of flashes per event as a function of run
  //

  TH2F *frameNumberFlashesRun = new TH2F("frameNumberFlashesRun","Average Number of Flashes per Event", 1000, DetectorStabilityChain->GetMinimum("Run")-100, DetectorStabilityChain->GetMaximum("Run")+100, 1000, 0, 200);
  frameNumberFlashesRun->GetYaxis()->SetTitle("Average Number of Flashes");
  // frameNumberFlashesRun->GetYaxis()->SetTitleOffset(1.5);
  frameNumberFlashesRun->GetXaxis()->SetTitle("Run Number");
  frameNumberFlashesRun->Draw();

  TLegend *lNumberFlashesRun = new TLegend(0.59,0.69,0.86,0.87);
  lNumberFlashesRun->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NAllFlashesAverage:Run","","SAME");
  TGraph *gNAllFlashesAverageRun = (TGraph*)gPad->GetPrimitive("Graph");
  lNumberFlashesRun->AddEntry(gNAllFlashesAverageRun ,"All Flashes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("N50PEFlashesAverage:Run","","SAME");
  TGraph *gN50PEFlashesAverageRun  = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gN50PEFlashesAverageRun ->SetMarkerStyle(8);
  gN50PEFlashesAverageRun ->SetMarkerColor(2);
  lNumberFlashesRun->AddEntry(gN50PEFlashesAverageRun ,"Flashes > 50 PE","p");

  lNumberFlashesRun->Draw();
  c1->Print("NumberFlashesRun.png");



  //
  // Plot averge number of flashes per event as a function of date
  //


  TH2F *frameNumberFlashesDate = new TH2F("frameNumberFlashesDate","Average Number of Flashes per Event", 1000, DetectorStabilityChain->GetMinimum("EventTime")-100000, DetectorStabilityChain->GetMaximum("EventTime")+100000, 1000, 0, 200);
  frameNumberFlashesDate->GetYaxis()->SetTitle("Average Number of Flashes");
  // frameNumberFlashesDate->GetYaxis()->SetTitleOffset(1.5);
  frameNumberFlashesDate->Draw();
  frameNumberFlashesDate->GetXaxis()->SetTitle("Date/Time");
  frameNumberFlashesDate->GetXaxis()->SetTimeDisplay(1);
  frameNumberFlashesDate->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M}");
  frameNumberFlashesDate->GetXaxis()->SetLabelOffset(0.025);
  frameNumberFlashesDate->GetXaxis()->SetTitleOffset(1.5);

  TLegend *lNumberFlashesDate = new TLegend(0.59,0.69,0.86,0.87);
  lNumberFlashesDate->SetFillColor(0);
  // leg->SetLineColor(0);

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(1);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("NAllFlashesAverage:EventTime","","SAME");
  TGraph *gNAllFlashesAverageDate = (TGraph*)gPad->GetPrimitive("Graph");
  lNumberFlashesDate->AddEntry(gNAllFlashesAverageDate ,"All Flashes","p");

  DetectorStabilityChain->SetMarkerStyle(8);
  DetectorStabilityChain->SetMarkerColor(2);
  DetectorStabilityChain->SetMarkerSize(1.0);
  DetectorStabilityChain->Draw("N50PEFlashesAverage:EventTime","","SAME");
  TGraph *gN50PEFlashesAverageDate  = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  gN50PEFlashesAverageDate ->SetMarkerStyle(8);
  gN50PEFlashesAverageDate ->SetMarkerColor(2);
  lNumberFlashesDate->AddEntry(gN50PEFlashesAverageDate ,"Flashes > 50 PE","p");

  lNumberFlashesDate->Draw();
  c1->Print("NumberFlashesDate.png");


}






