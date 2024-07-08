# Sistema de estacionamiento inteligente

## Trabajo Practico 1 - Curso Sistemas embebidos - ArmBook 2024

## Alumno : 
* Diaz Mateo - mateo99.d@gmail.com

## Profesores : 
- Ariel Lutenberg 
- Sergio Caprile  
- Juan Manuel Reta 
- Eduardo Filomena

## Descripción
Este proyecto implementa un sistema de estacionamiento autonomo e inteligente utilizando la plataforma MBED. El objetivo ese llevar el control de un estacionamiento de vehiculos de manera autonoma. En esta primera instancia se simula el control de ingreso al establecimiento, como asi tambien la disponibilidad en el mismo.

El sistema se compone de 2 botones que simulan el ingreso(verde) y egreso(rojo) de los vehiculos, dos leds que indican si existe o no disponibilidad para el ingreso, y un display 7 segmentos que le muestra al usuario la cantidad de lugares disponibles.


## Desarrollo
### Circuito
El proyecto se basó en la placa de desarrollo STM32F4, en particular el modeloSTM32F401RE. La misma cuenta con un microcontrolador STM32F401RET6, el cual posee un núcleo ARM Cortex-M4. El resto de componentes se planteo en una protoboard como se mostrara en siguientes imagenes.

#### Placa de desarrollo:
*NUCLEO_F401RE

![placa_desarrollo](https://github.com/mateooD/Tp1_armBookCourse_2024/blob/main/figures/placa_desarrollo.png)

Podemos plantear un diagrama como el siguiente:

![diagrama_bloques](https://github.com/mateooD/Tp1_armBookCourse_2024/blob/main/figures/diagrama_bloques.png)



### Funcionamiento

En primer lugar se pretende que el sistema arranque apagado, y en el monitor serial se cargue la fecha de trabajo. Una vez hecho eso, el sistema partirá en este caso con todos los lugares disponibles.Se simulara enotnces la salida y entrada de vehiculos con botones,y se mostrará en el display los lugares disponibles.En caso de que no exista mas lugar disponible, se encendera luz roja, de lo contrario una luz verde estará encendida.
La alimentacion de todo el sistema en este caso se utilizaron las salidas de 3,3v y GND de la placa.
Para que se puedan visualizar los valores en pantalla por comunicacion serial, se debió incluir el archivo mbed_app.json para que la combinación %2.f sea correctamente interpretada en el compilador.

### Asignacion Pines
Salidas digitales:
```cpp
//Salidas digitales display
DigitalOut segA(SEG_A);
DigitalOut segB(SEG_B);
DigitalOut segC(SEG_C);
DigitalOut segD(SEG_D);
DigitalOut segE(SEG_E);
DigitalOut segF(SEG_F);
DigitalOut segG(SEG_G);

//Leds externos
DigitalOut ledR(LED_R);
DigitalOut ledG(LED_G);
```
Entradas Digitales:
```cpp

DigitalIn resetButton(RESET_BUTTON);
DigitalIn buttonDown(BUTTON_DOWN, PullDown);
DigitalIn buttonUp(BUTTON_UP, PullDown);

```
Comunicación serial:
```cpp
UnbufferedSerial uartUsb(UART_TX, UART_RX, BAUD_RATE); //Comunicacion serial

```
### Perifericos a utilizar:

- **Button Reset** : Inicio del sistema 
- **Button Green** : Ingreso vehiculo
- **Button Red** : Egreso vehiculo
- **Led Green** : Lugares disponibles
- **Led Red** : Estacionamiento lleno
- **Display 7Seg** : Visibilidad lugares disponibles
- **Uart** : Comunicación con PC



## Imagenes del circuito y funcionamiento

### Imagenes circuito

Situacion con lugares disponibles:

![7_places](https://github.com/mateooD/Tp1_armBookCourse_2024/blob/main/figures/7_places.jpeg)

Situacion sin lugares disponibles:

![0_places](https://github.com/mateooD/Tp1_armBookCourse_2024/blob/main/figures/0_places.jpeg)

### Comunicacion serial PC

Mensaje de ingreso y muestra de lugares disponibles en el establecimiento:

![monitor_serial](https://github.com/mateooD/Tp1_armBookCourse_2024/blob/main/figures/serial_monitor.png)


### Video Funcionamiento
:construction: En proceso :construction:

## Codigo
En el repositorio se encuentran el archivo main, junto con las librerias necesarias para el funcionamiento

Esta en desarrollo la documentacion con ***Doxygen***.

:construction: En proceso :construction:

**solicitud revision**