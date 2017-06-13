#ifndef WS2812B_H
#define WS2812B_H

#include <stdint.h>

enum ws2812b_order {
	WS2812B_ORDER_RGB,
	WS2812B_ORDER_GRB,
	WS2812B_ORDER_BGR
};

struct ws2812b {
	const uint8_t pin;
	const uint16_t count;
	const enum ws2812b_order order;
	uint8_t *data;
};

void ws2812b_init(struct ws2812b *ws2812b);
void ws2812b_free(struct ws2812b *ws2812b);
void ws2812b_set_led(struct ws2812b *ws2812b, uint16_t led, uint8_t r, uint8_t g, uint8_t b);
void ws2812b_clear(struct ws2812b *ws2812b);
void ws2812b_show(const struct ws2812b *ws2812b);

#endif
