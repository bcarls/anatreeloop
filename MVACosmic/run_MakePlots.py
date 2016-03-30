
import ROOT
import sys
import time

import matplotlib
import math
matplotlib.rc('text', usetex=True)
matplotlib.rcParams['text.latex.preamble'] = [
       r'\usepackage{siunitx}',   # i need upright \micro symbols, but you need...
       r'\sisetup{detect-all}',   # ...this to force siunitx to actually use your fonts
       r'\usepackage{helvet}',    # set the normal font here
       r'\usepackage{sansmath}',  # load up the sansmath so that math -> helvet
       r'\sansmath'               # <- tricky! -- gotta actually tell tex to use!
] 
# matplotlib.rc('font', family="serif", serif="palatino")
from rootplot import root2matplotlib as r2m
from matplotlib import pyplot as plt
import pickle


# Turn on batch mode
# sys.argv.append( '-b-' )

def main(argv):

    ROOT.gROOT.SetBatch()
    ROOT.gStyle.SetOptStat(False)

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

    if inputFile == '':
        print 'No input file specified. Use "-s" to specify one.'
        return 0

    f = ROOT.TFile(inputFile) 


    # Plot cosmic retention efficiencies as a function of length
    cTrackOriginEfficiency = ROOT.TCanvas("cTrackOrginEfficiency")

    hTrackOriginNoCosRem = f.Get("hTrackOriginNoCosRem")
    hTrackOriginTMVA = f.Get("hTrackOriginTMVA")
    hTrackOriginGT = f.Get("hTrackOriginGT")

    hTrackOriginNoCosRem.SetStats(False)
    hTrackOriginTMVA.SetStats(False)
    hTrackOriginGT.SetStats(False)

    # hTrackOriginNoCosRem.Sumw2()
    # hTrackOriginFM.Sumw2()
    # hTrackOriginGT.Sumw2()
    # hTrackOriginTMVA.Sumw2()

    hTrackOriginTMVA.Divide(hTrackOriginTMVA,hTrackOriginNoCosRem,1.0,1.0,"B")
    hTrackOriginGT.Divide(hTrackOriginGT,hTrackOriginNoCosRem,1.0,1.0,"B")

    hTrackOriginTMVA.SetMaximum(1.0)
    hTrackOriginTMVA.SetLineColor(6)
    hTrackOriginTMVA.SetTitle("Efficiency after cosmic removal for true tracks")
    hTrackOriginTMVA.GetYaxis().SetTitle("Efficiency")
    hTrackOriginTMVA.GetXaxis().SetTitle("Origin")
    hTrackOriginTMVA.SetLineWidth(3)

    hTrackOriginGT.SetLineColor(2)
    hTrackOriginGT.SetLineWidth(3)

    hTrackOriginTMVA.Draw()
    hTrackOriginGT.Draw("SAME")
  
    lgTrackOriginEfficiency = ROOT.TLegend(0.1,0.6,0.4,0.9)
    lgTrackOriginEfficiency.AddEntry(hTrackOriginTMVA,"TMVA and GT","l")
    lgTrackOriginEfficiency.AddEntry(hTrackOriginGT,"GT","l")
    lgTrackOriginEfficiency.SetBorderSize(0)
    lgTrackOriginEfficiency.Draw()


    # Now use matplotlib to make the efficiency plot
    plt.figure()
    ax1 = plt.axes()

    hTrackOriginTMVAR2M= r2m.Hist(hTrackOriginTMVA)
    hTrackOriginGTR2M= r2m.Hist(hTrackOriginGT)
    stack = r2m.HistStack()
    stack.add(hTrackOriginTMVAR2M, label="TMVA and GT")
    stack.add(hTrackOriginGTR2M, label="GT Only")
    hTrackOriginTMVAR2M.hist(histtype='step', color='b',normed=False,linewidth=2)
    hTrackOriginGTR2M.hist(histtype='step', color='r',normed=False,linewidth=2)
    stack.show_titles()
    plt.title("Efficiencies")
    plt.xlabel("Origin")
    plt.ylabel(r'Efficiency')
    plt.margins(y=0.05)
    plt.ylim(ymin=0,ymax=1.0)
    plt.legend(loc='upper right')
    plt.savefig('demo_plots/TrackOriginEfficiency.png')


    # Save everything
    hf = ROOT.TFile ("MakePlots.root","recreate")
    cTrackOriginEfficiency.Write()
    hf.Close()

if __name__ == '__main__':
    sys.exit(main(sys.argv))



