/*
 * Copyright (c) 2021 Jonathan Hahn
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

int main(void)
{
	const struct device *uart0 = DEVICE_DT_GET(DT_NODELABEL(pio1_uart0));
	const struct device *uart1 = DEVICE_DT_GET(DT_NODELABEL(pio1_uart1));


	unsigned char recv;

	if (!device_is_ready(uart0) || !device_is_ready(uart1)) {
		printk("uart devices not ready\n");
		return 0;
	}

	while (true) {

		uart_poll_out(uart0, 'c');

		/* give the uarts some time to get the data through */
		k_sleep(K_MSEC(50));

		int ret = uart_poll_in(uart1, &recv);

		if (ret < 0) {
			printk("Receiving failed. Error: %d\n", ret);
		} else {
			printk("Received %c\n", recv);
		}

		k_sleep(K_MSEC(2000));
	}
	return 0;
}
