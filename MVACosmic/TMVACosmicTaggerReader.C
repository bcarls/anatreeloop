{
    // Create a TMVA reader
    TMVA::Reader reader("Color=True");
    
    
    // Register input variables. Their names and order must be same in training
    Float_t trackPerpDistXBound, log_trackPerpDistYBound, log_trackPerpDistZBound, trackPerpDistToABound, log_trackPIDA, trackPIDA, log_trackKE, log_trackRange, trackRange, trackThetaXZ, trackThetaYZ, trackNearestDistUntaggedToTaggedCosGT, trackNearestDistUntaggedToTaggedCosGTFM;

   reader.AddVariable( "trackPerpDistToABound", &trackPerpDistToABound);
   reader.AddVariable( "trackPIDA", &trackPIDA);
   reader.AddVariable( "log(trackRange)", &log_trackRange);
   reader.AddVariable( "trackThetaYZ", &trackThetaYZ);
   reader.AddVariable( "trackNearestDistUntaggedToTaggedCosGT", &trackNearestDistUntaggedToTaggedCosGT);
   

    
    // Book the neural network with backpropagation
    // reader.BookMVA("TMVAClassification_MLP", "weights/TMVAClassification_MLP.weights.xml");
    reader.BookMVA("TMVAClassification_BDT", "weights/TMVAClassification_BDT.weights.xml");
    
    
    // A histogram to be filled
    TH1D sgnResponseHist("sgnResponseHist", "NN response in signal events", 20, 0., 1.);
    sgnResponseHist.Sumw2();
    TH1F hTrackOriginNoCosRem("hTrackOriginNoCosRem","Origin for tracks before cosmic removal; Origin; Tracks", 3, 0, 3);
    TH1F hTrackOriginTMVA("hTrackOriginTMVA","Origin for tracks not removed by TMVA cut; Origin; Tracks", 3, 0, 3);
    TH1F hTrackOriginGT("hTrackOriginGT","Origin for tracks not removed by GT cut; Origin; Tracks", 3, 0, 3);
    TH1F hTrackOriginGTFM("hTrackOriginGTFM","Origin for tracks not removed by GT and FM cut; Origin; Tracks", 3, 0, 3);
    hTrackOriginNoCosRem.GetXaxis()->SetBinLabel(1,"Unknown");
    hTrackOriginNoCosRem.GetXaxis()->SetBinLabel(2,"Neutrino");
    hTrackOriginNoCosRem.GetXaxis()->SetBinLabel(3,"Cosmic");
    hTrackOriginTMVA.GetXaxis()->SetBinLabel(1,"Unknown");
    hTrackOriginTMVA.GetXaxis()->SetBinLabel(2,"Neutrino");
    hTrackOriginTMVA.GetXaxis()->SetBinLabel(3,"Cosmic");
    hTrackOriginGT.GetXaxis()->SetBinLabel(1,"Unknown");
    hTrackOriginGT.GetXaxis()->SetBinLabel(2,"Neutrino");
    hTrackOriginGT.GetXaxis()->SetBinLabel(3,"Cosmic");
    hTrackOriginGTFM.GetXaxis()->SetBinLabel(1,"Unknown");
    hTrackOriginGTFM.GetXaxis()->SetBinLabel(2,"Neutrino");
    hTrackOriginGTFM.GetXaxis()->SetBinLabel(3,"Cosmic");
    
    
    // Open the source file and get the tree
    TFile srcFile("../ToRead.root");
    TTree *srcTree = (TTree *) srcFile.Get("tAll");
    unsigned long const nEntries = srcTree->GetEntries();
    
    
    // Set branch addresses to read the tree
    Float_t trackPerpDistYBound, trackPerpDistZBound, trackKE;
    Float_t weight;
    Int_t trackOrigin, trackTaggedCosGT, trackTaggedCosGTFM;

    srcTree->SetBranchAddress("trackPerpDistXBound", &trackPerpDistXBound);
    srcTree->SetBranchAddress("trackPerpDistYBound", &trackPerpDistYBound);
    srcTree->SetBranchAddress("trackPerpDistZBound", &trackPerpDistZBound);
    srcTree->SetBranchAddress("trackPerpDistToABound", &trackPerpDistToABound);
    srcTree->SetBranchAddress("trackPIDA", &trackPIDA);
    srcTree->SetBranchAddress("trackKE", &trackKE);
    srcTree->SetBranchAddress("trackRange", &trackRange);
    srcTree->SetBranchAddress("trackThetaXZ", &trackThetaXZ);
    srcTree->SetBranchAddress("trackThetaYZ", &trackThetaYZ);
    srcTree->SetBranchAddress("trackOrigin", &trackOrigin);
    srcTree->SetBranchAddress("trackTaggedCosGT", &trackTaggedCosGT);
    srcTree->SetBranchAddress("trackTaggedCosGTFM", &trackTaggedCosGTFM);
    srcTree->SetBranchAddress("weight", &weight);

    
    // Loop over the tree
    for (unsigned long ev = 0; ev < nEntries; ++ev)
    {
        srcTree->GetEntry(ev);
       
        if(trackKE < 0)
            continue;
        
        // Calculate the few input variables that require some transformation
        log_trackPerpDistYBound = log(trackPerpDistYBound);
        log_trackPerpDistZBound = log(trackPerpDistZBound);
        log_trackKE = log(trackKE);
        log_trackPIDA = log(trackPIDA);
        log_trackRange = log(trackRange);
        
        // Calculate response of the neural network for the current event
        // double const response = reader.EvaluateMVA("TMVAClassification_MLP");
        double response = reader.EvaluateMVA("TMVAClassification_BDT");

        hTrackOriginNoCosRem.Fill(trackOrigin);

        // Did this survive the TMVA and GT cosmic ray cut?
        if(response > 0.05 && trackTaggedCosGT != 1)
          hTrackOriginTMVA.Fill(trackOrigin);

        // Did this survive the GT cosmic ray cut?
        if(trackTaggedCosGT != 1)
          hTrackOriginGT.Fill(trackOrigin);

        // Did this survive the TMVA and GT and FM cosmic ray cut?
        // if(response > 0.05 and trackTaggedCosGTFM != 1)
        //   hTrackOriginTMVA.Fill(trackOrigin);

        // Did this survive the GT and FM cosmic ray cut?
        if(trackTaggedCosGTFM != 1)
          hTrackOriginGTFM.Fill(trackOrigin);


        // Fill the histogram
        sgnResponseHist.Fill(response, weight);
    }
    
    
    // Create a canvas and adjust decoration
    // TCanvas canvas;
    // gStyle->SetOptStat(0);
    // sgnResponseHist.SetMarkerStyle(20);
    // sgnResponseHist.SetLineColor(kBlack);
    
    // Draw the histogram and save the figure
    // sgnResponseHist.Draw("p0 e1");
    // canvas.Print("sgnResponse.png");

    TFile f("histograms.root","recreate");
    hTrackOriginNoCosRem.Write();
    hTrackOriginTMVA.Write();
    hTrackOriginGT.Write();
    hTrackOriginGTFM.Write();
    sgnResponseHist.Write();
    f.Close();
}
