from python.CombineRunner import *

path_datacards = '/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards'
CombineRunner16 = CombineRunner(path_datacards, 2016)
CombineRunner17 = CombineRunner(path_datacards, 2017)
CombineRunner18 = CombineRunner(path_datacards, 2018)

noSyst = ['lumi']

systematics = [
    'lumi', 
    'muid', 'muiso', 'eleid', 'elereco','btag_bc', 'btag_udsg',# 'pu',
    #'mutrigger', 'eletrigger', # they do not exist yet :(
    #'JEC', 'JER',
    'rate_scales_tt', 'rate_scales_t', 'rate_scales_V', 'rate_scales_VV', 'rate_qcd', #'rate_scales_HH',
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

#AutoMCStats = bool(True);
fitDiagnostics = bool(False);




combineInput16='combineRateShape_Inclusive_NNbkgweightX8_removeQCD_classes4_TrainOn30_allYears_2016.root'
combineInput17='combineRateShape_Inclusive_NNbkgweightX8_removeQCD_classes4_TrainOn30_allYears_2017.root'
combineInput18='combineRateShape_Inclusive_NNbkgweightX8_removeQCD_classes4_TrainOn30_allYears_2018.root'


# fullsyst
CombineRunner16.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput16, True, 'syst_2016_')
CombineRunner17.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput17, True, 'syst_2017_')
CombineRunner18.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput18, True, 'syst_2018_')

CombineRunner16.CombineChannelsInference(channels, 'syst_2016_')
CombineRunner17.CombineChannelsInference(channels, 'syst_2017_')
CombineRunner18.CombineChannelsInference(channels, 'syst_2018_')

# noMCStats
CombineRunner16.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput16, False, 'noMCSt_2016_')
CombineRunner17.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput17, False, 'noMCSt_2017_')
CombineRunner18.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput18, False, 'noMCSt_2018_')

CombineRunner16.CombineChannelsInference(channels, 'noMCSt_2016_')
CombineRunner17.CombineChannelsInference(channels, 'noMCSt_2017_')
CombineRunner18.CombineChannelsInference(channels, 'noMCSt_2018_')

CombineRunner16.CreateInferenceDatacards(nodes_inference, channels, backgrounds, noSyst, combineInput16, False, 'noSyst_2016_')
CombineRunner17.CreateInferenceDatacards(nodes_inference, channels, backgrounds, noSyst, combineInput17, False, 'noSyst_2017_')
CombineRunner18.CreateInferenceDatacards(nodes_inference, channels, backgrounds, noSyst, combineInput18, False, 'noSyst_2018_')

CombineRunner16.CombineChannelsInference(channels, 'noSyst_2016_')
CombineRunner17.CombineChannelsInference(channels, 'noSyst_2017_')
CombineRunner18.CombineChannelsInference(channels, 'noSyst_2018_')
'''
cardnametag16='bkgX8_2016_'
cardnametag17='bkgX8_2017_'
cardnametag18='bkgX8_2018_'

CombineRunner16.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput16, AutoMCStats, cardnametag16)
CombineRunner17.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput17, AutoMCStats, cardnametag17)
CombineRunner18.CreateInferenceDatacards(nodes_inference, channels, backgrounds, systematics, combineInput18, AutoMCStats, cardnametag18)


CombineRunner16.CombineChannelsInference(channels, cardnametag16)
CombineRunner17.CombineChannelsInference(channels, cardnametag17)
CombineRunner18.CombineChannelsInference(channels, cardnametag18)
'''

#CombineRunner.CreateDatacards(nodes, channels, backgrounds, systematics, combineInput, AutoMCStats)

print '-------------------------------------'
#CombineRunner.CombineChannels(nodes, channels, '')
print '-------------------------------------'
#CombineRunner.ExecuteCombineCombination(nodes, channels, fitDiagnostics, '')
