//Déclaration des bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h> // pour prompt

//Prototype
void separe(char* ligne, char** mots);



char prompt[PATH_MAX] = "shell/SNS" ;         //path_max longueur maximale qu'un chemin peut avoir sous Linux

int main()
{
	char **mots; //pour séparer la ligne écrite en plusieurs parties
	char *ligne; // la ligne saisie
	ssize_t taille =0; // truc dont getline a besoin, avec 0 il lit jusqu'au bout de la ligne 
	separe(ligne, mots); //separe met directement les mots dans le tableau mots
	while(1) //boucle infinie
	{ 
		printf("%s$ ", prompt); //ce qui est affiché au debut de chaque ligne, %s renvoit la chaine de caractere prompt
		getline(&ligne, &taille, stdin); //on envoie la ligne au getline, le nombre de caractères et l'endroit où on ecrit
    }
    
  }


void separe(char* ligne, char** mots)
{
	char *duplication; // pour travailler sur la ligne il faut la dupliquer 
	duplication= strdup(ligne); //pour dupliquer la ligne 
	int i =0;
	char *mot= strtok(duplication, " \n\t\r"); // r et n correspondent au retour à la ligne, t correspond à la tabulation au cas où
	//strtok lit la ligne et s'arrête au moment où il trouve un espace, retour a la ligne ou tabulation 
	while(mot !=NULL) //tant qu'on a un mot
	{
		mots[i++]=mot; //il rajoute le mot dans le tableau mots
		mot=strtok(NULL, " \n\t\r"); //pour reprendre à l'endroit où strtok s'est arrêté
	}
}

