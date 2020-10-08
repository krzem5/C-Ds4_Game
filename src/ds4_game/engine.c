#include <g_engine.h>
#include <engine.h>
#include <ds4.h>
#include <stdio.h>
#include <data.h>
#include <font.h>



struct VertexShaderInput{
	RawMatrix wm;
	RawMatrix cm;
	RawMatrix pm;
};



VS_INPUT_LAYOUT vs_inp[]={
	{
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	},
	{
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		0,
		12,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	}
};



VS_INPUT_LAYOUT vs_inp2[]={
	{
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	},
	{
		"COLOR",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		12,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	}
};



struct SHADER_DATA sdt[1]={
	{
		SHADER_DATA_TYPE_CONSTANT_BUFFER,
		0,
		0,
		SHADER_DATA_FLAG_VS|SHADER_DATA_FLAG_PS
	}
};



/*********************************/
const D3D11_SAMPLER_DESC _sd={
	D3D11_FILTER_MIN_MAG_MIP_POINT,
	D3D11_TEXTURE_ADDRESS_CLAMP,
	D3D11_TEXTURE_ADDRESS_CLAMP,
	D3D11_TEXTURE_ADDRESS_CLAMP,
	0,
	0,
	D3D11_COMPARISON_NEVER,
	0,0,0,0,
	0,
	0
};
ID3D11SamplerState* sd;
/*********************************/



VertexShader vs;
PixelShader ps;
VertexShader vs2;
PixelShader ps2;
ConstantBuffer cb;
Camera c;
Matrix wm;
Matrix pm;
ObjectBuffer ob;
Font px_f;
RenderedText txt;



void _init_func(void){
	/*******************************/
	ID3D11Device_CreateSamplerState(_d3_d,&_sd,&sd);
	/*******************************/
	DS4_init();
	vs=GEngine_load_vertex_shader(g_vertex_shader,sizeof(g_vertex_shader),vs_inp,sizeof(vs_inp));
	ps=GEngine_load_pixel_shader(g_pixel_shader,sizeof(g_pixel_shader));
	vs2=GEngine_load_vertex_shader(g_vertex_shader2,sizeof(g_vertex_shader2),vs_inp2,sizeof(vs_inp2));
	ps2=GEngine_load_pixel_shader(g_pixel_shader2,sizeof(g_pixel_shader2));
	cb=GEngine_create_constant_buffer(sizeof(struct VertexShaderInput));
	sdt->id=cb;
	GEngine_set_shader_data(sdt);
	c=GEngine_create_camera(50,5,0,5,0,-90,0,0);
	c->lock=true;
	c->enabled=true;
	wm=GEngine_identity_matrix();
	pm=GEngine_perspective_fov_matrix(GENGINE_PIDIV2,GEngine_aspect_ratio(),0.01f,1000);
	// pm=GEngine_ortographic_matrix((float)GEngine_window_width(),(float)GEngine_window_height(),0.01f,1000);
	ob=GEngine_box_object_buffer();
	GEngine_set_color(0,0,0,255);
	px_f=load_font(KENNEY_PIXEL,sizeof(KENNEY_PIXEL)/sizeof(FontCharacter),KENNEY_PIXEL_FONT_TEX);
	txt=render_text(5,5,0,"Connect a Controller...",px_f);
}



void _render_func(double dt){
	static double t=0;
	t+=dt*1e-6;
	Matrix cm=GEngine_update_camera(c,(float)(dt*1e-6));
	if (cm==NULL){
		return;
	}
	struct VertexShaderInput cb1={
		GEngine_as_raw_matrix(wm),
		GEngine_as_raw_matrix(cm),
		GEngine_as_raw_matrix(pm)
	};
	GEngine_update_constant_buffer(cb,&cb1);
	GEngine_use_vertex_shader(vs2);
	GEngine_use_pixel_shader(ps2);
	GEngine_draw_object_buffer(ob);
	GEngine_use_vertex_shader(vs);
	GEngine_use_pixel_shader(ps);
	/*********************************/
	ID3D11DeviceContext_VSSetShaderResources(_d3_dc,0,1,&txt->_t);
	ID3D11DeviceContext_PSSetShaderResources(_d3_dc,0,1,&txt->_t);
	ID3D11DeviceContext_VSSetSamplers(_d3_dc,0,1,&sd);
	ID3D11DeviceContext_PSSetSamplers(_d3_dc,0,1,&sd);
	draw_rendered_text(txt);
	/*********************************/
	GEngine_free_matrix(cm);
	if (GEngine_is_pressed(0x1b)==true){
		GEngine_close();
	}
}



void run_game(void){
	GEngine_set_init_func(_init_func);
	GEngine_set_render_func(_render_func);
	atexit(GEngine_close);
	GEngine_create(L"Ds4 Game");
	// struct DS4DeviceList* l=DS4_find_all();
	// struct DS4Device* d=DS4_connect(l->p);
	// DS4_free_list(l);
	// while (true){
	// 	static uint64_t t=0;
	// 	DS4_update(d);
	// 	t+=d->dt;
	// 	printf("BUTTONS: %x\n",d->btn);
	// 	d->fr=(d->ry>20?d->ry*2:0);
	// 	d->sr=(d->ly>20?d->ly*2:0);
	// 	DS4_hsl(d,(uint8_t)((double)(t/1000)/20),255,255);
	// }
	// DS4_close(d);
	// DS4_cleanup();
}
