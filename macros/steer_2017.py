from python.CombineRunner import *

path_datacards = '/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards'
CombineRunner = CombineRunner(path_datacards, 2017)

#systematics = ['lumi']

systematics = [
    'lumi', 
    'muid', 'muiso', 'eleid', 'elereco','btag_bc', 'btag_udsg', #'pu'
    #'mutrigger', 'eletrigger', # they do not exist yet :(
    #'JEC', 'JER',
    'rate_scales_tt', 'rate_scales_t', 'rate_scales_V', 'rate_scales_VV', 'rate_qcd',# 'rate_scales_HH',
    'rate_pdf_gg', 'rate_pdf_gq', 'rate_pdf_qq', 'rate_pdf_ttv',
    'scale_TTbar', 'scale_WJets', 'scale_DYJets', 'scale_TTV', 'scale_Diboson', 
    'pdf_TTbar', 'pdf_WJets', 'pdf_DYJets', 'pdf_TTV', 'pdf_Diboson',
    #'scale_SingleTop', 'pdf_SingleTop'
    'scale_HH', 'pdf_HH'
]

#backgrounds = ['TTbar']
backgrounds = ['TTbar', 'SingleTop', 'WJets', 'DYJets', 'Diboson', 'TTV', 'QCD']
#backgrounds = ['TTbar', 'DYJets', 'SingleTop', 'WJets', 'Diboson', 'TTV']
#backgrounds = ['TTbar', 'SingleTop', 'WJets']
#backgrounds = ['QCD']

#channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch', 'qcdcrmuch', 'srech', 'ttcrech', 'stcrech', 'wdycrech', 'qcdcrech']
channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch', 'srech', 'ttcrech', 'stcrech', 'wdycrech']
#channels = ['srmuch', 'srech']
#channels = ['srmuch']
#channels = ['srmuch', 'ttcrmuch', 'stcrmuch', 'wdycrmuch']
#channels = ['srech', 'ttcrech', 'stcrech', 'wdycrech']

nodes = ['1']
#nodes = ['0','1','2p45','5']

nodes_inference = ['0','1','2p45','5']

AutoMCStats = bool(True);
fitDiagnostics = bool(False);


combineInput='combineRateShape_Inclusive_NNremoveQCD_classes4_TrainOn30_allYears_2017.root'

cardnametag='NN_2017'

CombineRunner.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput, AutoMCStats, cardnametag)
CombineRunner.CombineChannelsInference(channels, cardnametag)


#CombineRunner.CreateDatacards(nodes, channels, backgrounds, systematics, combineInput, AutoMCStats)

print '-------------------------------------'
#CombineRunner.CombineChannels(nodes, channels)
print '-------------------------------------'
#CombineRunner.ExecuteCombineCombination(nodes, channels, fitDiagnostics)
