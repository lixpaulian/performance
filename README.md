# performance
A project to evaluate the performance of different compilers. The industry wants us to believe that commercial compilers generate faster and more compact code than gcc.

The project is still work in progress. For now there is a (not yet finalized) comparison of gcc vs IAR which includes the standard coremark 1.0 benchmark and a separate, smaller test implementing an XXTEA encryption/decryption algorithm. The initial results show that, as expected, the IAR was slightly faster on the coremark 1.0 benchmark, but massively slower on the XXTEA benchmark. I have no idea yet why, but the next step is to time individual parts of the coremark benchmark to find out where are the differences coming from. You will notice there are two separate file sets for the coremark test, the standard ones and the _timed.c variants. A microsecond tick obtained from a 32-bit timer is used for timing various sections of code.

The tests are run on the STM32F746-DISCOVERY board from ST.

