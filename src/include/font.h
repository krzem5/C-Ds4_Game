#include <common.h>



typedef struct _FONT* Font;



struct FontCharacter{
	char ch;
	uint8_t w;
	float ua;
	float va;
	float ub;
	float vb;
};



Font load_font(struct FontCharacter* c){

}
