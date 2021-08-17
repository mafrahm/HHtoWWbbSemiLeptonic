import os
import sys
import subprocess
from multiprocessing import Process

from functions import *



class CombineRunner:

    def __init__(self, path_datacards, year):
        self.path_datacards = path_datacards
        self.year = year
        print 'created an instance of "CombineRunner". Let\'s go!'


    def CreateDatacards(self, nodes, categories, channels, backgrounds, systematics, rootfilename):
        for node in nodes:
            for cat in categories:
                for chan in channels:
                    if not cat in categories_per_channel[chan]: continue
                    create_datacard(self.year, node, cat, chan, backgrounds, systematics, self.path_datacards, 'input/' + rootfilename)

    def CombineChannels(self, nodes, categories, channels):
        combine_dir = os.getenv('CMSSW_BASE') + '/src/HiggsAnalysis/CombinedLimit'
        if not os.path.exists(combine_dir):
            raise RuntimeError('Combine not set-up where expected: %s.' % (combine_dir))
        processes = []
        for node in nodes:
            datacards = []
            finalname = self.path_datacards + '/COMB'
            for chan in channels:
                finalname += '_' + chan + '_cat'
                for cat in categories:
                    if not cat in categories_per_channel[chan]: continue
                    #datacards.append(self.path_datacards + '/' + variables_per_category[cat] + '_' + chan + '_cat' + cat + '_' + node + '.txt')
                    datacards.append(self.path_datacards + '/' + chan + '_cat' + cat + '_' + node + '.txt')
                    finalname += cat
            finalname += '_' + node + '.txt'
            command = [combine_dir + '/scripts/combineCards.py']
            command += datacards
            f = open(finalname, 'w')
            processes.append(subprocess.Popen(command, stdout=f))

        for p in processes:
            p.wait()

    def ExecuteCombineCombination(self, nodes, categories, channels):
        cwd = os.getcwd()
        if not os.path.exists(self.path_datacards + '/output'):
            raise RuntimeError('Combine output directory not where expected: %s.' % (self.path_datacards + '/output'))
        os.chdir(self.path_datacards + '/output');
        combine_dir = os.getenv('CMSSW_BASE') + '/src/HiggsAnalysis/CombinedLimit'
        processes = []
        for node in nodes:
            combcard = self.path_datacards + '/COMB'
            for chan in channels:
                combcard += '_' + chan + '_cat'
                for cat in categories:
                    if not cat in categories_per_channel[chan]: continue
                    combcard += cat
            combcard += '_' + node + '.txt'
            name = signaltag + "_" + node

            #command = ['combine', '-n', signaltag, combcard]
            command = ['combine', '-n', name, '--run', 'blind', combcard]
            #command = ['combine', '-n', signaltag, '-M', 'FitDiagnostics', combcard]
            #command = ['combine', '-M', 'FitDiagnostics', '-t', '-1', '--rMin', '-5', '--rMax', '5', '--saveShapes', combcard]
            #command = ['combine', '-M', 'FitDiagnostics', '-t', '-1', '--rMin', '-10', '--rMax', '10', '--expectSignal', '2', '--saveShapes', combcard]
            diagnostics = ['combine', '-n', name, '-M', 'FitDiagnostics', '-t', '-1', '--rMin', '-200', '--rMax', '200', '--expectSignal', '2', '--saveShapes', '--saveWithUncertainties', '--cminDefaultMinimizerTolerance', '1e-2', '--cminDefaultMinimizerStrategy', '0', combcard]
            #diagnostics = ['combine', '-M', 'FitDiagnostics', '-t', '-1', '--rMin', '-20', '--rMax', '20', '--saveShapes', '--cminDefaultMinimizerTolerance', '1e-2', '--cminDefaultMinimizerStrategy', '0', combcard]
            processes.append(subprocess.Popen(diagnostics))
            processes.append(subprocess.Popen(command))



        for p in processes:
            p.wait()

        os.chdir(cwd)
