#include <ESP8266WiFi.h>
const char* ssid     = "Laboratorio";      // SSID
const char* password = "laboratorio";      // Password
const char* host = "192.168.1.6";  // IP serveur - Server IP
const int   port = 80;            // Port serveur - Server Port
const int   watchdog = 5000;        // Fréquence du watchdog - Watchdog frequency
unsigned long previousMillis = millis(); 

void setup(void)
{ 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  
  Serial.begin(9600);
 
  delay(700);

}
void loop() {
  
     int datouno = 99;
    float datodos = 99.5;   
    String datotres = "\"pepe\"";       
   

    unsigned long currentMillis = millis();
    
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
    }

    String url = "/nodeMcu/index.php?datouno=";
    url += datouno;
    url += "&datodos=";
    url += datodos;
     url += "&datotres=";
    url += datotres;
    
    // Enviamos petición al servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  
    // Leemos la respuesta del servidor
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
}
