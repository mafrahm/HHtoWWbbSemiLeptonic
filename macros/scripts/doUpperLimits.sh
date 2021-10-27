# example datacard is here: /afs/cern.ch/user/m/mfackeld/public/datacards/dnn_score_max/emu_dnn_node_HH_2B2VTo2L2Nu_GluGlu_NLO/datacard.txt


datacards="srmuch_allNodes.txt,ttcrmuch_allNodes.txt,stcrmuch_allNodes.txt,wdycrmuch_allNodes.txt,srech_allNodes.txt,ttcrech_allNodes.txt,stcrech_allNodes.txt,wdycrech_allNodes.txt"
cd /nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards

law run PlotUpperLimits \
    --version test \
    --datacards $datacards \
    --xsec fb \
    --y-log \
    --workers 4
