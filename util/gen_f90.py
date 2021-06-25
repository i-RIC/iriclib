import os
import re

TARGET_FILES_F90 = [
  'iriclib_bc.h',
  'iriclib_cc.h',
  'iriclib_complex.h',
  'iriclib_geo.h',
  'iriclib_geoutil.h',
  'iriclib_grid.h',
  'iriclib_grid_solverlib.h',
  'iriclib_gui_coorp.h',
  'iriclib_init.h',
  'iriclib_not_withbaseid.h',
  'iriclib_not_withgridid.h',
  'iriclib_solution.h',
  'iriclib_sol_cell.h',
  'iriclib_sol_gridcoord.h',
  'iriclib_sol_iface.h',
  'iriclib_sol_jface.h',
  'iriclib_sol_kface.h',
  'iriclib_sol_node.h',
  'iriclib_sol_particle.h',
  'iriclib_sol_particlegroup.h',
  'iriclib_sol_polydata.h',
]

def _gen_f90_interface_content(fname_lower, dims):
  cont = '  ' + "interface " + fname_lower + "\n"
  for dim in dims:
    cont += "    " + "module procedure " + fname_lower + "_{0}d".format(dim) + "\n"
  cont += "  " + "end interface" + "\n"
  cont += "\n"
  return cont

def gen_f90_interface_content(fdef):
  ret_is_void = 'void ' in fdef

  defstr = fdef
  defstr = defstr.replace('IRICLIBDLL ', '')
  defstr = defstr.replace(';', '')
  m = re.search(r'(\w+) (\w+)\((.*)\)', defstr)

  (retval, fname, args) = m.groups()
  fname_lower = fname.lower()

  if fname_lower == 'cg_iric_read_grid2d_cellarea': return ""
  if fname_lower == 'cg_iric_read_grid2d_findcell': return ""
  if fname_lower == 'cg_iric_read_grid2d_interpolatewithcell': return ""

  if ('node' in fname_lower or 'cell' in fname_lower or 'iface' in fname_lower or 'jface' in fname_lower or 'kface' in fname_lower) and not ('count' in fname_lower):
    return _gen_f90_interface_content(fname_lower, range(1, 4))

  if '_grid2d_coords' in fname_lower:
    return _gen_f90_interface_content(fname_lower, [1, 2])

  if '_grid3d_coords' in fname_lower:
    return _gen_f90_interface_content(fname_lower, [1, 3])

  return ""

def _gen_f90_source_content(fdef, dim):
  ret_is_void = 'void ' in fdef

  defstr = fdef
  defstr = defstr.replace('IRICLIBDLL ', '')
  defstr = defstr.replace(';', '')
  m = re.search(r'(\w+) (\w+)\((.*)\)', defstr)

  (retval, fname, args) = m.groups()

  arglist = args.split(',')

  while '' in arglist:
    arglist.remove('')

  if ("Size2" in fname): return ""

  fname_lower = fname.lower()
  argNames = list()
  argDefs = list()

  if dim is None:
    dimstr = ':'
  else:
    dimstr = ','.join([':'] * dim)

  for a in arglist:
    a = a.strip()
    frags = a.split(' ')
    aname = frags.pop()
    f = " ".join(frags)

    argNames.append(aname)

    if f == 'int':
      argDefs.append('integer, intent(in):: ' + aname)

    elif f == 'int*':
      if '_arr' in aname:
        if 'read' in fname_lower:
          argDefs.append('integer, dimension({0}), intent(out):: '.format(dimstr) + aname)
        elif 'write' in fname_lower:
          argDefs.append('integer, dimension({0}), intent(in):: '.format(dimstr) + aname)
        else:
          print('ERROR unexpected for ' + fname)
      else:
        argDefs.append('integer, intent(out):: ' + aname)

    elif f == 'float':
      argDefs.append('real, intent(in):: ' + aname)

    elif f == 'float*':
      if '_arr' in aname:
        if 'read' in fname_lower:
          argDefs.append('real, dimension({0}), intent(out):: '.format(dimstr) + aname)
        elif 'write' in fname_lower:
          argDefs.append('real, dimension({0}), intent(in):: '.format(dimstr) + aname)
        else:
          print('ERROR unexpected for ' + fname)
      else:
        argDefs.append('real, intent(out):: ' + aname)

    elif f == 'double':
      argDefs.append('double precision, intent(in):: ' + aname)

    elif f == 'double*':
      if '_arr' in aname:
        if 'read' in fname_lower:
          argDefs.append('double precision, dimension({0}), intent(out):: '.format(dimstr) + aname)
        elif 'write' in fname_lower:
          argDefs.append('double precision, dimension({0}), intent(in):: '.format(dimstr) + aname)
        else:
          print('ERROR unexpected for ' + fname)
      else:
        argDefs.append('double precision, intent(out):: ' + aname)

    elif f == 'char*':
      argDefs.append('character(*), intent(out):: ' + aname)
    
    elif f == 'const char*':
      argDefs.append('character(*), intent(in):: ' + aname)

    elif f == '':
      continue

    else:
      print('unknown <' + aname + ">")
  
  if not ret_is_void:
    argNames.append('ier')
    argDefs.append('integer, intent(out):: ier')

  content = "  " + "subroutine " + fname_lower
  if not dim is None:
    content += '_{0}d'.format(dim)
  content += "(" + ", ".join(argNames) + ")\n"

  for argDef in argDefs:
    content += "    " + argDef + "\n"

  content += "\n"
  content += "    " + "call " + fname_lower + "_f2c &\n"
  content += "      (" + ", ".join(argNames) + ")\n"
  content += "\n"
  content += "  " + "end subroutine\n"
  content += "\n"

  return content

def gen_f90_source_content(fdef):
  ret_is_void = 'void ' in fdef

  defstr = fdef
  defstr = defstr.replace('IRICLIBDLL ', '')
  defstr = defstr.replace(';', '')
  m = re.search(r'(\w+) (\w+)\((.*)\)', defstr)

  (retval, fname, args) = m.groups()
  fname_lower = fname.lower()

  if \
  fname_lower == 'cg_iric_read_grid2d_cellarea' or \
  fname_lower == 'cg_iric_read_grid2d_findcell' or \
  fname_lower == 'cg_iric_read_grid2d_interpolatewithcell':

    return _gen_f90_source_content(fdef, None)

  if ('node' in fname_lower or 'cell' in fname_lower or 'iface' in fname_lower or 'jface' in fname_lower or 'kface' in fname_lower) and not ('count' in fname_lower):
    cont = ''
    for dim in range(1, 4):
      cont += _gen_f90_source_content(fdef, dim)
    return cont

  if '_grid2d_coords' in fname_lower:
    cont = ''
    for dim in [1, 2]:
      cont += _gen_f90_source_content(fdef, dim)
    return cont

  if '_grid3d_coords' in fname_lower:
    cont = ''
    for dim in [1, 3]:
      cont += _gen_f90_source_content(fdef, dim)
    return cont

  return _gen_f90_source_content(fdef, None)

def gen_f90():
  pass
  with open(os.path.join('..', 'iric.f90'), 'w', encoding='utf-8') as f_source:
    with open('iric.f90.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

    interfaces = list()
    sources = list()

    for filename in TARGET_FILES_F90:
      sources.append("\n")
      sources.append("  ! from {0}\n".format(filename))
      sources.append("\n")

      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line:
            # functions with "WithBaseId" cause error, because the symbol has too many characters.
            if 'WithBaseId' in line: continue 

            interfaces.append(gen_f90_interface_content(line))
            sources.append(gen_f90_source_content(line))

      sources.append("\n")

    for interface in interfaces:
      f_source.write(interface)

    f_source.write("\n")
    f_source.write("contains\n")
    f_source.write("\n")

    for source in sources:
      f_source.write(source)

    with open('iric.f90.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)
