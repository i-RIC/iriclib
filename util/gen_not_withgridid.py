import os

from gen_code_util import build_call_line

TARGET_FILES_NOT_WITHGRIDID = [
  'iriclib_bc.h',
  'iriclib_complex.h',
  'iriclib_grid.h',
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

def gen_not_withgridid_header_line(withgridid_def):
  ret = withgridid_def
  ret = ret.replace(', int gid', '')
  ret = ret.replace('_WithGridId', '')
  return ret

def gen_not_withgridid_header_line_writegrid(withgridid_def):
  ret = withgridid_def
  ret = ret.replace(', int* gid', '')
  ret = ret.replace('_WithGridId', '')
  return ret

def gen_not_withgridid_header():
  with open(os.path.join('..', 'iriclib_not_withgridid.h'), 'w', encoding='utf-8') as f_header:
    with open('iriclib_not_withgridid.h.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

    for filename in TARGET_FILES_NOT_WITHGRIDID:
      f_header.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line and 'WithGridId' in line:
            if 'WriteGridCoord' in line:
              newline = gen_not_withgridid_header_line_writegrid(line)
            else:
              newline = gen_not_withgridid_header_line(line)

            f_header.write(newline)
      f_header.write("\n")

    with open('iriclib_not_withgridid.h.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

def gen_not_withgridid_source_content(withgridid_def):
  ret_is_void = 'void ' in withgridid_def

  content = ''
  content += withgridid_def.replace(';', '').replace('IRICLIBDLL ', '') \
    .replace(', int gid', '').replace('_WithGridId', '')
  content += "{\n"
  content += "  int gid;\n"

  if not ret_is_void:
    content += "  int ier = getlastGridId(fid, &gid);\n"
    content += "  RETURN_IF_ERR;\n"
  else:
    content += "  getlastGridId(fid, &gid);\n"

  content += "\n"
  if ret_is_void:
    content += "  " + build_call_line(withgridid_def) + ";\n"
  else:
    content += "  return " + build_call_line(withgridid_def) + ";\n"
  content += "}\n"
  content += "\n"

  return content

def gen_not_withgridid_source_content_writegrid(withgridid_def):
  content = ''
  content += withgridid_def.replace(';', '').replace('IRICLIBDLL ', '') \
    .replace(', int* gid', '').replace('_WithGridId', '')
  content += "{\n"
  content += "  int gid;\n"
  content += "\n"

  call_line = build_call_line(withgridid_def)
  call_line = call_line.replace(', gid', ', &gid')

  content += "  return " + call_line + ";\n"
  content += "}\n"
  content += "\n"

  return content

def gen_not_withgridid_source():
  with open(os.path.join('..', 'iriclib_not_withgridid.cpp'), 'w', encoding='utf-8') as f_source:
    with open('iriclib_not_withgridid.cpp.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

    for filename in TARGET_FILES_NOT_WITHGRIDID:
      f_source.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line and 'WithGridId' in line:
            if 'WriteGridCoord' in line:
              content = gen_not_withgridid_source_content_writegrid(line)
            else:
              content = gen_not_withgridid_source_content(line)

            f_source.write(content)
      f_source.write("\n")

    with open('iriclib_not_withgridid.cpp.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

def gen_not_withgridid():
  gen_not_withgridid_header()
  gen_not_withgridid_source()
