import os
import re

from gen_code_util import build_call_line

TARGET_FILES_WRAPPER = [
  'iriclib_bc.h',
  'iriclib_cc.h',
  'iriclib_complex.h',
  'iriclib_geo.h',
  'iriclib_geoutil.h',
  'iriclib_grid.h',
  'iriclib_grid_solverlib.h',
  'iriclib_not_withbaseid.h',
  'iriclib_not_withgridid.h',
  'iriclib_sol_cell.h',
  'iriclib_sol_gridcoord.h',
  'iriclib_sol_iface.h',
  'iriclib_sol_jface.h',
  'iriclib_sol_kface.h',
  'iriclib_sol_node.h',
  'iriclib_sol_particle.h',
  'iriclib_sol_particlegroup.h',
  'iriclib_sol_polydata.h',
  'iriclib_solution.h',
]

def gen_wrapper_header_line(fdef):
  fdef = fdef.replace('IRICLIBDLL ', '')
  fdef = fdef.replace(';', '')

  m = re.search(r'(\w+) (\w+)\((.*)\)', fdef)
  (retval, fname, args) = m.groups()

  arglist = args.split(',')
  args = list()
  for a in arglist:
    a = a.strip()
    frags = a.split(' ')
    aname = frags.pop()
    if '_arr' in aname:
      a2 = a
      a2 = a2.replace('int* ', 'IntArrayContainer& ')
      a2 = a2.replace('double* ', 'RealArrayContainer& ')

      args.append(a2)
    else:
      m1 = re.search('cg_iRIC_Write_(.+_|)Functional', fname)
      m2 = re.search('cg_iRIC_Write_(.+_|)FunctionalWithName', fname)
      m3 = re.search('cg_iRIC_Write_BC_Indices', fname)
      m4 = re.search('cg_iRIC_Write_Sol_Particle_Pos', fname)

      if (m1 or m2 or m3) and aname == 'length':
        continue
      if (m4) and aname == 'count':
        continue

      args.append(a)
  
  return retval + " IRICLIBDLL " + fname + "(" + ", ".join(args) + ");\n"

def gen_wrapper_header():
  with open(os.path.join('..', 'iriclib_wrapper.h'), 'w', encoding='utf-8') as f_header:
    with open('iriclib_wrapper.h.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

    for filename in TARGET_FILES_WRAPPER:
      f_header.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if not 'IRICLIBDLL' in line: continue
          if not '_arr' in line: continue
          if 'RealSingle' in line: continue

          f_header.write(gen_wrapper_header_line(line))

      f_header.write("\n")

    with open('iriclib_wrapper.h.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

def gen_wrapper_source_content(fdef):
  fdef = fdef.replace('IRICLIBDLL ', '')
  fdef = fdef.replace(';', '')

  m = re.search(r'(\w+) (\w+)\((.*)\)', fdef)
  (retval, fname, args) = m.groups()

  arglist = args.split(',')
  iargs = list()
  oargs = list()
  for a in arglist:
    a = a.strip()
    frags = a.split(' ')
    aname = frags.pop()

    m1 = re.search('cg_iRIC_Write_(.+_|)Functional', fname)
    m2 = re.search('cg_iRIC_Write_(.+_|)FunctionalWithName', fname)
    m3 = re.search('cg_iRIC_Write_BC_Indices', fname)
    m4 = re.search('cg_iRIC_Write_Sol_Particle_Pos', fname)

    if (m1 or m2 or m3) and aname == 'length':
      continue
    if (m4) and aname == 'count':
      continue

    if '_arr' in aname:
      a2 = a
      a2 = a2.replace('int* ', 'IntArrayContainer& ')
      a2 = a2.replace('double* ', 'RealArrayContainer& ')

      iargs.append(a2)

      if m1 and aname == 'x_arr':
        oargs.append('x_arr.size()')

      if m2 and aname == 'v_arr':
        oargs.append('v_arr.size()')
      
      if m3 and aname == 'idx_arr':
        oargs.append('idx_arr.size()')

      if m4 and aname == 'x_arr':
        oargs.append('x_arr.size()')

      oargs.append(aname + '.pointer()')
    else:
      iargs.append(a)
      oargs.append(aname)

  content = retval + " " + fname + "(" + ", ".join(iargs) + ")\n"
  content += "{\n"

  if 'cg_iRIC_Write_BC_Indices' in fname and not ('cg_iRIC_Write_BC_Indices2' in fname):
    fname = fname.replace('cg_iRIC_Write_BC_Indices', 'cg_iRIC_Write_BC_Indices2')

  if retval == 'void':
    content += "\t" + fname + "(" + ", ".join(oargs) + ");\n"
  else:
    content += "\t" + "return " + fname + "(" + ", ".join(oargs) + ");\n"

  content += "}\n"
  content += "\n"
  return content

def gen_wrapper_source():
  with open(os.path.join('..', 'iriclib_wrapper.cpp'), 'w', encoding='utf-8') as f_header:
    with open('iriclib_wrapper.cpp.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

    for filename in TARGET_FILES_WRAPPER:
      f_header.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if not 'IRICLIBDLL' in line: continue
          if not '_arr' in line: continue
          if 'RealSingle' in line: continue

          f_header.write(gen_wrapper_source_content(line))

      f_header.write("\n")

    with open('iriclib_wrapper.cpp.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)


def gen_wrapper():
  gen_wrapper_header()
  gen_wrapper_source()
