#ifndef COMMON_H
#define COMMON_H
#include <signal.h>
#include <stdint.h>
#include <limits.h>



#define bool _Bool
#define false 0
#define true 1
#ifdef NULL
#undef NULL
#endif
#define NULL ((void*)0)
#define assert(x) \
	do{ \
		if (!(x)){ \
			printf("%s:%i (%s): %s: Assertion Failed\n",__FILE__,__LINE__,__func__,#x); \
			raise(SIGABRT); \
		} \
	} while (0)



typedef struct _RAW_TEXTURE RawTexture;
typedef struct _FONT* Font;
typedef struct _FONT_CHARACTER FontCharacter;



struct _RAW_TEXTURE{
	int f;
	uint64_t r;
	uint64_t sz;
	const uint8_t* dt;
};



struct _FONT{
	uint8_t _l;
};



struct _FONT_CHARACTER{
	char ch;
	uint8_t w;
	float ua;
	float va;
	float ub;
	float vb;
};



#endif
