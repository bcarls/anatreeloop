
import ROOT
import sys
import time

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

    # A Plot
    cPerpDistYBound= ROOT.TCanvas("cPerpDistYBound")
    hPerpDistYBound= f.Get("track_boundaries/hPerpDistYBound")
    hPerpDistYBound.SetLineColor(2)
    hPerpDistYBound.SetLineWidth(3)
    hPerpDistYBound.SetStats(False)
    hPerpDistYBound.GetYaxis().SetTitleOffset(1.5)
    hPerpDistYBound.Draw()

    # A Plot
    cPerpDistZBound= ROOT.TCanvas("cPerpDistZBound")
    hPerpDistZBound= f.Get("track_boundaries/hPerpDistZBound")
    hPerpDistZBound.SetLineColor(2)
    hPerpDistZBound.SetLineWidth(3)
    hPerpDistZBound.SetStats(False)
    hPerpDistZBound.GetYaxis().SetTitleOffset(1.2)
    hPerpDistZBound.Draw()

    
    # A Plot
    cNearestDistUntaggedToTaggedGTTrackLength = ROOT.TCanvas("cNearestDistUntaggedToTaggedGTTrackLength")
    hNearestDistUntaggedToTaggedGTTrackLength = f.Get("hNearestDistUntaggedToTaggedGTTrackLength")
    hNearestDistUntaggedToTaggedGTTrackLength.SetStats(False)
    hNearestDistUntaggedToTaggedGTTrackLength.Draw("COLZ")

    # A Plot
    cPerpDistToABoundTrackLength = ROOT.TCanvas("cPerpDistToABoundTrackLength")
    hPerpDistToABoundTrackLength = f.Get("hPerpDistToABoundTrackLength")
    hPerpDistToABoundTrackLength.SetStats(False)
    hPerpDistToABoundTrackLength.Draw("COLZ")

    # Save everything
    hf = ROOT.TFile ("MakePlotsData.root","recreate")
    cPerpDistYBound.Write()
    cPerpDistZBound.Write()
    cNearestDistUntaggedToTaggedGTTrackLength.Write()
    cPerpDistToABoundTrackLength.Write()

    hf.Close()












#     # Plot cosmic retention efficiencies as a function of length
#     cPerpDistToABoundTrueCosEfficiency = ROOT.TCanvas("cPerpDistToABoundTrueCosEfficiency")

#     hPerpDistToABoundTrueCosNoCosRem = f.Get("track_boundaries/hPerpDistToABoundTrueCosNoCosRem")
#     hPerpDistToABoundTrueCosFM =  f.Get("track_boundaries/hPerpDistToABoundTrueCosFM")
#     hPerpDistToABoundTrueCosGT = f.Get("track_boundaries/hPerpDistToABoundTrueCosGT")
#     hPerpDistToABoundTrueCosGTFM = f.Get("track_boundaries/hPerpDistToABoundTrueCosGTFM")

#     hPerpDistToABoundTrueCosNoCosRem.SetStats(False)
#     hPerpDistToABoundTrueCosFM.SetStats(False)
#     hPerpDistToABoundTrueCosGT.SetStats(False)
#     hPerpDistToABoundTrueCosGTFM.SetStats(False)

#     # hPerpDistToABoundTrueCosNoCosRem.Sumw2()
#     # hPerpDistToABoundTrueCosFM.Sumw2()
#     # hPerpDistToABoundTrueCosGT.Sumw2()
#     # hPerpDistToABoundTrueCosGTFM.Sumw2()

#     hPerpDistToABoundTrueCosGT.Divide(hPerpDistToABoundTrueCosGT,hPerpDistToABoundTrueCosNoCosRem,1.0,1.0,"B")
#     hPerpDistToABoundTrueCosFM.Divide(hPerpDistToABoundTrueCosFM,hPerpDistToABoundTrueCosNoCosRem,1.0,1.0,"B")
#     hPerpDistToABoundTrueCosGTFM.Divide(hPerpDistToABoundTrueCosGTFM,hPerpDistToABoundTrueCosNoCosRem,1.0,1.0,"B")
   
#     hPerpDistToABoundTrueCosGT.SetMaximum(1.0)
#     hPerpDistToABoundTrueCosGT.SetLineColor(2)
#     hPerpDistToABoundTrueCosGT.SetLineWidth(3)
#     hPerpDistToABoundTrueCosGT.SetTitle("Efficiency after cosmic removal for true cosmic tracks")
#     hPerpDistToABoundTrueCosGT.GetYaxis().SetTitle("Efficiency")
#     hPerpDistToABoundTrueCosGT.GetXaxis().SetTitle("Closest Distance to a TPC Boundary [cm]")

#     hPerpDistToABoundTrueCosFM.SetLineColor(4)
#     hPerpDistToABoundTrueCosFM.SetLineWidth(3)

#     hPerpDistToABoundTrueCosGTFM.SetLineColor(6)
#     hPerpDistToABoundTrueCosGTFM.SetLineWidth(3)

#     hPerpDistToABoundTrueCosGT.Draw("")
#     hPerpDistToABoundTrueCosFM.Draw("SAME")
#     hPerpDistToABoundTrueCosGTFM.Draw("SAME")
   
#     lgPerpDistToABoundTrueCosEfficiency = ROOT.TLegend(0.6,0.6,0.9,0.875)
#     lgPerpDistToABoundTrueCosEfficiency.AddEntry(hPerpDistToABoundTrueCosGT,"Geom Tagger","l")
#     lgPerpDistToABoundTrueCosEfficiency.AddEntry(hPerpDistToABoundTrueCosFM,"Flash Match","l")
#     lgPerpDistToABoundTrueCosEfficiency.AddEntry(hPerpDistToABoundTrueCosGTFM,"Geom Tagger and Flash Match","l")
#     lgPerpDistToABoundTrueCosEfficiency.SetBorderSize(0)
#     lgPerpDistToABoundTrueCosEfficiency.Draw()






#     # Plot cosmic retention efficiencies as a function of length
#     cTrackOriginTotal = ROOT.TCanvas("cTrackOrginTotal")

#     hTrackOriginTotalNoCosRem = f.Get("track_origins/hTrackOriginNoCosRem").Clone()
#     hTrackOriginTotalFM =  f.Get("track_origins/hTrackOriginFM").Clone()
#     hTrackOriginTotalGT = f.Get("track_origins/hTrackOriginGT").Clone()
#     hTrackOriginTotalGTFM = f.Get("track_origins/hTrackOriginGTFM").Clone()

#     hTrackOriginTotalNoCosRem.SetStats(False)
#     hTrackOriginTotalFM.SetStats(False)
#     hTrackOriginTotalGT.SetStats(False)
#     hTrackOriginTotalGTFM.SetStats(False)

#     # hTrackOriginTotalNoCosRem.Sumw2()
#     # hTrackOriginTotalFM.Sumw2()
#     # hTrackOriginTotalGT.Sumw2()
#     # hTrackOriginTotalGTFM.Sumw2()

#     hTrackOriginTotalGT.SetMaximum( 1.1*max(hTrackOriginTotalFM.GetMaximum(),hTrackOriginTotalGT.GetMaximum(), hTrackOriginTotalGTFM.GetMaximum()))
#     hTrackOriginTotalGT.SetLineColor(2)
#     hTrackOriginTotalGT.SetLineWidth(3)
#     hTrackOriginTotalGT.SetTitle("Total tracks after cosmic removal")
#     hTrackOriginTotalGT.GetYaxis().SetTitle("Number of tracks")

#     hTrackOriginTotalFM.SetLineColor(4)
#     hTrackOriginTotalFM.SetLineWidth(3)

#     hTrackOriginTotalGTFM.SetLineColor(6)
#     hTrackOriginTotalGTFM.SetLineWidth(3)

#     hTrackOriginTotalGT.Draw()
#     hTrackOriginTotalFM.Draw("SAME")
#     hTrackOriginTotalGTFM.Draw("SAME")
   
#     lgTrackOriginTotal = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackOriginTotal.AddEntry(hTrackOriginTotalGT,"Geom Tagger","l")
#     lgTrackOriginTotal.AddEntry(hTrackOriginTotalFM,"Flash Match","l")
#     lgTrackOriginTotal.AddEntry(hTrackOriginTotalGTFM,"Geom Tagger and Flash Match","l")
#     lgTrackOriginTotal.SetBorderSize(0)
#     lgTrackOriginTotal.Draw()











#     # Plot cosmic retention efficiencies as a function of length
#     cTrackOriginEfficiency = ROOT.TCanvas("cTrackOrginEfficiency")

#     hTrackOriginNoCosRem = f.Get("track_origins/hTrackOriginNoCosRem").Clone()
#     hTrackOriginFM =  f.Get("track_origins/hTrackOriginFM").Clone()
#     hTrackOriginGT = f.Get("track_origins/hTrackOriginGT").Clone()
#     hTrackOriginGTFM = f.Get("track_origins/hTrackOriginGTFM").Clone()

#     hTrackOriginNoCosRem.SetStats(False)
#     hTrackOriginFM.SetStats(False)
#     hTrackOriginGT.SetStats(False)
#     hTrackOriginGTFM.SetStats(False)

#     # hTrackOriginNoCosRem.Sumw2()
#     # hTrackOriginFM.Sumw2()
#     # hTrackOriginGT.Sumw2()
#     # hTrackOriginGTFM.Sumw2()

#     hTrackOriginGT.Divide(hTrackOriginGT,hTrackOriginNoCosRem,1.0,1.0,"B")
#     hTrackOriginFM.Divide(hTrackOriginFM,hTrackOriginNoCosRem,1.0,1.0,"B")
#     hTrackOriginGTFM.Divide(hTrackOriginGTFM,hTrackOriginNoCosRem,1.0,1.0,"B")
   
#     hTrackOriginGT.SetMaximum(1.0)
#     hTrackOriginGT.SetLineColor(2)
#     hTrackOriginGT.SetLineWidth(3)
#     hTrackOriginGT.SetTitle("Efficiency after cosmic removal")
#     hTrackOriginGT.GetYaxis().SetTitle("Efficiency")

#     hTrackOriginFM.SetLineColor(4)
#     hTrackOriginFM.SetLineWidth(3)

#     hTrackOriginGTFM.SetLineColor(6)
#     hTrackOriginGTFM.SetLineWidth(3)

#     hTrackOriginGT.Draw()
#     hTrackOriginFM.Draw("SAME")
#     hTrackOriginGTFM.Draw("SAME")
   
#     lgTrackOriginEfficiency = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackOriginEfficiency.AddEntry(hTrackOriginGT,"Geom Tagger","l")
#     lgTrackOriginEfficiency.AddEntry(hTrackOriginFM,"Flash Match","l")
#     lgTrackOriginEfficiency.AddEntry(hTrackOriginGTFM,"Geom Tagger and Flash Match","l")
#     lgTrackOriginEfficiency.SetBorderSize(0)
#     lgTrackOriginEfficiency.Draw()










#     # Plot cosmic retention efficiencies as a function of length
#     cTrackLengthEfficiency = ROOT.TCanvas("cTrackLengthEfficiency")
    
#     hTrackLengthNoCosRem = f.Get("track_lengths/hTrackLengthNoCosRem")
#     hTrackLengthFM =  f.Get("track_lengths/hTrackLengthFM")
#     hTrackLengthGT = f.Get("track_lengths/hTrackLengthGT")
#     hTrackLengthGTFM = f.Get("track_lengths/hTrackLengthGTFM")
   
#     hTrackLengthNoCosRem.SetStats(False)
#     hTrackLengthFM.SetStats(False)
#     hTrackLengthGT.SetStats(False)
#     hTrackLengthGTFM.SetStats(False)

#     # hTrackLengthNoCosRem.Sumw2()
#     # hTrackLengthFM.Sumw2()
#     # hTrackLengthGT.Sumw2()
#     # hTrackLengthGTFM.Sumw2()

#     hTrackLengthGT.Divide(hTrackLengthGT,hTrackLengthNoCosRem,1.0,1.0,"B")
#     hTrackLengthFM.Divide(hTrackLengthFM,hTrackLengthNoCosRem,1.0,1.0,"B")
#     hTrackLengthGTFM.Divide(hTrackLengthGTFM,hTrackLengthNoCosRem,1.0,1.0,"B")
   
#     hTrackLengthGT.SetMaximum(1.0)
#     hTrackLengthGT.SetLineColor(2)
#     hTrackLengthGT.SetLineWidth(3)
#     hTrackLengthGT.SetTitle("Efficiency after cosmic removal")
#     hTrackLengthGT.GetYaxis().SetTitle("Efficiency")

#     hTrackLengthFM.SetLineColor(4)
#     hTrackLengthFM.SetLineWidth(3)

#     hTrackLengthGTFM.SetLineColor(6)
#     hTrackLengthGTFM.SetLineWidth(3)

#     hTrackLengthGT.Draw()
#     hTrackLengthFM.Draw("SAME")
#     hTrackLengthGTFM.Draw("SAME")
   
#     lgTrackLengthEfficiency = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackLengthEfficiency.AddEntry(hTrackLengthGT,"Geom Tagger","l")
#     lgTrackLengthEfficiency.AddEntry(hTrackLengthFM,"Flash Match","l")
#     lgTrackLengthEfficiency.AddEntry(hTrackLengthGTFM,"Geom Tagger and Flash Match","l")
#     lgTrackLengthEfficiency.SetBorderSize(0)
#     lgTrackLengthEfficiency.Draw()











#     # Plot cosmic retention efficiencies as a function of length
#     cTrackLengthTrueCosEfficiency = ROOT.TCanvas("cTrackLengthTrueCosEfficiency")

#     hTrackLengthTrueCosNoCosRem = f.Get("track_lengths/hTrackLengthTrueCosNoCosRem")
#     hTrackLengthTrueCosFM =  f.Get("track_lengths/hTrackLengthTrueCosFM")
#     hTrackLengthTrueCosGT = f.Get("track_lengths/hTrackLengthTrueCosGT")
#     hTrackLengthTrueCosGTFM = f.Get("track_lengths/hTrackLengthTrueCosGTFM")
   
#     hTrackLengthTrueCosNoCosRem.SetStats(False)
#     hTrackLengthTrueCosFM.SetStats(False)
#     hTrackLengthTrueCosGT.SetStats(False)
#     hTrackLengthTrueCosGTFM.SetStats(False)

#     # hTrackLengthTrueCosNoCosRem.Sumw2()
#     # hTrackLengthTrueCosFM.Sumw2()
#     # hTrackLengthTrueCosGT.Sumw2()
#     # hTrackLengthTrueCosGTFM.Sumw2()

#     hTrackLengthTrueCosGT.Divide(hTrackLengthTrueCosGT,hTrackLengthTrueCosNoCosRem,1.0,1.0,"B")
#     hTrackLengthTrueCosFM.Divide(hTrackLengthTrueCosFM,hTrackLengthTrueCosNoCosRem,1.0,1.0,"B")
#     hTrackLengthTrueCosGTFM.Divide(hTrackLengthTrueCosGTFM,hTrackLengthTrueCosNoCosRem,1.0,1.0,"B")
   
#     hTrackLengthTrueCosGT.SetMaximum(1.0)
#     hTrackLengthTrueCosGT.SetLineColor(2)
#     hTrackLengthTrueCosGT.SetLineWidth(3)
#     hTrackLengthTrueCosGT.SetTitle("Efficiency after cosmic removal for true cosmic tracks")
#     hTrackLengthTrueCosGT.GetYaxis().SetTitle("Efficiency")

#     hTrackLengthTrueCosFM.SetLineColor(4)
#     hTrackLengthTrueCosFM.SetLineWidth(3)

#     hTrackLengthTrueCosGTFM.SetLineColor(6)
#     hTrackLengthTrueCosGTFM.SetLineWidth(3)

#     hTrackLengthTrueCosGT.Draw()
#     hTrackLengthTrueCosFM.Draw("SAME")
#     hTrackLengthTrueCosGTFM.Draw("SAME")
   
#     lgTrackLengthTrueCosEfficiency = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackLengthTrueCosEfficiency.AddEntry(hTrackLengthTrueCosGT,"Geom Tagger","l")
#     lgTrackLengthTrueCosEfficiency.AddEntry(hTrackLengthTrueCosFM,"Flash Match","l")
#     lgTrackLengthTrueCosEfficiency.AddEntry(hTrackLengthTrueCosGTFM,"Geom Tagger and Flash Match","l")
#     lgTrackLengthTrueCosEfficiency.SetBorderSize(0)
#     lgTrackLengthTrueCosEfficiency.Draw()




#     # Plot cosmic retention efficiencies as a function of length
#     cTrackLengthTrueNuEfficiency = ROOT.TCanvas("cTrackLengthTrueNuEfficiency")

#     hTrackLengthTrueNuNoCosRem = f.Get("track_lengths/hTrackLengthTrueNuNoCosRem")
#     hTrackLengthTrueNuFM =  f.Get("track_lengths/hTrackLengthTrueNuFM")
#     hTrackLengthTrueNuGT = f.Get("track_lengths/hTrackLengthTrueNuGT")
#     hTrackLengthTrueNuGTFM = f.Get("track_lengths/hTrackLengthTrueNuGTFM")

#     hTrackLengthTrueNuNoCosRem.SetStats(False)
#     hTrackLengthTrueNuFM.SetStats(False)
#     hTrackLengthTrueNuGT.SetStats(False)
#     hTrackLengthTrueNuGTFM.SetStats(False)

#     # hTrackLengthTrueNuNoCosRem.Sumw2()
#     # hTrackLengthTrueNuFM.Sumw2()
#     # hTrackLengthTrueNuGT.Sumw2()
#     # hTrackLengthTrueNuGTFM.Sumw2()

#     hTrackLengthTrueNuGT.Divide(hTrackLengthTrueNuGT,hTrackLengthTrueNuNoCosRem,1.0,1.0,"B")
#     hTrackLengthTrueNuFM.Divide(hTrackLengthTrueNuFM,hTrackLengthTrueNuNoCosRem,1.0,1.0,"B")
#     hTrackLengthTrueNuGTFM.Divide(hTrackLengthTrueNuGTFM,hTrackLengthTrueNuNoCosRem,1.0,1.0,"B")
   
#     hTrackLengthTrueNuGT.SetMaximum(1.0)
#     hTrackLengthTrueNuGT.SetLineColor(2)
#     hTrackLengthTrueNuGT.SetLineWidth(3)
#     hTrackLengthTrueNuGT.SetTitle("Efficiency after cosmic removal for true neutrino tracks")
#     hTrackLengthTrueNuGT.GetYaxis().SetTitle("Efficiency")

#     hTrackLengthTrueNuFM.SetLineColor(4)
#     hTrackLengthTrueNuFM.SetLineWidth(3)

#     hTrackLengthTrueNuGTFM.SetLineColor(6)
#     hTrackLengthTrueNuGTFM.SetLineWidth(3)

#     hTrackLengthTrueNuGT.Draw()
#     hTrackLengthTrueNuFM.Draw("SAME")
#     hTrackLengthTrueNuGTFM.Draw("SAME")
    
#     lgTrackLengthTrueNuEfficiency = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackLengthTrueNuEfficiency.AddEntry(hTrackLengthTrueNuGT,"Geom Tagger","l")
#     lgTrackLengthTrueNuEfficiency.AddEntry(hTrackLengthTrueNuFM,"Flash Match","l")
#     lgTrackLengthTrueNuEfficiency.AddEntry(hTrackLengthTrueNuGTFM,"Geom Tagger and Flash Match","l")
#     lgTrackLengthTrueNuEfficiency.SetBorderSize(0)
#     lgTrackLengthTrueNuEfficiency.Draw()





#     # Plot the track length based on true origin
#     cTrackLengthTrueNoCosRem = ROOT.TCanvas("cTrackLengthTrueNoCosRem")
#     hTrackLengthTrueNuNoCosRem = f.Get("track_lengths/hTrackLengthTrueNuNoCosRem")
#     hTrackLengthTrueCosNoCosRem = f.Get("track_lengths/hTrackLengthTrueCosNoCosRem")
  
#     hTrackLengthTrueNuNoCosRem.SetStats(False)
#     hTrackLengthTrueCosNoCosRem.SetStats(False)

#     # hTrackLengthTrueNuNoCosRem.Sumw2()
#     # hTrackLengthTrueCosNoCosRem.Sumw2()
    
#     hTrackLengthTrueNuNoCosRem.SetLineColor(2)
#     hTrackLengthTrueNuNoCosRem.SetLineWidth(3)

#     hTrackLengthTrueCosNoCosRem.SetLineColor(4)
#     hTrackLengthTrueCosNoCosRem.SetLineWidth(3)

#     hTrackLengthTrueCosNoCosRem.DrawNormalized()
#     hTrackLengthTrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackLengthTrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackLengthTrueNoCosRem.AddEntry(hTrackLengthTrueNuNoCosRem,"Neutrino","l")
#     lgTrackLengthTrueNoCosRem.AddEntry(hTrackLengthTrueCosNoCosRem,"Cosmic","l")
#     lgTrackLengthTrueNoCosRem.SetBorderSize(0)
#     lgTrackLengthTrueNoCosRem.Draw()





#     # Plot the track phi based on true origin
#     cTrackPhiTrueNoCosRem = ROOT.TCanvas("cTrackPhiTrueNoCosRem")
#     hTrackPhiTrueNuNoCosRem = f.Get("track_angles/hTrackPhiTrueNuNoCosRem")
#     hTrackPhiTrueCosNoCosRem = f.Get("track_angles/hTrackPhiTrueCosNoCosRem")
  
#     hTrackPhiTrueNuNoCosRem.SetStats(False)
#     hTrackPhiTrueCosNoCosRem.SetStats(False)

#     # hTrackPhiTrueNuNoCosRem.Sumw2()
#     # hTrackPhiTrueCosNoCosRem.Sumw2()
    
#     hTrackPhiTrueNuNoCosRem.SetLineColor(2)
#     hTrackPhiTrueNuNoCosRem.SetLineWidth(3)

#     hTrackPhiTrueCosNoCosRem.SetLineColor(4)
#     hTrackPhiTrueCosNoCosRem.SetLineWidth(3)

#     hTrackPhiTrueCosNoCosRem.DrawNormalized()
#     hTrackPhiTrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackPhiTrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackPhiTrueNoCosRem.AddEntry(hTrackPhiTrueNuNoCosRem,"Neutrino","l")
#     lgTrackPhiTrueNoCosRem.AddEntry(hTrackPhiTrueCosNoCosRem,"Cosmic","l")
#     lgTrackPhiTrueNoCosRem.SetBorderSize(0)
#     lgTrackPhiTrueNoCosRem.Draw()



#     # Plot the track theta based on true origin
#     cTrackThetaTrueNoCosRem = ROOT.TCanvas("cTrackThetaTrueNoCosRem")
#     hTrackThetaTrueNuNoCosRem = f.Get("track_angles/hTrackThetaTrueNuNoCosRem")
#     hTrackThetaTrueCosNoCosRem = f.Get("track_angles/hTrackThetaTrueCosNoCosRem")
  
#     hTrackThetaTrueNuNoCosRem.SetStats(False)
#     hTrackThetaTrueCosNoCosRem.SetStats(False)

#     # hTrackThetaTrueNuNoCosRem.Sumw2()
#     # hTrackThetaTrueCosNoCosRem.Sumw2()
    
#     hTrackThetaTrueNuNoCosRem.SetLineColor(2)
#     hTrackThetaTrueNuNoCosRem.SetLineWidth(3)

#     hTrackThetaTrueCosNoCosRem.SetLineColor(4)
#     hTrackThetaTrueCosNoCosRem.SetLineWidth(3)

#     hTrackThetaTrueCosNoCosRem.DrawNormalized()
#     hTrackThetaTrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackThetaTrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackThetaTrueNoCosRem.AddEntry(hTrackThetaTrueNuNoCosRem,"Neutrino","l")
#     lgTrackThetaTrueNoCosRem.AddEntry(hTrackThetaTrueCosNoCosRem,"Cosmic","l")
#     lgTrackThetaTrueNoCosRem.SetBorderSize(0)
#     lgTrackThetaTrueNoCosRem.Draw()




#     # Plot the track theta xz based on true origin
#     cTrackThetaXZTrueNoCosRem = ROOT.TCanvas("cTrackThetaXZTrueNoCosRem")
#     hTrackThetaXZTrueNuNoCosRem = f.Get("track_angles/hTrackThetaXZTrueNuNoCosRem")
#     hTrackThetaXZTrueCosNoCosRem = f.Get("track_angles/hTrackThetaXZTrueCosNoCosRem")
  
#     hTrackThetaXZTrueNuNoCosRem.SetStats(False)
#     hTrackThetaXZTrueCosNoCosRem.SetStats(False)

#     # hTrackThetaXZTrueNuNoCosRem.Sumw2()
#     # hTrackThetaXZTrueCosNoCosRem.Sumw2()
    
#     hTrackThetaXZTrueNuNoCosRem.SetLineColor(2)
#     hTrackThetaXZTrueNuNoCosRem.SetLineWidth(3)

#     hTrackThetaXZTrueCosNoCosRem.SetLineColor(4)
#     hTrackThetaXZTrueCosNoCosRem.SetLineWidth(3)

#     hTrackThetaXZTrueCosNoCosRem.DrawNormalized()
#     hTrackThetaXZTrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackThetaXZTrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackThetaXZTrueNoCosRem.AddEntry(hTrackThetaXZTrueNuNoCosRem,"Neutrino","l")
#     lgTrackThetaXZTrueNoCosRem.AddEntry(hTrackThetaXZTrueCosNoCosRem,"Cosmic","l")
#     lgTrackThetaXZTrueNoCosRem.SetBorderSize(0)
#     lgTrackThetaXZTrueNoCosRem.Draw()


#     # Plot the track theta yz based on true origin
#     cTrackThetaYZTrueNoCosRem = ROOT.TCanvas("cTrackThetaYZTrueNoCosRem")
#     hTrackThetaYZTrueNuNoCosRem = f.Get("track_angles/hTrackThetaYZTrueNuNoCosRem")
#     hTrackThetaYZTrueCosNoCosRem = f.Get("track_angles/hTrackThetaYZTrueCosNoCosRem")
  
#     hTrackThetaYZTrueNuNoCosRem.SetStats(False)
#     hTrackThetaYZTrueCosNoCosRem.SetStats(False)

#     # hTrackThetaYZTrueNuNoCosRem.Sumw2()
#     # hTrackThetaYZTrueCosNoCosRem.Sumw2()
    
#     hTrackThetaYZTrueNuNoCosRem.SetLineColor(2)
#     hTrackThetaYZTrueNuNoCosRem.SetLineWidth(3)

#     hTrackThetaYZTrueCosNoCosRem.SetLineColor(4)
#     hTrackThetaYZTrueCosNoCosRem.SetLineWidth(3)

#     hTrackThetaYZTrueCosNoCosRem.DrawNormalized()
#     hTrackThetaYZTrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackThetaYZTrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackThetaYZTrueNoCosRem.AddEntry(hTrackThetaYZTrueNuNoCosRem,"Neutrino","l")
#     lgTrackThetaYZTrueNoCosRem.AddEntry(hTrackThetaYZTrueCosNoCosRem,"Cosmic","l")
#     lgTrackThetaYZTrueNoCosRem.SetBorderSize(0)
#     lgTrackThetaYZTrueNoCosRem.Draw()


#     # Plot the track PIDA based on true origin
#     cTrackPIDATrueNoCosRem = ROOT.TCanvas("cTrackPIDATrueNoCosRem")
#     hTrackPIDATrueNuNoCosRem = f.Get("track_calo_pid/hTrackPIDATrueNuNoCosRem")
#     hTrackPIDATrueCosNoCosRem = f.Get("track_calo_pid/hTrackPIDATrueCosNoCosRem")
  
#     hTrackPIDATrueNuNoCosRem.SetStats(False)
#     hTrackPIDATrueCosNoCosRem.SetStats(False)

#     # hTrackPIDATrueNuNoCosRem.Sumw2()
#     # hTrackPIDATrueCosNoCosRem.Sumw2()
    
#     hTrackPIDATrueNuNoCosRem.SetLineColor(2)
#     hTrackPIDATrueNuNoCosRem.SetLineWidth(3)

#     hTrackPIDATrueCosNoCosRem.SetLineColor(4)
#     hTrackPIDATrueCosNoCosRem.SetLineWidth(3)

#     hTrackPIDATrueCosNoCosRem.DrawNormalized()
#     hTrackPIDATrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackPIDATrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackPIDATrueNoCosRem.AddEntry(hTrackPIDATrueNuNoCosRem,"Neutrino","l")
#     lgTrackPIDATrueNoCosRem.AddEntry(hTrackPIDATrueCosNoCosRem,"Cosmic","l")
#     lgTrackPIDATrueNoCosRem.SetBorderSize(0)
#     lgTrackPIDATrueNoCosRem.Draw()







#     # Plot the untagged true neutrino's distance to the closest tagged cosmic, via flash match
#     cNearestDistUntaggedTrueToTaggedCosFM = ROOT.TCanvas("cNearestDistUntaggedTrueToTaggedCosFM")
#     hNearestDistUntaggedTrueNuToTaggedCosFM = f.Get("hNearestDistUntaggedTrueNuToTaggedCosFM")
#     hNearestDistUntaggedTrueCosToTaggedCosFM = f.Get("hNearestDistUntaggedTrueCosToTaggedCosFM")

#     hNearestDistUntaggedTrueCosToTaggedCosFM.SetTitle("Distance of Untagged True to Flash Match")

#     hNearestDistUntaggedTrueNuToTaggedCosFM.SetStats(False)
#     hNearestDistUntaggedTrueCosToTaggedCosFM.SetStats(False)

#     # hNearestDistUntaggedTrueNuToTaggedCosFM.Sumw2()
#     # hNearestDistUntaggedTrueCosToTaggedCosFM.Sumw2()
    
#     hNearestDistUntaggedTrueNuToTaggedCosFM.SetLineColor(2)
#     hNearestDistUntaggedTrueNuToTaggedCosFM.SetLineWidth(3)

#     hNearestDistUntaggedTrueCosToTaggedCosFM.SetLineColor(4)
#     hNearestDistUntaggedTrueCosToTaggedCosFM.SetLineWidth(3)

#     hNearestDistUntaggedTrueCosToTaggedCosFM.DrawNormalized()
#     hNearestDistUntaggedTrueNuToTaggedCosFM.DrawNormalized("SAME")

#     lgNearestDistUntaggedTrueToTaggedCosFM = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgNearestDistUntaggedTrueToTaggedCosFM.AddEntry(hNearestDistUntaggedTrueNuToTaggedCosFM,"Neutrino","l")
#     lgNearestDistUntaggedTrueToTaggedCosFM.AddEntry(hNearestDistUntaggedTrueCosToTaggedCosFM,"Cosmic","l")
#     lgNearestDistUntaggedTrueToTaggedCosFM.SetBorderSize(0)
#     lgNearestDistUntaggedTrueToTaggedCosFM.Draw()



#     # Plot the untagged true neutrino's distance to the closest tagged cosmic, via geom tagger
#     cNearestDistUntaggedTrueToTaggedCosGT = ROOT.TCanvas("cNearestDistUntaggedTrueToTaggedCosGT")
#     hNearestDistUntaggedTrueNuToTaggedCosGT = f.Get("hNearestDistUntaggedTrueNuToTaggedCosGT")
#     hNearestDistUntaggedTrueCosToTaggedCosGT = f.Get("hNearestDistUntaggedTrueCosToTaggedCosGT")

#     hNearestDistUntaggedTrueCosToTaggedCosGT.SetTitle("Distance of Untagged True to Geom Tagged")

#     hNearestDistUntaggedTrueNuToTaggedCosGT.SetStats(False)
#     hNearestDistUntaggedTrueCosToTaggedCosGT.SetStats(False)

#     # hNearestDistUntaggedTrueNuToTaggedCosGT.Sumw2()
#     # hNearestDistUntaggedTrueCosToTaggedCosGT.Sumw2()
    
#     hNearestDistUntaggedTrueNuToTaggedCosGT.SetLineColor(2)
#     hNearestDistUntaggedTrueNuToTaggedCosGT.SetLineWidth(3)

#     hNearestDistUntaggedTrueCosToTaggedCosGT.SetLineColor(4)
#     hNearestDistUntaggedTrueCosToTaggedCosGT.SetLineWidth(3)

#     hNearestDistUntaggedTrueCosToTaggedCosGT.DrawNormalized()
#     hNearestDistUntaggedTrueNuToTaggedCosGT.DrawNormalized("SAME")

#     lgNearestDistUntaggedTrueToTaggedCosGT = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgNearestDistUntaggedTrueToTaggedCosGT.AddEntry(hNearestDistUntaggedTrueNuToTaggedCosGT,"Neutrino","l")
#     lgNearestDistUntaggedTrueToTaggedCosGT.AddEntry(hNearestDistUntaggedTrueCosToTaggedCosGT,"Cosmic","l")
#     lgNearestDistUntaggedTrueToTaggedCosGT.SetBorderSize(0)
#     lgNearestDistUntaggedTrueToTaggedCosGT.Draw()


#     # Plot the untagged true neutrino's distance to the closest tagged cosmic, via geom tagger
#     cNearestDistUntaggedTrueToTaggedCosGTFM = ROOT.TCanvas("cNearestDistUntaggedTrueToTaggedCosGTFM")
#     hNearestDistUntaggedTrueNuToTaggedCosGTFM = f.Get("hNearestDistUntaggedTrueNuToTaggedCosGTFM")
#     hNearestDistUntaggedTrueCosToTaggedCosGTFM = f.Get("hNearestDistUntaggedTrueCosToTaggedCosGTFM")

#     hNearestDistUntaggedTrueCosToTaggedCosGTFM.SetTitle("Distance of Untagged True to Geom and Flash Tagged")

#     hNearestDistUntaggedTrueNuToTaggedCosGTFM.SetStats(False)
#     hNearestDistUntaggedTrueCosToTaggedCosGTFM.SetStats(False)

#     # hNearestDistUntaggedTrueNuToTaggedCosGTFM.Sumw2()
#     # hNearestDistUntaggedTrueCosToTaggedCosGTFM.Sumw2()
    
#     hNearestDistUntaggedTrueNuToTaggedCosGTFM.SetLineColor(2)
#     hNearestDistUntaggedTrueNuToTaggedCosGTFM.SetLineWidth(3)

#     hNearestDistUntaggedTrueCosToTaggedCosGTFM.SetLineColor(4)
#     hNearestDistUntaggedTrueCosToTaggedCosGTFM.SetLineWidth(3)

#     hNearestDistUntaggedTrueCosToTaggedCosGTFM.DrawNormalized()
#     hNearestDistUntaggedTrueNuToTaggedCosGTFM.DrawNormalized("SAME")

#     lgNearestDistUntaggedTrueToTaggedCosGTFM = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgNearestDistUntaggedTrueToTaggedCosGTFM.AddEntry(hNearestDistUntaggedTrueNuToTaggedCosGTFM,"Neutrino","l")
#     lgNearestDistUntaggedTrueToTaggedCosGTFM.AddEntry(hNearestDistUntaggedTrueCosToTaggedCosGTFM,"Cosmic","l")
#     lgNearestDistUntaggedTrueToTaggedCosGTFM.SetBorderSize(0)
#     lgNearestDistUntaggedTrueToTaggedCosGTFM.Draw()


#     # Plot the track range based on true origin
#     cTrackRangeTrueNoCosRem = ROOT.TCanvas("cTrackRangeTrueNoCosRem")
#     hTrackRangeTrueNuNoCosRem = f.Get("track_calo_pid/hTrackRangeTrueNuNoCosRem")
#     hTrackRangeTrueCosNoCosRem = f.Get("track_calo_pid/hTrackRangeTrueCosNoCosRem")
  
#     hTrackRangeTrueNuNoCosRem.SetStats(False)
#     hTrackRangeTrueCosNoCosRem.SetStats(False)

#     # hTrackRangeTrueNuNoCosRem.Sumw2()
#     # hTrackRangeTrueCosNoCosRem.Sumw2()
    
#     hTrackRangeTrueNuNoCosRem.SetLineColor(2)
#     hTrackRangeTrueNuNoCosRem.SetLineWidth(3)

#     hTrackRangeTrueCosNoCosRem.SetLineColor(4)
#     hTrackRangeTrueCosNoCosRem.SetLineWidth(3)

#     hTrackRangeTrueCosNoCosRem.DrawNormalized()
#     hTrackRangeTrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackRangeTrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackRangeTrueNoCosRem.AddEntry(hTrackRangeTrueNuNoCosRem,"Neutrino","l")
#     lgTrackRangeTrueNoCosRem.AddEntry(hTrackRangeTrueCosNoCosRem,"Cosmic","l")
#     lgTrackRangeTrueNoCosRem.SetBorderSize(0)
#     lgTrackRangeTrueNoCosRem.Draw()



#     # Plot the track KE based on true origin
#     cTrackKETrueNoCosRem = ROOT.TCanvas("cTrackKETrueNoCosRem")
#     hTrackKETrueNuNoCosRem = f.Get("track_calo_pid/hTrackKETrueNuNoCosRem")
#     hTrackKETrueCosNoCosRem = f.Get("track_calo_pid/hTrackKETrueCosNoCosRem")
  
#     hTrackKETrueNuNoCosRem.SetStats(False)
#     hTrackKETrueCosNoCosRem.SetStats(False)

#     # hTrackKETrueNuNoCosRem.Sumw2()
#     # hTrackKETrueCosNoCosRem.Sumw2()
    
#     hTrackKETrueNuNoCosRem.SetLineColor(2)
#     hTrackKETrueNuNoCosRem.SetLineWidth(3)

#     hTrackKETrueCosNoCosRem.SetLineColor(4)
#     hTrackKETrueCosNoCosRem.SetLineWidth(3)

#     hTrackKETrueCosNoCosRem.DrawNormalized()
#     hTrackKETrueNuNoCosRem.DrawNormalized("SAME")

#     lgTrackKETrueNoCosRem = ROOT.TLegend(0.1,0.6,0.4,0.9)
#     lgTrackKETrueNoCosRem.AddEntry(hTrackKETrueNuNoCosRem,"Neutrino","l")
#     lgTrackKETrueNoCosRem.AddEntry(hTrackKETrueCosNoCosRem,"Cosmic","l")
#     lgTrackKETrueNoCosRem.SetBorderSize(0)
#     lgTrackKETrueNoCosRem.Draw()







#     # Save everything
#     hf = ROOT.TFile ("MakePlots.root","recreate")
#     cPerpDistToABoundTrueCosEfficiency.Write()
#     cTrackOriginTotal.Write()
#     cTrackOriginEfficiency.Write()
#     cTrackLengthTrueNuEfficiency.Write()
#     cTrackLengthTrueCosEfficiency.Write()
#     cTrackLengthEfficiency.Write()
#     cTrackLengthTrueNoCosRem.Write()
#     cTrackPhiTrueNoCosRem.Write()
#     cTrackThetaTrueNoCosRem.Write()
#     cTrackThetaXZTrueNoCosRem.Write()
#     cTrackThetaYZTrueNoCosRem.Write()
#     cTrackPIDATrueNoCosRem.Write()
#     cTrackRangeTrueNoCosRem.Write()
#     cTrackKETrueNoCosRem.Write()
#     cNearestDistUntaggedTrueToTaggedCosFM.Write()
#     cNearestDistUntaggedTrueToTaggedCosGT.Write()
#     cNearestDistUntaggedTrueToTaggedCosGTFM.Write()
#     hf.Close()

if __name__ == '__main__':
    sys.exit(main(sys.argv))



