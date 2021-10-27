version="version1"
datacards="srmuch_allNodes.txt,ttcrmuch_allNodes.txt,stcrmuch_allNodes.txt,wdycrmuch_allNodes.txt,srech_allNodes.txt,ttcrech_allNodes.txt,stcrech_allNodes.txt,wdycrech_allNodes.txt"
datacards_ech="srech_allNodes.txt,ttcrech_allNodes.txt,stcrech_allNodes.txt,wdycrech_allNodes.txt"
datacards_much="srmuch_allNodes.txt,ttcrmuch_allNodes.txt,stcrmuch_allNodes.txt,wdycrmuch_allNodes.txt"
cd /nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards

law run PlotLikelihoodScan \
    --version $version \
    --datacards $datacards \
    --pois kl \
    --scan-parameters kl,-25,25 \
    --workers 4

law run PlotUpperLimits \
    --version $version \
    --datacards $datacards \
    --xsec fb \
    --y-log \
    --scan-parameters kl,-30,30,61 \ # default
    --workers 4

law run PlotMultipleUpperLimits \
    --version $version \
    --multi-datacards $datacards:$datacards_much:$datacards_ech \
    --datacard-names Comb,Much,Ech \
    --xsex fb \
    --y-log \
    --workers 4

law run PlotUpperLimitsAtPoint \
    --version $version \
    --multi-datacards $datacards:$datacards_much:$datacards_ech \
    --datacard-names Comb,Much,Ech

law run PlotPullsAndImpacts \
    --version $version \
    --datacards $datacards \
    --pois r
