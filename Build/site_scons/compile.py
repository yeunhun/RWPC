# -*- coding: UTF-8 -*-'
"""
    compile.py

    Tool-specific initialization for build process.

    Copyright (c) 2021 HYUNDAI AUTOEVER Corp.

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By       Description
********************************************************************************
** 2.2.2      12-05-2019   TK Moon  Redmine #20531,#20532,#20540
** 2.2.0      11-08-2019   TK Moon  Redmine #19116,#20005,#19513
** 2.1.0      12-21-2018   TK Moon  Redmine #15255
** 2.0.0      09-20-2018   TK Moon  Redmine #14159
*******************************************************************************/
"""
Import('*')

import os
import cdt
import re
import sys
import common
from SCons.Node import FS, NodeList

##################################
# initialize
binary = None
err_log_lines = [str(env['COMPILE_RULE'])]
default_int_files, default_ext_files = [],[]
libraryFile, internalObjects, internalLibraries, externalObjects = [], [], [], []
fbl_path, external_include, internal_include = [], [], []
def _sort_override_folders(files):
    internal_include = files['internalPath'] + files['externalPath']
    external_include = files['externalPath']
    files['internalFile'] = list(set(sorted(files['internalFile'])))
    files['externalFile'] = list(set(sorted(files['externalFile'])))
    for p in env['OVERRIDE_COMPILE_DIR']:
        for _root, _dirs, _files in os.walk(p):
            for _a_file in _files:
                if _a_file.split('.')[-1] in env['CSuffixes']:
                    if any([f for f in files['internalFile'] if f.endswith(_a_file)]):
                        files['externalFile'][:] = [d for d in files['externalFile'] if not d.endswith(_a_file)]
                        files['internalFile'][:] = [d for d in files['internalFile'] if not d.endswith(_a_file)]
                        files['externalFile'][:] = [d for d in files['externalFile'] if not d.endswith(_a_file)]
                        files['internalFile'] += [os.path.join(_root, _a_file)]
                    elif any([f for f in files['externalFile'] if f.endswith(_a_file)]):
                        files['internalFile'][:] = [d for d in files['internalFile'] if not d.endswith(_a_file)]
                        files['externalFile'][:] = [d for d in files['externalFile'] if not d.endswith(_a_file)]
                        files['internalFile'][:] = [d for d in files['internalFile'] if not d.endswith(_a_file)]
                        files['externalFile'] += [os.path.join(_root, _a_file)]
                    else:
                        print (os.path.join(_root, _a_file))
    
    internal_include = sorted(list(set(internal_include)))
    external_include = sorted(list(set(external_include)))
    for p in internal_include:
        if p.startswith(tuple(env['OVERRIDE_COMPILE_DIR'])):
            internal_include.remove(p)
            internal_include.insert(0, p)
    for p in external_include:
        if p.startswith(tuple(env['OVERRIDE_COMPILE_DIR'])):
            external_include.remove(p)
            external_include.insert(0, p)
    return (internal_include, external_include)

def _filter_source_files(file_list, src_path):
    new_list = []
    for j in src_path:
        j = os.path.join(*j.split('/')) # use splat operator * to join path
        new_list += filter(lambda x: x.startswith(j), file_list)
    for n in new_list: # remove from file list if in new_list
        if n in files['internalFile']:
            files['internalFile'].remove(n)
        if n in files['externalFile']:
            files['externalFile'].remove(n)
    return new_list

# get all the files and paths for internal & external use if the folder starts with lib
files = cdt.CdtProject().get_filtered_static_files_n_paths(env)

(internal_include, external_include) = _sort_override_folders(files)

files['internalFile'] = sorted(list(set(files['internalFile'])))
files['externalFile'] = sorted(list(set(files['externalFile'])))
files['internalPath'] = sorted(list(set(files['internalPath'])))
files['externalPath'] = sorted(list(set(files['externalPath'])))

ext_src_files, int_src_files = [], []
# loop to divide compile option by pattern 
for i in env['PATTERN_LIST']:
    if i.keys()[0] == 'BSW' or \
       i.keys()[0] == 'MCAL'or \
       i.keys()[0] == 'FBL'or \
       i.keys()[0] == 'ASW':
        src_path = i[i.keys()[0]]['s_path']
        if i.keys()[0] == 'MCAL': # if MCAL folder release everything even excluded
            env['OVERRIDE_RELEASE_DIR'] = env['OVERRIDE_RELEASE_DIR'] + src_path
        if len(src_path) > 0: # if source path is configured
            tmp_ccflags = i[i.keys()[0]]['c_opt']
            tmp_cppdefines = i[i.keys()[0]]['d_opt']
            # for integration test enable when folder exists
            if os.path.exists(env['INT_TEST_DIR']):
              tmp_cppdefines.append('INSTST_TESTCODE_INTEGRATED')
            if i[i.keys()[0]]['int_path']:
                internalLibraries.extend(i[i.keys()[0]]['int_path'])
            is_internal = int(i[i.keys()[0]]['is_int'])
            include_header = []
            # filter source files based on configured path
            tmp_ext_files = _filter_source_files(files['externalFile'], src_path)
            tmp_int_files = _filter_source_files(files['internalFile'], src_path)
            if len(tmp_int_files) > 0: # if any internal file exists
                if is_internal == 1: # create internalObjects if "is internal" is true
                    include_header = internal_include
                    internalObjects += env.Object(
                        source=tmp_int_files,
                        INCLUDE_PATH=[include_header],
                        CCFLAGS=tmp_ccflags,
                        CPPDEFINES=tmp_cppdefines)
                    int_src_files.extend(tmp_int_files) # for debugging
                elif is_internal == 0:
                    # add internal sources to externalObjects sources if "is internal" is false
                    # these folders and files will be copied to released project directory.
                    env['OVERRIDE_RELEASE_DIR'].extend(tmp_int_files) 
                    tmp_ext_files.extend(tmp_int_files)
            if len(tmp_ext_files) > 0: # if any external file exists
                include_header = external_include
                if is_internal == 0:
                    include_header = internal_include
                externalObjects += env.Object(
                    source=tmp_ext_files, 
                    INCLUDE_PATH=[include_header],
                    CCFLAGS=tmp_ccflags,
                    CPPDEFINES=tmp_cppdefines)
                ext_src_files.extend(tmp_ext_files) # for debugging
    else:
        print("The pattern \"{0}\" is not supported, Please check your settings".format(i.keys()[0]))
        sys.exit(-1)
        
err_log_lines.extend([str(['Compile for External'])])
for _file in list(set(ext_src_files)):
    err_log_lines.extend(['\t{0}'.format(_file)])

err_log_lines.extend([str(['Compile for Internal'])])
for _file in list(set(int_src_files)):
    err_log_lines.extend(['\t{0}'.format(_file)])

err_log_lines.extend([str(['DefaultCompileOptions'])])
""" compile any left over internal & external files """ 
if len(files['internalFile']) > 0: # if internal files are left to compile
    internalObjects += env.Object(
        source=files['internalFile'],
        INCLUDE_PATH=[internal_include],
        CCFLAGS=env['DEFAULT_CCFLAGS'],
        CPPDEFINES=env['DEFAULT_CPPDEFS'])
    err_log_lines.extend(['\tInternalFiles'])
    for opt in env['DEFAULT_CCFLAGS'] + env['DEFAULT_CPPDEFS']:
        err_log_lines.extend(['\t\tDefaultOption is {0}'.format(opt)])
if len(files['externalFile']) > 0: # if external files are left to compile
    externalObjects += env.Object(
        source=files['externalFile'],
        INCLUDE_PATH=external_include,
        CCFLAGS=env['DEFAULT_CCFLAGS'],
        CPPDEFINES=env['DEFAULT_CPPDEFS'])
    err_log_lines.extend(['\tExternalFiles'])
    for opt in env['DEFAULT_CCFLAGS'] + env['DEFAULT_CPPDEFS']:
        err_log_lines.extend(['\t\tDefaultOption is {0}'.format(opt)])

lib_sources= internalLibraries + internalObjects
if len(lib_sources) > 0: # if at least one source for library exist(s)
    project_name = env['PROJECT'].replace('.', '_')
    env['LIBRARY_FILE'] = os.path.join(env['LIB_OUTPUT_DIR'], 'lib' + project_name)
    libraryFile = env.Library(source=lib_sources, target=env['LIBRARY_FILE'])
    env['LIBRARY_FILE'] += env['LIBSUFFIX']
    env['LIBPATH'] += [env['LIB_OUTPUT_DIR']]

env['LIBS'] += common.get_library_name(libraryFile, env['LIB_INSTALL_DIR'])
# add .a file to be generated
if os.path.exists(env['LIB_INSTALL_DIR']):
    env['LIBPATH'] += [env['LIB_INSTALL_DIR']]

targetFiles = [os.path.join(env['DEBUG_DIR'], env['PROJECT'])]
binary = env.Program(target=targetFiles, source=[env['OBJECT_FILES'],externalObjects])
env.Depends(binary, libraryFile)

# give before build result to input to set dependencies
if not pre_build == None: 
    env.Depends(binary, pre_build)
    
if env['SCONS_LOG_FLAG'] == True and len(err_log_lines) > 1:
    common.print_to_log(env, err_log_lines)

if any([c for c in env['COMPILE_RULE'] if c.lower().endswith(('fbl'))]):
    fbl_str = 'FBL'
else:
    fbl_str = ''
env.Alias('Build' + fbl_str, binary)
env.Clean('Build' + fbl_str, env['DEBUG_DIR'])
env.Alias('Compile' + fbl_str, binary)
env.Clean('Compile' + fbl_str, env['DEBUG_DIR'])

Return('binary')
