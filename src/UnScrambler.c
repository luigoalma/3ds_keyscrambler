#include <stdio.h>
#include "types.h"

u8 *Key_Unscrambler(u8 normal_key[0x10], u8 Key[0x10], const u8 C[0x10], u8 X_or_Y){
	int i;
	u8 shifted_X_xor_Y_addition_C[0x10];
	for(i=0;i<16;i++){
		//Too many type casts? or not enough type casts? I'll never know.
		//Also, masking a type casted u8 value with 0xff? Totally necessary.
		if(i > 10) shifted_X_xor_Y_addition_C[i] = (u8)((((u8)normal_key[i-11] << (u8)1)&0xFE) + (((u8)normal_key[(i+1)-11] >> (u8)7)&0x01))&0xff;
		else if(i == 10) shifted_X_xor_Y_addition_C[i] = (u8)((((u8)normal_key[5+i] << (u8)1)&0xFE) + (((u8)normal_key[0] >> (u8)7)&0x01))&0xff;
		else shifted_X_xor_Y_addition_C[i] = (u8)((((u8)normal_key[5+i] << (u8)1)&0xFE) + (((u8)normal_key[5+i+1] >> (u8)7)&0x01))&0xff;
	}
	u8 shifted_X_xor_Y[0x10];
	u8 carry = 0;
	for(i=0;i<16;i++){
		//More type casts.
		shifted_X_xor_Y[15-i] = (u8)((u8)shifted_X_xor_Y_addition_C[15-i] - (u8)carry - (u8)C[15-i]);
		carry = (u8)(((u16)((u8)shifted_X_xor_Y_addition_C[15-i] - (u8)carry - (u8)C[15-i])) >> (u8)8)&0x01;
	}
	u8 shifted_X[0x10];
	static u8 X[0x10];
	static u8 Y[0x10];
	if(X_or_Y){
		// KeyX
		for(i=0;i<16;i++){
			//Type casts.
			shifted_X[i] = (u8)((u8)shifted_X_xor_Y[i] ^ (u8)Key[i]);
		}
		for(i=0;i<16;i++){
			//Even more type casts and masks.
			if(i!=0) X[i] = (u8)((((u8)shifted_X[i] >> (u8)2)&0x3F) + (((u8)shifted_X[i-1] << (u8)6)&0xC0))&0xff;
			else X[i] = (u8)((((u8)shifted_X[i] >> (u8)2)&0x3F) + (((u8)shifted_X[15] << (u8)6)&0xC0))&0xff;
		}
		return X;
	}
	else {
		//KeyY
		for(i=0;i<16;i++){
			//Uhmm, it seems that I just don't stop with the type casts and masks.
			if(i!=15) shifted_X[i] = (u8)((((u8)Key[i] << (u8)2)&0xFC) + (((u8)Key[i+1] >> (u8)6)&0x03))&0xff;
			else shifted_X[i] = (u8)((((u8)Key[i] << (u8)2)&0xFC) + (((u8)Key[0] >> (u8)6)&0x03))&0xff;
		}
		for(i=0;i<16;i++){
			//The type casts! They're everywhere!
			Y[i] = (u8)((u8)shifted_X_xor_Y[i] ^ (u8)shifted_X[i]);
		}
		return Y;
	}
}

u8 *Key_Scrambler(u8 X[0x10], u8 Y[0x10], const u8 C[0x10]){
	int i;
	u8 shifted_X[0x10];
	for(i=0;i<16;i++){
		//The joke is already dead, but I keep doing it. So, more type casts and masks.
		if(i!=15) shifted_X[i] = (u8)((((u8)X[i] << (u8)2)&0xFC) + (((u8)X[i+1] >> (u8)6)&0x03))&0xff;
		else shifted_X[i] = (u8)((((u8)X[i] << (u8)2)&0xFC) + (((u8)X[0] >> (u8)6)&0x03))&0xff;
	}
	u8 shifted_X_xor_Y[0x10];
	for(i=0;i<16;i++){
		//Do I need to say anything more about the type casts?
		shifted_X_xor_Y[i] = (u8)((u8)shifted_X[i] ^ (u8)Y[i]);
	}
	u8 shifted_X_xor_Y_addition_C[0x10];
	u8 carry = 0;
	for(i=0;i<16;i++){
		//Type casts. Type casts everywhere.
		shifted_X_xor_Y_addition_C[15-i] = (u8)((u8)shifted_X_xor_Y[15-i] + (u8)carry + (u8)C[15-i]);
		carry = (u8)(((u16)((u8)shifted_X_xor_Y[15-i] + (u8)carry + (u8)C[15-i])) >> (u8)8);
	}
	static u8 normal_key[0x10];
	for(i=0;i<16;i++){
		//Just make it stop! Oh wait, there's no more type casts and masks after this loop.
		if(i < 5) normal_key[i] = (u8)((((u8)shifted_X_xor_Y_addition_C[10+i] << (u8)7)&0x80) + (((u8)shifted_X_xor_Y_addition_C[10+i+1] >> (u8)1)&0x7F))&0xff;
		else if (i == 5) normal_key[i] = (u8)((((u8)shifted_X_xor_Y_addition_C[10+i] << (u8)7)&0x80) + (((u8)shifted_X_xor_Y_addition_C[0] >> (u8)1)&0x7F))&0xff;
		else normal_key[i] = (u8)((((u8)shifted_X_xor_Y_addition_C[-6+i] << (u8)7)&0x80) + (((u8)shifted_X_xor_Y_addition_C[-6+i+1] >> (u8)1)&0x7F))&0xff;
	}
	return normal_key;
}
