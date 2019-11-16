import os

from gen_code_util import build_call_line

TARGET_FILES_NOT_WITHBASEID = [
  'iriclib_complex.h',
]

def gen_not_withbaseid_header_line(withbaseid_def):
  ret = withbaseid_def
  ret = ret.replace(', int bid', '')
  ret = ret.replace('_WithBaseId', '')
  return ret

def gen_not_withbaseid_header():
  with open(os.path.join('..', 'iriclib_not_withbaseid.h'), 'w', encoding='utf-8') as f_header:
    with open('iriclib_not_withbaseid.h.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

    for filename in TARGET_FILES_NOT_WITHBASEID:
      f_header.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line and 'WithBaseId' in line:
            newline = gen_not_withbaseid_header_line(line)

            f_header.write(newline)
      f_header.write("\n")

    with open('iriclib_not_withbaseid.h.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_header.write(l)

def gen_not_withbaseid_source_content(withbaseid_def):
  content = ''
  content += withbaseid_def.replace(';', '').replace('IRICLIBDLL ', '') \
    .replace(', int bid', '').replace('_WithBaseId', '')
  content += "{\n"
  content += "  int bid = 1;\n"
  content += "\n"
  content += "  return " + build_call_line(withbaseid_def) + ";\n"
  content += "}\n"
  content += "\n"

  return content

def gen_not_withbaseid_source():
  with open(os.path.join('..', 'iriclib_not_withbaseid.cpp'), 'w', encoding='utf-8') as f_source:
    with open('iriclib_not_withbaseid.cpp.header.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

    for filename in TARGET_FILES_NOT_WITHBASEID:
      f_source.write("// from {0}\n".format(filename))
      with open(os.path.join('..', filename), 'r', encoding='utf-8') as f:
        for line in f:
          if 'IRICLIBDLL' in line and 'WithBaseId' in line:
            content = gen_not_withbaseid_source_content(line)

            f_source.write(content)
      f_source.write("\n")

    with open('iriclib_not_withbaseid.cpp.footer.txt', 'r', encoding='utf-8') as f:
      for l in f:
        f_source.write(l)

def gen_not_withbaseid():
  gen_not_withbaseid_header()
  gen_not_withbaseid_source()
