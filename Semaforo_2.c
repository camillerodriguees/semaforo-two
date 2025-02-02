#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include <stdio.h>

#define LED_BLUE 11
#define LED_RED 12
#define LED_GREEN 13
#define BUTTON 5
#define DELAY_MS 3000 // Mantemos o delay original

volatile bool is_running = false; // Indica se a sequência está em andamento

// Callback para acionar os LEDs de forma sequencial dentro do tempo desejado
int64_t led_callback(alarm_id_t id, void *user_data) {
    static int state = 0;

    if (!is_running) { // Se a sequência foi interrompida, não faz nada
        return 0;
    }

    switch (state) {
        case 0:
            printf("Acendendo todos os LEDs\n");
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 1);
            gpio_put(LED_GREEN, 1);
            break;
        case 1:
            printf("Desligando LED AZUL\n");
            gpio_put(LED_BLUE, 0);
            break;
        case 2:
            printf("Desligando LED VERMELHO\n");
            gpio_put(LED_RED, 0);
            break;
        case 3:
            printf("Desligando LED VERDE\n");
            gpio_put(LED_GREEN, 0);
            is_running = false; // Permite nova ativação pelo botão
            state = 0; // Reinicia o estado para a próxima execução
            return 0; // Para a execução aqui
    }

    state++;

    // Adiciona a próxima execução do callback dentro do tempo correto
    add_alarm_in_ms(DELAY_MS / 2, led_callback, NULL, false);

    return 0;
}

// Função para detectar clique do botão e iniciar a sequência
void button_callback(uint gpio, uint32_t events) {
    if (!is_running) { // Garante que só inicie se não estiver rodando
        sleep_ms(50); // Debounce
        if (gpio_get(BUTTON) == 0) { // Confirma que o botão ainda está pressionado
            printf("Botão pressionado! Iniciando sequência...\n");
            is_running = true;
            add_alarm_in_ms(0, led_callback, NULL, false);
        }
    }
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs como saída
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0); // Garante que o LED está apagado na inicialização

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    // Configuração do botão como entrada com pull-up
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    // Configuração da interrupção para o botão
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (1) {
        tight_loop_contents(); // Mantém o loop ativo sem consumir processamento excessivo
    }
}