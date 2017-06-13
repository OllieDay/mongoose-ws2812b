#include "ws2812b.h"
#include "fw/src/mgos_bitbang.h"
#include "fw/src/mgos_gpio.h"
#include "fw/src/mgos_hal.h"

#include <stdlib.h>
#include <string.h>

void ws2812b_init(struct ws2812b *const ws2812b) {
	ws2812b->data = calloc(ws2812b->count * 3, sizeof *ws2812b->data);

	mgos_gpio_set_mode(ws2812b->pin, MGOS_GPIO_MODE_OUTPUT);
	mgos_gpio_write(ws2812b->pin, 0);
}

void ws2812b_free(struct ws2812b *const ws2812b) {
	free(ws2812b->data);
}

void ws2812b_set_led(struct ws2812b *const ws2812b, const uint16_t led, const uint8_t r, const uint8_t g, const uint8_t b) {
	uint8_t v0 = 0;
	uint8_t v1 = 0;
	uint8_t v2 = 0;

	switch (ws2812b->order) {
		case WS2812B_ORDER_RGB:
			v0 = r;
			v1 = g;
			v2 = b;
			break;
		case WS2812B_ORDER_GRB:
			v0 = g;
			v1 = r;
			v2 = b;
			break;
		case WS2812B_ORDER_BGR:
			v0 = b;
			v1 = g;
			v2 = r;
			break;
	}

	const uint16_t i = led * 3;

	ws2812b->data[i] = v0;
	ws2812b->data[i + 1] = v1;
	ws2812b->data[i + 2] = v2;
}

void ws2812b_clear(struct ws2812b *const ws2812b) {
	memset(ws2812b->data, 0, ws2812b->count * 3);
}

void ws2812b_show(const struct ws2812b *const ws2812b) {
	mgos_gpio_write(ws2812b->pin, 0);
	mgos_usleep(60);
	mgos_bitbang_write_bits(ws2812b->pin, MGOS_DELAY_100NSEC, 3, 8, 7, 6, ws2812b->data, ws2812b->count * 3);
	mgos_gpio_write(ws2812b->pin, 0);
	mgos_usleep(60);
	mgos_gpio_write(ws2812b->pin, 1);
}
