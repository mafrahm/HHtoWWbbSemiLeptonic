from python.CombineRunner import *

# this is supposed to combine all 5 channels in the future
path_datacards = '/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards'
CombineRunner = CombineRunner(path_datacards, 2016)

#systematics = ['lumi', 'rate_ttbar', 'rate_dy', 'rate_ttv', 'rate_diboson', 'rate_singletop', 'rate_wjets', 'rate_qcd', 'pu', 'pdf', 'muid', 'muiso', 'mutrigger', 'eleid', 'elereco', 'eletrigger', 'btag_bc', 'btag_udsg', 'scale_TTbar', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 'scale_SingleTop', 'scale_WJets']
#systematics = ['lumi', 'rate_ttbar', 'rate_dy', 'rate_ttv', 'rate_diboson', 'rate_singletop', 'rate_wjets', 'rate_qcd', 'pu', 'muid', 'muiso', 'eleid', 'elereco', 'btag_bc', 'btag_udsg', 'scale_TTbar', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 'scale_SingleTop', 'scale_WJets'] #'pdf'
systematics = ['lumi', 'rate_qcd', 'pu', 'muid', 'muiso', 'eleid', 'elereco','btag_bc', 'btag_udsg', 'scale_TTbar', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 'scale_SingleTop', 'scale_WJets']
#systematics = ['lumi', 'pu', 'muid', 'muiso', 'eleid', 'elereco','btag_bc', 'btag_udsg']
#systematics = ['lumi']

backgrounds = ['TTbar', 'DYJets', 'SingleTop', 'WJets', 'Diboson', 'TTV', 'QCD']
#backgrounds = ['TTbar', 'DYJets', 'SingleTop', 'WJets', 'Diboson', 'TTV']
#backgrounds = ['QCD']

#channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch', 'qcdcrmuch', 'srech', 'ttcrech', 'stcrech', 'wdycrech', 'qcdcrech']
channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch', 'srech', 'ttcrech', 'stcrech', 'wdycrech']
#channels = ['srmuch']
#channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch']
#channels = ['srech', 'ttcrech', 'stcrech', 'wdycrech']

#nodes = ['SM']
nodes = ['cHHH1']
#nodes = ['cHHH0', 'cHHH1', 'cHHH2p45', 'cHHH5']

#CombineRunner.CreateDatacards(nodes, channels, backgrounds, systematics, 'NN_combine_histograms_2016.root')
#CombineRunner.CreateDatacards(nodes, channels, backgrounds, systematics, 'combineInput_limits1bins2016.root')
CombineRunner.CreateDatacards(nodes, channels, backgrounds, systematics, 'combineInput_PTJet30_NNincl_classes4_fraction050_2016.root')


print '-------------------------------------'
CombineRunner.CombineChannels(nodes, channels)
print '-------------------------------------'
CombineRunner.ExecuteCombineCombination(nodes, channels)
