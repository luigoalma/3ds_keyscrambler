#ifndef _KEYUNSCRAMBLER_UNSCRAMBLER_H
#define _KEYUNSCRAMBLER_UNSCRAMBLER_H
void Key_Unscrambler(u8 *normal_key, u8 *Key, const u8 *C, u8 X_or_Y, u8 *return_key);
void Key_Scrambler(u8 *X, u8 *Y, const u8 *C, u8 *normal_key);
#endif
