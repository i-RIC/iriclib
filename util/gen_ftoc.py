import os
import re

TARGET_FILES_FTOC = [
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

def gen_ftoc_source_content(fdef):
  ret_is_void = 'void ' in fdef

  defstr = fdef
  defstr = defstr.replace('IRICLIBDLL ', '')
  defstr = defstr.replace(';', '')
  m = re.search(r'(\w+) (\w+)\((.*)\)', defstr)

  (retval, fname, args) = m.groups()

  arglist = args.split(',')

  if ("Size2" in fname): return ""

  content = "void IRICLIBDLL FMNAME(" + fname.lower() + "_f2c, " + fname.upper() + "_F2C)"
  args = list()
  iargs = list()

  input_chars = list()
  output_chars = list()
  output_charps = list()

  str_lenargs = ''

  for a in arglist:
    a = a.strip()
    frags = a.split(' ')
    aname = frags.pop()
    f = " ".join(frags)

    if f == 'int':
      args.append('int* ' + aname)
      iargs.append("*" + aname)

    elif f == 'int*':
      args.append('int* ' + aname)
      iargs.append(aname)

    elif f == 'float':
      args.append('float* ' + aname)
      iargs.append("*" + aname)

    elif f == 'float*':
      args.append('float* ' + aname)
      iargs.append(aname)

    elif f == 'double':
      args.append('double* ' + aname)
      iargs.append("*" + aname)

    elif f == 'double*':
      args.append('double* ' + aname)
      iargs.append(aname)

    elif f == 'char*':
      args.append('STR_PSTR(' + aname + ')')
      iargs.append('c_' + aname)
      str_lenargs += ' STR_PLEN(' + aname + ')'
      output_chars.append(aname)
    
    elif f == 'const char*':
      args.append('STR_PSTR(' + aname + ')')
      iargs.append('c_' + aname)
      str_lenargs += ' STR_PLEN(' + aname + ')'
      input_chars.append(aname)

    elif f == 'const char**':
      args.append('STR_PSTR(' + aname + ')')
      iargs.append('&ptr_' + aname)
      str_lenargs += ' STR_PLEN(' + aname + ')'
      output_charps.append(aname)

    elif f == '':
      continue

    else:
      print('unknown <' + a + ">")
  
  if not ret_is_void:
    args.append('int *ier')

  content += " (" + ", ".join(args) + str_lenargs + ") {\n"

  ier = "*ier"
  ierpointer = "ier"
  if ret_is_void and (len(input_chars) > 0 or len(output_chars) > 0):
    content += "\t" + "int ier;\n"
    content += "\n"
    ier = "ier"
    ierpointer = "&ier"
  
  for c in input_chars:
    content += "\t" + "char c_" + c + "[STRINGMAXLEN + 1];\n"
  for c in output_chars:
    content += "\t" + "char c_" + c + "[STRINGMAXLEN + 1];\n"
  for c in output_charps:
    content += "\t" + "char c_" + c + "[STRINGMAXLEN + 1];\n"
    content += "\t" + "const char* ptr_" + c + ";\n"

  for c in input_chars:
    content += "\t" + "string_2_C_string(STR_PTR(" + c + "), STR_LEN(" + c + "), c_" + c + ", STRINGMAXLEN, " + ierpointer + ");\n"
    content += "\t" + "if (" + ier + " != 0) return;\n"
  
  if len(input_chars) > 0:
    content += "\n"

  if ret_is_void:
    content += "\t" + fname + "(" + ", ".join(iargs) + ");\n"
  else:
    content += "\t" + "*ier = " + fname + "(" + ", ".join(iargs) + ");\n"

  if len(output_chars) > 0:
    content += "\n"

  for c in output_chars:
    content += "\t" + "if (" + ier + " != 0) return;\n"
    content += "\t" + "string_2_F_string(c_" + c + ", STR_PTR(" + c + "), STR_LEN(" + c + "), " + ierpointer + ");\n"

  for c in output_charps:
    content += "\t" + "if (" + ier + " != 0) return;\n"
    content += "\t" + "strncpy(c_" + c + ", ptr_" + c + ", STRINGMAXLEN);\n"
    content += "\t" + "string_2_F_string(c_" + c + ", STR_PTR(" + c + "), STR_LEN(" + c + "), " + ierpointer + ");\n"

  content += "}\n"
  content += "\n"

  return content

def gen_ftoc():
  pass
  with open(os.path.join('..', 'iriclib_ftoc.cpp'), 'w', encoding='utf-8') as f_source:
    with open('iriclib_ftoc.cpp.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

    for filename in TARGET_FILES_FTOC:
      f_source.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line:
            content = gen_ftoc_source_content(line)

            f_source.write(content)
      f_source.write("\n")

    with open('iriclib_ftoc.cpp.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)
