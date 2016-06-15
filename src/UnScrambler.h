#ifndef _KEYUNSCRAMBLER_UNSCRAMBLER_H
#define _KEYUNSCRAMBLER_UNSCRAMBLER_H
u8 *Key_Unscrambler(u8 normal_key[0x10], u8 Key[0x10], const u8 C[0x10], u8 X_or_Y);
u8 *Key_Scrambler(u8 X[0x10], u8 Y[0x10], const u8 C[0x10]);
#endif
