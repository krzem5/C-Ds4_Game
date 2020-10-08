#include <common.h>
#include <font.h>
#include <texture.h>
#include <d3d11_1.h>
#include <g_engine.h>
#include <stdio.h>



Font load_font(const FontCharacter* c,uint8_t sz,RawTexture tx){
	Font o=malloc(sizeof(struct _FONT));
	o->_t=create_texture(tx);
	o->_l=0;
	o->_dt=NULL;
	for (uint8_t i=0;i<sz;i++){
		assert((c+i)->ch!=UINT8_MAX);
		if ((c+i)->ch>=o->_l){
			o->_l=(c+i)->ch+1;
			o->_dt=realloc(o->_dt,(size_t)o->_l*5*sizeof(float));
		}
		*(o->_dt+(size_t)(c+i)->ch*5)=(c+i)->w;
		*(o->_dt+(size_t)(c+i)->ch*5+1)=(c+i)->ua;
		*(o->_dt+(size_t)(c+i)->ch*5+2)=(c+i)->va;
		*(o->_dt+(size_t)(c+i)->ch*5+3)=(c+i)->ub;
		*(o->_dt+(size_t)(c+i)->ch*5+4)=(c+i)->vb;
	}
	return o;
}



RenderedText render_text(float x,float y,float z,char* s,Font f){
	static float HEIGHT=64.0f;/*****************************************/
	size_t ln=0;
	float w=0;
	while (*(s+ln)!=0){
		w-=*(f->_dt+((size_t)*(s+ln))*5)/2;
		ln++;
	}
	float* vl=malloc(ln*20*sizeof(float));
	uint16_t* il=malloc(ln*6*sizeof(uint16_t));
	RenderedText o=malloc(sizeof(struct _RENDERED_TEXT));
	o->_t=f->_t;
	o->_il=(uint32_t)(ln*2);
	for (size_t i=0;i<ln;i++){
		float* c_dt=f->_dt+((size_t)*(s+ln))*5;
		*(vl+i*20)=x+w;
		*(vl+i*20+1)=y-HEIGHT;
		*(vl+i*20+2)=z;
		*(vl+i*20+3)=*(c_dt+1);
		*(vl+i*20+4)=*(c_dt+2);
		*(vl+i*20+5)=x+w+*c_dt;
		*(vl+i*20+6)=y-HEIGHT;
		*(vl+i*20+7)=z;
		*(vl+i*20+8)=*(c_dt+3);
		*(vl+i*20+9)=*(c_dt+2);
		*(vl+i*20+10)=x+w;
		*(vl+i*20+11)=y+HEIGHT;
		*(vl+i*20+12)=z;
		*(vl+i*20+13)=*(c_dt+1);
		*(vl+i*20+14)=*(c_dt+4);
		*(vl+i*20+15)=x+w+*c_dt;
		*(vl+i*20+16)=y+HEIGHT;
		*(vl+i*20+17)=z;
		*(vl+i*20+18)=*(c_dt+3);
		*(vl+i*20+19)=*(c_dt+4);
		*(il+i*6)=(uint16_t)i*4;
		*(il+i*6+1)=(uint16_t)i*4+1;
		*(il+i*6+2)=(uint16_t)i*4+2;
		*(il+i*6+3)=(uint16_t)i*4+1;
		*(il+i*6+4)=(uint16_t)i*4+3;
		*(il+i*6+5)=(uint16_t)i*4+2;
		w+=*c_dt;
	}
	printf("%s: %llu\n",s,ln*20*sizeof(float));
	D3D11_BUFFER_DESC bd={
		(UINT)(ln*20*sizeof(float)),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		0,
		0,
		0
	};
	D3D11_SUBRESOURCE_DATA dt={
		vl,
		0,
		0
	};
	HRESULT hr=ID3D11Device_CreateBuffer(_d3_d,&bd,&dt,&o->_vb);
	free(vl);
	if (FAILED(hr)){
		printf("ERR4___\n");
		return NULL;
	}
	bd.Usage=D3D11_USAGE_DEFAULT;
	bd.ByteWidth=(UINT)(ln*6*sizeof(uint16_t));
	bd.BindFlags=D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags=0;
	dt.pSysMem=il;
	hr=ID3D11Device_CreateBuffer(_d3_d,&bd,&dt,&o->_ib);
	free(il);
	if (FAILED(hr)){
		printf("ERR5___\n");
		return NULL;
	}
	return o;
}



void draw_rendered_text(RenderedText txt){
	unsigned int off=0;
	unsigned int st=5*sizeof(float);
	ID3D11DeviceContext_IASetVertexBuffers(_d3_dc,0,1,&txt->_vb,&st,&off);
	ID3D11DeviceContext_IASetIndexBuffer(_d3_dc,txt->_ib,DXGI_FORMAT_R16_UINT,0);
	ID3D11DeviceContext_IASetPrimitiveTopology(_d3_dc,D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ID3D11DeviceContext_DrawIndexed(_d3_dc,txt->_il,0,0);
}
