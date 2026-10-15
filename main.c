#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable:4996)

enum {TAILLECMD = 31};

int main() {
  char saisie[TAILLECMD];
  printf("Voici les differentes commandes:\nEXIT\nINSCRIRE\nPARTICIPANTS\nCREER\nCONCOURS\nGAIN\nSCORES\nCLASSEMENT\nCOMPARAISON\nBILAN\nVeuillez entre une de ces commandes:\t ");
  scanf("%s", &saisie);
  do {

  } while (strcmp(saisie, "EXIT" != 0)); //dès que exit ça plante tout
}
