# README-issue-18

## Abstract

I've used the new FileLocker class to lock CGNS file, to avoid the situation
that solver and iRIC GUI access the same CGNS file at the same timing, but
the File Locker did not work correctly.

So I've added two additional test programs:

* unittest_cg_open_modify
* unittest_cg_open_read

## unittest_cg_open_modify

This programs works like a solver. It opens CGNS file, repeats calling:

```
iRIC_Write_Sol_Start() // this calls FileLocker::lock()

cg_iRIC_Write_Sol_xxx()
...
cg_iRIC_Flush()

iRIC_Write_Sol_End() // this calls FileLocker::unlock()
```

## unittest_cg_open_read

This programs works like the iRIC GUI. It tries to lock the CGNS file,
opens CGNS file in read-only mode, and read the result.

## How to test

* Build unittest_cg_open_modify and unittest_cg_open_read, and
  put them to the same folder. 

* Copy case_read_hdf5.cgn in master branch to the folder above,
  and rename it to Case1.cgn

* Start unittest_cg_open_modify first. See that message like "Sol written 0" is shown

* Start unittest_cg_open_read, in another command prompt, just after message
  "iRIC_Write_Sol_Start() succeeded" is shown in the command prompt above.

Then, in unittest_cg_open_read calls, `iRIC_Write_Sol_Start()` and it does not
wait the call of `iRIC_Write_Sol_End()` in unittest_cg_open_modify, immediately
tries to call `cg_open()`, and message "cg_open() failed" is shown.

## TODO

So, the current implementation of FileLocker is incomplete. It succeed to lock
the file at the first time only. When lock(), unlock(), lock() is called,
the second lock() does not work correctly.

I have to fix this.
