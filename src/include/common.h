/*
 * filename:	common.h
 * date:	04.17.24
 * author:	Lucas Merritt/merrittlj
 * description:	commonly used macros, typedefs, etc. NOT related at all to any modules
 */


/* #define _NOP (asm("nop")) */
#define _NOP ((void) 0)
typedef void (*func_ptr)(void);
