#if !defined(__NO_LIBRARY_ATTRIBUTES__)
.FILE_ATTR  libGroup      = myfilter.h;
.FILE_ATTR  libFunc       = __cyc_test_t2;
.FILE_ATTR  libFunc       = cyc_test_t2;
.FILE_ATTR  libName       = libdsp;
.FILE_ATTR  prefersMem    = internal;
.FILE_ATTR  prefersMemNum = "30";
.FILE_ATTR  FuncName      = __cyc_test_t2;
#endif

.GLOBAL __cyc_test_t2;
.TYPE   __cyc_test_t2,STT_FUNC;

.SECTION/DOUBLEANY program;
.ALIGN 2;

__cyc_test_t2:

	  [--SP] = (R7:4);
      R7 = SYSCFG;
      BITCLR(R7,1);
      SYSCFG = R7;
      (R7:4) = [SP++];
      RTS;

.__cyc_test_t2.end: