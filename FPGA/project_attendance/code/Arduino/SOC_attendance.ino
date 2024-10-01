 #include <BluetoothSerial.h>

BluetoothSerial SerialBT;

esp_spp_sec_t sec_mask = ESP_SPP_SEC_NONE;
esp_spp_role_t role = ESP_SPP_ROLE_MASTER;

std::map<String, String> deviceAddresses = {
  {"SOC1", "98:DA:60:04:C9:33"},
  {"SOC2", "98:DA:60:08:1B:1E"},
  {"SOC3", "98:DA:60:04:FA:64"},
  {"SOC4", "98:DA:60:07:B8:F6"},
  {"SOC5", "98:DA:60:04:A0:BA"},
  {"SOC6", "98:DA:60:05:22:84"},
  {"SOC7", "98:DA:60:05:24:4D"},
  {"SOC8", "98:DA:60:05:67:EF"},
  {"SOC9", "98:DA:60:04:C9:97"}
};

BTAddress createBTAddress(const String& addrStr) {
  // BTAddress 생성자를 통해 주소를 직접 초기화
  BTAddress addr(addrStr.c_str());
  return addr;
}

void connect_bt(const String& name) {
  Serial.printf("%s에 연결 시도\n", name.c_str());
  
  if (deviceAddresses.find(name) != deviceAddresses.end()) {
    String addrStr = deviceAddresses[name];
    BTAddress addr = createBTAddress(addrStr);

    Serial.printf("Connecting to %s at address %s\n", name.c_str(), addr.toString().c_str());
    
    if (SerialBT.connect(addr, 1, sec_mask, role)) {
      Serial.printf("Connection to %s successful!\n", name.c_str());
    } else {
      Serial.printf("Connection to %s failed\n", name.c_str());
    }
  } else {
    Serial.printf("No saved address info for %s\n", name.c_str());
  }
}

void disconnectDevice() {
  if (SerialBT.connected()) {
    SerialBT.disconnect();
    Serial.printf("블루투스 연결 해제\n");
  }
}

void uart(const String& name) {
  Serial.printf("uart start\n");

  String sendData = "Q";
  String receivedString_prod = "";
  String receivedString_student = "";
  
  Serial.printf("Q전송1\n");
  delay(100);
  Serial2.print(sendData);

  while (Serial2.available() > 0) {
    char key = Serial2.read();
    receivedString_prod += key;
  }
  delay(100);

  if (receivedString_prod.length() > 0) {
    Serial.printf("인증 key: ");
    Serial.printf(receivedString_prod.c_str());
    Serial.printf("\n");
  }

  SerialBT.print(sendData);
  delay(100);

  while (SerialBT.available() > 0) {
    char key = SerialBT.read();
    receivedString_student += key;
  }
  delay(100);

  if (receivedString_student.length() > 0) {
    Serial.printf("학생 key: ");
    Serial.printf(receivedString_student.c_str());
    Serial.printf("\n");
  }

  bool isAuthenticated = (receivedString_prod == receivedString_student);
  sendResponse(name, isAuthenticated);
  receivedString_prod = "";
  receivedString_student = "";
}

void sendResponse(const String& name, bool isAuthenticated) {
  String responseChar;
  String btResponseChar;

  // 인증 상태에 따라 응답을 설정합니다.
  if (isAuthenticated) {
    responseChar = (name == "SOC1") ? '1' :
                   (name == "SOC2") ? '2' :
                   (name == "SOC3") ? '3' : 
                   (name == "SOC4") ? '4' :
                   (name == "SOC5") ? '5' :
                   (name == "SOC6") ? '6' :
                   (name == "SOC7") ? '7' :
                   (name == "SOC8") ? '8' : '9';
    btResponseChar = '1';
  } else {
    responseChar = (name == "SOC1") ? 'A' :
                   (name == "SOC2") ? 'B' :
                   (name == "SOC3") ? 'C' :
                   (name == "SOC4") ? 'D' :
                   (name == "SOC5") ? 'E' :
                   (name == "SOC6") ? 'F' :
                   (name == "SOC7") ? 'G' :
                   (name == "SOC8") ? 'H' : 'I';
    btResponseChar = '0';
  }

  Serial2.print(responseChar);
  SerialBT.print(btResponseChar);
  delay(100);
}

void cntrl(const String& device){
  connect_bt(device);
  if(SerialBT.connected()){
    uart(device);
    disconnectDevice();
  }
  delay(100);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  if (!SerialBT.begin("ESP32test", true)) {
    Serial.printf("블루투스 설정 실패");
    abort();
  }
}

void loop() {
  cntrl("SOC1");
  cntrl("SOC2");
  cntrl("SOC3");
  cntrl("SOC4");
  // cntrl("SOC5");
  // cntrl("SOC6");
  // cntrl("SOC7");
  // cntrl("SOC8");
  // cntrl("SOC9");
}