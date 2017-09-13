# README

This is the unit test for the new implementation of the following two
functions:

* iRIC_Write_Sol_Start()
* iRIC_Write_Sol_End()

The new functions of these two are something unique, so I could not 
just add case to unittests_cgnsfile, but created a separate unit test.

## How to test

1. Launch two shells (or command prompt)
2. Start unittest_lock in one window --> iRIC_Write_Sol_Start() is called, 
   and it will sleep for 10 seconds
3. Start unittest_lock in another window within 10 seconds --> iRIC_Write_Sol_Start()
   is called, but it will wait until iRIC_Write_Sol_End() is called in the unittest_lock
   that is launched in the first shell.

If it behave like above, the test is successful. If some error occurs in
the functions, or iRIC_Write_Sol_Start() in the second shell does not wait for
iRIC_Write_Sol_End() call in the first shell, the test is a failure.
