del _iric.pyd
del _iric.py
swig -c++ -python -cppext cpp iric.i
cl /LD iric_wrap.cpp ^
  -I"D:\iRIC_dev\Miniconda3\envs\iric_hdf5\include" ^
  "D:\iRIC_dev\Miniconda3\envs\iric_hdf5\libs\python38.lib" ^
  "..\release\iriclib.lib" ^
  "..\cgnslib_dummy\release\cgnsdll.lib"

rename iric_wrap.dll _iric.pyd
del iric_wrap.lib
del iric_wrap.obj
del iric_wrap.exp

copy iric_custom.py D:\iRIC_dev\Miniconda3\envs\iric_hdf5\Lib\site-packages\iric.py
copy _iric.pyd D:\iRIC_dev\Miniconda3\envs\iric_hdf5\Lib\site-packages\_iric.pyd
