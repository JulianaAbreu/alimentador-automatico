#include <UIPEthernet.h>
#include <utility/logging.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <AFMotor.h>

byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x05 };
IPAddress ip(192, 169, 100, 100);

// MQTT
long lastReconnectAttempt = 0;
const char *server = "m11.cloudmqtt.com";
const char *user = "*****";
const char *pass = "**********";
const int port = 19604;
const char* mqttTopicSub ="motorcomando";

// Pinos
AF_DCMotor motor(3);
const int PIR = 8;

// Intervalo
unsigned long previousMillis = 0;
static const long intervalo = 0;

// handle message arrived
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Callback: ");
  Serial.println(topic);
  payload[length]='\0';
  String msg = String((char*)payload);

  Serial.print("Tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem: ");
  Serial.print(msg);
  Serial.println("xxxxxxxxxxx");

  if(msg == "1") {
    Serial.println("Liga motor");
    motor.setSpeed(255);
    motor.run(FORWARD);
    delay(2000);
    motor.setSpeed(0);
  } else if(msg == "0") {
    Serial.println("Desliga motor");
    motor.setSpeed(0);
  }
}

EthernetClient ethClient;
PubSubClient client(server, port, callback, ethClient);

// reconnect in mqtt
boolean reconnect() {
  Serial.println("Tentando conectar...");
  if (client.connect("arduino", user, pass)) {
    Serial.println("Conectado");
    if (client.subscribe("presence")) {
      Serial.println("Inscrito em presencacomando");
    }
    if (client.subscribe("motorcomando")) {
      Serial.println("Inscrito em motorcomando");
    }
  }
  return client.connected();
}

void setup() {
  pinMode(PIR, INPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial ok");

  //Ethernet
  Ethernet.begin(mac);
  lastReconnectAttempt = 0;
  Serial.println("Tentando conectar...");
  
  //MQTT
  if (client.connect("arduino", user, pass)) {
    Serial.println("Conectado!");
  }  else {
    Serial.println("Falhou conex. MQTT!");
  }

  // subscribe in topic
  Serial.println("se inscreveu no topico");
  client.subscribe(mqttTopicSub);
}

void loop() {
 bool leitura = digitalRead(PIR);
 unsigned long currentMillis = millis();

  if(leitura == HIGH) {
    // after detecting presence, 2 hour interval
    if(currentMillis - previousMillis >= intervalo) {
        previousMillis = currentMillis;
        detectPresence("presence", leitura);
        Serial.println("Pet Detectado");
        openMotor("motorcomando", "1");
      }
  }

 Serial.flush();
  if (!client.connected()) {
    Serial.println("Desconectado");
    long now = millis();
    if (now - lastReconnectAttempt > 2500) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    client.loop();
  }
  
}

// detect presence and subscribe to MQTT
void detectPresence(char* topic, int detected) {
  if(client.connected()){
    if(detected) {
        if(client.publish(topic, "HIGH")) {
          Serial.println("Enviado");
          Serial.println(topic);
         }
      }  
  }
}

// open motor and subscribe to MQTT
void openMotor(char* topic, int estado) {
  if(client.connected()){
    if(estado == "1") {
       if(client.publish(topic, estado)) {
          Serial.println("Enviado");
          motor.setSpeed(2000);
          delay(500);
          motor.setSpeed(0);
        } 
    }
  }
}
