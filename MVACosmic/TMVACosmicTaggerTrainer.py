import ROOT
import MVAPlotter

# Set the file that will store the output
outputFile = ROOT.TFile.Open( "TMVA.root", "RECREATE" );

# Create the factory object, the TMVA class powering the MVA analysis
factory = ROOT.TMVA.Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" )

# Here we add variables
factory.AddVariable( "trackPerpDistToABound", "trackPerpDistToABound", "cm", 'F' )
factory.AddVariable( "trackPIDA", "trackPIDA", "stuff", 'F' )
factory.AddVariable( "log(trackRange)", "log(trackRange)", "", 'F' )
factory.AddVariable( "trackThetaYZ", "trackThetaYZ", "radians", 'F' )
factory.AddVariable( "trackNearestDistUntaggedToTaggedCosGT", "trackNearestDistUntaggedToTaggedCosGT", "cm", 'F' )

# We open up the training samples
inputBackground = ROOT.TFile.Open("../Cosmic_Background.root")
inputSignal = ROOT.TFile.Open("../Neutrino_Signal.root")
signal     = inputSignal.Get("tTrueNuGT")
background = inputBackground.Get("tTrueCosGT")

# Add the training samples to the factor object
factory.AddSignalTree(signal)
factory.AddBackgroundTree(background)

# If we choose, we could supplied cuts, I don't here
mycuts = ROOT.TCut("")
mycutb = ROOT.TCut("")

# We prepare the factory, giving it cuts and the number of training samples to use
factory.PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=1000:nTrain_Background=7000:SplitMode=Random:NormMode=NumEvents:!V" )

# Tell the factory object which technique to use, here I've chosen a boosted decision tree
factory.BookMethod( ROOT.TMVA.Types.kBDT, "BDT", "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" )

# Finally, we train our decision tree
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()

# Call the plotting script
MVAPlotter.Plot(outputFile)

# Save the output file, we can use macros to read it
outputFile.Close();



