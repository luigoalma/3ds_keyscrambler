#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "UnScrambler.h"
#ifdef INCLUDE_CONSTANT_C
//Change this string with the Constant C if you want a build with the Constant C
//Note: It should be a hex value of 16 bytes (32 characters long)
const char* const_c = "00000000000000000000000000000000";
#endif

void Print_Usage(char* name){
	printf("Usage:\n"
	"For Normal Key:\n"
#ifdef INCLUDE_CONSTANT_C
	"%s N KeyX KeyY\n"
	"For KeyX:\n"
	"%s X Normal_Key KeyY\n"
	"For KeyY:\n"
	"%s Y Normal_Key KeyX\n\n",
#else
	"%s N KeyX KeyY Constant_C\n"
	"For KeyX:\n"
	"%s X Normal_Key KeyY Constant_C\n"
	"For KeyY:\n"
	"%s Y Normal_Key KeyX Constant_C\n\n",
#endif
	name, name, name);
}

int Check_Keys(const char* Key){
	const char *valid_characters = "0123456789ABCDEFabcdef";
	const char *v = Key;
	while(*v){
		if (!strchr(valid_characters, *v)) return 1;
		v++;
	}
	return 0;
}

void Print_Key(const u8 *Key, char *keyname){
	int i;
	for(i=0;i<16;i++){
		printf("%02X", Key[i]);
	}
	printf(" - %s\n", keyname);
}

int main(int argc, char* argv[])
{
#ifdef INCLUDE_CONSTANT_C
	if(argc < 4){
#else
	if(argc < 5){
#endif
		printf("Not enough arguments.\n");
		Print_Usage(argv[0]);
		return 1;
	}
	if(!(strncmp(argv[1],"N", 1) == 0) && !(strncmp(argv[1],"X", 1) == 0) && !(strncmp(argv[1],"Y", 1) == 0)){
		printf("Bad argument.\n");
		Print_Usage(argv[0]);
		return 1;
	}
#ifdef INCLUDE_CONSTANT_C
	if(strlen(argv[2])!=32 || strlen(argv[3])!=32 || strlen(const_c)!=32){
		if(!(strlen(const_c)!=32)) printf("At least one of the Keys does not have the correct length.\n");
		else printf("The constant C used on build time does not have the correct length.\n");
#else
	if(strlen(argv[2])!=32 || strlen(argv[3])!=32 || strlen(argv[4])!=32){
		printf("At least one of the Keys does not have the correct length.\n");
#endif
		return 1;
	}
#ifdef INCLUDE_CONSTANT_C
	if(Check_Keys(argv[2]) || Check_Keys(argv[3]) || Check_Keys(const_c)){
		if(!Check_Keys(const_c)) printf("At least one of the Keys is bad.\n");
		else printf("The constant C used on build time is not a valid hex value.\n");
#else
	if(Check_Keys(argv[2]) || Check_Keys(argv[3]) || Check_Keys(argv[4])){
		printf("At least one of the Keys is bad.\n");
#endif
		return 1;
	}
	char a[2];
	u8 Keys[3][0x10];
	int i,j;
#ifdef INCLUDE_CONSTANT_C
	for(i=0;i<2;i++){
#else
	for(i=0;i<3;i++){
#endif
		for(j=0;j<16;j++){
			a[0] = argv[i+2][j*2];
			a[1] = argv[i+2][(j*2)+1];
			Keys[i][j] = (u8)strtol(a, NULL, 16);
		}
	}
#ifdef INCLUDE_CONSTANT_C
	for(i=0;i<16;i++){
		a[0] = const_c[i*2];
		a[1] = const_c[(i*2)+1];
		Keys[2][i] = (u8)strtol(a, NULL, 16);
	}
#endif
	if(strncmp(argv[1],"N", 1) == 0){
		Print_Key(Keys[0], "KeyX");
		Print_Key(Keys[1], "KeyY");
		Print_Key(Keys[2], "C");
		u8 *returned_key = Key_Scrambler(Keys[0], Keys[1], Keys[2]);
		Print_Key(returned_key, "Normal Key");
	}
	else if(strncmp(argv[1],"X", 1) == 0){
		Print_Key(Keys[0], "Normal Key");
		Print_Key(Keys[1], "KeyY");
		Print_Key(Keys[2], "C");
		u8 *returned_key = Key_Unscrambler(Keys[0], Keys[1], Keys[2], 1);
		Print_Key(returned_key, "KeyX");
	}
	else if(strncmp(argv[1],"Y", 1) == 0){
		Print_Key(Keys[0], "Normal Key");
		Print_Key(Keys[1], "KeyX");
		Print_Key(Keys[2], "C");
		u8 *returned_key = Key_Unscrambler(Keys[0], Keys[1], Keys[2], 0);
		Print_Key(returned_key, "KeyY");
	}
	return 0;
}
