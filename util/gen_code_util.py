import re

def build_call_line(withgridid_def):
  defstr = withgridid_def
  defstr = defstr.replace('IRICLIBDLL ', '')
  defstr = defstr.replace(';', '')
  m = re.search(r'(\w+) (\w+)\((.+)\)', defstr)
  (retval, fname, args) = m.groups()
  arglist = args.split(',')
  arglist2 = list()
  for a in arglist:
    frags = a.split(' ')
    arglist2.append(frags.pop())

  return fname + '(' + ', '.join(arglist2) + ')'
