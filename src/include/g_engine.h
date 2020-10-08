#ifndef GENGINE_H
#define GENGINE_H
#include <common.h>
#include <d3d11_1.h>



#define GENGINE_2PI ((float)6.283185307f)
#define GENGINE_PI ((float)3.141592654f)
#define GENGINE_PIDIV2 ((float)1.570796327f)
#define GENGINE_PIDIV4 ((float)0.785398163f)
#define GENGINE_1DIVPI ((float)0.318309886f)
#define GENGINE_1DIV2PI ((float)0.159154943f)
#define GENGINE_PIDIV180 ((float)0.017453293f)
#define GENGINE_60_FPS ((float)0.016666666f)
#define GEngine_raw_vector(x,y,z,w) ((RawVector){(x),(y),(z),(w)})
#define GEngine_raw_identity_matrix() ((RawMatrix){1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1})
#define GEngine_raw_matrix(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) ((RawMatrix){(a),(b),(c),(d),(e),(f),(g),(h),(i),(j),(k),(l),(m),(n),(o),(p)})
#define GEngine_as_raw_matrix(m) (*((RawMatrix*)(m)))
#define GEngine_pos_from_camera(c) ((RawVector){(c)->x,(c)->y,(c)->z,1})
#define GEngine_free_matrix(m) ((m)!=NULL?(free((m)),NULL):NULL)
#define GEngine_animation_finished(a) ((a)->_c==true)
#define GEngine_draw_model_all(m) \
	do{ \
		for (uint8_t __i=0;__i<m->ll;__i++){ \
			GEngine_draw_model(m,__i); \
		} \
	} while (0)



struct _VECTOR;
struct _MATRIX;
struct _CAMERA;
struct _OBJECT_BUFFER;
struct _MODEL;
struct _ANIMATION;
struct _ANIMATOR;



typedef uint32_t VertexShader;
typedef uint32_t PixelShader;
typedef uint32_t ConstantBuffer;
typedef struct _VECTOR* Vector;
typedef struct _VECTOR RawVector;
typedef struct _MATRIX* Matrix;
typedef struct _MATRIX RawMatrix;
typedef struct _CAMERA* Camera;
typedef struct _OBJECT_BUFFER* ObjectBuffer;
typedef struct _MODEL* Model;
typedef struct _ANIMATION* Animation;
typedef struct _ANIMATOR* Animator;
typedef D3D11_INPUT_ELEMENT_DESC VS_INPUT_LAYOUT;
typedef void (*GEngine_init_func)(void);
typedef void (*GEngine_render_func)(double dt);



enum SHADER_DATA_TYPE{
	SHADER_DATA_TYPE_CONSTANT_BUFFER=0x01,
	SHADER_DATA_TYPE_TEXTURE=0x02,
	SHADER_DATA_TYPE_SAMPLER_STATE=0x03
};



enum SHADER_DATA_FLAGS{
	SHADER_DATA_FLAG_VS=0x01,
	SHADER_DATA_FLAG_PS=0x02
};



enum _ANIMATION_BONE_FLAG{
	_ANIMATION_BONE_FLAG_X=0x01,
	_ANIMATION_BONE_FLAG_Y=0x02,
	_ANIMATION_BONE_FLAG_Z=0x04,
	_ANIMATION_BONE_FLAG_RX=0x08,
	_ANIMATION_BONE_FLAG_RY=0x10,
	_ANIMATION_BONE_FLAG_RZ=0x20
};



struct _VECTOR{
	float x;
	float y;
	float z;
	float w;
};



struct _MATRIX{
	float _00;
	float _01;
	float _02;
	float _03;
	float _10;
	float _11;
	float _12;
	float _13;
	float _20;
	float _21;
	float _22;
	float _23;
	float _30;
	float _31;
	float _32;
	float _33;
};



struct _CAMERA{
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
	float ms;
	float rs;
	bool lock;
	bool enabled;
	bool _fs;
	float _dx;
	float _dy;
	float _dz;
	float _drx;
	float _dry;
	float _drz;
};



struct _OBJECT_BUFFER{
	uint32_t vll;
	float* vl;
	uint32_t ill;
	uint32_t* il;
	uint32_t st;
	ID3D11Buffer* _vb;
	ID3D11Buffer* _ib;
};



struct _MODEL_BONE{
	uint8_t nml;
	char* nm;
	float l;
	float* dt;
	float* t;
	uint32_t wil;
	uint16_t* il;
	float* wl;
	uint8_t cl;
	struct _MODEL_BONE* c;
};



struct _MODEL_LAYER{
	uint8_t nml;
	char* nm;
	uint8_t bl;
	struct _MODEL_BONE* b;
	ConstantBuffer m_cb;
	uint32_t dtll;
	uint32_t ill;
	float* dtl;
	uint16_t* il;
	ID3D11Buffer* _vb;
	ID3D11Buffer* _ib;
};



struct _MODEL{
	char* nm;
	float* t;
	uint8_t ll;
	struct _MODEL_LAYER* l;
	uint8_t sl;
};



struct _MODEL_PHONG_CB{
	RawVector ac;
	RawVector dc;
	RawVector sc;
	float se;
};



union _ANIMATION_BONE_ATTR{
	float v;
	float* l;
};



struct _ANIMATION_BONE{
	uint8_t f;
	union _ANIMATION_BONE_ATTR x;
	union _ANIMATION_BONE_ATTR y;
	union _ANIMATION_BONE_ATTR z;
	union _ANIMATION_BONE_ATTR rx;
	union _ANIMATION_BONE_ATTR ry;
	union _ANIMATION_BONE_ATTR rz;
};



struct _ANIMATION{
	char* nm;
	uint16_t d;
	uint16_t bl;
	struct _ANIMATION_BONE* b;
};



struct _ANIMATOR{
	Model m;
	Animation a;
	bool _c;
	uint16_t _f;
	float _lt;
};



struct SHADER_DATA{
	enum SHADER_DATA_TYPE t;
	ConstantBuffer id;
	uint16_t r;
	uint8_t f;
};



extern HWND _w;
extern uint32_t _ww;
extern uint32_t _wh;
extern bool _wf;
extern float _cc[4];
extern GEngine_init_func _if;
extern GEngine_render_func _rf;
extern ID3D11Device* _d3_d;
extern ID3D11Device1* _d3_d1;
extern ID3D11DeviceContext* _d3_dc;
extern ID3D11DeviceContext1* _d3_dc1;
extern IDXGISwapChain* _d3_sc;
extern IDXGISwapChain1* _d3_sc1;
extern ID3D11RenderTargetView* _d3_rt;
extern ID3D11Texture2D* _d3_ds;
extern ID3D11DepthStencilView* _d3_sv;
extern ID3D11VertexShader** _vsl;
extern ID3D11PixelShader** _psl;
extern ID3D11Buffer** _cbl;
extern size_t* _cblsz;
extern uint8_t* _cblp;
extern uint32_t _vsll;
extern uint32_t _psll;
extern uint32_t _cbll;
extern uint8_t* _kb;
extern bool _rkb;



uint32_t GEngine_window_width();



uint32_t GEngine_window_height();



float GEngine_aspect_ratio();



Matrix GEngine_identity_matrix();



Matrix GEngine_y_rotation_matrix(float a);



Matrix GEngine_perspective_fov_matrix(float fov,float a,float n,float f);



Matrix GEngine_ortographic_matrix(float w,float h,float n,float f);



Camera GEngine_create_camera(float ms,float rs,float x,float y,float z,float rx,float ry,float rz);



Matrix GEngine_update_camera(Camera c,float dt);



Model GEngine_load_model(const char* fp,uint8_t sl);



void GEngine_update_model(Model m,uint8_t i);



void GEngine_draw_model(Model m,uint8_t i);



void GEngine_draw_model_bones(Model m,uint8_t i);



Animation GEngine_load_animation(const char* fp,Model m);



Animator GEngine_create_animator(Model m);



void GEngine_set_animation(Animator a,Animation an);



void GEngine_update_animator(Animator a,float dt);



ObjectBuffer GEngine_create_object_buffer();



ObjectBuffer GEngine_box_object_buffer();



void GEngine_update_object_buffer(ObjectBuffer ob);



void GEngine_draw_object_buffer(ObjectBuffer ob);



void GEngine_set_init_func(GEngine_init_func f);



void GEngine_set_render_func(GEngine_render_func f);



void GEngine_create(const wchar_t* nm);



bool GEngine_window_focused(void);



bool GEngine_is_pressed(uint32_t k);



void GEngine_set_color(float r,float g,float b,float a);



VertexShader GEngine_load_vertex_shader(const BYTE* dt,size_t ln,VS_INPUT_LAYOUT* il,uint16_t ill);



PixelShader GEngine_load_pixel_shader(const BYTE* dt,size_t ln);



ConstantBuffer GEngine_create_constant_buffer(uint16_t l);



void GEngine_update_constant_buffer(ConstantBuffer cb,void* dt);



void GEngine_set_shader_data(struct SHADER_DATA* dt);



void GEngine_use_vertex_shader(VertexShader vs);



void GEngine_use_pixel_shader(PixelShader ps);



void GEngine_close(void);



#endif
