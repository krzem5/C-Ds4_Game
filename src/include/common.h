#ifndef COMMON_H
#define COMMON_H
#define COBJMACROS
#include <windows.h>
#include <d3d11_1.h>
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
typedef ID3D11ShaderResourceView* Texture;
typedef struct _FONT* Font;
typedef struct _FONT_CHARACTER FontCharacter;
typedef struct _RENDERED_TEXT* RenderedText;



struct _RAW_TEXTURE{
	uint32_t f;
	uint32_t w;
	uint32_t h;
	uint32_t p;
	uint32_t sp;
	const uint8_t* dt;
};



struct _FONT{
	Texture _t;
	uint8_t _l;
	float* _dt;
};



struct _FONT_CHARACTER{
	char ch;
	uint8_t w;
	float ua;
	float va;
	float ub;
	float vb;
};



struct _RENDERED_TEXT{
	Texture _t;
	uint32_t _il;
	ID3D11Buffer* _vb;
	ID3D11Buffer* _ib;
};



#endif
