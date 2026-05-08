#include "pico/stdlib.h"
#include "hardware/adc.h"

#define MQ2_PIN 26        // ADC0 -> GPIO26
#define RED_LED 15
#define GREEN_LED 14
#define BUZZER 13

#define THRESHOLD 3000

int main()
{
    stdio_init_all();

    // LED and buzzer setup
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // ADC setup
    adc_init();
    adc_gpio_init(MQ2_PIN);
    adc_select_input(0);

    while (1)
    {
        uint16_t gas_value = adc_read();

        // Smoke detected
        if (gas_value > THRESHOLD)
        {
            gpio_put(RED_LED, 1);
            gpio_put(GREEN_LED, 0);
            gpio_put(BUZZER, 1);
        }
        else
        {
            gpio_put(RED_LED, 0);
            gpio_put(GREEN_LED, 1);
            gpio_put(BUZZER, 0);
        }

        sleep_ms(200);
    }

    return 0;
}
