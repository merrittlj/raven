#ifndef APP_COMMON_HPP
#define APP_COMMON_HPP


#include "app/app_conf.h"
#include "hw/common.hpp"

#include <cstddef>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


/* Basic definitions */
#undef NULL
#define NULL                    0

#undef FALSE
#define FALSE                   0

#undef TRUE
#define TRUE                    (!0)

/* Critical Section definition */
#define BACKUP_PRIMASK()    uint32_t primask_bit= __get_PRIMASK()
#define DISABLE_IRQ()       __disable_irq()
#define RESTORE_PRIMASK()   __set_PRIMASK(primask_bit)

/* Macro delimiters */
#define M_BEGIN     do {

#define M_END       } while(0)

/* Some useful macro definitions */
#ifndef MAX
#define MAX(x, y)          (((x)>(y))?(x):(y))
#endif

#ifndef MIN
#define MIN(x, y)          (((x)<(y))?(x):(y))
#endif

#define MODINC(a, m)       M_BEGIN  (a)++;  if ((a)>=(m)) (a)=0;  M_END

#define MODDEC(a, m)       M_BEGIN  if ((a)==0) (a)=(m);  (a)--;  M_END

#define MODADD(a, b, m)    M_BEGIN  (a)+=(b);  if ((a)>=(m)) (a)-=(m);  M_END

#define MODSUB(a, b, m)    MODADD( a, (m)-(b), m )

#define PAUSE(t)           M_BEGIN \
    __IO int _i; \
    for ( _i = t; _i > 0; _i -- ); \
    M_END

#define DIVF(x, y)         ((x)/(y))

#define DIVC(x, y)         (((x)+(y)-1)/(y))

#define DIVR(x, y)         (((x)+((y)/2))/(y))

#define SHRR(x, n)         ((((x)>>((n)-1))+1)>>1)

#define U32 uint32_t

#define BITN(w, n)         (((w)[(n)/32] >> ((n)%32)) & 1)

#define BITNSET(w, n, b)   M_BEGIN (w)[(n)/32] |= ((U32)(b))<<((n)%32); M_END

#define READ_BIT(var, pos) (((var) >> (pos)) & 1U)
#define SET_BIT(var, pos) ((var) |= (1U << (pos)))
#define CLEAR_BIT(var, pos) ((var) &= ~(1U << (pos)))

#define VariableBit_Reset_BB(VariableAddress, BitNumber) \
    (*(volatile uint32_t *) (RAM_BB_BASE | ((VariableAddress - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
#define VariableBit_Set_BB(VariableAddress, BitNumber) \
    (*(volatile uint32_t *) (RAM_BB_BASE | ((VariableAddress - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)
#define VariableBit_Get_BB(VariableAddress, BitNumber) \
    (*(volatile uint32_t *) (RAM_BB_BASE | ((VariableAddress - RAM_BASE) << 5) | ((BitNumber) << 2)))

template <typename C, typename Arg, void (C::*M)(Arg)>
void AsFunc(void* p, Arg arg)
{
    (static_cast<C*>(p)->*M)(arg);
}

/* Compiler */
#define PLACE_IN_SECTION( __x__ )  __attribute__((section (__x__)))

#ifdef WIN32
#define ALIGN(n)
#else
#define ALIGN(n)             __attribute__((aligned(n)))
#endif


#endif /* APP_COMMON_HPP */
