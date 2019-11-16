import os
import re

from gen_code_util import build_call_line

TARGET_FILES_NOT_MUL = [
  'iriclib_bc.h',
  'iriclib_cc.h',
  'iriclib_complex.h',
  'iriclib_geoutil.h',
  'iriclib_grid.h',
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

def gen_not_mul_header_line(mul_def):
  ret = mul_def
  ret = ret.replace('int fid, ', '')
  ret = ret.replace('int fid', '')
  ret = ret.replace('_Mul', '')
  return ret

def gen_not_mul_header():
  with open(os.path.join('..', 'iriclib_not_mul.h'), 'w', encoding='utf-8') as f_header:
    with open('iriclib_not_mul.h.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

    for filename in TARGET_FILES_NOT_MUL:
      f_header.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line and '_Mul' in line:
            newline = gen_not_mul_header_line(line)
            f_header.write(newline)
      f_header.write("\n")

    with open('iriclib_not_mul.h.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

def gen_not_mul_source_content(withmul_def):
  ret_is_void = 'void ' in withmul_def

  content = ''
  content += withmul_def.replace(';', '').replace('IRICLIBDLL ', '') \
    .replace('int fid, ', '').replace('int fid', '').replace('_Mul', '')
  content += "{\n"
  content += "  int fid;\n"

  if not ret_is_void:
    content += "  int ier = _iric_lastFileId(&fid);\n"
    content += "  RETURN_IF_ERR;\n"
  else:
    content += "  _iric_lastFileId(&fid);\n"
  content += "\n"

  if not ret_is_void:
    content += "  return " + build_call_line(withmul_def) + ";\n"
  else:
    content += "  " + build_call_line(withmul_def) + ";\n"
  content += "}\n"
  content += "\n"

  return content

def gen_not_mul_source():
  with open(os.path.join('..', 'iriclib_not_mul.cpp'), 'w', encoding='utf-8') as f_source:
    with open('iriclib_not_mul.cpp.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

    for filename in TARGET_FILES_NOT_MUL:
      f_source.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line and '_Mul' in line:
            content = gen_not_mul_source_content(line)

            f_source.write(content)
      f_source.write("\n")

    with open('iriclib_not_mul.cpp.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

def gen_not_mul():
  gen_not_mul_header()
  gen_not_mul_source()
