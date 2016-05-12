
import ROOT
import sys

def main(argv):

    ROOT.gSystem.Load("build/AnaTreeLoop/libAnaTreeLoop")

    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeTracks.cxx");
    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeHits.cxx");
    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeRunInfo.cxx");
    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeFlash.cxx");
    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeVertex.cxx");
    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeTruth.cxx");
    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeAlgs.cxx");
    # ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeLoopEventDisplay.cxx");


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

    # ROOT.gROOT.SetBatch(False)
    t = ROOT.AnaTreeLoopEventDisplay(c)

    t.SetNEvents(nevts)
    t.SetNEventsToReport(1000)
    t.SetTrackModule("trackkalmanhit")
    # t.SetTrackModule("trackkalmanhitcc")
    # t.SetTrackModule("pandoraCosmicKHit")
    # t.SetVertexModule("pandoraCosmic")

    t.SetWindowOffset(1600)

    t.SetOutputFile("AnaTreeLoopWireVariation.root")
    t.Loop()



if __name__ == '__main__':
    sys.exit(main(sys.argv))












