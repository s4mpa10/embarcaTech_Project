#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define Led_Vermelho 13
#define Led_Azul 12
#define Led_Verde 11

#define BUTTON_A 5
#define BUTTON_B 6

absolute_time_t tempo_absoluto;
float tempo_amarelo;
float tempo_vermelho;


void config_pin(){
    gpio_init(Led_Vermelho);
    gpio_init(Led_Azul);
    gpio_init(Led_Verde);
    gpio_set_dir(Led_Vermelho,GPIO_OUT);
    gpio_set_dir(Led_Azul,GPIO_OUT);
    gpio_set_dir(Led_Verde,GPIO_OUT);
}

void config_button(){
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A,GPIO_IN);
    gpio_set_dir(BUTTON_B,GPIO_IN); 
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);
}

void combinar_cores(int red, int blue, int green){
    gpio_put(Led_Vermelho, red);
    gpio_put(Led_Azul, blue);
    gpio_put(Led_Verde, green);
}

void semaforo(){
    tempo_absoluto = to_ms_since_boot(get_absolute_time());
    printf("Tempo do Absoluto: %lld\n", tempo_absoluto);

    tempo_amarelo = delayed_by_ms(tempo_absoluto, 10000);
    
    tempo_vermelho = delayed_by_ms(tempo_absoluto, 20000);

    if ((gpio_get(BUTTON_A) == 0)){
        combinar_cores(0,0,1);
        
        if(time_reached(tempo_amarelo)){
            combinar_cores(0,1,0);

            printf("Tempo do led Amarelo: %lld\n", tempo_amarelo);
        }

        if ((time_reached(tempo_vermelho))){
            combinar_cores(0,1,0);
            printf("Tempo do led Vermelho: %lld\n", tempo_vermelho);

        }

    }

    else if (gpio_get(BUTTON_B) == 0){       
        combinar_cores(0,0,0);        
    }
}


int main()
{
    stdio_init_all();
    config_pin();
    config_button();

    while (true) {

        semaforo();

    }
    
    sleep_ms(10);
}
