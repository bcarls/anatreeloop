
import matplotlib
import ROOT
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
import sys



# Interface if called as standalone

def main(argv):

    # f = ROOT.TFile("TMVA.root") 
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
    Plot(f)


# Function that plots MVA stuff

def Plot(f):

    # Plot PIDA
    
    htrackPIDA_Signal = f.Get("InputVariables_Id/trackPIDA__Signal_Id")
    htrackPIDA_Background = f.Get("InputVariables_Id/trackPIDA__Background_Id")
    
    plt.figure()
    ax1 = plt.axes()
    htrackPIDA_SignalR2M = r2m.Hist(htrackPIDA_Signal)
    htrackPIDA_BackgroundR2M = r2m.Hist(htrackPIDA_Background)
    stack = r2m.HistStack()
    stack.add(htrackPIDA_SignalR2M, label="Signal, Neutrino")
    stack.add(htrackPIDA_BackgroundR2M, label="Background, Cosmic")
    htrackPIDA_SignalR2M.hist(histtype='stepfilled', color='b',normed=True,linewidth=1, alpha=0.5)
    htrackPIDA_BackgroundR2M.hist(histtype='stepfilled', color='r',normed=True,linewidth=1, alpha=0.5)
    stack.show_titles()
    plt.title("PIDA")
    plt.xlabel(r"PIDA [MeV/cm$^{1.42}$]")
    plt.ylabel(r'$dN_{}/^{}2.22$ MeV/cm$^{1.42}$')
    plt.margins(y=0.05)
    plt.ylim(ymin=0)
    plt.legend(loc='upper right')
    plt.savefig('demo_plots/trackPIDA.png')
  
  
  
  
  
  
    # Plot closest distance to a boundary
    
    htrackPerpDistToABound_Signal = f.Get("InputVariables_Id/trackPerpDistToABound__Signal_Id")
    htrackPerpDistToABound_Background = f.Get("InputVariables_Id/trackPerpDistToABound__Background_Id")
    
    plt.figure()
    ax1 = plt.axes()
    htrackPerpDistToABound_SignalR2M = r2m.Hist(htrackPerpDistToABound_Signal)
    htrackPerpDistToABound_BackgroundR2M = r2m.Hist(htrackPerpDistToABound_Background)
    stack = r2m.HistStack()
    stack.add(htrackPerpDistToABound_SignalR2M, label="Signal, Neutrino")
    stack.add(htrackPerpDistToABound_BackgroundR2M, label="Background, Cosmic")
    htrackPerpDistToABound_SignalR2M.hist(histtype='stepfilled', color='b',normed=True,linewidth=1, alpha=0.5)
    htrackPerpDistToABound_BackgroundR2M.hist(histtype='stepfilled', color='r',normed=True,linewidth=1, alpha=0.5)
    stack.show_titles()
    plt.title("Closest Distance to a Boundary")
    plt.xlabel(r"Dist [cm]")
    plt.ylabel(r'$dN_{}/^{}2.95$ cm')
    plt.margins(y=0.05)
    plt.ylim(ymin=0)
    plt.legend(loc='upper right')
    plt.savefig('demo_plots/trackPerpDistToABound.png')
    
    
    
    
    
    
    
    # Plot track range
    
    hlog_trackRange_Signal = f.Get("InputVariables_Id/log_trackRange___Signal_Id")
    hlog_trackRange_Background = f.Get("InputVariables_Id/log_trackRange___Background_Id")
    
    plt.figure()
    ax1 = plt.axes()
    hlog_trackRange_SignalR2M = r2m.Hist(hlog_trackRange_Signal)
    hlog_trackRange_BackgroundR2M = r2m.Hist(hlog_trackRange_Background)
    stack = r2m.HistStack()
    stack.add(hlog_trackRange_SignalR2M, label="Signal, Neutrino")
    stack.add(hlog_trackRange_BackgroundR2M, label="Background, Cosmic")
    hlog_trackRange_SignalR2M.hist(histtype='stepfilled', color='b',normed=True,linewidth=1, alpha=0.5)
    hlog_trackRange_BackgroundR2M.hist(histtype='stepfilled', color='r',normed=True,linewidth=1, alpha=0.5)
    stack.show_titles()
    plt.title("log(track range)")
    plt.xlabel(r"log(track range)")
    plt.ylabel(r'$dN_{}/^{}0.384$')
    plt.margins(y=0.05)
    plt.ylim(ymin=0)
    plt.legend(loc='upper right')
    plt.savefig('demo_plots/log_trackRange.png')
    
    
    
    # Plot track theta XZ
    
    htrackThetaYZ_Signal = f.Get("InputVariables_Id/trackThetaYZ__Signal_Id")
    htrackThetaYZ_Background = f.Get("InputVariables_Id/trackThetaYZ__Background_Id")
    
    plt.figure()
    ax1 = plt.axes()
    htrackThetaYZ_SignalR2M = r2m.Hist(htrackThetaYZ_Signal)
    htrackThetaYZ_BackgroundR2M = r2m.Hist(htrackThetaYZ_Background)
    stack = r2m.HistStack()
    stack.add(htrackThetaYZ_SignalR2M, label="Signal, Neutrino")
    stack.add(htrackThetaYZ_BackgroundR2M, label="Background, Cosmic")
    htrackThetaYZ_SignalR2M.hist(histtype='stepfilled', color='b',normed=True,linewidth=1, alpha=0.5)
    htrackThetaYZ_BackgroundR2M.hist(histtype='stepfilled', color='r',normed=True,linewidth=1, alpha=0.5)
    stack.show_titles()
    plt.title("Track $\\theta_{YZ}$")
    plt.xlabel("$\\theta_{YZ}$ [radians]")
    plt.ylabel(r'$dN_{}/^{}0.0402$ radians')
    plt.margins(y=0.05)
    plt.ylim(ymin=0)
    plt.legend(loc='upper right')
    plt.savefig('demo_plots/trackThetaYZ.png')
    
    
    
    # Plot closest distance to a boundary
    
    htrackkNearestDistUntaggedToTaggedCosGT_Signal = f.Get("InputVariables_Id/trackNearestDistUntaggedToTaggedCosGT__Signal_Id")
    htrackkNearestDistUntaggedToTaggedCosGT_Background = f.Get("InputVariables_Id/trackNearestDistUntaggedToTaggedCosGT__Background_Id")
    
    plt.figure()
    ax1 = plt.axes()
    htrackkNearestDistUntaggedToTaggedCosGT_SignalR2M = r2m.Hist(htrackkNearestDistUntaggedToTaggedCosGT_Signal)
    htrackkNearestDistUntaggedToTaggedCosGT_BackgroundR2M = r2m.Hist(htrackkNearestDistUntaggedToTaggedCosGT_Background)
    stack = r2m.HistStack()
    stack.add(htrackkNearestDistUntaggedToTaggedCosGT_SignalR2M, label="Signal, Neutrino")
    stack.add(htrackkNearestDistUntaggedToTaggedCosGT_BackgroundR2M, label="Background, Cosmic")
    htrackkNearestDistUntaggedToTaggedCosGT_SignalR2M.hist(histtype='stepfilled', color='b',normed=True,linewidth=1, alpha=0.5)
    htrackkNearestDistUntaggedToTaggedCosGT_BackgroundR2M.hist(histtype='stepfilled', color='r',normed=True,linewidth=1, alpha=0.5)
    stack.show_titles()
    plt.title("Distance to Nearest Tagged Cosmic")
    plt.xlabel(r"Dist [cm]")
    plt.ylabel(r'$dN_{}/^{}12.6$ cm')
    plt.margins(y=0.05)
    plt.ylim(ymin=0)
    plt.legend(loc='upper right')
    plt.savefig('demo_plots/trackkNearestDistUntaggedToTaggedCosGT.png')
    
    
    
    # Plot the response 
    
    hMVA_BDT_Signal = f.Get("Method_BDT/BDT/MVA_BDT_S")
    hMVA_BDT_Background = f.Get("Method_BDT/BDT/MVA_BDT_B")
    
    plt.figure()
    ax1 = plt.axes()
    hMVA_BDT_SignalR2M = r2m.Hist(hMVA_BDT_Signal)
    hMVA_BDT_BackgroundR2M = r2m.Hist(hMVA_BDT_Background)
    stack = r2m.HistStack()
    stack.add(hMVA_BDT_SignalR2M, label="Signal, Neutrino")
    stack.add(hMVA_BDT_BackgroundR2M, label="Background, Cosmic")
    hMVA_BDT_SignalR2M.hist(histtype='stepfilled', color='b',normed=True,linewidth=1, alpha=0.5)
    hMVA_BDT_BackgroundR2M.hist(histtype='stepfilled', color='r',normed=True,linewidth=1, alpha=0.5)
    stack.show_titles()
    plt.title("BDT Response")
    plt.xlabel("BDT Response")
    plt.ylabel(r'(1/N) dN/dx')
    plt.margins(y=0.05)
    plt.ylim(ymin=0)
    plt.legend(loc='upper left')
    plt.savefig('demo_plots/MVA_BDT.png')
    
    
    
    # Plot the efficiencies and significance
    
    hMVA_BDT_effSignal = f.Get("Method_BDT/BDT/MVA_BDT_effS")
    hMVA_BDT_effBackground = f.Get("Method_BDT/BDT/MVA_BDT_effB")
    
    plt.figure()
    ax1 = plt.axes()
    hMVA_BDT_effSignalR2M = r2m.Hist(hMVA_BDT_effSignal)
    hMVA_BDT_effBackgroundR2M = r2m.Hist(hMVA_BDT_effBackground)
    stack = r2m.HistStack()
    stack.add(hMVA_BDT_effSignalR2M, label="Signal, Neutrino")
    stack.add(hMVA_BDT_effBackgroundR2M, label="Background, Cosmic")
    hMVA_BDT_effSignalR2M.hist(histtype='step', color='b',normed=False,linewidth=2)
    hMVA_BDT_effBackgroundR2M.hist(histtype='step', color='r',normed=False,linewidth=2)
    stack.show_titles()
    plt.title("Efficiencies")
    plt.xlabel("Cut Value on Response")
    plt.ylabel(r'Efficiency')
    plt.margins(y=0.05)
    plt.ylim(ymin=0)
    plt.legend(loc='upper right')
    plt.savefig('demo_plots/MVA_BDT_eff.png')
  





if __name__ == '__main__':
    sys.exit(main(sys.argv))



