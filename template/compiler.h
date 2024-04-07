#ifndef __COMPILER_H__
#define __COMPILER_H__

#define no_inline       __attribute__ ((noinline))
#define always_inline   inline __attribute__ ((__always_inline__))

#endif /* __COMPILER_H__ */