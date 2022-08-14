#include <NetworkManager.hpp>
#include <SPIFFS.h>

const char* readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
  }

  String fileContent;
  char* fileContentChar; 
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;
  }
  fileContent.toCharArray(fileContentChar, 100, (uint16_t)0);
  return (const char*)fileContentChar;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}