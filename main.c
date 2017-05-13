//Déclaration des bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h> // pour prompt

char prompt[PATH_MAX] = "shell/SNS" ;         //path_max longueur maximale qu'un chemin peut avoir sous Linux

int main()
{
	char **mots; //pour séparer la ligne écrite en plusieurs parties
	char *ligne; // la ligne saisie
	ssize_t taille =0; // truc dont getline a besoin, avec 0 il lit jusqu'au bout de la ligne 
	while(1) //boucle infinie
	{ 
		printf("%s$ ", prompt); //ce qui est affiché au debut de chaque ligne, %s renvoit la chaine de caractere prompt
		getline(&ligne, &taille, stdin); //on envoie la ligne au getline, le nombre de caractères et l'endroit où on ecrit
    }
    
  }

//Test 
