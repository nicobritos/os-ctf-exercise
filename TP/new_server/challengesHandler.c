#include "challengesHandler.h"
#include <stdio.h>
#include <string.h>

#define HASH_COMMAND_LENGTH 44

typedef struct t_challengeCDT {
    const char *description;
    const char *research;
    const char *answer;
} t_challengeCDT;

void hash(char *out, char *in);

static const t_challengeCDT challenges[CHALLENGES_LENGTH] = {
    {
        "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n"
            "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
            "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
            "El desafío final consiste en crear un servidor que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta"
            "Además deberán implementar el cliente para comunicarse con este servidor.\n\n"
            "Deberán estar atentos a los desafíos ocultos.\n\n"
            "Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con \"entendido\\n\"",
        "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
        "eb112daf85b0e0fd7c662a23e53cd7b3"
    },
    {
        "# \033[D \033[A \033[A \033[D \033[B \033[C \033[B \033[D *",
        "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
        "5758b4bf840c5ace20d99eb532c71df7"
    },
    {
        "https://vocaroo.com/i/s1lD9m8lGzei",
        "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?",
        "029f8eb213944c40683dbf63b10c529b"
    },
    {
        "EBADF... abrilo y verás o redirijilo ;)",
        "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
        "4b686aae68f1cc95eea31b87c7939cb1"
    },
    {
        "respuesta = strings[250]",
        "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
        "4df7184afd235967b93670386783701d"
    },
    {
        ".data .bss .comment ? .shstrtab .symtab .strtab",
        "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?",
        "1a48227f647065a628394511d8a3d76a"
    },
    {
        "mixed fds",
        "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
        "495213ba05e806e698e596b9d826ae99"
    },
    {
        "Portrait",
        "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?",
        "ec5e1ae6629ce3c9cbc869e4fdec7814"
    },
    {
        "Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo",
        "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?",
        "97948f7a5ff8b7ff45ed8a9388f1b396"
    },
    {
        "quine",
        "¿Cuáles son las características del protocolo SCTP?",
        "062bca7bb736a217a853f7a6ad9821aa"
    },
    {
        "b gdbme y encontrá el valor mágico",
        "¿Qué es un RFC?",
        "469ce529bbe8586e554e11a297a83241"
    },
    {
        "Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto",
        NULL,
        NULL
    }
};


t_challengeADT getChallenge(uint8_t challenge) {
    if (challenge == NULL) return NULL;
    return challenges + challenge;
}

const char *getChallengeDescription(t_challengeADT challenge) {
    if (challenge == NULL) return NULL;
    return challenge->description;
}

const char *getChallengeResearchQuestion(t_challengeADT challenge) {
    if (challenge == NULL) return NULL;
    return challenge->research;
}

uint8_t isValidAnswer(t_challengeADT challenge, const char *answer) {
    if (challenge == NULL) return 0;
    char buffer[HASH_COMMAND_LENGTH];
    hash(buffer, answer);
    return strcmp(buffer, challenge->answer);
}

void hash(char *out, char *in) {
  char buffer [MAX_ANSWER_LENGTH + HASH_COMMAND_LENGTH];
  FILE *popenFile;
  
  snprintf(buffer, HASH_COMMAND_LENGTH, "echo -n \"%s\" | md5sum | cut -d \' \' -f 1", in);
  popenFile = popen(buffer, "r");
  if (popenFile == NULL) {
    perror("popen error on hash");
    exit(1);
  }

  fgets(out, HASH_COMMAND_LENGTH, popenFile);
  return;
}
