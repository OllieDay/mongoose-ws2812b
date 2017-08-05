# mongoose-ws2812b
Mongoose driver for the WS2812B (aka NeoPixel) RGB LED strip.

## Overview
This driver enables control of the WS2812B (aka NeoPixel) RGB LED strip on Mongoose OS.

## Setup
1. Copy the `ws2812b` directory into the firmware's `src` directory and add it to the `sources` section of `mos.yml`
2. Include the header `"ws2812b/ws2812b.h"` in the appropriate places.

## Usage

### Initialization
The `ws2812b` struct represents an instance of an LED strip and once initialized is used for controlling the LEDs.

```c
struct ws2812b strip = {
	// GPIO pin for the LED strip
	.pin = 0,
	// Total number of LEDs
	.count = 8,
	// Colour order of the LED: RGB, GRB, or BGR
	.order = WS2812B_ORDER_GRB
};

ws2812b_init(&strip);
```

### Clearing the LED color (switching all LEDs off)

```c
// Set each LED colour to 0 red, 0 green, 0 blue (off)
ws2812b_clear(&strip);

// Show the updated colours
ws2812b_show(&strip);
```

### Setting the LED color

```c
// LED number to set
uint16_t led = 0;

// RGB colour value
uint8_t r = 0xFF;
uint8_t g = 0xFF;
uint8_t b = 0xFF;

ws2812b_set_led(&strip, led, r, g, b);

// Refresh the LEDs
ws2812b_show(&strip);
```

### Freeing
Once finished with the device, allocated memory for the `data` member of the `ws2812b` struct must be freed accordingly.

```c
ws2812b_free(&strip);
```
