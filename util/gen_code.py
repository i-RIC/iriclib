import os
import re

from gen_ftoc import gen_ftoc
from gen_not_withbaseid import gen_not_withbaseid
from gen_not_withgridid import gen_not_withgridid
from gen_wrapper import gen_wrapper
from gen_swig import gen_swig
from gen_f90 import gen_f90

if __name__ == "__main__":
  gen_not_withgridid()
  gen_not_withbaseid()
  gen_ftoc()
  gen_wrapper()
  gen_swig()
  gen_f90()
