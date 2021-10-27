path="/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros"
Node="HH_1"


python $path/python/nuisanceToCSV.py --abs --all ../data/datacards/output/fitDiagnostics$Node.root
python python/nuisance_plot.py
cd Plots
mv nuisance_plot.pdf nuisance_plot_$Node.pdf
mv nuisance_plot.eps nuisance_plot_$Node.eps
mv nuisance_plot.png nuisance_plot_$Node.png
