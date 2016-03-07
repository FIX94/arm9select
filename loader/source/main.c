#include "common.h"

#define PAYLOAD_ADDRESS		0x24000000

extern u8 payload_stage2_bin[];
extern u32 payload_stage2_bin_size;

int main()
{
	memcpy((void*)PAYLOAD_ADDRESS, payload_stage2_bin, payload_stage2_bin_size);
	((void (*)())PAYLOAD_ADDRESS)();
    return 0;
}
