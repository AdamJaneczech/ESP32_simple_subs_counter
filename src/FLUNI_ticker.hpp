#include <NetworkManager.hpp>
#include <SPIFFS.h>

const char* readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
  }
  int msg_len = 0; 
  while(file.available()){
    //fileContentChar += file.read();
    Serial.write(char(file.read()));
    msg_len++;
  }
  const char* fileContentChar = new char[msg_len];
  return fileContentChar;
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
  file.close();
}