del _iric.pyd
del _iric.py
swig -c++ -python -cppext cpp iric.i
cl /LD iric_wrap.cpp ^
  -I"D:\miniconda3\envs\iric\include" ^
  -I"..\..\src" ^
  -I "D:\iRIC\dev_vc2013_64\iricdev\lib\install\cgnslib-3.2.1-patch1\release\include" ^
  "D:miniconda3\envs\iric\libs\python39.lib" ^
  "..\release\iriclib.lib" ^
  "D:\iRIC\dev_vc2013_64\iricdev\lib\install\cgnslib-3.2.1-patch1\release\lib\cgnsdll.lib"

rename iric_wrap.dll _iric.pyd
del iric_wrap.lib
del iric_wrap.obj
del iric_wrap.exp

copy iric_custom.py D:\miniconda3\envs\iric\Lib\site-packages\iric.py
copy _iric.pyd D:\miniconda3\envs\iric\Lib\site-packages\_iric.pyd
