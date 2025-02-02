# 🔴🟢🔵 Projeto: Sequência de LEDs com Botão - Raspberry Pi Pico

Este projeto implementa uma **sequência de LEDs** que é ativada ao pressionar um botão, utilizando um **Raspberry Pi Pico**. Quando o botão é pressionado, os três LEDs (**azul, vermelho e verde**) acendem simultaneamente e depois apagam **um por um** com um **intervalo de tempo de 1,5 segundos** entre cada desligamento.

O código foi **testado no Wokwi** e já acompanha o arquivo **`diagram.json`**, permitindo a execução direta sem necessidade de configuração adicional.

## 🎯 Objetivo

Criar um **sistema de controle de LEDs** acionado por botão, onde os LEDs são acesos e apagados em sequência, garantindo que o botão só pode ser pressionado novamente após o último LED ser desligado.

## 🛠️ Tecnologias Utilizadas

- **Linguagem C**
- **Pico SDK**
- **Simulador Wokwi**
- **Bibliotecas padrão do Pico (pico/stdlib.h, hardware/gpio.h, hardware/timer.h)**

## 🔧 Como Funciona?

1. **O botão é pressionado**, acionando a sequência de LEDs.
2. **Todos os LEDs acendem simultaneamente**.
3. Após **3 segundos**, **o LED azul apaga**.
4. Após mais **3 segundos**, **o LED vermelho apaga**.
5. Após mais **3 segundos**, **o LED verde apaga**.
6. **O sistema entra em estado de espera** até que o botão seja pressionado novamente.

### ❗ Restrição do Botão

O botão **só pode iniciar uma nova sequência quando o último LED for desligado**. Durante a execução da sequência, pressionar o botão **não terá efeito**. Isso evita que a função **callback** seja chamada novamente antes do término da sequência.

## 📎 Mapeamento dos Pinos

| Componente  | Pino do Pico |
|------------|-------------|
| LED Azul   | GP11        |
| LED Vermelho | GP12      |
| LED Verde  | GP13        |
| Botão      | GP5         |

## 🚀 Como Rodar o Projeto

### 1️⃣ Clonar o Repositório

```sh
git clone https://github.com/camillerodriguees/semaforo-two.git

