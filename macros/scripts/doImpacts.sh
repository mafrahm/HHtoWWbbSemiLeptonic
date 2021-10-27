datacard="COMB_srmuch_ttcrmuch_stcrmuch_wdycrmuch_srech_ttcrech_stcrech_wdycrech_1.txt"
dataroot="COMB_srmuch_ttcrmuch_stcrmuch_wdycrmuch_srech_ttcrech_stcrech_wdycrech_1.root"
path="/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards/Impacts"
outpath="/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots"

rMin="-120"
rMax="120"
minTol="1e-4"
RFS="2"

cd $path
cp ../$datacard .
text2workspace.py $datacard -m 125
echo "=========== doInitialFit ========"
combineTool.py -M Impacts -d $dataroot -t -1 -m 125 --rMin $rMin --rMax $rMax --expectSignal 1 --cminDefaultMinimizerTolerance $minTol --cminDefaultMinimizerStrategy 0 --robustFit 1 --setRobustFitStrategy $RFS --doInitialFit

echo "=========== doFits =============="
combineTool.py -M Impacts -d $dataroot -t -1 -m 125 --rMin $rMin --rMax $rMax --expectSignal 1 --cminDefaultMinimizerTolerance $minTol --cminDefaultMinimizerStrategy 0 --robustFit 1 --setRobustFitStrategy $RFS --doFits

echo "=========== impacts.json ========"
combineTool.py -M Impacts -d $dataroot -t -1 -m 125 --rMin $rMin --rMax $rMax --expectSignal 1 --cminDefaultMinimizerTolerance $minTol --cminDefaultMinimizerStrategy 0 -o impacts.json

echo "=========== plotImpacts ========="
plotImpacts.py -i impacts.json -o impacts
cp impacts.pdf $outpath
