//Déclaration des bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h> // pour prompt
#include <dirent.h>  // pour ls

//Prototype
void separe(char* ligne, char** mots);

void quitter(char** mots);
void deplacer(char** mots);
void renommer(char** mots);
void changerP(char** mots);
void ls(char** mots);
void supprimer(char** mots);


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
		separe(ligne, mots); //separe met directement les mots dans le tableau mots
	    if(strcmp(mots[0], "exit") == 0) // si le mot de la ligne est exit 
		{
			quitter(mots);
		}
		else if(strcmp(mots[0], "cd") == 0)
		{
			deplacer(mots);
		}
		else if(strcmp(mots[0], "supprimer") == 0) 
		{
			supprimer(mots);
		}
		else if(strcmp(mots[0], "renommer") == 0)
		{
			renommer(mots);
		}
		else if(strcmp(mots[0], "changePrompt") == 0)
		{
			changerP(mots);
		}
		else if(strcmp(mots[0], "Lister") == 0) //lister le contenu du dossier donné en argument
		{
			ls(mots);
		}
		else if(strcmp(mots[0], "Lister_RepC") == 0)  // lister le contenu du repertoire courant
		{
			mots[1] = NULL;
			ls(mots);
		}
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
	
	mots[i++]=NULL; //pour faire en sorte qu'après le dernier mot récupéré ce soit NULL car on avait un problème sur cd 
	//exemple
}

void quitter(char** mots) //fonctionnalité quitter
{
	exit(0);
}

void deplacer(char** mots) //fonctionnalité cd
{
	if(mots[1]==NULL) //Si il n'y a pas de mot après cd
	{printf("Déplacement impossible\n");} //message d'erreur
	else if(chdir(mots[1]) != 0)
	{
		perror("sns"); // perror permet d'afficher le message d'erreur
	}
}


void supprimer(char** mots) //fonctionnalité pour supprimer un fichier
{ 
	if(mots[1]==NULL) //Si il n'y a pas de mot après supprimer 
	{printf("Suppression impossible, pas de fichier en argument.\n");} //message d'erreur
	else if(remove(mots[1]) != 0) 
	{
		perror("sns"); // perror permet d'afficher le message d'erreur
	}
}

void renommer(char** mots) //fonctionnalité pour renommer un fichier
{ 
	if(mots[1]==NULL) //s'il n'y a pas de mot après renommer 
	{printf("Fichier source introuvable.\n");} //message d'erreur
	else if(mots[2]==NULL) //s'il manque le fichier de destination
	{printf("Error: pas de fichier de destination\n");}
	else if(rename(mots[1], mots[2]) != 0) // si c'est 0 c'est bon sinon erreur
	{
		perror("sns"); // perror permet d'afficher le message d'erreur
	}
}


void changerP(char** mots) //fonctionnalité pour changer le prompt
{
	getcwd(prompt, PATH_MAX); // getcwd = get current working directory, il prend le chemin et le met dans le prompt
}

void ls(char** mots) //fonctionnalité lister
{
	DIR* dossier; //représente le dossier dont on va lister mes fichiers, DIR est dans dirent.h
	struct dirent *fichier; // struct dirent est le type de la variable qui represente un fichier
	if(mots[1]==NULL)
	{
	char dossierCourant[PATH_MAX];
	getcwd(dossierCourant, PATH_MAX);
	dossier= opendir(dossierCourant); //ouvre le dossier et permet des modifs dans ce dossier
	}
	else
	{dossier=opendir(mots[1]);
	}

	if(dossier==NULL) // si le dossier n'existe pas
	{perror(mots[1]);}
	while(fichier=readdir(dossier)) //tant qu'on arrive à recuperer le fait qu'il y ait un fichier
	//dans le dossier on affiche son nom
	{printf("%s ", fichier->d_name);}  //d_name c'est le nom du fichier

	printf("\n"); //pour que le prompt se réaffiche à la ligne et ne soit pas collé

}
