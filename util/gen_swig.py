import copy
import os
import re

from gen_code_util import build_call_line

TARGET_FILES_SWIG = [
  'iriclib_bc.h',
  'iriclib_cc.h',
  'iriclib_complex.h',
  'iriclib_geo.h',
  'iriclib_geoutil.h',
  'iriclib_grid.h',
  'iriclib_gui_coorp.h',
  'iriclib_init.h',
  'iriclib_not_withbaseid.h',
  'iriclib_not_withgridid.h',
  'iriclib_sol_particle.h',
  'iriclib_sol_particlegroup.h',
  'iriclib_sol_polydata.h',
  'iriclib_solution.h',
  'iriclib_wrapper.h',
]

def gen_swig_i_content(fdef):
  fdef2 = fdef
  fdef2 = fdef2.replace('IRICLIBDLL ', '')
  fdef2 = fdef2.replace(';', '')
  m = re.search(r'(\w+) (\w+)\((.*)\)', fdef2)

  (retval, fname, args) = m.groups()

  arglist = args.split(',')
  args = list()

  for a in arglist:
    a = a.strip()
    frags = a.split(' ')
    aname = frags.pop()
    atype = " ".join(frags)

    if atype == "int*" or atype == "double*":
      args.append(atype + " OUTPUT")
    else:
      args.append(a)

  return retval + " " + fname + "(" + ", ".join(args) + ");\n"

def gen_swig_i():
  with open(os.path.join('..', 'python_binding', 'iric.i'), 'w', encoding='utf-8') as f_i:
    with open('iric.i.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_i.write(l)

    for filename in TARGET_FILES_SWIG:
      f_i.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if not 'IRICLIBDLL' in line: continue
          if 'RealSingle' in line: continue
          if 'StringLen' in line: continue
          if filename != 'iriclib_wrapper.h' and '_arr' in line: continue

          f_i.write(gen_swig_i_content(line))

      f_i.write("\n")

    with open('iric.i.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_i.write(l)

def gen_size_func(fname, args):
  
  m = re.search('(cg_iRIC_Read_BC_Indices)(.*)', fname)
  if m:
    main, suffix = m.groups()
    return 'cg_iRIC_Read_BC_IndicesSize2' + suffix, args
  
  m = re.search('((cg_iRIC_Read_(.*))FunctionalWithName)(.*)', fname)
  if m:
    d1, main, d2, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    return main + 'FunctionalSize' + suffix, args2

  m = re.search('(cg_iRIC_Read_Grid_(Real|Integer|Complex)_Node)(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Grid_Functional_(Real|Integer)_Node)(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Grid_(Real|Integer|Complex)_Cell)(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()

    return 'cg_iRIC_Read_Grid_CellCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Grid_Functional_(Real|Integer)_Cell)(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_CellCount' + suffix, args2

  m = re.search('(cg_iRIC_GetGridCoord[1-3]d)(.*)', fname)
  if m:
    m, suffix = m.groups()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args

  m = re.search('(cg_iRIC_Read_Grid[1-3]d_Coords)(.*)', fname)
  if m:
    m, suffix = m.groups()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args

  m = re.search('(cg_iRIC_Read_Grid_FunctionalDimension_(Integer|Real))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()

    return 'cg_iRIC_Read_Grid_FunctionalDimensionSize' + suffix, args

  m = re.search('(cg_iRIC_Read_Grid_FunctionalTime)(.*)', fname)
  if m:
    m, suffix = m.groups()

    return 'cg_iRIC_Read_Grid_FunctionalTimeSize' + suffix, args

  m = re.search('(cg_iRIC_Read_Sol_Node_(Integer|Real))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_Cell_(Integer|Real))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_CellCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_IFace_(Integer|Real))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_IFaceCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_JFace_(Integer|Real))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_JFaceCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_KFace_(Integer|Real))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_KFaceCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_GridCoord[1-3]d)(.*)', fname)
  if m:
    m, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_Grid[1-3]d_Coords)(.*)', fname)
  if m:
    m, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_(Integer|Real))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()
    args2.pop()

    return 'cg_iRIC_Read_Grid_NodeCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_Particle_(Real|Integer))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()

    return 'cg_iRIC_Read_Sol_Particle_Count' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_Particle_(Pos.d))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()

    return 'cg_iRIC_Read_Sol_Particle_Count' + suffix, args

  m = re.search('(cg_iRIC_Read_Sol_ParticleGroup_(Real|Integer))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()

    return 'cg_iRIC_Read_Sol_ParticleGroup_Count' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_ParticleGroup_(Pos.d))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()

    return 'cg_iRIC_Read_Sol_ParticleGroup_Count' + suffix, args

  m = re.search('(cg_iRIC_Read_Sol_PolyData_(Real|Integer))(.*)', fname)
  if m:
    m, d1, suffix = m.groups()
    args2 = copy.copy(args)
    args2.pop()

    return 'cg_iRIC_Read_Sol_PolyData_DataCount' + suffix, args2

  m = re.search('(cg_iRIC_Read_Sol_PolyData_Type)(.*)', fname)
  if m:
    m, suffix = m.groups()

    return 'cg_iRIC_Read_Sol_PolyData_DataCount' + suffix, args

  m = re.search('(cg_iRIC_Read_Sol_PolyData_Pos2d)(.*)', fname)
  if m:
    m, suffix = m.groups()

    return 'cg_iRIC_Read_Sol_PolyData_CoordinateCount' + suffix, args

  m = re.search('(cg_iRIC_Read_Grid_TriangleElements)(.*)', fname)
  if m:
    m, suffix = m.groups()

    return 'cg_iRIC_Read_Grid_TriangleElementsSize2' + suffix, args

  if fname == 'iRIC_Geo_Polygon_Read_Points':
    return 'iRIC_Geo_Polygon_Read_PointCount', args

  if fname == 'iRIC_Geo_Polygon_Read_HolePoints':
    return 'iRIC_Geo_Polygon_Read_HolePointCount', args
  
  if fname == 'iRIC_Geo_RiverSurvey_Read_Altitudes':
    return 'iRIC_Geo_RiverSurvey_Read_AltitudeCount', args

  m = re.search("((cg_iRIC_Read_(.*))Functional)(.*)", fname)
  if m:
    d1, main, d2, suffix = m.groups()
    return main + 'FunctionalSize' + suffix, args

  return '@TODO FIX THIS', list()

def gen_iric_py_content(fdef):
  fdef2 = fdef
  fdef2 = fdef2.replace('IRICLIBDLL ', '')
  fdef2 = fdef2.replace(';', '')
  m = re.search(r'(\w+) (\w+)\((.*)\)', fdef2)

  (retval, fname, args) = m.groups()

  arglist = args.split(',')

  args = list() # args of the api
  rets = list() # return values of the api
  arrays_in = dict()
  arrays_out = dict()
  w_rets = list() # return values of the wrapper func
  w_args = list() # args of the wrapper func

  if retval == 'int':
    w_rets.append('ier')

  content = ''

  for a in arglist:
    a = a.strip()
    frags = a.split(' ')
    aname = frags.pop()
    atype = " ".join(frags)

    if atype == "int*" or atype == "double*" or aname == "strvalue":
      w_rets.append(aname)
      rets.append(aname)

    elif atype == "IntArrayContainer&" or atype == "RealArrayContainer&":
      if "_Read" in fname or "GetGridCoord" in fname or "GetTriangleElements" in fname:
        arrays_out[aname] = atype.replace('&', '')
        w_args.append(aname.replace('_arr', ''))
        rets.append(aname.replace('_arr', '') + ".get()")

      elif "_Write" in fname:
        arrays_in[aname] = atype.replace('&', '')
        args.append(aname)
        w_args.append(aname.replace('_arr', ''))

      else:
        print("Invalid function name {0}".format(fname))

    else:
      args.append(aname)
      w_args.append(aname)

  content = "def " + fname + "(" + ", ".join(args) + "):\n"

  if len(arrays_out) > 0:
    size_f, args2 = gen_size_func(fname, args)
    content += "\t" + "size = " + size_f + "(" + ", ".join(args2) + ")\n"
  
  for n, t in arrays_in.items():
    content += "\t" + n.replace('_arr', '') + " = " + t + "(" + n + ".size)\n"
    content += "\t" + n.replace('_arr', '') + ".set(" + n + ")\n"

  for n, t in arrays_out.items():
    content += "\t" + n.replace('_arr', '') + " = " + t + "(size)\n"

  content += "\t" + ", ".join(w_rets) + " = _iric." + fname + "(" + ", ".join(w_args) + ")\n"

  if fname == "iRIC_Check_Cancel":
    content += "\t" + "return ier" + "\n"

  else:
    if retval == 'int':
      content += "\t" + "_checkErrorCode(ier)\n"

    if len(rets) > 0:
      content += "\t" + "return " + ", ".join(rets) + "\n"

  content += "\n"

  return content

def gen_iric_py():
  with open(os.path.join('..', 'python_binding', 'iric_custom.py'), 'w', encoding='utf-8') as f_i:
    with open('iric_custom.py.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_i.write(l)

    for filename in TARGET_FILES_SWIG:
      f_i.write("# from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if not 'IRICLIBDLL' in line: continue
          if 'RealSingle' in line: continue
          if 'StringLen' in line: continue
          if filename != 'iriclib_wrapper.h' and '_arr' in line: continue

          f_i.write(gen_iric_py_content(line))

      f_i.write("\n")

    with open('iric_custom.py.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_i.write(l)

def gen_swig():
  gen_swig_i()
  gen_iric_py()
