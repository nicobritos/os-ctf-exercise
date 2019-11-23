#include "stringHelper.h"
#include <stdio.h>
#include <stdint.h>

#define HASH_COMMAND_LENGTH 40

static const char *challenges[MENUS_LENGTH] = {
    "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n"
        "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
        "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
        "El desafío final consiste en crear un servidor que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta"
        "Además deberán implementar el cliente para comunicarse con este servidor.\n\n"
        "Deberán estar atentos a los desafíos ocultos.\n\n"
        "Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con \"entendido\\n\"",
    "# \033[D \033[A \033[A \033[D \033[B \033[C \033[B \033[D *",
    "https://vocaroo.com/i/s1lD9m8lGzei",
    "EBADF... abrilo y verás o redirijilo ;)",
    "respuesta = strings[250]",
    ".data .bss .comment ? .shstrtab .symtab .strtab",
    "mixed fds",
    "Portrait",
    "Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo",
    "quine",
    "b gdbme y encontrá el valor mágico",
    "Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto"
};

static const char *researchQuestions[RESEARCH_QUESTIONS_LENGTH] = {
    "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
    "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
    "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?",
    "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
    "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
    "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?",
    "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
    "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?",
    "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?",
    "¿Cuáles son las características del protocolo SCTP?",
    "¿Qué es un RFC?"
};

static const char *hashes[HASHES_LENGTH] = {
    "eb112daf85b0e0fd7c662a23e53cd7b3",
    "5758b4bf840c5ace20d99eb532c71df7",
    "029f8eb213944c40683dbf63b10c529b",
    "4b686aae68f1cc95eea31b87c7939cb1",
    "4df7184afd235967b93670386783701d",
    "1a48227f647065a628394511d8a3d76a",
    "495213ba05e806e698e596b9d826ae99",
    "ec5e1ae6629ce3c9cbc869e4fdec7814",
    "97948f7a5ff8b7ff45ed8a9388f1b396",
    "062bca7bb736a217a853f7a6ad9821aa",
    "469ce529bbe8586e554e11a297a83241"
};

const char *getChallenge(uint8_t challenge) {
    if (challenge >= MENUS_LENGTH) return NULL;
    return challenges[challenge];
}

const char *getResearchQuestion(uint8_t challenge) {
    if (challenge >= RESEARCH_QUESTIONS_LENGTH) return NULL;
    return researchQuestions[challenge];
}

const char *getAnswerHash(uint8_t challenge) {
    if (challenge >= HASHES_LENGTH) return NULL;
    return hashes[challenge];
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

  fgets(out, 0x28, popenFile);
  return;
}
