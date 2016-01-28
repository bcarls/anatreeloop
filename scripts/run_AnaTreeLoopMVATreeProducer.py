
import ROOT
import sys



def main(argv):

    ROOT.gROOT.ProcessLine(".L AnaTreeTracks.cxx");
    ROOT.gROOT.ProcessLine(".L AnaTreeVertex.cxx");
    ROOT.gROOT.ProcessLine(".L AnaTreeTruth.cxx");
    ROOT.gROOT.ProcessLine(".L AnaTreeAlgs.cxx");
    ROOT.gROOT.ProcessLine(".L AnaTreeLoopMVATreeProducer.cxx");

    inputFile = ''
    inputFileList = ''
    nevts = 0
    # Parse arguments
    args = argv[1:]
    while len(args) > 0:
        if args[0] == '-s' or args[0] == '--source' :
            if len(args) > 1:
                inputFile = args[1]
                del args[0:2]
        elif args[0] == '-S' or args[0] == '--source-list' :
            if len(args) > 1:
                inputFileList = args[1]
                del args[0:2]
        elif args[0] == '-n' or args[0] == '--nevts' :
            if len(args) > 1:
                nevts = int(args[1])
                del args[0:2]

    if inputFile == '' and inputFileList == '':
        print 'No input file(s) specified. Use "-s" or "--source" to specify one. Additionally, a file list can be supplied with "-S" or "--source-list".'
        return 0
   


    # Read in file(s) and create the TChain c
    inputFiles = []
    c = ROOT.TChain("analysistree/anatree") 
    if inputFile != '':
        inputFiles.append(inputFile)
    elif inputFileList != '':
        inputFiles = open(inputFileList).read().splitlines()

    for f in inputFiles:
        print 'Adding input file: '+f+'.'
        c.Add(f)

    t = ROOT.AnaTreeLoopMVATreeProducer(c)

    t.SetNEvents(nevts)
    t.SetNEventsToReport(1000)
    t.SetTrackModule("trackkalmanhit")
    # t.SetTrackModule("pandoraCosmicKHit")

    t.SetOutputFile("AnaTreeLoopMVATreeProducer.root")
    # t.SetOutputTreeFile("Neutrino_Signal.root")
    t.SetOutputTreeFile("Cosmic_Background.root")
    t.Loop()


if __name__ == '__main__':
    sys.exit(main(sys.argv))



