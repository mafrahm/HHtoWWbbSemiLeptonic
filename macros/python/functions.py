import os
import sys
import subprocess
import time
import signal
from multiprocessing import Process
from multiprocessing import Pool
from constants import *



def write_lines(path, filename, lines):
    outfile = open(path+filename, 'w')
    for line in lines:
        outfile.write(line)
        outfile.write('\n')
    outfile.close()

def get_lines_datacard_header(channel, node, backgrounds):
    lines = []
    lines.append('# Datacard for channel %s, for node %s \n' % (channel, node))
    lines.append('# HEADER')
    lines.append('imax 1')
    lines.append('jmax %i' % (len(backgrounds)))
    lines.append('kmax *')
    return lines

def get_lines_datacard_channels(varcat):
    lines = []
    lines.append('# CHANNELS')
    lines.append('bin %s' % (varcat))
    lines.append('observation -1')
    return lines

def get_lines_datacard_input(rootfilename, year):
    lines = []
    #     shapes * * input/combine_histograms_mc_fullsyst_much.root $CHANNEL__$PROCESS_2016v3 $CHANNEL__$PROCESS_2016v3__$SYSTEMATIC
    lines.append('# INPUT')
    lines.append('shapes * * %s $CHANNEL__$PROCESS_%s $CHANNEL__$PROCESS_%s__$SYSTEMATIC' % (rootfilename, yeartags[year], yeartags[year]))
    return lines

def get_lines_datacard_processes(varcat, node, backgrounds):
    lines = []
    lines.append('# PROCESSES')

    line = 'bin        '
    for i in range(len(backgrounds) + 1):
        line += varcat + '  '
    lines.append(line)

    #line = 'process    ' + signaltag + '_' + node + '  '
    line = 'process    ' + signaltag.replace('X', node) + '  '
    for bkg in backgrounds:
        if bkg in backgrounds:
            line += bkg + '  '
    lines.append(line)

    line = 'process    0  '
    idx = 1
    for bkg in backgrounds:
        line += str(idx) + '  '
        idx += 1
    lines.append(line)

    line = 'rate       -1  '
    for bkg in backgrounds:
        line += '-1  '
    lines.append(line)

    return lines




def get_lines_datacard_systematics(systematics, node, backgrounds, year):
    signal = signaltag.replace('X', node)
    print 'signal: %s' %(signal)
    lines = []
    lines.append('# SYSTEMATICS')
    for syst in systematics:
        if not syst in processes_per_systematic.keys():
            raise RuntimeError('Systematic %s not in constant dictionaries.' % (syst))
        print 'syst: %s' % (syst)
        if(correlateYears[syst]):
            line = syst + '  ' + pdf_per_systematic[syst] + '  '
        else:
            line = syst + str(year) + '  ' + pdf_per_systematic[syst] + '  '

        # first for signal:
        #if processes_per_systematic[syst] == 'all' or processes_per_systematic[syst] == signaltag + '_' + node:
        if processes_per_systematic[syst] == 'all':
            line += str(value_per_systematic_and_process[syst,'all']) + '  '
        elif signal in processes_per_systematic[syst]:
            line += str(value_per_systematic_and_process[syst,signal]) + '  '
        else:
            line += '-  '
        for bkg in backgrounds:
            if processes_per_systematic[syst] == 'all':
                line += str(value_per_systematic_and_process[syst,'all']) + '  '
            elif bkg in processes_per_systematic[syst]:
                line += str(value_per_systematic_and_process[syst,bkg]) + '  '
            else:
                line += '-  '
        lines.append(line)

    return lines

def get_lines_datacard_statistics():
    lines = []
    lines.append('# STATISTICS')
    lines.append('* autoMCStats 0 0 1')
    return lines



def create_datacard(year, node, channel, backgrounds, systematics, path_datacards, rootfilename, AutoMCStats):
    print 'Creating datacard for node %s in channel %s. ' % (node, channel)
    if not os.path.exists(path_datacards):
        raise RuntimeError('Path %s does not exist.' % (path_datacards))
    # else: print 'Datacard directory: %s' % (path_datacards)
    if not os.path.exists(path_datacards + '/' + rootfilename):
        raise RuntimeError('Rootfile %s does not exist.' % (path_datacards + '/' + rootfilename))
    # else: print 'rootfile containing histograms: %s' % (path_datacards + '/' + rootfilename)

    filename_datacard = channel + '_' + node + '.txt' # + '_node_'
    #filename_datacard = channel + '_' + signaltag.replace('X', node) + '.txt' # + '_node_'
    print 'filename: %s ' % (filename_datacard)
    print 'going to create file: %s' % (path_datacards + '/' + filename_datacard)
    varcat = channel
    separator = ['-----------------------------\n']



    lines_header = get_lines_datacard_header(channel, node, backgrounds) + separator
    lines_channels = get_lines_datacard_channels(varcat) + separator
    lines_input = get_lines_datacard_input(rootfilename, year)
    lines_processes = get_lines_datacard_processes(varcat, node, backgrounds)
    lines_systematics = get_lines_datacard_systematics(systematics, node, backgrounds, year)
    lines_statistics = get_lines_datacard_statistics()


    lines = lines_header + lines_channels + lines_input + lines_processes + lines_systematics
    if AutoMCStats:
        lines  += lines_statistics
    write_lines(path_datacards + '/', filename_datacard, lines)
