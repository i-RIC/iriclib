# README

This is the unit test for the new implementation of the following two
functions:

* iRIC_Write_Sol_Start()
* iRIC_Write_Sol_End()

The new functions of these two are something unique, so I could not 
just add case to unittests_cgnsfile, but created a separate unit test.

## How to test

* Build unittest_cg_open_modify and unittest_cg_open_read, and
  put them to the same folder. 

* Copy case_read_hdf5.cgn in master branch to the folder above,
  and rename it to Case1.cgn

* Start unittest_cg_open_modify first. See that message like "Sol written 0" is shown

* Start unittest_cg_open_read, in another command prompt, just after message
  "iRIC_Write_Sol_Start() succeeded" is shown in the command prompt above.

Then, in unittest_cg_open_read calls, `iRIC_Write_Sol_Start()` and it waits
the call of `iRIC_Write_Sol_End()` in unittest_cg_open_modify, and call `cg_open()`.

And, unittest_cg_open_modify waits until `iRIC_Write_Sol_End()` in unittest_cg_open_read
is called.

