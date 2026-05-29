# -*- coding: UTF-8 -*-'
"""
    generate.py

    Tool-specific initialization for build process.

    Copyright (c) 2021 HYUNDAI AUTOEVER Corp.

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By           Description                          **
********************************************************************************
** 2.4.0      07-16-2020    TK Moon      Redmine #22142
** 2.1.0      21-Dec-2018   TK Moon      Redmine #15255
** 2.0.0      20-Sep-2018   TK Moon      Redmine #14159
*******************************************************************************/
"""
Import('*')

import os
import cdt
import re
import sys
import common
from xml.etree.ElementTree import parse
from collections import OrderedDict

##################################
# initialize
generated, t_Files, s_Files = [],[],[]
generated_files, expected_files = [], []
err_log_lines = [str(env['COMPILE_RULE'])] 
env['bsw_list'], env['mcal_list'] = [],[]
gen_fbl = False
# additional initial values for tresos MCAL generation
s_File_list, t_File_list = [],[]
mcal_generates, mcal_loads = [],['Resource', 'Os']
mcal_def_tar, mcal_def_der = '', ''

cdt.CdtProject().set_config_file_variable(env, env['CURRENT_PATH'])
# parse configured folders to override input files for generation
for p in env['OVERRIDE_DIR']:
    # set files to override if given directory exsits
    if os.path.isdir(p):
        cdt.CdtProject().set_config_file_variable(env, p) # parse all files in a project

if any([x for x in env['COMPILE_RULE'] if re.search('fbl', x, re.I)]):
    gen_fbl = True

try:
    if not gen_fbl:
        # Generate MCAL Modules #######################################################
        # loop MCAL modules first
        for g in [x for x in env['GENERATION_LIST'] if x.values()[0]['isMcal']]:
            env['OUTPUTDIR'] = env['MCAL_OUTPUT_DIR']
            moduleName = g.keys()[0]
            s_Files = g.values()[0]['src']
            if os.path.exists(env['INT_TEST_DIR']):
                s_Files += g.values()[0]['tsrc']
            t_Files = []
            if not g.values()[0]['used']: 
                continue # if module is not used ignore it
            if moduleName.lower().endswith('fbl'):
                break # break loop for FBL gen
            # for all modules provided by the MCAL vendor
            """ for MCAL generation """
            if env['MCAL_GEN_TYPE'] in ['tresosmcal', 'rh850mcal'] and not moduleName.endswith('Os'):
                if not env['MCU_TYPE'].lower().startswith('tc'):
                    inc_folder = 'include'
                else:
                    inc_folder = 'inc' # Aurix use inc folder name
            else:
                inc_folder = 'inc'
            if not moduleName.endswith('Os'):
                for x in g.values()[0]['tar']:
                    if x.endswith('.h'):
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], inc_folder, x)])
                    elif x.lower().split('.')[-1] in env['CSuffixes']:
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], 'src', x)])
                    elif not x.endswith('.h') and not x.endswith(tuple(env['CSuffixes'])):
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], x)])
                # tresos MCAL must genearte at once
                if env['MCAL_GEN_TYPE'] == 'tresosmcal':
                    env['mcal_list'].extend(t_Files)
                    s_File_list.extend(s_Files)
                    t_File_list.extend(t_Files)
                    mcal_generates.extend([moduleName + g.values()[0]['postfix']])
                    mcal_loads.extend([moduleName])
                    mcal_def_tar = g.values()[0]['mdt']
                    mcal_def_der = g.values()[0]['mdd']
                elif env['MCAL_GEN_TYPE'] == 'rh850mcal':
                    generateMCAL = env.GenerateMCAL(
                        target=t_Files,
                        source=s_Files,
                        MCAL_GENERATOR=env['files'][moduleName + g.values()[0]['postfix'] + '.exe'],
                        OUTPUTDIR=env['OUTPUTDIR'],
                        TRANSLATION_TEMPLATE=env['files']['translation_template.trxml']
                    )
                    generated += [generateMCAL]
                    env.Alias('Generate' + moduleName, generateMCAL)
                    env.Clean('Generate' + moduleName, generateMCAL)
                    env.Alias('GenerateMCAL', generateMCAL)
                    env.Clean('GenerateMCAL', generateMCAL)
                    env['mcal_list'].extend(t_Files)
                elif env['MCAL_GEN_TYPE'] == 'c4kmcal':
                    generateMCAL = env.GenerateMCAL(
                        target=t_Files,
                        source=s_Files,
                        MCALLOADS=[moduleName],
                        OUTPUTDIR=env['OUTPUTDIR'],
                    )
                    generated += [generateMCAL]
                    env.Alias('Generate' + moduleName, generateMCAL)
                    env.Clean('Generate' + moduleName, generateMCAL)
                    env.Alias('GenerateMCAL', generateMCAL)
                    env.Clean('GenerateMCAL', generateMCAL)
                    env['mcal_list'].extend(t_Files)
                else:
                    print ("No matching mcal found, Check your generation configs for MCAL module")
                    sys.exit(-1)
            # for nxp(freescale) os
            elif moduleName.endswith('Os') and env['MCU_TYPE'].lower().startswith('mpc560'):
                env['OUTPUTDIR'] = env['BSW_OUTPUT_DIR']
                for x in g.values()[0]['tar']:
                    if x.endswith('.h'):
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], inc_folder, x)])
                    elif x.lower().split('.')[-1] in env['CSuffixes']:
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], 'src', x)])
                generateBSW = env.GenerateFreescaleOs(
                    target=t_Files,
                    source=s_Files,
                    OS_GENERATOR=env['files']['sg.exe'],
                    INPUT_LINK=env['LINKSCRIPT'],
                    OUTPUTDIRSRC=os.path.join(env['OUTPUTDIR'],'src'),
                    OUTPUTDIRINC=os.path.join(env['OUTPUTDIR'],'inc'),
                )
                generated += [generateBSW]
                env.Alias('GenerateOs', generateBSW)
                env.Clean('GenerateOs', generateBSW)
                env['LINKSCRIPT'] = os.path.join(env['OUTPUTDIR'], env['PROJECT'] + '.ld')
                env['bsw_list'].extend(t_Files)
            elif moduleName.endswith('Os') and env['MCU_TYPE'].lower().startswith('rh850f1'):
                env['OUTPUTDIR'] = env['BSW_OUTPUT_DIR']
                for x in g.values()[0]['tar']:
                    if x.endswith('.h'):
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], inc_folder, x)])
                    elif x.lower().split('.')[-1] in env['CSuffixes']:
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], 'src', x)])
                    elif not x.endswith('.h') and not x.endswith(tuple(env['CSuffixes'])):
                        t_Files.extend([os.path.join(env['OUTPUTDIR'], x)])
                generateOs = env.GenerateRenesasOs(
                    target=t_Files,
                    source=s_Files,
                    OS_GENERATOR=env['files']['Os_Configurator.exe']
                )
                generated += [generateOs]
                env.Alias('GenerateOs', generateOs)
                env.Clean('GenerateOs', generateOs)
                env['bsw_list'].extend(t_Files)
        
        # tresos MCAL must genearte at once
        if env['MCAL_GEN_TYPE'] == 'tresosmcal' and any([x for x in env['GENERATION_LIST'] if x.values()[0]['isMcal']]):
            # tresos MCAL requires Dem module as mcal load if Ecud_Dem_Mcal is present
            if 'Ecud_Dem_Mcal' in s_File_list:
                mcal_loads.extend(['Dem'])
            # tresos MCAL requires CanIf module as mcal load if Ecud_CanIf is present
            if 'Ecud_CanIf_Mcal' in s_File_list:
                mcal_loads.extend(['CanIf'])
            # tresos MCAL requires FlsLoader module as mcal load if Ecud_FlsLoader is used
            if 'Ecud_FlsLoader' in s_File_list:
                mcal_loads.extend(['FlsLoader'])
            # tresos MCAL requires EcuM module as mcal load if Ecud_Dem_Mcal is present
            if 'Ecud_EcuM_Mcal' in s_File_list:
                mcal_loads.extend(['EcuM'])
            generateMCAL = env.GenerateMCAL(
                target=list(OrderedDict.fromkeys(t_File_list)), # remove duplicates
                source=list(OrderedDict.fromkeys(s_File_list)), # remove duplicates
                MCALDEFINES=[{'target': mcal_def_tar}, {'derivate': mcal_def_der}],
                MCALLOADS=mcal_loads,
                MCALGENERATES=mcal_generates,
                OUTPUTDIR=env['MCAL_OUTPUT_DIR'],
            )
            generated += [generateMCAL]
            env.Alias('GenerateMCAL', generateMCAL)
            env.Clean('GenerateMCAL', generateMCAL)
            env['mcal_list'].extend(t_Files)
        # Generate AUTRON BSW Modules #################################################
        for g in [x for x in env['GENERATION_LIST'] if not x.values()[0]['isMcal']]:
            if not g.values()[0]['used']: 
                continue # if module is not used ignore it    
            env['OUTPUTDIR'] = env['BSW_OUTPUT_DIR']
            moduleName = g.keys()[0]
            s_Files = g.values()[0]['src']
            if os.path.exists(env['INT_TEST_DIR']):
                s_Files += g.values()[0]['tsrc']
            m_flag = ''
            ver = ''
            # check if flag array's key value is not empty
            if g.values()[0]['flag'] and g.values()[0]['flag'][0]['k']:
                for f in g.values()[0]['flag']:
                    if f['k'] == '-v':
                        ver = f['v']
                        continue
                    m_flag = m_flag + ' ' + f['k'] + '  ' + env['files'][f['v']]
            t_Files = []
            # for all other BSW modules including Os provided by AUTRON
            # set output path accordingly
            if g.values()[0]['ar44'] == True:
                #create yml
                option_list = [f.split('\r')[0] for f in g.values()[0]['opts']]
                #yml_file = os.path.join(env['OUTPUTDIR'],'input_files.yml')
                yml_file = os.path.join('Build\\','input_files.yml')
                common.creat_yml_from_input(env, moduleName, ver, option_list, yml_file, s_Files)
            
            for x in g.values()[0]['tar']:
                if x.lower().startswith('swcd_'):
                    t_file = os.path.join(env['OUTPUTDIR'], 'swcd', x)
                    t_Files.extend([t_file])
                    env['files'][x] = t_file
                    is_swcd_expected = True
                elif x.lower().startswith('bswmd_'):
                    t_file = os.path.join(env['OUTPUTDIR'], 'bswmd', x)
                    t_Files.extend([t_file])
                    env['files'][x] = t_file
                    is_bswmd_expected = True
                elif x.endswith('.h'):
                    t_Files.extend([os.path.join(env['OUTPUTDIR'], 'inc', x)])
                elif x.endswith('Os_Imp_Cfg.850'): # TODO: os imp cfg .850 file is a header??
                    t_Files.extend([os.path.join(env['OUTPUTDIR'], 'inc', x)])
                elif x.lower().split('.')[-1] in env['CSuffixes']:
                    t_Files.extend([os.path.join(env['OUTPUTDIR'], 'src', x)])
                elif x.endswith('.ld'):
                    t_Files.extend([os.path.join(env['OUTPUTDIR'], x)])
                elif x.endswith('.orti'):
                    t_Files.extend([os.path.join(env['OUTPUTDIR'], 'orti', x)])
                elif x.lower().split('.')[-1] in env['MATCH_PATTERN']:
                    t_file = os.path.join(env['OUTPUTDIR'], 'xml', x)
                    t_Files.extend([t_file])
                    env['files'][x] = t_file   
                
            bsw_def = g.values()[0]['def']
            generator_name = ''
            if 'TRANSFORMER' in bsw_def:
                bsw_def.remove('TRANSFORMER')
                bsw_def.insert(0, env['TRANSFORMER'])
            if g.values()[0]['gen_ext'] !='':
                generator_name = g.values()[0]['gen_ext']
            elif moduleName.lower().startswith(('comxf','e2exf','ethswt')):
                generator_name = moduleName + '.bat' # ComXf and E2EXf file extension is .bat
                if 'TRANSFORMER' in bsw_def:
                    bsw_def.remove('TRANSFORMER')
                    bsw_def.insert(0, env['TRANSFORMER'])
            else:
                if g.values()[0]['ar44'] == True:
                    generator_name = moduleName + '.bat'
                else:
                    generator_name = moduleName + '.exe'

            #in case of ar44
            #because these have too many input files
            #it may exceed limitation of cmd line length
            #in case of Rte, it needs all input files list to generate.
            #if g.values()[0]['ar44'] and not moduleName == 'Rte':
            #    s_Files = []
            generateBSW = env.GenerateBSW(
                target=t_Files,
                source=s_Files,
                BSW_GENERATOR=env['files'][generator_name],
                BSWDEFINES=bsw_def,
                BSW_INCLUDE_PATH=g.values()[0]['inc'],
                BSW_FLAGS=m_flag,
                BSW_AR44=g.values()[0]['ar44'],
                FBL=False,
            )
            generated += [generateBSW]
            if 'S' in g.values()[0]['def']:
                env.Alias('Generate' + moduleName + '_S', generateBSW)
                env.Clean('Generate' + moduleName + '_S', generateBSW)
            elif 'B' in g.values()[0]['def']:
                env.Alias('Generate' + moduleName + '_B', generateBSW)
                env.Clean('Generate' + moduleName + '_B', generateBSW)
            else:
                env.Alias('Generate' + moduleName, generateBSW)
                env.Clean('Generate' + moduleName, generateBSW)
            
            # if BSW_INCLUDE_PATH, set dependcy for each file
            for a_path in g.values()[0]['inc']:
                for root, dirs, files in os.walk(a_path):
                    for a_file in files:
                        if a_file.lower().split('.')[-1] in env['MATCH_PATTERN']:
                            env.Depends(generateBSW, os.path.join(root, a_file))

            if moduleName.startswith('PduR') and not ('B' in g.values()[0]['def']):
                _list = common.get_bsw_config_from_arxml(env, env['files']['Ecud_PduR.arxml'],g.values()[0]['ar44'])
                t_Files.extend(_list)
            elif moduleName.startswith('Rte'):
                _list = common.get_component_from_arxml(env, env['files']['EcuExtract.arxml'], env['files']['Ecud_Rte.arxml'])
                t_Files.extend(_list)
            env['bsw_list'].extend(t_Files)
            
    # Generate FBL Modules #######################################################
    if gen_fbl:
        for g in [x for x in env['GENERATION_LIST'] if not x.values()[0]['isMcal']]:
            env['OUTPUTDIR'] = env['BSW_OUTPUT_DIR']
            moduleName = g.keys()[0]
            s_Files = g.values()[0]['src']
            if os.path.exists(env['INT_TEST_DIR']):
                s_Files += g.values()[0]['tsrc']
            t_Files = []
            if not g.values()[0]['used']: 
                continue # if module is not used ignore it
            if moduleName.lower().endswith('fbl'):
                xsl_flag = ''
                if g.values()[0]['flag'] and g.values()[0]['flag'][0]['k']:
                    for f in g.values()[0]['flag']:
                        if f['k'] == '-XSL':
                            xsl_flag = env['files'][f['v']]
                # check if FBL module generation is xsl based
                if not xsl_flag == '':
                    # TODO: list size should always equal to 2 for now
                    dir1, dir2 = '', ''
                    if g.values()[0]['def']:
                        dir1 = g.values()[0]['def'][0]
                        dir2 = g.values()[0]['def'][1]
                    for x in g.values()[0]['tar']:
                        if x.endswith('.h'):
                            t_Files.extend([os.path.join(env['OUTPUTDIR'], 'inc', x)])
                        elif x.lower().split('.')[-1] in env['CSuffixes']:
                            t_Files.extend([os.path.join(env['OUTPUTDIR'], 'src', x)])
                    generateFBL = env.GenerateFBL(
                        target=t_Files,
                        source=s_Files,
                        FBL_GENERATOR=os.path.join(env['JAVA_HOME']),
                        DIR1=dir1,
                        DIR2=dir2,
                        FBLXSL=xsl_flag,
                    )
                    generated += [generateFBL]
                    env.Alias('GenerateFBL', generateFBL)
                    env.Clean('GenerateFBL', generateFBL)
                else: # all other FBL module generation
                    f_ext = '.exe'
                    bsw_def = g.values()[0]['def']
                    # set output path accordingly
                    t_name = g.values()[0]['tar'][0]
                    for x in g.values()[0]['tar']:
                        if x.endswith('.h'):
                            t_Files.extend([os.path.join(env['OUTPUTDIR'], 'inc', x)])
                        elif x.lower().split('.')[-1] in env['CSuffixes']:
                            t_Files.extend([os.path.join(env['OUTPUTDIR'], 'src', x)])
                    m_flag = ''
                    # check if flag array's key value is not empty
                    if g.values()[0]['flag'] and g.values()[0]['flag'][0]['k']:
                        for f in g.values()[0]['flag']:
                            m_flag = m_flag + ' ' + f['k'] + '  ' + env['files'][f['v']]
                    generateBSW = env.GenerateBSW(
                        target=t_Files,
                        source=s_Files,
                        BSW_GENERATOR=env['files'][moduleName + f_ext],
                        BSWDEFINES=bsw_def,
                        BSW_INCLUDE_PATH=g.values()[0]['inc'],
                        BSW_FLAGS=m_flag,
                        FBL=True,
                    )
                    generated += [generateBSW]
                    env.Alias('Generate' + moduleName, generateBSW)
                    env.Clean('Generate' + moduleName, generateBSW)
                env['bsw_list'].extend(t_Files)
except NameError as error:
    try: 
        filename = re.search(r'name \'(\w+)\' is not defined', error.message).group(1)
        message = 'If you intended filename(' + filename + "), the file does not exist.(Case-sensitive)"
        print message
    except Exception as e:
        print (e.message)
        raise
    raise
except Exception as e:
    try:
        err_msg = "{0}: Error in line {1}, {2} ".format(e.filename, e.lineno, e.msg)
    except:
        err_msg = e.message
        pass 
    print ("Please check your settings", err_msg)
    sys.exit(-1)

env['bsw_list'] = list(set(sorted(env['bsw_list'])))
env['mcal_list'] = list(set(sorted(env['mcal_list'])))
generated += [env.RemoveTimestamp(generated)]
for gen in generated:
    for g in gen:
        err_log_lines.extend(["\tGenerate files \"{0}\"".format(g.path)])
if gen_fbl:
    env.Alias('GenerateFBL', generated)
    env.Clean('GenerateFBL', env['OUTPUTDIR'])
else:
    env.Alias('GenerateAll', generated)
    env.Clean('GenerateAll', env['BSW_OUTPUT_DIR'] + env['MCAL_OUTPUT_DIR'])

# give init build result to input to set dependencies
if not init_build == None:
    env.Depends(generated, init_build)

if env['SCONS_LOG_FLAG'] == True and len(err_log_lines) > 1:
    common.print_to_log(env, err_log_lines)

""" print expected files not generated """
def _check_for_expected_files(path, gen_list):
    err_log_lines.extend([str(['Expected file check'])])
    suffix_list = env['CSuffixes'] + ['h']
    expected_files = [f.replace('/', os.sep) for f in gen_list if f.split('.')[-1] in suffix_list]
    if not os.path.isdir(path):
        print ("Please do generation first.")
        sys.exit(-1)
    for root, dirs, files in os.walk(path):
        root_dir = os.path.relpath(root, env['CURRENT_PATH'])
        for a_file in files:
            current_file = os.path.join(root_dir, a_file)
            # check only matching suffix
            if current_file.split('.')[-1] in suffix_list:
                generated_files.append(current_file)
                if current_file in expected_files: 
                    expected_files.remove(current_file)
                else: # if expected file does not match
                    print ("More generated file \"{0}\" found for compile".format(current_file))
                    # leave scons_log for other generated files not used for compile
                    err_log_lines.extend(['\tMore generated file for compile: {0}'.format(a_file)])
    
    for f in expected_files:
        print ("Expected file \"{0}\" configured is not generated".format(f))
        err_log_lines.extend(['\tExtra expected file configured: {0}'.format(a_file)])

if any([x for x in env['COMPILE_RULE'] if x.lower().startswith(('build'))]):
    if any([x for x in env['COMPILE_RULE'] if re.search('fbl', x, re.I)]):
        _check_for_expected_files(env['FBL_OUTPUT_DIR'], env['bsw_list'])
    else:
        _check_for_expected_files(env['MCAL_OUTPUT_DIR'], env['mcal_list'])
        _check_for_expected_files(env['BSW_OUTPUT_DIR'], env['bsw_list'])

Return ('generated')