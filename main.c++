#include <HCSR04.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <BluetoothSerial.h>

float distancia;
float porcentagem;

BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd(0x27, 16, 2);
UltraSonicDistanceSensor distanceSensor(4, 2);

void setup() 
{
    Serial.begin(115200); // Inicializa a comunicação serial com o PC
    SerialBT.begin("ESP32_BT"); // Inicializa o Bluetooth com o nome "ESP32_BT"
    lcd.init();
    lcd.backlight();
}

void loop() 
{

    distancia = 38 - distanceSensor.measureDistanceCm();
    Serial.print("Distância do sensor: ");
    Serial.print(distanceSensor.measureDistanceCm());
    Serial.print("  Altura da lixeira: ");
    porcentagem = distancia * 100 / 38;
    
    if (distancia < 0)
    {
        distancia = 0;
    }

    if (porcentagem < 0) 
    {
        porcentagem = 0;
    }

    lcd.setCursor(0, 0);
    lcd.print("Valor da Lixeira");

    lcd.setCursor(0, 1);

    if (distancia <= 0 || distanceSensor.measureDistanceCm() < 0) 
    {
        lcd.print("Lixeira Aberta..");
    } 
    if (distancia >= 38) 
    {
        if(distancia == 39){
          lcd.print("Lixeira Aberta..");
        }else
          lcd.print("Lixeira Cheia...");
    } 
    else 
    {
        lcd.print("                "); // Limpa a linha
        lcd.setCursor(0, 1);
        lcd.print(distancia);
        lcd.setCursor(5, 1);
        lcd.print("cm");
        lcd.setCursor(8, 1);
        lcd.print("  ");
        lcd.setCursor(10, 1);
        lcd.print(porcentagem);
        lcd.setCursor(15, 1);
        lcd.print("%");
        
    }
    
    Serial.println(distancia); // Envia a distância para o Serial Monitor
    SerialBT.print(porcentagem); // Envia a porcentagem via Bluetooth
    delay(5000);
}
