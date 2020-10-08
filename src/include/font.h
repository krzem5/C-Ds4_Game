#ifndef FONT_H
#define FONT_H
#include <common.h>
#include <d3d11.h>



Font load_font(const FontCharacter* c,uint8_t sz,RawTexture tx);



RenderedText render_text(float x,float y,float z,char* s,Font f);



void draw_rendered_text(RenderedText txt);



#endif
