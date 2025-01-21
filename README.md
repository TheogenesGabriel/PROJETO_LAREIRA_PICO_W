# Projeto LEDs com Efeito de Lareira

## Descrição
Este projeto utiliza a placa **Raspberry Pi Pico W** para criar um efeito visual que simula o cintilar de uma chama, utilizando LEDs controlados por PWM. O sistema inclui um display OLED para exibição de mensagens e botões para controlar a intensidade do efeito de fogo. O projeto também faz uso de um buzzer para notificações sonoras.

## Características Principais
- Controle de intensidade do efeito de chama utilizando botões.
- Exibição de mensagens no display OLED via protocolo I2C.
- Geração de efeitos visuais com LEDs vermelhos e amarelos.
- Integração de um buzzer para sinalizações sonoras.

## Materiais Utilizados
- 3 resistores de 110 Ohms
- 3 jumpers macho-fêmea
- 1 LED amarelo
- 2 LEDs vermelhos
- 1 globo de uma lâmpada LED (ou alternativa como uma folha de papel em formato de cone)

## Observações
- O efeito é mais visível em ambientes com pouca luminosidade.
- Caso não possua o globo de lâmpada, pode-se improvisar com papel.

## Funcionalidades do Código
1. **Inicialização dos GPIOs e Periféricos:**
   - Configuração de botões como entradas com pull-up.
   - Configuração de LEDs para saída PWM.
   - Configuração do display OLED via I2C.

2. **Controle do Efeito de Fogo:**
   - Gera valores aleatórios para simular o brilho oscilante das chamas.
   - Controla a intensidade das chamas com os botões A (aumentar) e B (diminuir).

3. **Notificações Sonoras:**
   - Emite um som pelo buzzer ao pressionar os botões.

## Estrutura do Código
- **setup_prf:** Configuração inicial dos GPIOs.
- **setup_pwm:** Configura LEDs como saídas PWM.
- **fire_effect:** Controla o brilho dos LEDs para simular o efeito de fogo.
- **play_sound:** Controla o buzzer para emitir sons.
- **main:**
  - Inicializa os periféricos.
  - Exibe mensagens no display OLED.
  - Executa o loop principal com leitura dos botões e ajuste da intensidade das chamas.

## Como Usar
1. **Conexões:**
   - Conecte os LEDs e resistores aos GPIOs especificados (16, 17 e 18).
   - Conecte os botões nos GPIOs 5 e 6.
   - Conecte o buzzer ao GPIO 21.
   - Configure os pinos I2C (SDA: 14, SCL: 15).

2. **Execução:**
   - Compile e envie o código para a Raspberry Pi Pico W.
   - O display OLED mostrará as opções "Aumentar" e "Diminuir".
   - Use os botões para controlar a intensidade.

3. **Melhoria Visual:**
   - Para um efeito mais imersivo, utilize um globo de lâmpada LED ou papel em forma de cone.

## Link de Demonstração
[Insira aqui o link para o vídeo ou imagens do funcionamento do projeto](#)

## Dependências
- Biblioteca **pico/stdlib**: Para controle de GPIOs.
- Biblioteca **hardware/pwm**: Para controle de LEDs por PWM.
- Biblioteca **hardware/i2c** e **ssd1306**: Para comunicação e controle do display OLED.

## Autor
**Theógenes Gabriel Araújo de Andrade**

**Data de Criação:** 20/01/2025

---

Se tiver dúvidas ou quiser mais informações, sinta-se à vontade para entrar em contato!

