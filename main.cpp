//=====[Libraries]=========================================
#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]============================================
#define SEG_A D7
#define SEG_B D8
#define SEG_C D2
#define SEG_D D3
#define SEG_E D4
#define SEG_F D5
#define SEG_G D6

#define LED_R D11
#define LED_G D12

#define RESET_BUTTON BUTTON1
#define BUTTON_DOWN D9
#define BUTTON_UP D10

#define UART_TX USBTX
#define UART_RX USBRX

#define BAUD_RATE 9600
#define DATE_LENGTH 10

#define INIT_MESSAGE_DELAY 2000
#define DEBOUNCE_TIME 20

//=====[Declaration and initialization of public global objects]==============
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

//Entradas digitales
DigitalIn resetButton(RESET_BUTTON);
DigitalIn buttonDown(BUTTON_DOWN, PullDown);
DigitalIn buttonUp(BUTTON_UP, PullDown);

UnbufferedSerial uartUsb(UART_TX, UART_RX, BAUD_RATE); //Comunicacion serial

// Arreglo para los segmentos del display
DigitalOut segments[] = {segA, segB, segC, segD, segE, segF, segG};

// Patrones para los dígitos en el display de 7 segmentos (cátodo común) (Tabla)
const int digitPatterns[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

//=====[Declaration and initialization of public global variables]=============
int counter = 9; //Almacena lugares siponibles
char date[DATE_LENGTH + 1]; // Para almacenar la fecha ingresada (dd/mm/aaaa)
bool dateRequested = false;
bool dateReceived = false;

//=====[Declarations (prototypes) of public functions]=========================
void showDigit(int digit);
void updateLEDs(int counter);
bool isButtonPressed(DigitalIn &button);
void sendCount(int count);
void requestDate();
void readDate();
void initializeSystem();
void handleButtonPress();
size_t getStringLength(const char* str);

//=====[Main function]========================
int main() {
    initializeSystem();

    while (true) {
        if (!dateRequested && resetButton.read() == 1) {
            requestDate();
        }

        if (dateRequested && !dateReceived) {
            readDate();
        }

        if (dateReceived) {
            showDigit(counter);
            updateLEDs(counter);   
        }

        handleButtonPress();
    }
}


//=====[Implementations of public functions]===================================

// Función para inicializar el sistema
void initializeSystem() {
    uartUsb.write("Iniciando sistema...\n\r", 20);
    uartUsb.write("\n\r", 2); 
    delay(INIT_MESSAGE_DELAY);
    uartUsb.write("Sistema iniciado.\n", 18);
    
}

// Función para solicitar la fecha al usuario
void requestDate() {
    uartUsb.write("Por favor, ingrese la fecha en formato dd/mm/aaaa:\r\n\r\n", 51); 
    dateRequested = true;
}
 // Función para leer la fecha ingresada por el usuario
void readDate() {
    static int index = 0;
    char c;
    if (uartUsb.readable()) {
        uartUsb.read(&c, 1);  // Leer un carácter por comunicación serial
        date[index++] = c;  
        if (index >= DATE_LENGTH) {
            date[DATE_LENGTH] = '\0';  // Agregar terminación nula para formar una cadena de caracteres
            dateReceived = true;  
            uartUsb.write("\r\nIngreso exitoso.\r\n\r\n", 21); // Enviar mensaje de ingreso exitoso
            index = 0;  
        }
    }
}

// Función para manejar el debounce del botón
bool isButtonPressed(DigitalIn &button) {
    if (button.read() == 1) { // Si el botón está presionado
        delay(DEBOUNCE_TIME); // Esperar 20ms para el debounce
        if (button.read() == 1) { // Verificar nuevamente el estado del botón
            while (button.read() == 1) {} // Esperar a que se suelte el botón
            return true;
        }
    }
    return false;
}

// Función para manejar la lógica de los botones
void handleButtonPress() {
    if (isButtonPressed(buttonUp)) {
        if (counter < 9) {
            counter++;
            showDigit(counter);
            updateLEDs(counter);
            sendCount(counter);
        }
    }

    if (isButtonPressed(buttonDown)) {
        if (counter > 0) {
            counter--;
            showDigit(counter);
            updateLEDs(counter);
            sendCount(counter);
        }
    }
}

// Función para mostrar un dígito en el display de 7 segmentos
void showDigit(int digit) {
    for (int i = 0; i < 7; i++) {
        segments[i] = digitPatterns[digit][i];
    }
}

// Función para actualizar los LEDs externos
void updateLEDs(int counter) {
    if (counter == 0) {
        ledR = 1;  // Encender LED rojo
        ledG = 0;  // Apagar LED verde
    } else {
        ledR = 0;  // Apagar LED rojo
        ledG = 1;  // Encender LED verde
    }
}

// Función para enviar el conteo por comunicación serial (Upon successful return, these functions return the number of characters
//printed (excluding the null byte used to end output to strings).
void sendCount(int count) {
    char buffer[30];
    int length = sprintf(buffer, "Lugares disponibles: %d\n", count);
    uartUsb.write(buffer, length);
}
