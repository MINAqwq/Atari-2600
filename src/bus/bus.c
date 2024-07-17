#include "bus.h"
#include "../utils/debug.h"

#define INDEX_ROM(addr)	 (addr & 0x0FFF)
#define INDEX_TIA(addr)	 (addr & 0x3F)
#define INDEX_RAM(addr)	 ((addr & 0xFF) - 0x80)
#define INDEX_RIOT(addr) ((addr & 0x1F) - 0x280)

/* !!! this checks depend on each other */

/*****************************************
 * $1000-$1FFF = ROM Addresses $000-$FFF *
 * ------------------------------------- *
 *                                       *
 *     mirror: $x000                     *
 *                                       *
 *     x = {odd}                         *
 *                                       *
 *****************************************/
int8_t
bus_address_is_rom(uint8_t x)
{
	return (x % 2);
}

/***************************************************
 * $0000-$003F = TIA Addresses $00-$3F (zero page) *
 * ----------------------------------------------- *
 *                                                 *
 *     mirror: $xyz0                               *
 *                                                 *
 *     x = {even}                                  *
 *     y = {anything}                              *
 *     z = {0, 4}                                  *
 *                                                 *
 ***************************************************/
int8_t
bus_address_is_tia(uint8_t z)
{
	return (z < 8);
}

/**************************************
 * $0080-$00FF = RIOT RAM (zero page) *
 * ---------------------------------- *
 *                                    *
 *     mirror: $xy80                  *
 *                                    *
 *     x = {even}                     *
 *     y = {0,1,4,5,8,9,$C,$D}        *
 *                                    *
 **************************************/
int8_t
bus_address_is_ram(uint8_t y)
{
	return (!y || y == 1 || y == 4 || y == 5 || y == 8 || y == 9 ||
		y == 0xC || y == 0xD);
}

/****************************************
 * $0280-$029F = RIOT Addresses $00-$1F *
 * ------------------------------------ *
 *                                      *
 *     mirror: $xyz0                    *
 *                                      *
 *     x = {even}                       *
 *     y = {2,3,6,7,$A,$B,$E,$F}        *
 *     z = {8,$A,$C,$E}                 *
 *                                      *
 ****************************************/

/* if all checks above retuned false we know its a riot address */

void
bus_write(uint16_t addr, uint8_t val, Bus *b)
{
	uint8_t x;
	uint8_t y;
	uint8_t z;

	debug_log("MEM: write 0x%02X to $%04X", val, addr);

	x = ((addr >> 12) & 0xF);
	if (bus_address_is_rom(x)) {
		/* you can't write to rom idiot */
		return;
	}

	z = ((addr >> 4) & 0xF);
	if (bus_address_is_tia(z)) {
		debug_log("WRITE TO TIA");
		b->dummy_tia[INDEX_TIA(addr)] = val;
		return;
	}

	y = ((addr >> 8) & 0xF);
	if (bus_address_is_ram(y)) {
		debug_log("WRITE TO RAM");
		b->ram[INDEX_RAM(addr)] = val;
		return;
	}

	debug_log("WRITE TO RIOT");
	b->dummy_riot[INDEX_RIOT(addr)] = val;
}

uint8_t
bus_read(uint16_t addr, const Bus *b)
{
	uint8_t x;
	uint8_t y;
	uint8_t z;
	uint8_t val;

	x = ((addr >> 12) & 0xF);
	if (bus_address_is_rom(x)) {
		debug_log("READ FROM ROM");
		val = b->rom[INDEX_ROM(addr)];
		goto bus_read_final;
	}

	z = ((addr >> 4) & 0xF);
	if (bus_address_is_tia(z)) {
		debug_log("READ FROM TIA");
		val = b->dummy_tia[INDEX_TIA(addr)];
		goto bus_read_final;
	}

	y = ((addr >> 8) & 0xF);
	if (bus_address_is_ram(y)) {
		debug_log("READ FROM RAM");
		val = b->ram[INDEX_RAM(addr)];
		goto bus_read_final;
	}

	debug_log("READ ROM RIOT");
	val = b->dummy_riot[INDEX_RIOT(addr)];

bus_read_final:
	debug_log("MEM: read 0x%02X from $%04X", val, addr);

	return val;
}
