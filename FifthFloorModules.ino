#define G433_SPEED 1000
#define RADIO_DATA PB0
#define RADIO_VCC  PB3
#define ID 32
#define KEY 34
#define TYPE 11

#include <Gyver433.h>
#include <util/delay.h>

Gyver433_TX <RADIO_DATA> tx;

byte count = 15;

void setup() {
  pinMode(RADIO_VCC, OUTPUT);           // Питание радио
  pinMode(PB1, INPUT_PULLUP);           // Кнопка с подтяжко
}

void loop() {
  volatile uint8_t data[5];             // Буфер
  data[0] = ID >> 8;                       // Адрес
  data[1] = ID;                       // Адрес
  data[2] = KEY;
  data[3] = TYPE;
  data[4] = 0; // Состояние кнопки

  count += 1;
  if (count > 20) {
    data[4] = 1;
    count = 15;
  }
  digitalWrite(RADIO_VCC, HIGH);        // Запитываем
  _delay_ms(1);                         // Немного ждем
  tx.sendData(data);                    // Отправляем пакет
  digitalWrite(RADIO_VCC, LOW);         // Отключаем и идем спать
  _delay_ms(3000);
}