

#include "root/TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include <fstream>

// Returns the plane for a given channel
// 0 for U, 1 for V, 2 for Y
Short_t ChannelToPlane(Short_t channel){

  if(channel < 2400)
    return 0;
  if(2400 <= channel && channel < 2*2400)
    return 1;
  if(2*2400 <= channel)
    return 2;
  return -999;
}



Double_t langaufun(Double_t *x, Double_t *par) {

   //Fit parameters:
   //par[0]=Width (scale) parameter of Landau density
   //par[1]=Most Probable (MP, location) parameter of Landau density
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
   //
   //In the Landau distribution (represented by the CERNLIB approximation),
   //the maximum is located at x=-0.22278298 with the location parameter=0.
   //This shift is corrected within this function, so that the actual
   //maximum is identical to the MP parameter.

      // Numeric constants
      Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
      Double_t mpshift  = -0.22278298;       // Landau maximum location

      // Control constants
      Double_t np = 100.0;      // number of convolution steps
      Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

      // Variables
      Double_t xx;
      Double_t mpc;
      Double_t fland;
      Double_t sum = 0.0;
      Double_t xlow,xupp;
      Double_t step;
      Double_t i;


      // MP shift correction
      mpc = par[1] - mpshift * par[0];

      // Range of convolution integral
      xlow = x[0] - sc * par[3];
      xupp = x[0] + sc * par[3];

      step = (xupp-xlow) / np;
      for(i=1.0; i<=np/2; i++) {
         xx = xlow + (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);

         xx = xupp - (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
      }

      return (par[2] * step * sum * invsq2pi / par[3]);
}

TF1 *langaufit(TH1F *his, Double_t *fitrange, Double_t *startvalues, Double_t *parlimitslo, Double_t *parlimitshi, Double_t *fitparams, Double_t *fiterrors, Double_t *ChiSqr, Int_t *NDF)
{
   // Once again, here are the Landau * Gaussian parameters:
   //   par[0]=Width (scale) parameter of Landau density
   //   par[1]=Most Probable (MP, location) parameter of Landau density
   //   par[2]=Total area (integral -inf to inf, normalization constant)
   //   par[3]=Width (sigma) of convoluted Gaussian function
   //
   // Variables for langaufit call:
   //   his             histogram to fit
   //   fitrange[2]     lo and hi boundaries of fit range
   //   startvalues[4]  reasonable start values for the fit
   //   parlimitslo[4]  lower parameter limits
   //   parlimitshi[4]  upper parameter limits
   //   fitparams[4]    returns the final fit parameters
   //   fiterrors[4]    returns the final fit errors
   //   ChiSqr          returns the chi square
   //   NDF             returns ndf

   Int_t i;
   Char_t FunName[100];

   sprintf(FunName,"Fitfcn_%s",his->GetName());

   TF1 *ffitold = (TF1*)gROOT->GetListOfFunctions()->FindObject(FunName);
   if (ffitold) delete ffitold;

   TF1 *ffit = new TF1(FunName,langaufun,fitrange[0],fitrange[1],4);
   ffit->SetParameters(startvalues);
   ffit->SetParNames("Width","MP","Area","GSigma");

   for (i=0; i<4; i++) {
      ffit->SetParLimits(i, parlimitslo[i], parlimitshi[i]);
   }

   his->Fit(FunName,"RB0");   // fit within specified range, use ParLimits, do not plot

   ffit->GetParameters(fitparams);    // obtain fit parameters
   for (i=0; i<4; i++) {
      fiterrors[i] = ffit->GetParError(i);     // obtain fit parameter errors
   }
   ChiSqr[0] = ffit->GetChisquare();  // obtain chi^2
   NDF[0] = ffit->GetNDF();           // obtain ndf

   return (ffit);              // return fit function

}


Int_t langaupro(Double_t *params, Double_t &maxx, Double_t &FWHM) {

   // Seaches for the location (x value) at the maximum of the
   // Landau-Gaussian convolute and its full width at half-maximum.
   //
   // The search is probably not very efficient, but it's a first try.

   Double_t p,x,fy,fxr,fxl;
   Double_t step;
   Double_t l,lold;
   Int_t i = 0;
   Int_t MAXCALLS = 10000;

   // Search for maximum
   p = params[1] - 0.1 * params[0];
   step = 0.05 * params[0];
   lold = -2.0;
   l    = -1.0;

   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;
      lold = l;
      x = p + step;
      l = langaufun(&x,params);
      if (l < lold)
         step = -step/10;
      p += step;
   }

   if (i == MAXCALLS)
      return (-1);
   maxx = x;
   fy = l/2;

   // Search for right x location of fy

   p = maxx + params[0];
   step = params[0];
   lold = -2.0;
   l    = -1e300;
   i    = 0;

   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;
      lold = l;
      x = p + step;
      l = TMath::Abs(langaufun(&x,params) - fy);
      if (l > lold)
         step = -step/10;
      p += step;
   }

   if (i == MAXCALLS)
      return (-2);
   fxr = x;

   // Search for left x location of fy
   p = maxx - 0.5 * params[0];
   step = -params[0];
   lold = -2.0;
   l    = -1e300;
   i    = 0;
   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;
      lold = l;
      x = p + step;
      l = TMath::Abs(langaufun(&x,params) - fy);
      if (l > lold)
         step = -step/10;
      p += step;
   }
   if (i == MAXCALLS)
      return (-3);

   fxl = x;
   FWHM = fxr - fxl;
   return (0);
}
















void dQdxFitter(){

  TFile *f = new TFile("AnaTreeLoopWireVariation.root");
  TCanvas *c1 = new TCanvas("c1","Tree test");
  TH1F *UWiredQdx = new TH1F("UWiredQdx","dQdx for U Plane; Wire; dQ/dx [ADC/cm]",2400,0,2400);
  UWiredQdx->SetMaximum(750);
  UWiredQdx->SetMarkerStyle(2);
  UWiredQdx->SetMarkerSize(0.5);
  TH1F *VWiredQdx = new TH1F("VWiredQdx","dQdx for V Plane; Wire; dQ/dx [ADC/cm]",2400,0,2400);
  VWiredQdx->SetMaximum(750);
  VWiredQdx->SetMarkerStyle(2);
  VWiredQdx->SetMarkerSize(0.5);
  TH1F *YWiredQdx = new TH1F("YWiredQdx","dQdx for Y Plane; Wire; dQ/dx [ADC/cm]",3456,0,3456);
  YWiredQdx->SetMaximum(750);
  YWiredQdx->SetMarkerStyle(2);
  YWiredQdx->SetMarkerSize(0.5);

  TH1F *UWiredQdxGainCorrected = new TH1F("UWiredQdxGainCorrected","Gain Corrected dQdx for U Plane; Wire; dQ/dx [ADC/cm]",2400,0,2400);
  UWiredQdxGainCorrected->SetMaximum(750);
  UWiredQdxGainCorrected->SetMarkerStyle(2);
  UWiredQdxGainCorrected->SetMarkerSize(0.5);
  TH1F *VWiredQdxGainCorrected  = new TH1F("VWiredQdxGainCorrected","Gain Corrected dQdx for V Plane; Wire; dQ/dx [ADC/cm]",2400,0,2400);
  VWiredQdxGainCorrected->SetMaximum(750);
  VWiredQdxGainCorrected->SetMarkerStyle(2);
  VWiredQdxGainCorrected->SetMarkerSize(0.5);
  TH1F *YWiredQdxGainCorrected = new TH1F("YWiredQdxGainCorrected","Gain Corrected dQdx for Y Plane; Wire; dQ/dx [ADC/cm]",3456,0,3456);
  YWiredQdxGainCorrected->SetMaximum(5000);
  YWiredQdxGainCorrected->SetMarkerStyle(2);
  YWiredQdxGainCorrected->SetMarkerSize(0.5);


  TH1F *UWiredQdxWidth  = new TH1F("UWiredQdxWidth","dQdx Width for U Plane; Wire; dQ/dx [ADC/cm]",2400,0,2400);
  UWiredQdxWidth->SetMaximum(200);
  UWiredQdxWidth->SetMarkerStyle(2);
  UWiredQdxWidth->SetMarkerSize(0.5);
  TH1F *VWiredQdxWidth  = new TH1F("VWiredQdxWidth","dQdx Width for V Plane; Wire; dQ/dx [ADC/cm]",2400,0,2400);
  VWiredQdxWidth->SetMaximum(200);
  VWiredQdxWidth->SetMarkerStyle(2);
  VWiredQdxWidth->SetMarkerSize(0.5);
  TH1F *YWiredQdxWidth = new TH1F("YWiredQdxWidth","dQdx Width for Y Plane; Wire; dQ/dx [ADC/cm]",3456,0,3456);
  YWiredQdxWidth->SetMaximum(200);
  YWiredQdxWidth->SetMarkerStyle(2);
  YWiredQdxWidth->SetMarkerSize(0.5);


  // Setup the histograms summing all of the dQ/dx distributions for all wires in each plane
  TH1F *hUPlanedQdxAllWires = new TH1F("hUPlanedQdxAllWires","dQdx for All Wires in U Plane;dQ/dx [ADC/cm];Hits",75,0,1000);
  hUPlanedQdxAllWires->Sumw2();
  TH1F *hVPlanedQdxAllWires = new TH1F("hVPlanedQdxAllWires","dQdx for All Wires in V Plane;dQ/dx [ADC/cm];Hits",75,0,1000);
  hVPlanedQdxAllWires->Sumw2();
  TH1F *hYPlanedQdxAllWires = new TH1F("hYPlanedQdxAllWires","dQdx for All Wires in Y Plane;dQ/dx [ADC/cm];Hits",75,0,2000);
  hYPlanedQdxAllWires->Sumw2();
  // std::map<Short_t, Float_t> channelTodQdxUPlane;
  // std::map<Short_t, Float_t> channelTodQdxVPlane;
  // std::map<Short_t, Float_t> channelTodQdxYPlane;
  std::map<Short_t, Float_t> channelTodQdx;

  gStyle->SetOptFit(1111);

  // Get gain histogram
  TFile *fGain = new TFile("20160204_PulserGain_Run3048.root");
  TH1F *hGainVsChan = (TH1F*)fGain->Get("hGainVsChan");


  // Setup TTree for storing the dQdx values
  TTree *WireVariationCalibTree= new TTree("WireVariationCalibTree","TTree storing MPV values for wire variation fits");
  Short_t fTTreePlane;
  Short_t fTTreeChannel;
  Short_t fTTreeWire;
  Double_t fTTreedQdxMPV;
  WireVariationCalibTree->Branch("Plane",&fTTreePlane,"Plane/S");
  WireVariationCalibTree->Branch("Channel",&fTTreeChannel,"Channel/S");
  WireVariationCalibTree->Branch("Wire",&fTTreeWire,"Wire/S");
  WireVariationCalibTree->Branch("dQdxMPV",&fTTreedQdxMPV,"dQdxMPV/D");


  // Create stopwatch for timing fits
  TStopwatch *stopwatch = new TStopwatch();
  double totalYFitTime = 0;
  double totalUFitTime = 0;
  double totalVFitTime = 0;
  double totalYFits = 0;
  double totalUFits = 0;
  double totalVFits = 0;




  // Do the U Plane
  for(int i=0; i < 2400; i++){
  // for(int i=1000; i < 1100; i++){
    stopwatch->Start();
    TH1F *hdQdx = (TH1F*)f->Get("hit_dqdx/u_plane/hUPlanedQdx_"+(TString)Form("%d",i));
    hUPlanedQdxAllWires->Add(hdQdx);

    // Get gain for this wire
    double fWireGain = hGainVsChan->GetBinContent(i);
    // Make sure we have a good number of entries before fitting
    if(hdQdx->GetEntries() < 100){
      UWiredQdx->SetBinContent(i+1,0);
      std::pair<std::map<Short_t, Float_t >::iterator,bool> ret;
      ret = channelTodQdx.insert(std::pair<Short_t, Float_t>(i,-999999));
      continue;
    }
    // Setting fit range and start values
    Double_t fr[2];
    Double_t sv[4], pllo[4], plhi[4], fp[4], fpe[4];
    // fr[0]=200; fr[1]=1000;
    fr[0]=0.6*1.0*hdQdx->GetMean(); fr[1]=1000;
    sv[0]=20;
    pllo[0]=10; plhi[0]=50;
    sv[1]=0.8*hdQdx->GetMean();
    pllo[1]=0.6*hdQdx->GetMean(); plhi[1]=1.0*hdQdx->GetMean(); 
    sv[2]=50000.0; 
    pllo[2]=1.0; plhi[2]=100000000.0; 
    sv[3]=100;
    pllo[3]=1; plhi[3]=200;
    Double_t chisqr;
    Int_t    ndf;
    TF1 *fitsnr = langaufit(hdQdx,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
    Double_t SNRPeak, SNRFWHM;
    langaupro(fp,SNRPeak,SNRFWHM);
    hdQdx->Draw();
    fitsnr->Draw("SAME");
    if(fp[1] > 0){
      UWiredQdx->SetBinContent(i+1,fp[1]);
      UWiredQdxGainCorrected->SetBinContent(i+1,fWireGain*fp[1]);
      UWiredQdxWidth->SetBinContent(i+1,fp[3]);
      // Insert channel and MPV into the channel to dQdx map
      std::pair<std::map<Short_t, Float_t >::iterator,bool> ret;
      ret = channelTodQdx.insert(std::pair<Short_t, Float_t>(i,fp[1]));
      // Fill TTree
      fTTreePlane = 0;
      fTTreeChannel = i;
      fTTreeWire = i;
      fTTreedQdxMPV = fp[1];
      WireVariationCalibTree->Fill();
    }
    c1->Print("hUPlanedQdx_"+(TString)Form("%d",i)+".png");
    stopwatch->Stop();
    stopwatch->Print();
    totalUFitTime += stopwatch->CpuTime();
    totalUFits++;
  }
  UWiredQdx->Draw("P");
  c1->Print("UPlanedQdx.png");
  c1->Print("UPlanedQdx.C");
  // UWiredQdxGainCorrected->Draw("P");
  // c1->Print("UPlanedQdxGainCorrected.png");
  // c1->Print("UPlanedQdxGainCorrected.C");
  UWiredQdxWidth->Draw("P");
  c1->Print("UPlanedQdxWidth.png");
  c1->Print("UPlanedQdxWidth.C");




  // Do the V Plane
  for(int i=0; i < 2400; i++){
  // for(int i=1000; i < 1100; i++){
    stopwatch->Start();
    TH1F *hdQdx = (TH1F*)f->Get("hit_dqdx/v_plane/hVPlanedQdx_"+(TString)Form("%d",i));
    hVPlanedQdxAllWires->Add(hdQdx);

    // Get gain for this wire
    double fWireGain = hGainVsChan->GetBinContent(2400+i);

    // Make sure we have a good number of entries before fitting
    if(hdQdx->GetEntries() < 100){
      VWiredQdx->SetBinContent(i+1,0);
      std::pair<std::map<Short_t, Float_t >::iterator,bool> ret;
      ret = channelTodQdx.insert(std::pair<Short_t, Float_t>(2400+i,-999999));
      continue;
    }
    // Setting fit range and start values
    Double_t fr[2];
    Double_t sv[4], pllo[4], plhi[4], fp[4], fpe[4];
    // fr[0]=0; fr[1]=1000;
    fr[0]=0.5*1.0*hdQdx->GetMean(); fr[1]=1000;
    sv[0]=20;
    pllo[0]=10; plhi[0]=50;
    sv[1]=0.8*hdQdx->GetMean();
    pllo[1]=0.6*hdQdx->GetMean(); plhi[1]=1.0*hdQdx->GetMean(); 
    sv[2]=50000.0; 
    pllo[2]=1.0; plhi[2]=100000000.0; 
    sv[3]=100;
    pllo[3]=1; plhi[3]=200;
    Double_t chisqr;
    Int_t    ndf;
    TF1 *fitsnr = langaufit(hdQdx,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
    Double_t SNRPeak, SNRFWHM;
    langaupro(fp,SNRPeak,SNRFWHM);
    hdQdx->Draw();
    fitsnr->Draw("SAME");
    if(fp[1] > 0){
      VWiredQdx->SetBinContent(i+1,fp[1]);
      VWiredQdxGainCorrected->SetBinContent(i+1,fWireGain*fp[1]);
      VWiredQdxWidth->SetBinContent(i+1,fp[3]);
      // Insert channel and MPV into the channel to dQdx map
      std::pair<std::map<Short_t, Float_t >::iterator,bool> ret;
      ret = channelTodQdx.insert(std::pair<Short_t, Float_t>(i+2400,fp[1]));
      // Fill TTree
      fTTreePlane = 0;
      fTTreeChannel = i;
      fTTreeWire = i;
      fTTreedQdxMPV = fp[1];
      WireVariationCalibTree->Fill();
    }
    c1->Print("hVPlanedQdx_"+(TString)Form("%d",i)+".png");
    stopwatch->Stop();
    stopwatch->Print();
    totalVFitTime += stopwatch->CpuTime();
    totalVFits++;
  }
  VWiredQdx->Draw("P");
  c1->Print("VPlanedQdx.png");
  c1->Print("VPlanedQdx.C");
  VWiredQdxGainCorrected->Draw("P");
  c1->Print("VPlanedQdxGainCorrected.png");
  c1->Print("VPlanedQdxGainCorrected.C");
  VWiredQdxWidth->Draw("P");
  c1->Print("VPlanedQdxWidth.png");
  c1->Print("VPlanedQdxWidth.C");

  
  // Do the Y Plane
  for(int i=0; i < 3456; i++){
  // for(int i=1000; i < 1010; i++){
    stopwatch->Start();
    TH1F *hdQdx = (TH1F*)f->Get("hit_dqdx/y_plane/hYPlanedQdx_"+(TString)Form("%d",i));
    hYPlanedQdxAllWires->Add(hdQdx);

    // Get gain for this wire
    double fWireGain = hGainVsChan->GetBinContent(2400+2400+i);

    // Make sure we have a good number of entries before fitting
    if(hdQdx->GetEntries() < 100){
      YWiredQdx->SetBinContent(i+1,0);
      std::pair<std::map<Short_t, Float_t >::iterator,bool> ret;
      ret = channelTodQdx.insert(std::pair<Short_t, Float_t>(2400+2400+i,-999999));
      continue;
    }
    // Setting fit range and start values
    Double_t fr[2];
    Double_t sv[4], pllo[4], plhi[4], fp[4], fpe[4];
    fr[0]=0.5*1.0*hdQdx->GetMean(); fr[1]=2000;
    sv[0]=30;
    pllo[0]=10; plhi[0]=50;
    sv[1]=0.8*hdQdx->GetMean();
    pllo[1]=0.6*hdQdx->GetMean(); plhi[1]=1.0*hdQdx->GetMean(); 
    sv[2]=50000.0; 
    pllo[2]=1.0; plhi[2]=100000000.0; 
    sv[3]=100;
    pllo[3]=1; plhi[3]=200;
    Double_t chisqr;
    Int_t    ndf;
    TF1 *fitsnr = langaufit(hdQdx,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
    Double_t SNRPeak, SNRFWHM;
    langaupro(fp,SNRPeak,SNRFWHM);
    hdQdx->Draw();
    fitsnr->Draw("SAME");
    if(fp[1] > 0){
      YWiredQdx->SetBinContent(i+1,fp[1]);
      YWiredQdxGainCorrected->SetBinContent(i+1,fWireGain*fp[1]);
      YWiredQdxWidth->SetBinContent(i+1,fp[3]);
      // Insert channel and MPV into the channel to dQdx map
      std::pair<std::map<Short_t, Float_t >::iterator,bool> ret;
      ret = channelTodQdx.insert(std::pair<Short_t, Float_t>(2400+2400+i,fp[1]));
      // Fill TTree
      fTTreePlane = 0;
      fTTreeChannel = i;
      fTTreeWire = i;
      fTTreedQdxMPV = fp[1];
      WireVariationCalibTree->Fill();
    }
    c1->Print("hYPlanedQdx_"+(TString)Form("%d",i)+".png");
    stopwatch->Stop();
    stopwatch->Print();
    totalYFitTime += stopwatch->CpuTime();
    totalYFits++;
  }
  YWiredQdx->Draw("P");
  c1->Print("YPlanedQdx.png");
  c1->Print("YPlanedQdx.C");
  YWiredQdxGainCorrected->Draw("P");
  c1->Print("YPlanedQdxGainCorrected.png");
  c1->Print("YPlanedQdxGainCorrected.C");
  YWiredQdxWidth->Draw("P");
  c1->Print("YPlanedQdxWidth.png");
  c1->Print("YPlanedQdxWidth.C");

  TFile fTTree("WireVariationCalibTree.root","recreate");
  WireVariationCalibTree->Write();
  fTTree.Close();

  if(totalYFits!= 0) std::cout << "Average time per Y wire fit: " << totalYFitTime/totalYFits << std::endl;
  if(totalUFits!= 0) std::cout << "Average time per U wire fit: " << totalUFitTime/totalUFits << std::endl;
  if(totalVFits!= 0) std::cout << "Average time per V wire fit: " << totalVFitTime/totalVFits << std::endl;




  //
  // Now fitting the entire dQ/dx distribution for all wires in each plane
  //

  // Setup the text file to write to
  ofstream dQdxCalibration;
  dQdxCalibration.open("dQdxCalibration.txt");

  // U Plane 
  // Setting fit range and start values
  // Double_t frUPlane[2];
  // Double_t svUPlane[4], plloUPlane[4], plhiUPlane[4], fpUPlane[4], fpeUPlane[4];
  // frUPlane[0]=0; frUPlane[1]=1000;
  // svUPlane[0]=30;
  // plloUPlane[0]=10; plhiUPlane[0]=50;
  // svUPlane[1]=0.8*hUPlanedQdxAllWires->GetMean();
  // plloUPlane[1]=0.6*hUPlanedQdxAllWires->GetMean(); plhiUPlane[1]=1.0*hUPlanedQdxAllWires->GetMean(); 
  // svUPlane[2]=50000.0; 
  // plloUPlane[2]=1.0; plhiUPlane[2]=1e10; 
  // svUPlane[3]=100;
  // plloUPlane[3]=1; plhiUPlane[3]=200;
  // Double_t chisqrUPlane;
  // Int_t    ndfUPlane;
  // TF1 *fitsnrUPlane = langaufit(hUPlanedQdxAllWires,frUPlane,svUPlane,plloUPlane,plhiUPlane,fpUPlane,fpeUPlane,&chisqrUPlane,&ndfUPlane);
  // Double_t SNRPeakUPlane, SNRFWHMUPlane;
  // langaupro(fpUPlane,SNRPeakUPlane,SNRFWHMUPlane);
  // hUPlanedQdxAllWires->Draw();
  // fitsnrUPlane->Draw("SAME");
  // c1->Print("UPlanedQdxAllWiresFit.png");
  // c1->Print("UPlanedQdxAllWiresFit.C");
  // // Determine the correction
  // for(auto channelTodQdxItr = channelTodQdxUPlane.begin(); 
  //     channelTodQdxItr != channelTodQdxUPlane.end();
  //     channelTodQdxItr++){
  //   if(channelTodQdxItr->second < 0){
  //     std::cout << "Channel: " << channelTodQdxItr->first 
  //       << " Channel dQ/dx: " << channelTodQdxItr->second
  //       << " Correction: " 
  //       << 1 
  //       << std::endl;
  //     dQdxCalibration << channelTodQdxItr->first << " " << 1 << std::endl;
  //     continue;
  //   }
  //   std::cout << "Channel: " << channelTodQdxItr->first 
  //     << " Channel dQ/dx: " << channelTodQdxItr->second
  //     << " Correction: " 
  //     << fpUPlane[1]/channelTodQdxItr->second 
  //     << std::endl;
  //     dQdxCalibration << channelTodQdxItr->first << " " << fpUPlane[1]/channelTodQdxItr->second << std::endl;
    
  // }

  
  
  // V Plane 
  // Setting fit range and start values
  // Double_t frVPlane[2];
  // Double_t svVPlane[4], plloVPlane[4], plhiVPlane[4], fpVPlane[4], fpeVPlane[4];
  // frVPlane[0]=0; frVPlane[1]=2000;
  // svVPlane[0]=30;
  // plloVPlane[0]=10; plhiVPlane[0]=50;
  // svVPlane[1]=0.8*hVPlanedQdxAllWires->GetMean();
  // plloVPlane[1]=0.6*hVPlanedQdxAllWires->GetMean(); plhiVPlane[1]=1.0*hVPlanedQdxAllWires->GetMean(); 
  // svVPlane[2]=50000.0; 
  // plloVPlane[2]=1.0; plhiVPlane[2]=1e10; 
  // svVPlane[3]=100;
  // plloVPlane[3]=1; plhiVPlane[3]=200;
  // Double_t chisqrVPlane;
  // Int_t    ndfVPlane;
  // TF1 *fitsnrVPlane = langaufit(hVPlanedQdxAllWires,frVPlane,svVPlane,plloVPlane,plhiVPlane,fpVPlane,fpeVPlane,&chisqrVPlane,&ndfVPlane);
  // Double_t SNRPeakVPlane, SNRFWHMVPlane;
  // langaupro(fpVPlane,SNRPeakVPlane,SNRFWHMVPlane);
  // hVPlanedQdxAllWires->Draw();
  // fitsnrVPlane->Draw("SAME");
  // c1->Print("VPlanedQdxAllWires.png");
  // c1->Print("VPlanedQdxAllWires.C");
  // // Determine the correction
  // for(auto channelTodQdxItr = channelTodQdxVPlane.begin(); 
  //     channelTodQdxItr != channelTodQdxVPlane.end();
  //     channelTodQdxItr++){
  //   if(channelTodQdxItr->second < 0){
  //     std::cout << "Channel: " << channelTodQdxItr->first 
  //       << " Channel dQ/dx: " << channelTodQdxItr->second
  //       << " Correction: " 
  //       << 1 
  //       << std::endl;
  //     dQdxCalibration << channelTodQdxItr->first << " " << 1 << std::endl;
  //     continue;
  //   }
  //   std::cout << "Channel: " << channelTodQdxItr->first 
  //     << " Channel dQ/dx: " << channelTodQdxItr->second
  //     << " Correction: " 
  //     << fpVPlane[1]/channelTodQdxItr->second 
  //     << std::endl;
  //     dQdxCalibration << channelTodQdxItr->first << " " << fpVPlane[1]/channelTodQdxItr->second << std::endl;
  // }




  // Y Plane 
  // Setting fit range and start values
  // Double_t frYPlane[2];
  // Double_t svYPlane[4], plloYPlane[4], plhiYPlane[4], fpYPlane[4], fpeYPlane[4];
  // frYPlane[0]=250; frYPlane[1]=2000;
  // svYPlane[0]=30;
  // plloYPlane[0]=10; plhiYPlane[0]=50;
  // svYPlane[1]=0.8*hYPlanedQdxAllWires->GetMean();
  // plloYPlane[1]=0.6*hYPlanedQdxAllWires->GetMean(); plhiYPlane[1]=1.0*hYPlanedQdxAllWires->GetMean(); 
  // svYPlane[2]=50000.0; 
  // plloYPlane[2]=1.0; plhiYPlane[2]=1e10; 
  // svYPlane[3]=100;
  // plloYPlane[3]=1; plhiYPlane[3]=200;
  // Double_t chisqrYPlane;
  // Int_t    ndfYPlane;
  // TF1 *fitsnrYPlane = langaufit(hYPlanedQdxAllWires,frYPlane,svYPlane,plloYPlane,plhiYPlane,fpYPlane,fpeYPlane,&chisqrYPlane,&ndfYPlane);
  // Double_t SNRPeakYPlane, SNRFWHMYPlane;
  // langaupro(fpYPlane,SNRPeakYPlane,SNRFWHMYPlane);
  // hYPlanedQdxAllWires->Draw();
  // fitsnrYPlane->Draw("SAME");
  // c1->Print("YPlanedQdxAllWires.png");
  // c1->Print("YPlanedQdxAllWires.C");
  // // Determine the correction
  // for(auto channelTodQdxItr = channelTodQdxYPlane.begin(); 
  //     channelTodQdxItr != channelTodQdxYPlane.end();
  //     channelTodQdxItr++){
  //   if(channelTodQdxItr->second < 0){
  //     std::cout << "Channel: " << channelTodQdxItr->first 
  //       << " Channel dQ/dx: " << channelTodQdxItr->second
  //       << " Correction: " 
  //       << 1 
  //       << std::endl;
  //     dQdxCalibration << channelTodQdxItr->first << " " << 1 << std::endl;
  //     continue;
  //   }
  //   std::cout << "Channel: " << channelTodQdxItr->first 
  //     << " Channel dQ/dx: " << channelTodQdxItr->second
  //     << " Correction: " 
  //     << fpYPlane[1]/channelTodQdxItr->second 
  //     << std::endl;
  //     dQdxCalibration << channelTodQdxItr->first << " " << fpYPlane[1]/channelTodQdxItr->second << std::endl;
  // }








  // Average the MPVs for all planes
  // For the array, elements 0, 1, 2 are for U, V, Y planes respectively
  Double_t meanMPVForPlane[3] = {0};
  Int_t nMPVForPlane[3] = {0};
  for(auto channelTodQdxItr = channelTodQdx.begin(); 
      channelTodQdxItr != channelTodQdx.end();
      channelTodQdxItr++){
    if(channelTodQdxItr->second < 0){
      continue;
    }
    meanMPVForPlane[ChannelToPlane(channelTodQdxItr->first)]+=channelTodQdxItr->second;
    nMPVForPlane[ChannelToPlane(channelTodQdxItr->first)]++;
  }
  if(nMPVForPlane[0]!=0) meanMPVForPlane[0]/=nMPVForPlane[0];
  if(nMPVForPlane[1]!=0) meanMPVForPlane[1]/=nMPVForPlane[1];
  if(nMPVForPlane[2]!=0) meanMPVForPlane[2]/=nMPVForPlane[2];


  for(auto channelTodQdxItr = channelTodQdx.begin(); 
      channelTodQdxItr != channelTodQdx.end();
      channelTodQdxItr++){
    if(channelTodQdxItr->second < 0){
      std::cout << "Channel: " << channelTodQdxItr->first 
        << " Channel dQ/dx: " << channelTodQdxItr->second
        << " Correction: " 
        << 1 
        << std::endl;
      dQdxCalibration << channelTodQdxItr->first << " " << 1 << std::endl;
      continue;
    }
    std::cout << "Channel: " << channelTodQdxItr->first 
      << " Channel dQ/dx: " << channelTodQdxItr->second
      << " Correction: " 
      <<  meanMPVForPlane[ChannelToPlane(channelTodQdxItr->first)]/channelTodQdxItr->second
      << std::endl;
      dQdxCalibration << channelTodQdxItr->first << " " << meanMPVForPlane[ChannelToPlane(channelTodQdxItr->first)]/channelTodQdxItr->second << std::endl;
  }


  dQdxCalibration.close();

}






