/*

PROJETO LEDS COM EFEITO DE LAREIRA: ABORDAGEM COM RASPBERRRY PI PICO W, DISPLAY OLED E CONTROLE DE GPIOs
==================================================================================================================================

DESCRIÇÃO: O projeto visa utilizar-se do hardware embarcado na placa BitDogLab para a criação de um efeito de chama que lembre o efeito cintilante e oscilante do fogo. O mesmo se baseou na utilização de um diplay com tecnologias OLED para apresentar mensagem para o usuário com as opções "aumentar" e "diminuir" a intensidade da chama. A proposta visa elaborar, a partir dos conhecimentos adquiridos na capacitação do Embarcatech, manipular os dispositivos de saída com função de PWM, além de controle de botões, buzzers e protocolos de comunicações como o i2c.

DATA: 20/01/2025

AUTOR: Theógenes Gabriel Araújo de Andrade.

==================================================================================================================================

MATERIAIS USADOS:

3 - Resistores de 110 Ohms;
3 - Jumpers macho-fêmea;
1 - Led amarelo;
2 - Leds Vermelhos;
1 - Globo de uma lâmpada led.

OBSERVAÇÃO: O efeito visual é vibrante e bem interessante, caso não possua o Globo da lampada Led pode-se usar uma folha de papel em formato de cone. Ademais, o efeito fica mais bonito em locais com pouca luminosidade, uma vez que o mesmo busca ser um item de decoração.

==================================================================================================================================


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include <time.h>


const uint I2C_SDA = 14;
const uint I2C_SCL = 15;
#define led1 16
#define led2 17
#define led3 18
#define btn1 5
#define btn2 6
#define buzzer 21

void setup_prf(){

    // Inicializa  os dispositivos
   gpio_init(btn1);
   gpio_init(btn2);
   gpio_init(buzzer);

    // Define o tipo de estado
   gpio_set_dir(btn1, GPIO_IN);
   gpio_set_dir(btn2, GPIO_IN);
   gpio_set_dir(buzzer, GPIO_OUT);

    // Define o botão como Pull_up
   gpio_pull_up(btn1);
   gpio_pull_up(btn2);
}

// Função para inicialização dos Leds PWM
void setup_pwm(uint led){
    gpio_set_function(led, GPIO_FUNC_PWM); //configura o pino como saída PWM
    pwm_set_enabled(pwm_gpio_to_slice_num(led), true); //ativa o pwm
}

void fire_efect(uint16_t valx, uint16_t valy, uint16_t pct){
    // Gera valores aleatórios de brilho para os LEDs
    uint16_t brilho1 = rand() % (valx + valy) - pct; //  inicial, primeiro valor 31240 e o segundo valor é o 31136
    uint16_t brilho2 = rand() % (valx + valy) - pct;
    uint16_t brilho3 = rand() % (valx+ valy) - pct;

    // Atualiza os níveis de brilho PWM
    pwm_set_gpio_level(led1, brilho1);
    pwm_set_gpio_level(led2, brilho2);
    pwm_set_gpio_level(led3, brilho3);
   
}
void play_sound(uint frequency, uint duration_ms) {
    uint delay = 1000000 / (2 * frequency); // Calcula o atraso (microsegundos) para a frequência
    uint cycles = frequency * duration_ms / 1000; // Número de ciclos para a duração

    for (uint i = 0; i < cycles; i++) {
        gpio_put(buzzer, 1); // Liga o buzzer
        sleep_us(delay);         // Espera metade do período
        gpio_put(buzzer, 0); // Desliga o buzzer
        sleep_us(delay);         // Espera a outra metade
    }
}


int main()
{
    stdio_init_all();   // Inicializa os tipos stdio padrão presentes ligados ao binário
    setup_prf();
    setup_pwm(led1);    // Configura o primeiro led como PWM
    setup_pwm(led2);    // ...
    setup_pwm(led3);    // ...


    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    srand(time(NULL));

restart:

// Criação do Texto de Exibição
    char *text[] = {
        //"             "
        "ESCOLHA QUAL A ",
        "INTENSIDADE    ",
        "               ",
        "BOTAO A OU B   ",
        "               ",
        "A  AUMENTAR    ",
        "               ",
        "B  DIMINUIR    ",
        };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    //delay para inicialização
    sleep_ms(2000);

    // Inicialização dos botões
    bool botA = false;
    bool botB = false;

    int val = 0;
    int x = 31240;
    int k = 31136;
    fire_efect(x, y, val);

    // Laço de execução do programa
    while(true) {

            // Leitura do estado lógico dos botões
            botA = gpio_get(btn1);  
            botB = gpio_get(btn2);

            if(!botA || !botB){     // Verifica se algum dos botões foram pressionados 
                play_sound(300, 150);   // Sinal sonoro é emitido indicando o pressionamento do botão
                sleep_ms(250);  // Duração do bip sonoro
                if(!botA){  // Caso o botão A seja pressionado
                    val = 3892; // Valor de acrecimo no Botão
                    if(x <= 31240){ // Intensidade máxima
                        x = x + val;
                        k = k + val;
                    }
                    printf("botão A pressionado\n");
                }else{
                    val = 3892; // Valor de decrescimo do botão
                    if(x >= 3892){  // Intensidade mínima
                        x = x - val;
                        k = k - val;
                    }
                    printf("botão B pressionado\n");
                }
                
            }
            val = 0; // Zera o valor de acrescimo/redução
            fire_efect(x, k, val); //Exibe o efeito visual
            sleep_ms(rand() % 100); // pequeno atraso aleatório para o  efeito cintilante, bem como a leitura do estado do botão
        }


    return 0;
}