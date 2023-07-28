#ifndef BITMAP_H
#define BITMAP_H
#include <stdint.h>

struct bitmap
{
	uint8_t *base_addr;
	uint32_t bit_num;
	uint32_t byte_len;
};

uint32_t bit_num2byte_len(uint32_t bit_num)
{
	return (bit_num % 8) ? (bit_num / 8 + 1) : (bit_num / 8);
}

void bitmap_init(struct bitmap *btmp, void *base, uint32_t bit_num)
{
	btmp->base_addr = (uint8_t *)base;
	btmp->bit_num = bit_num;
	btmp->byte_len = bit_num2byte_len(btmp->bit_num);
}

uint32_t bitmap_get(struct bitmap *btmp, uint32_t idx)
{
	uint32_t byte_off = idx / 8;
	uint32_t bit_off = idx % 8;
	return btmp->base_addr[byte_off] & (1 << bit_off);
}

uint32_t bitmap_set(struct bitmap *btmp, uint32_t idx)
{
	uint32_t byte_off = idx / 8;
	uint32_t bit_off = idx % 8;
	btmp->base_addr[byte_off] |= (1 << bit_off);
}

uint32_t bitmap_clear(struct bitmap *btmp, uint32_t idx)
{
	uint32_t byte_off = idx / 8;
	uint32_t bit_off = idx % 8;
	btmp->base_addr[byte_off] &= ~(1 << bit_off);
}

int32_t bitmap_scan(struct bitmap *btmp, uint32_t val, uint32_t cnt)
{
	uint32_t left = 0;
	uint32_t right = 0;
	while (right < btmp->bit_num)
	{
		if (bitmap_get(btmp, right) != val)
		{
			left = right + 1;
		}
		if (right - left + 1 == cnt)
		{
			return left;
		}
		right++;
	}
	return -1;
}

#endif