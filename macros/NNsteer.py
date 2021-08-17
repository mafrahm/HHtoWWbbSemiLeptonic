from python.CombineRunner import *

# this is supposed to combine all 5 channels in the future
path_datacards = '/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards'
CombineRunner = CombineRunner(path_datacards, 2016)

#systematics = ['lumi', 'rate_ttbar', 'rate_dy', 'rate_ttv', 'rate_diboson', 'rate_singletop', 'rate_wjets', 'rate_qcd', 'pu', 'pdf', 'muid', 'muiso', 'mutrigger', 'eleid', 'elereco', 'eletrigger', 'btag_bc', 'btag_udsg', 'scale_TTbar', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 'scale_SingleTop', 'scale_WJets']

systematics = ['lumi', 'rate_qcd', 'pu', 'muid', 'muiso', 'eleid', 'elereco','btag_bc', 'btag_udsg', 'pdf', 'scale_TTbar', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 'scale_SingleTop', 'scale_WJets']
#systematics = ['lumi', 'rate_ttbar', 'rate_dy', 'rate_ttv', 'rate_diboson', 'rate_singletop', 'rate_wjets']
#systematics = ['lumi', 'scale_TTbar', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 'scale_SingleTop', 'scale_WJets']
#systematics = ['lumi']

backgrounds = ['TTbar', 'DYJets', 'SingleTop', 'TTV', 'Diboson', 'WJets', 'QCD']

categories = ['A']
channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch', 'srech', 'ttcrech', 'stcrech', 'wdycrech']
#channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch']
#channels = ['srech', 'ttcrech', 'stcrech', 'wdycrech']

#nodes = ['SM']
#nodes = ['cHHH1']
nodes = ['cHHH0', 'cHHH1', 'cHHH2p45', 'cHHH5']

CombineRunner.CreateDatacards(nodes, categories, channels, backgrounds, systematics, 'NN_combine_histograms_2016.root')
print '-------------------------------------'
CombineRunner.CombineChannels(nodes, categories, channels)
print '-------------------------------------'
CombineRunner.ExecuteCombineCombination(nodes, categories, channels)
