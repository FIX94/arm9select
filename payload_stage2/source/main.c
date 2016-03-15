#include "common.h"
#include "sdmmc.h"
#include "i2c.h"
#include "fatfs/ff.h"
#include "screen_init.h"

#define PAYLOAD_ADDRESS		0x23F00000
#define PAYLOAD_SIZE		0x00100000
#define A11_PAYLOAD_LOC     0x1FFF8000  //keep in mind this needs to be changed in the ld script for screen_init too

//used to detect if we are cold booting
#define CFG_BOOTENV			0x10010000
#define COLDBOOT			0

extern u8 screen_init_bin[];
extern u32 screen_init_bin_size;

void ownArm11()
{
	memcpy((void*)A11_PAYLOAD_LOC, screen_init_bin, screen_init_bin_size);
	*((u32*)0x1FFFFFF8) = A11_PAYLOAD_LOC;
	for(int i = 0; i < 0x80000; i++)
	{
		*((u8*)0x1FFFFFF0) = 2;
	}
	for(volatile unsigned int i = 0; i < 0xF; ++i);
	while(*(volatile uint32_t *)0x1FFFFFF8 != 0);
}

static inline void jump()
{
	((void (*)())PAYLOAD_ADDRESS)();
}

void jumpAndTryEnableBL(char *file)
{
	FIL f;
	if(f_open(&f, file, FA_READ | FA_OPEN_EXISTING) == FR_OK)
	{
		ownArm11(); //enable screen backlight
		f_close(&f);
	}
	jump();
}

int tryLoadFile(char *file)
{
	FIL f;
	UINT br;
	if(f_open(&f, file, FA_READ | FA_OPEN_EXISTING) == FR_OK)
	{
		f_read(&f, (void*)PAYLOAD_ADDRESS, PAYLOAD_SIZE, &br);
		f_close(&f);
		return 1;
	}
	return 0;
}

int main()
{
	FATFS fs;
	if(f_mount(&fs, "0:", 0) == FR_OK)
	{
		u16 padInput = ~(*(u16*)0x10146000);
		if((padInput & (1<<0)) && tryLoadFile("/arm9select/a.bin"))
			jumpAndTryEnableBL("/arm9select/a_bl");
		else if((padInput & (1<<1)) && tryLoadFile("/arm9select/b.bin"))
			jumpAndTryEnableBL("/arm9select/b_bl");
		else if((padInput & (1<<2)) && tryLoadFile("/arm9select/select.bin"))
			jumpAndTryEnableBL("/arm9select/select_bl");
		else if((padInput & (1<<3)) && tryLoadFile("/arm9select/start.bin"))
			jumpAndTryEnableBL("/arm9select/start_bl");
		else if((padInput & (1<<4)) && tryLoadFile("/arm9select/right.bin"))
			jumpAndTryEnableBL("/arm9select/right_bl");
		else if((padInput & (1<<5)) && tryLoadFile("/arm9select/left.bin"))
			jumpAndTryEnableBL("/arm9select/left_bl");
		else if((padInput & (1<<6)) && tryLoadFile("/arm9select/up.bin"))
			jumpAndTryEnableBL("/arm9select/up_bl");
		else if((padInput & (1<<7)) && tryLoadFile("/arm9select/down.bin"))
			jumpAndTryEnableBL("/arm9select/down_bl");
		else if((padInput & (1<<8)) && tryLoadFile("/arm9select/r.bin"))
			jumpAndTryEnableBL("/arm9select/r_bl");
		else if((padInput & (1<<9)) && tryLoadFile("/arm9select/l.bin"))
			jumpAndTryEnableBL("/arm9select/l_bl");
		else if((padInput & (1<<10)) && tryLoadFile("/arm9select/x.bin"))
			jumpAndTryEnableBL("/arm9select/x_bl");
		else if((padInput & (1<<11)) && tryLoadFile("/arm9select/y.bin"))
			jumpAndTryEnableBL("/arm9select/y_bl");
		else if(tryLoadFile("/arm9select/default.bin"))
		{
			if(*(vu8*)CFG_BOOTENV == COLDBOOT)
				jumpAndTryEnableBL("/arm9select/default_bl");
			else //dont enable backlight again on soft reset
				jump();
		}
	}
	i2cWriteRegister(I2C_DEV_MCU, 0x20, (u8)(1<<0));
	return 0;
}
