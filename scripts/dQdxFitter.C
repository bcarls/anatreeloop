

#include "root/TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"

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
      Double_t np = 5000.0;      // number of convolution steps
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


void dQdxFitter(){

  TFile *f = new TFile("AnaTreeLoopWireVariation.root");
  TCanvas *c1 = new TCanvas("c1","Tree test");
  TH1F *YWiredQdx = new TH1F("YWiredQdx","dQdx for Y Plane",3456,0,3456);
  YWiredQdx->SetMaximum(500);
  YWiredQdx->SetMarkerStyle(2);
  YWiredQdx->SetMarkerSize(0.5);
  TH1F *UWiredQdx = new TH1F("UWiredQdx","dQdx for U Plane",2400,0,2400);
  UWiredQdx->SetMaximum(300);
  UWiredQdx->SetMarkerStyle(2);
  UWiredQdx->SetMarkerSize(0.5);
  TH1F *VWiredQdx = new TH1F("VWiredQdx","dQdx for V Plane",2400,0,2400);
  VWiredQdx->SetMarkerStyle(2);
  VWiredQdx->SetMarkerSize(0.5);
  VWiredQdx->SetMaximum(300);
  
  TH1F *YWiredQdxWidth = new TH1F("YWiredQdxWidth","dQdx Width for Y Plane",3456,0,3456);
  YWiredQdxWidth->SetMarkerStyle(2);
  YWiredQdxWidth->SetMarkerSize(0.5);
  YWiredQdxWidth->SetMaximum(200);
  TH1F *UWiredQdxWidth  = new TH1F("UWiredQdxWidth","dQdx Width for U Plane",2400,0,2400);
  UWiredQdxWidth->SetMaximum(200);
  UWiredQdxWidth->SetMarkerStyle(2);
  UWiredQdxWidth->SetMarkerSize(0.5);
  TH1F *VWiredQdxWidth  = new TH1F("VWiredQdxWidth","dQdx Width for V Plane",2400,0,2400);
  VWiredQdxWidth->SetMaximum(200);
  VWiredQdxWidth->SetMarkerStyle(2);
  VWiredQdxWidth->SetMarkerSize(0.5);

  gStyle->SetOptFit(1111);
  
  // Do the Y Plane
  for(int i=0; i < 3456; i++){
  // for(int i=1000; i < 1010; i++){
    TH1F *hdQdx = (TH1F*)f->Get("hit_dqdx/y_plane/hYPlanedQdx_"+(TString)Form("%d",i));

    // Make sure we have a good number of entries before fitting
    if(hdQdx->GetEntries() < 100){
      YWiredQdx->SetBinContent(i+1,0);
      continue;
    }
    TF1 *landaugaus = new TF1("func",langaufun,0,3000,4);
    landaugaus->SetParameter(0,20);
    landaugaus->SetParLimits(0,1,1e2);
    landaugaus->SetParameter(1,hdQdx->GetMean());
    landaugaus->SetParLimits(1,100,1e3);
    // landaugaus->SetParameter(2,20000);
    landaugaus->SetParameter(2,7000);
    // landaugaus->SetParameter(3,hdQdx->GetRMS());
    landaugaus->SetParameter(3,100);
    landaugaus->SetParLimits(3,10,200);
    hdQdx->Draw();
    hdQdx->Fit(landaugaus,"R");
    landaugaus->Draw("SAME");
    // if(landaugaus->GetParameter(1) > 0 && 
    //     landaugaus->GetProb() > 0.01)
    if(landaugaus->GetParameter(1) > 0){
      YWiredQdx->SetBinContent(i+1,landaugaus->GetParameter(1));
      YWiredQdxWidth->SetBinContent(i+1,landaugaus->GetParameter(3));
    }
    c1->Print("hYPlanedQdx_"+(TString)Form("%d",i)+".png");
  }

  YWiredQdx->Draw("P");
  c1->Print("YPlanedQdx.png");
  c1->Print("YPlanedQdx.C");
  YWiredQdxWidth->Draw("P");
  c1->Print("YPlanedQdxWidth.png");
  c1->Print("YPlanedQdxWidth.C");



  // Do the U Plane
  for(int i=0; i < 2400; i++){
  // for(int i=1000; i < 1010; i++){
    TH1F *hdQdx = (TH1F*)f->Get("hit_dqdx/u_plane/hUPlanedQdx_"+(TString)Form("%d",i));
    
    // Make sure we have a good number of entries before fitting
    if(hdQdx->GetEntries() < 100){
      UWiredQdx->SetBinContent(i+1,0);
      continue;
    }
    TF1 *landaugaus = new TF1("func",langaufun,0,3000,4);
    landaugaus->SetParameter(0,20);
    landaugaus->SetParLimits(0,1,1e2);
    landaugaus->SetParameter(1,hdQdx->GetMean());
    landaugaus->SetParLimits(1,10,1e3);
    landaugaus->SetParameter(2,20000);
    // landaugaus->SetParameter(3,hdQdx->GetRMS());
    landaugaus->SetParameter(3,100);
    landaugaus->SetParLimits(3,10,200);
    hdQdx->Draw();
    hdQdx->Fit(landaugaus,"R");
    landaugaus->Draw("SAME");
    // if(landaugaus->GetParameter(1) > 0 && 
    //     landaugaus->GetProb() > 0.01)
    if(landaugaus->GetParameter(1) > 0){
      UWiredQdx->SetBinContent(i+1,landaugaus->GetParameter(1));
      UWiredQdxWidth->SetBinContent(i+1,landaugaus->GetParameter(3));
    }
    c1->Print("hUPlanedQdx_"+(TString)Form("%d",i)+".png");
  }

  UWiredQdx->Draw("P");
  c1->Print("UPlanedQdx.png");
  c1->Print("UPlanedQdx.C");
  UWiredQdxWidth->Draw("P");
  c1->Print("UPlanedQdxWidth.png");
  c1->Print("UPlanedQdxWidth.C");



  // Do the V Plane
  for(int i=0; i < 2400; i++){
  // for(int i=1000; i < 1010; i++){
    TH1F *hdQdx = (TH1F*)f->Get("hit_dqdx/v_plane/hVPlanedQdx_"+(TString)Form("%d",i));
    
    // Make sure we have a good number of entries before fitting
    if(hdQdx->GetEntries() < 100){
      VWiredQdx->SetBinContent(i+1,0);
      continue;
    }
    TF1 *landaugaus = new TF1("func",langaufun,0,3000,4);
    landaugaus->SetParameter(0,20);
    landaugaus->SetParLimits(0,1,1e2);
    landaugaus->SetParameter(1,hdQdx->GetMean());
    landaugaus->SetParLimits(1,10,1e3);
    landaugaus->SetParameter(2,20000);
    // landaugaus->SetParameter(3,hdQdx->GetRMS());
    landaugaus->SetParameter(3,100);
    landaugaus->SetParLimits(3,10,200);
    hdQdx->Draw();
    hdQdx->Fit(landaugaus,"R");
    landaugaus->Draw("SAME");
    // if(landaugaus->GetParameter(1) > 0 && 
    //     landaugaus->GetProb() > 0.01)
    if(landaugaus->GetParameter(1) > 0){
      VWiredQdx->SetBinContent(i+1,landaugaus->GetParameter(1));
      VWiredQdxWidth->SetBinContent(i+1,landaugaus->GetParameter(3));
    }
    c1->Print("hVPlanedQdx_"+(TString)Form("%d",i)+".png");
  }

  VWiredQdx->Draw("P");
  c1->Print("VPlanedQdx.png");
  c1->Print("VPlanedQdx.C");
  VWiredQdxWidth->Draw("P");
  c1->Print("VPlanedQdxWidth.png");
  c1->Print("VPlanedQdxWidth.C");

}






