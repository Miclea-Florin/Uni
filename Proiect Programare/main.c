#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
int coduri[100000]={0};

#define GREEN 2
#define BLUE 3
#define RED 12
#define YELLOW 14
#define WHITE 15

void set_color(int color_code) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}


int valid_date(char var[15]){
        int dd,mm,yy;
        if(strlen(var)!=8)
            return 0;
        int DATA_=atoi(var);
        ///20220609;
        dd=DATA_%100;
        mm=DATA_/100%100;
        yy=DATA_/10000;
        //printf("dd=%d ; mm=%d ; yy=%d",dd,mm,yy);

        //check year
        if(yy>=1900 && yy<=9999)
        {
            //check month
            if(mm>=1 && mm<=12)
            {
                //check days
                if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                    return 1;
                else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                    return 1;
                else if((dd>=1 && dd<=28) && (mm==2))
                    return 1;
                else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
                    return 1;
                else {
                    set_color(RED);
                    printf("Data introdusa nu este valida!\n");
                    set_color(WHITE);
                    return 0; }
            }
            else
            {
                set_color(RED);
                printf("Data introdusa nu este valida!\n");
                set_color(WHITE);
                return 0;
            }
        }
        else
        {
            set_color(RED);
            printf("Data introdusa nu este valida!\n");
            set_color(WHITE);
            return 0;
        }

        return 1;


}

struct disponibilitate{
    char d[15];
    int val; // <=9999 disponibil  # 10000 => COD REZERVARE
};


struct vehicul{
    char marca[50];
    char tip[50];
    struct disponibilitate disp; // 1- disponibil | 0-indisponibil //
    int numar_locuri;
    char nr_inmatriculare[50];
    char culoare[50];
    int an;

}v[400];
int n=0; // o sa fie citire din fisier si nu o sa mai fie nevoie ca n sa fie 0 la inceput

int cod_unic(){
srand(time(NULL));   // Initialization, should only be called once.
int r = rand();

r=r%1000;
while(r<10000)
r=r*10+rand()%10;
return r;
}


void adauga(){
    printf("Doriti sa continuati? (1/0)\n");
    int back;
    scanf("%d",&back);
    if(back == 0)
        return;

    printf("Introduceti datele\n");
    printf("Marca:");
    scanf("%s",&v[n].marca);
    printf("Tip:");
    scanf("%s",&v[n].tip);
    //printf("Disponibilitate (1- disponibil | 0-indisponibil):");
    //scanf("%d",&v[n].disp);
    strcpy(v[n].disp.d,"YYYY/MM//DD");
    v[n].disp.val=1;
    printf("Numar de locuri:");
    scanf("%d",&v[n].numar_locuri);
    printf("Numar Inmatriculare:");
    scanf("%s",&v[n].nr_inmatriculare);
    printf("Culoare:");
    scanf("%s",&v[n].culoare);
    printf("An:");
    scanf("%d",&v[n].an);

    n++;
}


void init() {

    FILE *INPUT;
    INPUT = fopen("masini.csv", "r");
    n = 0;
    if (INPUT == NULL) {
        printf("Nu am putut deschide fisierul");
        exit(4);
    }
    char line[200];
    fgets(line,sizeof(line),INPUT);

    while (fgets(line, sizeof(line), INPUT)) {
    char *token;
    token = strtok(line,",");

    for(int j=1;j<=8;j++) {

        if(j == 1 )
            strcpy(v[n].marca,token);
        if(j == 2)
            strcpy(v[n].tip,token);
        if(j == 3) {
            v[n].disp.val = atoi(token);
            coduri[v[n].disp.val]=1;

        }
            if(j == 4)
            strcpy(v[n].disp.d,token);
        if(j == 5)
            v[n].numar_locuri=atoi(token);
        if( j == 6 )
            strcpy(v[n].nr_inmatriculare,token);
        if(j == 7)
            strcpy(v[n].culoare,token);
        if(j == 8)
            v[n].an= atoi(token);

        // debug printf("%s", token);
        token = strtok(NULL, ",");


        }
    n++;
    }
    fclose(INPUT);
    }





void sterge(){
    printf("Doriti sa continuati? (1/0)\n");
    int back;
    scanf("%d",&back);
    if(back == 0)
        return;
    int k;
    printf("Numarul autoturismului pe care vreti sa il stergeti ");
    scanf("%d",&k);
    for(int i=k-1;i<n-1;i++)
        v[i]=v[i+1];
    n--;



}






void afisare()
{




    for(int i=0;i<n;i++) {
        printf("Autovehiculul %d\n",i+1);

        printf("\nMarca: %s", v[i].marca);
        printf("\nTip: %s", v[i].tip);
        if(v[i].disp.val>9999) {
            char data_disp[15];

            set_color(RED);
            printf("\nDisponibilitate: Indisponibil, va fi disponibil din: ");
            set_color(WHITE);
            for(int k=0;k<strlen(v[i].disp.d);k++) {
                printf("%c", v[i].disp.d[k]);
                if (k == 3)
                printf("/");
                if(k==5)
                    printf("/");
                }
            }
        else {
            set_color(GREEN);
            printf("\nDisponibilitate: Disponibil");
            set_color(WHITE);
        }
            //printf("\nDisponibilitate: %d",v[i].disp);
        printf("\nNumar de locuri: %d",v[i].numar_locuri);
        printf("\nNumar Inmatriculare: %s",v[i].nr_inmatriculare);
        printf("\nCuloare: %s",v[i].culoare);
        printf("\nAn:%d\n\n\n",v[i].an);


    }



}


void actualizeaza()
{
    printf("Doriti sa continuati? (1/0)\n");
    int back;
    scanf("%d",&back);
    if(back == 0)
        return;
    int k;
    printf("Numarul autoturismului pe care vreti sa il actualizati");
    scanf("%d",&k);
    k--;

    printf("Introduceti datele\n");
    printf("Marca:");
    scanf("%s",&v[k].marca);
    printf("Tip:");
    scanf("%s",&v[k].tip);
    //printf("Disponibilitate (1- disponibil | 0-indisponibil):");
    //scanf("%d",&v[n].disp);
    //strcpy(v[k].disp.d,"YYYY/MM//DD");
    //v[k].disp.val=1;
    printf("Numar de locuri:");
    scanf("%d",&v[k].numar_locuri);
    printf("Numar Inmatriculare:");
    scanf("%s",&v[k].nr_inmatriculare);
    printf("Culoare:");
    scanf("%s",&v[k].culoare);
    printf("An:");
    scanf("%d",&v[k].an);

}




void rent() {
    printf("Doriti sa continuati? (1/0)\n");
    int back;
    scanf("%d", &back);
    if (back == 0)
        return;
    int k;
    do {
        printf("Numarul autoturismului pe care vreti sa il inchiriati:");
        scanf("%d", &k);
        k--;
        printf("\n\n");
       // printf(v[k].disp.val);
    }while (v[k].disp.val != 1);

    int codd;
    do {
        codd = cod_unic();
    }while(coduri[codd]!=0);
    v[k].disp.val=codd;


    printf("Codul de rezervare este:");
    set_color(YELLOW);
    printf("%d\n",codd);
    set_color(WHITE);
    char dataaa[50];
    do {
        printf("Data pana la care vreti sa rezervati autoturismul(yyyymmdd ex: 20220609):");
        scanf("%s",dataaa);
        //printf("aici\n");
        printf("\n");
    }while(valid_date(dataaa)==0);
    strcpy(v[k].disp.d,dataaa);
}

void cauta() {
    int criteriu;

    printf("Doriti sa continuati? (1/0)\n");
    int back;
    scanf("%d", &back);
    if (back == 0)
        return;

    do {
        printf("Alegeti categoria de cautare\n1.Marca\n2.Culoare \n3.An\n");
        scanf("%d", &criteriu);
    } while (criteriu > 3 && criteriu < 1);

    char marca[50];
    char culoare[50];
    //printf("%d", criteriu);
    int an;
    switch (criteriu) {
        case 1:
            fflush(stdin);
            printf("%s", "Marca pe care doriti sa o cautati:");
            scanf("%s", &marca);
            for (int i = 0; i < n; i++)
                if (strcmp((v[i].marca), marca) == 0) {
                    printf("Autovehiculul %d\n", i + 1);

                    printf("\nMarca: %s", v[i].marca);
                    printf("\nTip: %s", v[i].tip);
                    if (v[i].disp.val > 9999) {
                        char data_disp[15];

                        set_color(RED);
                        printf("\nDisponibilitate: Indisponibil, va fi disponibil din: ");
                        set_color(WHITE);
                        for (int k = 0; k < strlen(v[i].disp.d); k++) {
                            printf("%c", v[i].disp.d[k]);
                            //if (k == 4)
                            //printf("/");
                            //if(k==6)
                            //     printf("/");

                        }
                    } else { set_color(GREEN);
                        printf("\nDisponibilitate: Disponibil");
                            set_color(WHITE);}

                    //printf("\nDisponibilitate: %d",v[i].disp);
                    printf("\nNumar de locuri: %d", v[i].numar_locuri);
                    printf("\nNumar Inmatriculare: %s", v[i].nr_inmatriculare);
                    printf("\nCuloare: %s", v[i].culoare);
                    printf("\nAn:%d\n\n\n", v[i].an);


                }

            break;
        case 2:
            fflush(stdin);
            printf("%s", "Culoarea masinii pe care doriti sa o cautati:");
            scanf("%s", &culoare);
            for (int i = 0; i < n; i++)
            {    if (strcmp((v[i].culoare), culoare) == 0) {
                    printf("Autovehiculul %d\n", i + 1);

                    printf("\nMarca: %s", v[i].marca);
                    printf("\nTip: %s", v[i].tip);
                    if (v[i].disp.val > 9999) {
                        char data_disp[15];

                        set_color(RED);

                        printf("\nDisponibilitate: Indisponibil, va fi disponibil din: ");
                        set_color(WHITE);
                        for (int k = 0; k < strlen(v[i].disp.d); k++) {
                            printf("%c", v[i].disp.d[k]);
                            //if (k == 4)
                            //printf("/");
                            //if(k==6)
                            //     printf("/");
                        }
                    } else
                        printf("\nDisponibilitate: Disponibil");

                    //printf("\nDisponibilitate: %d",v[i].disp);
                    printf("\nNumar de locuri: %d", v[i].numar_locuri);
                    printf("\nNumar Inmatriculare: %s", v[i].nr_inmatriculare);
                    printf("\nCuloare: %s", v[i].culoare);
                    printf("\nAn:%d\n\n\n", v[i].an);
                }

    }
            break;

        case 3:

            fflush(stdin);
            printf("%s", "Anul masinii pe care doriti sa o cautati:");
            scanf("%d", &an);
            for (int i = 0; i < n; i++)
            {    if (v[i].an == an) {
                    printf("Autovehiculul %d\n", i + 1);

                    printf("\nMarca: %s", v[i].marca);
                    printf("\nTip: %s", v[i].tip);
                    if (v[i].disp.val > 9999) {
                        char data_disp[15];

                        set_color(RED);
                        printf("\nDisponibilitate: Indisponibil, va fi disponibil din: ");
                        set_color(WHITE);
                        for (int k = 0; k < strlen(v[i].disp.d); k++) {
                            printf("%c", v[i].disp.d[k]);
                            //if (k == 4)
                            //printf("/");
                            //if(k==6)
                            //     printf("/");
                        }
                    } else {set_color(GREEN);
                        printf("\nDisponibilitate: Disponibil");
                    set_color(WHITE);}

                    //printf("\nDisponibilitate: %d",v[i].disp);
                    printf("\nNumar de locuri: %d", v[i].numar_locuri);
                    printf("\nNumar Inmatriculare: %s", v[i].nr_inmatriculare);
                    printf("\nCuloare: %s", v[i].culoare);
                    printf("\nAn:%d\n\n\n", v[i].an);
                }

            }
            break;

    }
}

void cancel(){
    printf("Doriti sa continuati? (1/0)\n");
    int back;
    scanf("%d",&back);
    if(back == 0)
        return;
    int cod;
    printf("%s", "Introduceti codul de rezervare:" );
    scanf("%d",&cod);
    for(int i=0;i<n;i++)
        if(v[i].disp.val== cod) {
                v[i].disp.val = 1;
                strcpy(v[i].disp.d,"YYYY/MM/DD");
        }







}

void save_cars(){


    FILE *fpt;
    fpt = fopen("masini.csv", "w+");
    fprintf(fpt,"Marca, Tip, Disponibilitate, Data, numar de locuri, Numar inmatriculare, Culoare, An\n");
    for(int i=0;i<n;i++) {
        fprintf(fpt, "%s,%s,%d,%s,%d,%s,%s,%d\n", v[i].marca, v[i].tip, v[i].disp.val, v[i].disp.d, v[i].numar_locuri,
                v[i].nr_inmatriculare, v[i].culoare, v[i].an);
        //printf("%d\n",i);
    }
    fclose(fpt);

}

int main() {


    init();

int choice;

do{
    printf("\n");
    set_color(BLUE);
    printf("  _____            _     _      _           _                 _        \n"
           " |_   _|          | |   (_)    (_)         (_)     /\\        | |       \n"
           "   | |  _ __   ___| |__  _ _ __ _  ___ _ __ _     /  \\  _   _| |_ ___  \n"
           "   | | | '_ \\ / __| '_ \\| | '__| |/ _ \\ '__| |   / /\\ \\| | | | __/ _ \\ \n"
           "  _| |_| | | | (__| | | | | |  | |  __/ |  | |  / ____ \\ |_| | || (_) |\n"
           " |_____|_| |_|\\___|_| |_|_|_|  |_|\\___|_|  |_| /_/    \\_\\__,_|\\__\\___/ \n"
           "                                                                       \n");

    set_color(WHITE);
    printf("Meniu Principal: \n\n");
    printf("1. Vizualizeaza toate autoturismele\n");
    printf("2. Adauga autoturism\n");
    printf("3. Sterge autoturism\n");
    printf("4. Actualizeaza autoturism\n");
    printf("5. Cauta un autoturism\n");
    printf("6. Inchiriaza un autoturism\n");
    printf("7. Anulati o rezervare\n");
    printf("9. Exit\n");

    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
             afisare();

            break;
        case 2:
             adauga();
             set_color(GREEN);
             printf("Masina a fost adaugata cu succes.\n");
             set_color(WHITE);
             save_cars();
             break;
        case 3:

             sterge();
            set_color(GREEN);
            printf("Autoturismul a fost sters cu succes.\n");
            set_color(WHITE);
             save_cars();
             break;
        case 4:
              actualizeaza();
            set_color(GREEN);
            printf("Autoturismul a fost actualizat cu succes.\n");
            set_color(WHITE);
              save_cars();
              break;
              case 5:
             cauta();
            break;
        case 6:
            rent();
            save_cars();
            break;
        case 7:
            cancel();
            save_cars();
            break;
        case 9:
            break;
        default:
            printf("Input gresit. Introduceti din nou.");
    }

}while(choice!=9);



    FILE *fpt;
    fpt = fopen("masini.csv", "w+");
    fprintf(fpt,"Marca, Tip, Disponibilitate, Data, numar de locuri, Numar inmatriculare, Culoare, An\n");
    for(int i=0;i<n;i++) {
        fprintf(fpt, "%s,%s,%d,%s,%d,%s,%s,%d\n", v[i].marca, v[i].tip, v[i].disp.val, v[i].disp.d, v[i].numar_locuri,
                v[i].nr_inmatriculare, v[i].culoare, v[i].an);
    //printf("%d\n",i);
    }
    fclose(fpt);
return 0;



}