#include <common.h>
#include <texture.h>
#include <d3d11_1.h>
#include <g_engine.h>
#include <stdio.h>



Texture create_texture(RawTexture r){
	D3D11_TEXTURE2D_DESC d={
		r.w,
		r.h,
		1,
		1,
		r.f,
		{
			1,
			0
		},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		0
	};
	D3D11_SUBRESOURCE_DATA sd={
		r.dt,
		r.p,
		r.sp
	};
	ID3D11Texture2D* t=NULL;
	HRESULT hr=ID3D11Device_CreateTexture2D(_d3_d,&d,&sd,&t);
	if (FAILED(hr)){
		printf("%x\n",hr);
		assert(0);
		return NULL;
	}
	D3D11_SHADER_RESOURCE_VIEW_DESC rvd={
		r.f,
		D3D_SRV_DIMENSION_TEXTURE2D,
		{
			.Texture2D={
				0,
				1
			}
		}
	};
	Texture o=NULL;
	ID3D11Resource* tr;
	ID3D11Texture2D_QueryInterface(_d3_d,&IID_ID3D11Resource,(void**)&tr);
	ID3D11Device_CreateShaderResourceView(_d3_d,tr,&rvd,&o);
	IUnknown_Release(tr);
	return o;
}
