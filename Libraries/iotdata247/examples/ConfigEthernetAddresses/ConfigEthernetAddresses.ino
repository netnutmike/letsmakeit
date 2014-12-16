/*****************
 * Setting Ethernet Addresses for a SKAARHOJ device
 * 
 * - kasper
 */





// Including libraries: 
#include <EEPROM.h>      // For storing IP numbers

// MAC address for this *particular* Ethernet Shield!
// MAC address is printed on the shield
static uint8_t mac[] = { 
  0x90, 0xA2, 0xDA, 0x0D, 0x3F, 0xB6 };    // MAC address of your SKAARHOJ device

static uint8_t ip[] = {
  192, 168, 10, 99 };    // IP address of your SKAARHOJ device, typical default is 192.168.10.99

static uint8_t atemip[] = {
  192, 168, 10, 240 };    // IP address of your ATEM switcher, factory default is 192.168.10.240



char buffer[18];

void setup() { 
  Serial.begin(9600);
  Serial.println("\n- - - - - - - -\nSerial Started (ConfigEthernetAddresses)\n");


  // *********************************
  // INITIALIZE EEPROM memory:
  // *********************************
  // EEPROM MEMORY, Official list:
  // 0-1:  Initialization check
  // 2-5:  Arduino IP
  // 6-9:  ATEM IP
  // 10-16: Arduino MAC address (6+1 byte)
  // 17: Reboot counter
  // 20-24: 1st Robotic Camera
  // 25-29: 2nd Robotic Camera
  // 30-34: 3rd Robotic Camera
  // 35-39: 4th Robotic Camera
  // 40-44: 2nd ATEM (ATEM::ConfigEthernetAddressesExtended)
  // 45-49: Videohub (ATEM::ConfigEthernetAddressesExtended)
  // 50-66: TouchScreen Calibration (SkaarhojUtils::Touch_Calibrate)
  // 200-:  User defined.
  
  
  // Set these random values so this initialization is only run once! 
  // These values confirm that Device IP and ATEM IP has been set at some point (they don't have checksums)
  EEPROM.write(0,12);
  EEPROM.write(1,232);

  // Set default IP address for Arduino (192.168.10.99)
  EEPROM.write(2,ip[0]);
  EEPROM.write(3,ip[1]);
  EEPROM.write(4,ip[2]);
  EEPROM.write(5,ip[3]);
  sprintf(buffer, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  Serial.print("Storing SKAARHOJ Device (Arduino) IP address: \n    ");
  Serial.println(buffer);

  // Set default IP address for ATEM Switcher (192.168.10.240):
  EEPROM.write(6,atemip[0]);
  EEPROM.write(7,atemip[1]);
  EEPROM.write(8,atemip[2]);
  EEPROM.write(9,atemip[3]);
  sprintf(buffer, "%d.%d.%d.%d", atemip[0], atemip[1], atemip[2], atemip[3]);
  Serial.print("Storing ATEM IP address: \n    ");
  Serial.println(buffer);


  // Set MAC address + checksum:
  EEPROM.write(10,mac[0]);
  EEPROM.write(11,mac[1]);
  EEPROM.write(12,mac[2]);
  EEPROM.write(13,mac[3]);
  EEPROM.write(14,mac[4]);
  EEPROM.write(15,mac[5]);
  EEPROM.write(16, (mac[0]+mac[1]+mac[2]+mac[3]+mac[4]+mac[5]) & 0xFF);

  sprintf(buffer, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.print("Storing SKAARHOJ Device (Arduino) MAC address: \n    ");
  Serial.print(buffer);
  Serial.print(" - Checksum: ");
  Serial.println(EEPROM.read(16));


  EEPROM.write(17,0);

  Serial.println("DONE! Everything worked! Now, time to upload the sketch for this model...\n");
}

void loop() {
}

