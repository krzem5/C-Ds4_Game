#include <g_engine.h>
#include <engine.h>
#include <ds4.h>
#include <stdio.h>
#include <data.h>



struct VertexShaderInput{
	RawMatrix wm;
	RawMatrix cm;
	RawMatrix pm;
	RawVector cp;
	RawVector lp;
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
		"COLOR",
		0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		0,
		12,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	}
};



VS_INPUT_LAYOUT vs_inp_tex[]={
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
		"NORMAL",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		12,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	},
	{
		"TEXCOORD",
		0,
		DXGI_FORMAT_R32G32_FLOAT,
		0,
		24,
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



VertexShader vs;
VertexShader vs_tex;
PixelShader ps;
PixelShader ps_tex;
ConstantBuffer cb;
Matrix wm;
Matrix pm;
// Camera c;
ObjectBuffer ob;
Model m;
Model tm;
Animation ia;
Animation ftra;
Animator an;
struct Font* px_f;



void _init_func(void){
	DS4_init();
	vs=GEngine_load_vertex_shader(g_vertex_shader,sizeof(g_vertex_shader),vs_inp,sizeof(vs_inp)/sizeof(VS_INPUT_LAYOUT));
	vs_tex=GEngine_load_vertex_shader(g_vertex_shader_tex,sizeof(g_vertex_shader_tex),vs_inp_tex,sizeof(vs_inp_tex)/sizeof(VS_INPUT_LAYOUT));
	ps=GEngine_load_pixel_shader(g_pixel_shader,sizeof(g_pixel_shader));
	ps_tex=GEngine_load_pixel_shader(g_pixel_shader_tex,sizeof(g_pixel_shader_tex));
	cb=GEngine_create_constant_buffer(sizeof(struct VertexShaderInput));
	sdt->id=cb;
	// c=GEngine_create_camera(50,5,0,5,0,-90,0,0);
	// c->lock=true;
	// c->enabled=true;
	GEngine_set_shader_data(sdt);
	wm=GEngine_identity_matrix();
	pm=GEngine_perspective_fov_matrix(GENGINE_PIDIV2,GEngine_aspect_ratio(),0.01f,1000);
	ob=GEngine_box_object_buffer();
	// m=GEngine_load_model("rsrc\\ybot.mdl",1);
	// tm=GEngine_load_model("rsrc\\tree.mdl",1);
	// ia=GEngine_load_animation("rsrc\\idle.anm",m);
	// ftra=GEngine_load_animation("rsrc\\falling to roll.anm",m);
	// an=GEngine_create_animator(m);
	GEngine_set_color(0,0,0,255);
	px_f=load_font(PIXEL_FONT);
}



void _render_func(double dt){
	static double t=0;
	t+=dt*1e-6;
	if (GEngine_window_focused()==false){
		return;
	}
	// static bool ap=false;
	// GEngine_update_animator(an,(float)(dt*1e-6));
	// if (GEngine_animation_finished(an)==true){
	// 	ap=false;
	// 	GEngine_set_animation(an,ia);
	// }
	// if (GEngine_is_pressed(0x26)==true&&ap==false){
	// 	GEngine_set_animation(an,ftra);
	// 	ap=true;
	// }
	struct VertexShaderInput cb1={
		GEngine_as_raw_matrix(wm),
		GEngine_raw_identity_matrix(),
		GEngine_as_raw_matrix(pm),
		GEngine_raw_vector(0,0,0,1),
		GEngine_raw_vector(1000,-1000,-1000,1)
	};
	// GEngine_update_constant_buffer(cb,&cb1);
	GEngine_use_vertex_shader(vs);
	GEngine_use_pixel_shader(ps);
	GEngine_draw_object_buffer(ob);
	// GEngine_draw_model_bones(m,1);
	// GEngine_use_vertex_shader(vs_tex);
	// GEngine_use_pixel_shader(ps_tex);
	// GEngine_draw_model_all(m);
	// GEngine_draw_model_all(tm);
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
