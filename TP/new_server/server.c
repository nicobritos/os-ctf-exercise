#include "challengesHandler.h"
#include "clientConnection.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define PORT 23423
#define HASH_BUFFER 40
#define STRING_BUFFER 1024

void main() {
  char stringBuffer[STRING_BUFFER];
  char hashBuffer[HASH_BUFFER];
  int hashCompareResult;
  uint8_t challenge = 0;
  int clientFD;

  clientFD = serve(PORT);
  while (1) {
    system("clear");
    // // exitInMenu11(challenge, stringBuffer);
    // printf("------------- DESAFIO -------------");
    // printf("%s", getChallenge(challenge));
    // if (funciones[(long)challenge] != (void *)0x0) {
    //   (*(code *)funciones[(long)challenge])();
    // }
    // puts("\n----- PREGUNTA PARA INVESTIGAR -----");
    // decodeSavedString(preguntasInvestigar + (long)challenge * 0x2c6,stringBuffer);
    // printf("%s",stringBuffer);
    receive(clientFD, stringBuffer, STRING_BUFFER);
    // hash(stringBuffer,hashBuffer);
    // hashCompareResult = strcmp(hashBuffer,hashes[(long)challenge]);
    // if (hashCompareResult == 0) {
    //   puts("Respuesta correcta");
    //   challenge += 1;
    // }
    // else {
    //   printf("Respuesta incorrecta: %s",stringBuffer);
    // }
    sleep(1);
  }
}

