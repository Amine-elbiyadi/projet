#include <stdio.h>
#include<stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char* nomFil[50];
typedef struct {
    int day ;
    int month ; 
    int year ;
}DateNaissance;

typedef struct {
    char nomMod[50];
    float note; 
}Module;

typedef struct {
    char nomFi[50];
    int nbrMod; 
    Module *mod ;
    float moyenne ;
}Filiere;

typedef struct {
    char nomEc[50];
    int nbrFi;
    Filiere * filiere ;
}Ecole;

typedef struct Etudiant{
    char nom[50];
    char prenom[50];
    int age ;
    int ID;
    DateNaissance DT ;
    Filiere *filiere ;
    struct Etudiant *next ;
}Etudiant; 

typedef struct list{
    Etudiant* head;
    Etudiant* tail ;
}list;

bool CheckAje(DateNaissance date , int age ){
    int age1 ;
    time_t t;
    struct tm *currentTime;
    t = time(NULL);
    currentTime = localtime(&t);
    age1 = currentTime->tm_year + 1900 - date.year;
    if (currentTime->tm_mon + 1 <  date.month || (currentTime->tm_mon + 1 == date.month && currentTime->tm_mday < date.day)) {
        age1--; 
    }
    if (age == age1){
        return true;
    }
    else {
        return false ; 
    }
}

bool chekckID (Etudiant *etu){
    int i = 0; 
    while(nomFil[i]!= "\0"){
        if (recherchEtfID(etu,nomFil[i])){
            return true ;
        }
        i++;
    }
    return false ;
}
// la creation d un seulle etudiant 
Etudiant* creeEt(int nbrEtu ){
    Etudiant* etu ;
    etu = malloc(sizeof (Etudiant));
    if (etu == NULL ){
        printf ("Memory allocation failed!\n");
        return NULL;
    }
    printf("donner l'ID d etudiant %d :\n",nbrEtu);
    scanf("%d",&etu->ID);
    while (etu->ID >= 10000000 ){
        printf ("Inavalide id , vou devez entre un id de au plus 7 chifre !! \n");
        printf("Redonner l'ID d etudiant %d :",nbrEtu);
        scanf("%d",&etu->ID);
    }
    getchar();  // To consume the newline left by scanf
    printf("donner le nom d etudiant %d :",nbrEtu);
    fgets(etu->nom,sizeof(etu->nom),stdin);
    etu->nom[strcspn(etu->nom, "\n")] = '\0';
    printf("donner le prenom d etudiant %d :",nbrEtu);
    fgets(etu->prenom,sizeof(etu->prenom),stdin); 
    etu->prenom[strcspn(etu->prenom, "\n")] = '\0';
    printf("donner la date de naissance d etudiant %d :\n",nbrEtu);
    printf("\tdonner le jour :");
    scanf("%d",&etu->DT.day);
    printf("\tdonner le moi :");
    scanf("%d",&etu->DT.month);
    printf("\tdonner l annee  :");
    scanf("%d",&etu->DT.year);
    printf("donner l age  d etudiant %d :",nbrEtu);
    scanf("%d",&etu->age);
    while(!CheckAje(etu->DT,etu->age)){
        printf("L'age que vous avez entré ne correspond pas à la date de naissance !!\n");
        printf("Veuillez entrer les informations de nouveau :\n");
        printf("donner la date de naissance d etudiant %d :\n",nbrEtu);
        printf("\tdonner le jour :");
        scanf("%d",&etu->DT.day);
        printf("\tdonner le moi :");
        scanf("%d",&etu->DT.month);
        printf("\tdonner l annee  :");
        scanf("%d",&etu->DT.year);
        printf("donner l age  d etudiant %d : ",nbrEtu);
        scanf("%d",&etu->age);
    }
    printf("donner le nom de filiere dans la quelle l etudiant %d :",nbrEtu);
    fgets(etu->filiere->nomFi,sizeof(etu->filiere->nomFi),stdin);
    etu->filiere->nomFi[strcspn(etu->filiere->nomFi, "\n")] = '\0';
    etu->next = NULL;
    return etu ;
}
// la creation d une liste des etudiants
void creatlist(list * list ,int nbrEt){
    if(nbrEt == 0 ){
        return ;
    }
    Etudiant * tmp ;
    list->head = tmp = creeEt(1);
    for (int i = 1 ; i < nbrEt ; i++ ){
        tmp->next = creeEt(i);
        tmp = tmp->next; 
    }

}
//recher d un etudiant dans un file
bool recherchEtfNOM(Etudiant *etu,char * nomFil){
    Etudiant et;
    FILE * P ;
    P = fopen(nomFil,"r+");
    while (fscanf(P,"%d ,%s,%s,%d,%d-%d-%d,%s",et.ID,et.nom,et.prenom,et.age, et.DT.day,et.DT.month,et.DT.year,et.filiere->nomFi)==8){
        if (strcasecmp(et.nom,etu->nom) && strcasecmp(et.prenom,etu->prenom)){
            printf ("l'etudiant %s %s est trouve dans cette filiere !!",etu->nom,etu->prenom);
            etu = &et;
            return true ;
        }
    }
    return false;
}
//recherch par id 
bool recherchEtfID(Etudiant *etu,char * nomFil){
    Etudiant et;
    FILE * P ;
    P = fopen(nomFil,"r+");
    while (fscanf(P,"%d ,%s,%s,%d,%d-%d-%d,%s",et.ID,et.nom,et.prenom,et.age, et.DT.day,et.DT.month,et.DT.year,et.filiere->nomFi)==8){
        if (et.ID==etu->ID){
            printf ("l'etudiant de l'id : %d est trouve dans cette filiere !!",etu->ID);
            etu = &et;
            return true ;
        }
    }
    return false;
}


list* creeList( ){
    list *list;
    list->head=NULL;
    list->tail=NULL;
    return list;
}

list * ajoterList( list * list, Etudiant etudiant){
    
    if (list->head == NULL){
        list->head = &etudiant;
        list->tail = &etudiant;
        return list ;
    }
    list->tail->next = &etudiant;
    list->tail = &etudiant;
    return list ;
} 

Etudiant* recherchEtfAge(int * age ){
    Etudiant *et;
    FILE * P ;
    int i = 0;
    while(nomFil[i]!= "\0" ){
        P = fopen(nomFil[i],"r+");
        while (fscanf(P,"%d ,%s,%s,%d,%d-%d-%d,%s",et->ID,et->nom,et->prenom,et->age, et->DT.day,et->DT.month,et->DT.year,et->filiere->nomFi)==8){
            if (age == et->age){
                 = &et;
                return true ;
            }
        }
        i++;
    }
    return false;
}

int main (){
    Etudiant* etu ;
    etu = creeEt(1);
}                                                                                                                                                         