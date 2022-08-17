#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 500
#define LEN_LOCAL_PDI 30
#define NUM_LOCAIS 20
#define NUM_PDIS 3

typedef struct Utilizador{
    char nome[100];
    char morada[100];
    int dia,mes,ano,telefone;
    char local_hot[20];
}User;

typedef struct horario{
    int abertura;
    int fecho;
    char descanso[100];
}horario;

typedef struct Pdi{
    char nome[100];
    char description[100];
    horario n;
    int popularidade;
}Pdi;

typedef struct lnode_user *List_user;
typedef struct lnode_user{
    List_user next;
    User utilizador;
}List_node_user;

typedef struct lnode_pdi *List_pdi;
typedef struct lnode_pdi{
    List_pdi next;
    Pdi ponto;
}List_node_pdi;

typedef struct Local{
    char cidade[100];
    List_pdi lista_pdi;
    int popularidade;
}Local;

typedef struct lnode_local *List_local;
typedef struct lnode_local{
    List_local next;
    Local local;
}List_node_local;

typedef struct Viagem{
    List_local locais;
    List_pdi pontos;
}trip;

void clear(){
    system("@cls||clear");
}

void registo(int *ptr_tele){

    List_user novo=(List_user)malloc(sizeof(List_node_user));
    novo->next=NULL;
    fflush(stdin);
    printf("Nome: ");
    gets(novo->utilizador.nome);

    fflush(stdin);
    printf("Morada: ");
    gets(novo->utilizador.morada);

    dia:printf("Dia: ");
    scanf("%d",&(novo->utilizador.dia));

    if(novo->utilizador.dia<1 || novo->utilizador.dia>31){
        printf("Numero invalido\n");
        goto dia;
    }

    mes: printf("Mes: ");
    scanf("%d",&(novo->utilizador.mes));

    if(novo->utilizador.mes<1 || novo->utilizador.mes>12){
        printf("Numero invalido\n");
        goto mes;
    }

    ano: printf("Ano: ");
    scanf("%d",&(novo->utilizador.ano));

    if(novo->utilizador.ano<1900 || novo->utilizador.ano>2009){
        printf("Numero invalido\n");
        goto ano;
    }

    telefone: printf("Telefone: ");
    scanf("%d",&(novo->utilizador.telefone));

    if(novo->utilizador.telefone<900000000 || novo->utilizador.telefone>1000000000){
        printf("Numero invalido\n");
        goto telefone;
    }

    *ptr_tele=novo->utilizador.telefone;

    FILE *fp = fopen("Utilizadores.txt", "a");
    fprintf(fp, "%s,%s,%d,%d,%d,%d\n",novo->utilizador.nome,novo->utilizador.morada,novo->utilizador.dia,novo->utilizador.mes,novo->utilizador.ano,novo->utilizador.telefone);
    fclose(fp);
}

void login(int *ptrtele) {
    int e = 0;
    while (e == 0) {
        int b;
        int count = 0;
        char c[MAX_LENGTH];
        char *token;
        char nome[MAX_LENGTH];
        FILE *fptr = fopen("Utilizadores.txt", "r");
        printf("\nIntroduza o numero de telefone: ");
        scanf("%d", &b);
        printf("\n");
        while (!feof(fptr)) {
            fgets(c, MAX_LENGTH, fptr);
            token = strtok(c, ",");

            while (token != NULL) {
                count += 1;
                if (count % 6 == 1) {
                    strcpy(nome, token);
                }
                if (atoi(token) == b) {
                    *ptrtele=b;
                    printf("BEM VINDO %s!\n\n", nome);
                    e = 1;
                    break;
                }
                token = strtok(NULL, ",");
            }
        }
        if (e == 0) {
            printf("Numero introduzido invalido.");
        }
        fclose(fptr);
    }
}

void titulo(){
    puts(
         "  _____  _                                             _              _       __      ___                            \n |  __ \\| |                                           | |            | |      \\ \\    / (_)                           \n | |__) | | __ _ _ __   ___  __ _ _ __ ___   ___ _ __ | |_ ___     __| | ___   \\ \\  / / _  __ _  __ _  ___ _ __  ___ \n |  ___/| |/ _` | '_ \\ / _ \\/ _` | '_ ` _ \\ / _ \\ '_ \\| __/ _ \\   / _` |/ _ \\   \\ \\/ / | |/ _` |/ _` |/ _ \\ '_ \\/ __|\n | |    | | (_| | | | |  __/ (_| | | | | | |  __/ | | | || (_) | | (_| |  __/    \\  /  | | (_| | (_| |  __/ | | \\__ \\\n |_|    |_|\\__,_|_| |_|\\___|\\__,_|_| |_| |_|\\___|_| |_|\\__\\___/   \\__,_|\\___|     \\/   |_|\\__,_|\\__, |\\___|_| |_|___/\n                                                                                                 __/ |               \n                                                                                                |___/                ");
}

void menu(List_local *ptr_lista_original,int telefone_user,List_user *lista_users){
    FILE *fp=fopen("save_projeto.txt","r");
    List_local lista_locais_temp;
    List_pdi lista_pdis_temp;
    lista_locais_temp=NULL;
    lista_pdis_temp=NULL;
    int acao;
    int contador=0;
    char local_or_pdi[LEN_LOCAL_PDI];
    printf("\n\n");
    printf("--------------------------- \t GUIA DE COMANDO\t---------------------------\n\n");
    inicio:printf("\t1--> Ver Locais.\n");
    List_local lista_locais_ordenada;
    lista_locais_ordenada=NULL;
    ordena_locais(&lista_locais_ordenada,&(*ptr_lista_original));
    printf("\t2--> Ver PDIs.\n");
    printf("\t3--> Ver Popularidade.\n");
    printf("\t4--> Adicionar Locais/PDIS\n");
    printf("\t5--> Remover Locais/PDIS\n");
    printf("\t6--> Adicionar Local HOT\n");
    printf("\t7--> Ver Locais e PDIS favoritos\n");
    printf("\t8--> Viagem.\n");
    printf("\t9--> Terminar sessao.\n");
    printf("Accao a realizar: ");
    scanf("%d", &acao);
    fflush(stdin);
    printf("\n");
        if(acao == 1){
            clear();
            ver_locais(&(*ptr_lista_original));
            goto inicio;
        }
        else if(acao == 2) {
            clear();
            ver_pdis(&(*ptr_lista_original));
            goto inicio;
        }
        else if(acao == 3){
            clear();
            print_ordenado(&lista_locais_ordenada);
            goto inicio;
        }
        else if(acao == 4){
            inicio_max: printf("Local ou Ponto de interesse?\n");
            printf("\t1---> Local\n\t2--->Ponto de Interesse\n\t3---> Retroceder\n\nResposta:");
            int local_pdi;
            scanf("%d",&local_pdi);
            printf("\n");
            if (local_pdi==1){
                if (contador==3){
                    printf("Ja tem o maximo de locais favoritos. Tente outra vez\n\n");
                    goto inicio_max;
                }
                inicio_local: printf("Numero do Local:");
                int numero;
                scanf("%d",&numero);
                if (numero<1 || numero>20){
                    printf("\nNumero invalido\n\n");
                    goto inicio_local;
                }
                printf("\n");
                fseek(fp,0,SEEK_SET);
                char linha[MAX_LENGTH];
                clear();
                while(!feof(fp)){
                    fgets(linha,MAX_LENGTH,fp);
                    int n=atoi(linha);
                    if (n==numero){
                        fgets(linha,MAX_LENGTH,fp);
                        printf("Escolheu: %s\n",linha);
                        break;
                    }
                }
                strcpy(local_or_pdi,linha);
                List_local temp;
                temp= *ptr_lista_original;
                List_local temp2;
                temp2=lista_locais_temp;
                while(temp2!=NULL){
                    if(strcmp(temp2->local.cidade,local_or_pdi)==0){
                        clear();
                        printf("Ja o tem na lista\n");
                        goto inicio;
                    }
                    temp2=temp2->next;
                }
                while(temp!=NULL){
                    if (strcmp(temp->local.cidade,local_or_pdi)==0){
                        temp->local.popularidade+=1;
                        break;
                    }
                    temp=temp->next;
                }
                adicionar_l(&lista_locais_temp,local_or_pdi,&contador,&lista_locais_ordenada);
            }
            else if (local_pdi==2){
                printf("Ex: Bangkok corresponde a 2, se eu quiser o Grande palacio de Bangkok que é o primeiro PDI escrevo 2.1\n");
                inicio_pdi: printf("Numero do PDI: ");
                float numero;
                scanf("%f",&numero);
                int i;
                int aberto;
                int fecho;
                char descricao[MAX_LENGTH];
                for(i=1;i<=NUM_LOCAIS;i++){
                    if(numero==i){
                        clear();
                        printf("\nNumero invalido\n");
                        goto inicio_pdi;
                    }
                }
                if (numero<1 || numero>20){
                    clear();
                    printf("\nNumero invalido\n");
                    goto inicio_pdi;
                }
                char linha[MAX_LENGTH];
                printf("\n");
                fseek(fp,0,SEEK_SET);
                clear();
                while(!feof(fp)){
                    fgets(linha,MAX_LENGTH,fp);
                    float n=atof(linha);
                    if (n==numero){
                        fgets(linha,MAX_LENGTH,fp);
                        printf("Escolheu: %s",linha);
                        break;
                    }
                }
                char *token;
                strcpy(local_or_pdi,linha);
                fgets(linha,MAX_LENGTH,fp);
                strcpy(descricao,linha);
                i=0;
                fgets(linha,MAX_LENGTH,fp);
                token=strtok(linha,"*");
                while (token!=NULL){
                    if (i==1){
                        int a=atoi(token);
                        aberto=a;
                    }
                    else if(i==2){
                        int a=atoi(token);
                        fecho=a;
                        printf("\n");
                        break;
                    }
                    i++;
                    token=strtok(NULL,"*");
                }
                List_local temp;
                temp= *ptr_lista_original;
                List_pdi temp2;
                temp2=lista_pdis_temp;
                while(temp2!=NULL){
                    if(strcmp(temp2->ponto.nome,local_or_pdi)==0){
                        clear();
                        printf("Ja o tem na lista\n");
                        goto inicio;
                    }
                    temp2=temp2->next;
                }
                while(temp->next!=NULL){
                    List_pdi temp2;
                    temp2=temp->local.lista_pdi;
                    while(temp2!=NULL){
                        if (strcmp(temp2->ponto.nome,local_or_pdi)==0){
                            temp2->ponto.popularidade+=1;
                            break;
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
                adicionar_pdi(&lista_pdis_temp,local_or_pdi,descricao,aberto,fecho,&lista_locais_ordenada);
            }
            else if (local_pdi==3){
                goto inicio;
            }
            else{
                clear();
                printf("\nNumero invalido\n");
                goto inicio_max;
            }
            goto inicio;
        }
        else if(acao == 5){
            inicio_lpdi: printf("Local ou Ponto de interesse?\n");
            printf("\t1---> Local\tn2--->Ponto de Interesse\t\n--->Retroceder\n\nResposta:");
            int local_pdi;
            scanf("%d",&local_pdi);
            printf("\n");
            if (local_pdi==1){
                inicio_l: printf("Numero do Local:");
                int numero;
                scanf("%d",&numero);
                if (numero<1 || numero>20){
                    clear();
                    printf("\nNumero invalido\n");
                    goto inicio_l;
                }
                printf("\n");
                fseek(fp,0,SEEK_SET);
                char linha[MAX_LENGTH];
                clear();
                while(!feof(fp)){
                    fgets(linha,MAX_LENGTH,fp);
                    int n=atoi(linha);
                    if (n==numero){
                        fgets(linha,MAX_LENGTH,fp);
                        printf("Escolheu: %s\n",linha);
                        break;
                    }
                }
                strcpy(local_or_pdi,linha);
                remover_l(&lista_locais_temp,local_or_pdi,&contador);
                List_local temp;
                temp= *ptr_lista_original;
                while(temp!=NULL){
                    if (strcmp(temp->local.cidade,local_or_pdi)==0){
                        temp->local.popularidade-=1;
                        break;
                    }
                    temp=temp->next;
                }
            }
            else if(local_pdi==2){
                printf("Ex: Bangkok corresponde a 2, se eu quiser o Grande palacio de Bangkok que é o primeiro PDI escrevo 2.1\n");
                inicio_ponto: printf("Numero do ponto de interesse: ");
                float numero;
                scanf("%f",&numero);
                int i;
                for(i=1;i<=NUM_LOCAIS;i++){
                    if(numero==i){
                        clear();
                        printf("\nNumero invalido\n");
                        goto inicio_ponto;
                    }
                }
                if (numero<1 || numero>20){
                    clear();
                    printf("\nNumero invalido\n");
                    goto inicio_ponto;
                }
                char linha[MAX_LENGTH];
                printf("\n");
                fseek(fp,0,SEEK_SET);
                clear();
                while(!feof(fp)){
                    fgets(linha,MAX_LENGTH,fp);
                    float n=atof(linha);
                    if (n==numero){
                        fgets(linha,MAX_LENGTH,fp);
                        printf("Escolheu: %s",linha);
                        break;
                    }
                }
                strcpy(local_or_pdi,linha);
                remover_pdi(&lista_pdis_temp,local_or_pdi);
                List_local temp;
                temp= *ptr_lista_original;
                while(temp->next!=NULL){
                    List_pdi temp2;
                    temp2=temp->local.lista_pdi;
                    while(temp2!=NULL){
                        if (strcmp(temp2->ponto.nome,local_or_pdi)==0){
                            temp2->ponto.popularidade-=1;
                            break;
                        }
                        temp2=temp2->next;
                    }
                    temp=temp->next;
                }
            }
            else if(local_pdi==3){
                goto inicio;
            }
            else{
                clear();
                printf("\nNumero invalido\n");
                goto inicio_lpdi;
            }
            goto inicio;
        }
        else if(acao == 6){
            int hot;
            inicio_h: printf("Diga o numero do local:");
            scanf("%d",&hot);
            if (hot<1 || hot>20){
                clear();
                printf("\nNumero invalido\n");
                goto inicio_h;
            }
            printf("\n");
            fseek(fp,0,SEEK_SET);
            char linha[MAX_LENGTH];
            clear();
            while(!feof(fp)){
                fgets(linha,MAX_LENGTH,fp);
                int n=atoi(linha);
                if (n==hot){
                    fgets(linha,MAX_LENGTH,fp);
                    printf("Escolheu: %s",linha);
                    break;
                }
            }
            List_local temp;
            temp= *ptr_lista_original;
            while(temp!=NULL){
                if (strcmp(temp->local.cidade,linha)==0){
                    temp->local.popularidade+=1;
                    break;
                }
                temp=temp->next;
            }
            adicionar_hot(&(*lista_users),linha,telefone_user);
            goto inicio;
        }
        else if(acao == 7){
            clear();
            listagem_l_pdi(&lista_locais_temp,&lista_pdis_temp,&(*ptr_lista_original));
            goto inicio;
        }
        else if(acao == 8){
            trip viagem;
            clear();
            voyage(contador,&lista_locais_temp,&lista_pdis_temp,&(*lista_users),&lista_locais_ordenada,telefone_user,&viagem);
            goto inicio;
        }
        else if(acao == 9){
            clear();
            return 0;
        }
        else{
            clear();
            printf("Numero invaldido\n");
            goto inicio;
        }
    fclose(fp);
}

void ler_fich(List_local *ll){
    FILE *fp=fopen("save_projeto.txt","r");
    char linha[MAX_LENGTH];
    while(!feof(fp)){
        if (*ll==NULL){
            List_local novo;
            novo=(List_local)malloc(sizeof(List_node_local));
            novo->next=NULL;
            fgets(linha,MAX_LENGTH,fp);
            fgets(linha,MAX_LENGTH,fp);
            strcpy(novo->local.cidade,linha);
            novo->local.popularidade=0;
            int i;
            int k;
            List_pdi pdis;
            pdis=NULL;
            for(k=0;k<NUM_PDIS;k++){
                for(i=0;i<3;i++)
                    fgets(linha,MAX_LENGTH,fp);
                List_pdi novo2;
                novo2=(List_pdi)malloc(sizeof(List_node_pdi));
                novo2->next=NULL;
                novo2->ponto.popularidade=0;
                strcpy(novo2->ponto.nome,linha);
                fgets(linha,MAX_LENGTH,fp);
                strcpy(novo2->ponto.description,linha);
                fgets(linha,MAX_LENGTH,fp);
                char *token;
                token=strtok(linha,"*");
                int l=0;
                while(token!=NULL){
                    if(l==1){
                        int a =atoi(token);
                        novo2->ponto.n.abertura=a;
                    }
                    if (l==2){
                        int a=atoi(token);
                        novo2->ponto.n.fecho=a;
                        break;
                    }
                    l++;
                    token=strtok(NULL,"*");
                }
                if (pdis==NULL)
                    pdis=novo2;
                else{
                    List_pdi temp;
                    temp=pdis;
                    while(temp->next!=NULL){
                        temp=temp->next;
                    }
                    temp->next=novo2;
                }
            }
            novo->local.lista_pdi=pdis;
            *ll=novo;
            fgets(linha,MAX_LENGTH,fp);
        }
        else{
            List_local temp;
            temp=*ll;
            while(temp->next!=NULL)
                temp=temp->next;
            List_local novo;
            novo=(List_local)malloc(sizeof(List_node_local));
            novo->next=NULL;
            fgets(linha,MAX_LENGTH,fp);
            fgets(linha,MAX_LENGTH,fp);
            strcpy(novo->local.cidade,linha);
            novo->local.popularidade=0;
            int i;
            int k;
            List_pdi pdis;
            pdis=NULL;
            for(k=0;k<3;k++){
                for(i=0;i<3;i++)
                    fgets(linha,MAX_LENGTH,fp);
                List_pdi novo2;
                novo2=(List_pdi)malloc(sizeof(List_node_pdi));
                novo2->next=NULL;
                novo2->ponto.popularidade=0;
                strcpy(novo2->ponto.nome,linha);
                fgets(linha,MAX_LENGTH,fp);
                strcpy(novo2->ponto.description,linha);
                fgets(linha,MAX_LENGTH,fp);
                char *token;
                token=strtok(linha,"*");
                int l=0;
                while(token!=NULL){
                    if(l==1){
                        int a =atoi(token);
                        novo2->ponto.n.abertura=a;
                    }
                    if (l==2){
                        int a=atoi(token);
                        novo2->ponto.n.fecho=a;
                        break;
                    }
                    l++;
                    token=strtok(NULL,"*");
                }
                if (pdis==NULL)
                    pdis=novo2;
                else{
                    List_pdi temp;
                    temp=pdis;
                    while(temp->next!=NULL){
                        temp=temp->next;
                    }
                    temp->next=novo2;
                }
            }
            novo->local.lista_pdi=pdis;
            temp->next=novo;
            fgets(linha,MAX_LENGTH,fp);
        }
    }
    fclose(fp);
}

void adicionar_pdi(List_pdi *lpdi,char nome_pdi[],char pdi_descricao[],int aberto,int fecho,List_local *ptr_original){
    List_pdi novo=(List_pdi)malloc(sizeof(List_node_pdi));
    strcpy(novo->ponto.nome,nome_pdi);
    novo->ponto.n.abertura=aberto;
    novo->ponto.n.fecho=fecho;
    strcpy(novo->ponto.description,pdi_descricao);
    novo->next=NULL;
    List_local temp_local;
    temp_local=*ptr_original;
    while(temp_local!=NULL){
        List_pdi temp_pdis;
        temp_pdis=temp_local->local.lista_pdi;
        while(temp_pdis!=NULL){
            if(strcmp(temp_pdis->ponto.nome,novo->ponto.nome)==0){
                novo->ponto.popularidade=temp_pdis->ponto.popularidade;
                break;
            }
            temp_pdis=temp_pdis->next;
        }
        temp_local=temp_local->next;
    }
    if (*lpdi == NULL)
        *lpdi = novo;
    else{
        List_pdi temp;
        temp = *lpdi;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=novo;
    }
}

void remover_pdi(List_pdi *pdi,char nome_pdi[]){
    List_pdi temp=*pdi;
    List_pdi prev;
    if (*pdi==NULL)
        printf("A lista ta vazia. Adicione pontos de interesse se desejar remover futuramente\n\n");
    else if(temp!=NULL && strcmp(temp->ponto.nome,nome_pdi)==0){
        *pdi=temp->next;
        free(temp);
    }
    else{
        while(temp!=NULL && strcmp(temp->ponto.nome,nome_pdi)!=0){
            prev=temp;
            temp=temp->next;
        }
        if(temp==NULL)
            printf("O ponto de interesse nao pode ser removido porque nao esta presente na lista\n\n");
        else
            prev->next=temp->next;
    }
}

void adicionar_l(List_local *ll,char nome_local[],int *cont,List_local *ptr_original){
    List_local novo=(List_local)malloc(sizeof(List_node_local));
    strcpy(novo->local.cidade,nome_local);
    novo->next=NULL;
    List_local temp_local;
    temp_local=*ptr_original;
    while(temp_local!=NULL){
        if(strcmp(temp_local->local.cidade,novo->local.cidade)==0){
            novo->local.popularidade=temp_local->local.popularidade;
            break;
        }
        temp_local=temp_local->next;
    }
    if (*ll==NULL){
        *ll=novo;
        *cont+=1;
    }
    else{
        List_local temp;
        temp=*ll;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=novo;
        *cont+=1;
    }
    return 0;
}

void remover_l(List_local *ll,char nome_local[],int *ptr_cont){
    List_local temp=*ll;
    List_local prev;
    if (*ll==NULL)
        printf("A lista esta vazia. Adicione Locais se desejar remover futuramente\n\n");
    else if(temp!=NULL && strcmp(temp->local.cidade,nome_local)==0){
        *ll=temp->next;
        free(temp);
        *ptr_cont--;
    }
    else{
        while(temp!=NULL && strcmp(temp->local.cidade,nome_local)!=0){
            prev=temp;
            temp=temp->next;
        }
        if (temp==NULL)
            printf("O local nao pode ser removido porque nao esta presente na lista\n\n");
        else{
            prev->next=temp->next;
            *ptr_cont--;
        }
    }
}

void adicionar_hot(List_user *ptr_lista_users,char local_hot[],int tele){
    List_user temp;
    temp=*ptr_lista_users;
    while(temp!=NULL){
        if(temp->utilizador.telefone==tele){
            strcpy(temp->utilizador.local_hot,local_hot);
            printf("\n%s o teu local hot e %s",temp->utilizador.nome,temp->utilizador.local_hot);
            break;
        }
        temp=temp->next;
    }
}

void listagem_l_pdi(List_local *lista_l_user,List_pdi *lpdi_user,List_local *lista_original){
    List_local temp=*lista_l_user;
    List_pdi temp1=*lpdi_user;
    printf("Locais favoritos:\n\n");
    int i;
    if (*lista_l_user==NULL)
        printf("Ainda nao tem Locais favoritos\n\n");
    else if (temp->next==NULL){
        printf("\t-%s",temp->local.cidade);
        List_local temp3;
        temp3=*lista_original;
        while(temp3!=NULL){
            if(strcmp(temp3->local.cidade,temp->local.cidade)==0){
                printf("\t Popularidade: %d\n\n",temp3->local.popularidade);
                break;
            }
            temp3=temp3->next;
        }
    }
    else{
        while(temp!=NULL){
        List_local temp3;
        temp3=*lista_original;
            while(temp3!=NULL){
                if(strcmp(temp3->local.cidade,temp->local.cidade)==0){
                    printf("\t-%s",temp3->local.cidade);
                    printf("\tPopularidade: %d\n\n",temp3->local.popularidade);
                    break;
                }
                temp3=temp3->next;
            }
            temp=temp->next;
        }
    }
    printf("Ponto de Interesse favoritos:\n\n");
    if (*lpdi_user==NULL)
        printf("Ainda nao tem pontos de interesse favoritos\n\n");
    else if (temp1->next==NULL){
        List_local temp3;
        temp3=*lista_original;
        int stop;
        while(temp3!=NULL){
            List_pdi temp4;
            temp4=temp3->local.lista_pdi;
            while(temp4!=NULL){
                if(strcmp(temp4->ponto.nome,temp1->ponto.nome)==0){
                    printf("\t-%s",temp1->ponto.nome);
                    printf("\tPopularidade:%d\n\n",temp4->ponto.popularidade);
                    break;
                }
                temp4=temp4->next;
            }
            temp3=temp3->next;
        }
    }
    else{
        while(temp1!=NULL){
            List_local temp3;
            temp3=*lista_original;
            printf("\t-%s",temp1->ponto.nome);
            while(temp3!=NULL){
                List_pdi temp4;
                temp4=temp3->local.lista_pdi;
                while(temp4!=NULL){
                    if(strcmp(temp4->ponto.nome,temp1->ponto.nome)==0){
                        printf("\tPopularidade:%d\n\n",temp4->ponto.popularidade);
                        break;
                    }
                    temp4=temp4->next;
                }
                temp3=temp3->next;
            }
            temp1=temp1->next;
        }
    }
}

void ordena_locais(List_local *ptr_nova_lista,List_local *ptr_locais_original){
    int max=0;
    int i=0;
    List_local temp;
    temp=*ptr_locais_original;
    while(temp!=NULL){
        if(temp->local.popularidade>max){
            max=temp->local.popularidade;
        }
        temp=temp->next;
    }
    while(i!=NUM_LOCAIS){
        List_local temp2;
        temp2=*ptr_locais_original;
        while(temp2!=NULL){
            List_local novo;
            novo=(List_local)malloc(sizeof(List_node_local));
            novo->next=NULL;
            List_pdi pdis;
            pdis=NULL;
            List_pdi lista_pdis;
            lista_pdis=temp2->local.lista_pdi;
            if(temp2->local.popularidade==max){
                strcpy(novo->local.cidade,temp2->local.cidade);
                novo->local.popularidade=temp2->local.popularidade;
                ordena_pdis(&lista_pdis,&pdis);
            }
            else{
                temp2=temp2->next;
                continue;
            }
            if(*ptr_nova_lista==NULL){
                novo->local.lista_pdi=pdis;
                *ptr_nova_lista=novo;
                i++;
            }
            else{
                List_local temp3;
                temp3=*ptr_nova_lista;
                while(temp3->next!=NULL){
                    temp3=temp3->next;
                }
                novo->local.lista_pdi=pdis;
                temp3->next=novo;
                i++;
            }
            temp2=temp2->next;
        }
        max-=1;
    }
}

void ordena_pdis(List_pdi *ptr_lista_pdis,List_pdi *ptr_nova_lista_pdis){
    List_pdi temp;
    temp=*ptr_lista_pdis;
    int max=0;
    int i;
    while(temp!=NULL){
        if(temp->ponto.popularidade>max)
            max=temp->ponto.popularidade;
        temp=temp->next;
    }
    while(i!=NUM_PDIS){
        List_pdi temp2;
        temp2=*ptr_lista_pdis;
        while(temp2!=NULL){
            List_pdi novo;
            novo=(List_pdi)malloc(sizeof(List_node_pdi));
            novo->next=NULL;
            if(temp2->ponto.popularidade==max){
                strcpy(novo->ponto.nome,temp2->ponto.nome);
                strcpy(novo->ponto.description,temp2->ponto.description);
                novo->ponto.popularidade=temp2->ponto.popularidade;
                novo->ponto.n.abertura=temp2->ponto.n.abertura;
                novo->ponto.n.fecho=temp2->ponto.n.fecho;
            }
            else{
                temp2=temp2->next;
                continue;
            }
            if(*ptr_nova_lista_pdis==NULL){
                *ptr_nova_lista_pdis=novo;
                i++;
            }
            else{
                List_pdi temp3;
                temp3=*ptr_nova_lista_pdis;
                while(temp3->next!=NULL){
                    temp3=temp3->next;
                }
                temp3->next=novo;
                i++;
            }
            temp2=temp2->next;
        }
        max-=1;
    }
}

void print_ordenado(List_local *ptr_locais){
    List_local temp=*ptr_locais;
    printf("\n");
    while(temp!=NULL){
        printf("%d-",temp->local.popularidade);
        printf("%s",temp->local.cidade);
        List_pdi temp2;
        temp2=temp->local.lista_pdi;
        while(temp2!=NULL){
            printf("\t%d-%s",temp2->ponto.popularidade,temp2->ponto.nome);
            temp2=temp2->next;
        }
        temp=temp->next;
    }
    printf("\n");
}

void voyage(int cont_locais,List_local *lista_local_preferida,List_pdi *lista_pdis_preferida,List_user *ptr_lista_users,List_local *ptr_lista_ordenada,int tele,trip *ptr_trip){
    if (cont_locais==3){
        List_user temp_hot;
        temp_hot=*ptr_lista_users;
        while(temp_hot!=NULL){
            if(temp_hot->utilizador.telefone==tele)
                break;
            temp_hot=temp_hot->next;
        }
        List_local temp_local;
        temp_local=*ptr_lista_ordenada;
        List_local novo;
        novo=(List_local)malloc(sizeof(List_node_local));
        novo->next=*lista_local_preferida;
        while(temp_local!=NULL){
            if(strcmp(temp_local->local.cidade,temp_hot->utilizador.local_hot)==0){
                strcpy(novo->local.cidade,temp_local->local.cidade);
                novo->local.popularidade=temp_local->local.popularidade;
                novo->local.lista_pdi=temp_local->local.lista_pdi;
                break;
            }
            temp_local=temp_local->next;
        }
        (*ptr_trip).locais=novo;
        (*ptr_trip).pontos=*lista_pdis_preferida;
        printf("\n\n");
        print_viagem(&(*ptr_trip),&(*ptr_lista_ordenada));
    }
    else{
        printf("Nao tem Locais suficientes para fazer uma viagem");
        return 0;
    }
}

void print_viagem(trip *ptr_trip,List_local *ptr_original,List_user *users){
    List_local temp_locais;
    temp_locais=(*ptr_trip).locais;
    printf("-------VIAGEM-------\n\n");
    int pdis=0;
    int i=1;
    float cont_users=0;
    float local_favs=0;
    float hot=0;
    float prefer=0;
    float media;
    List_user temp_user;
    temp_user=*users;
    while(temp_user!=NULL){
        cont_users++;
        List_local temp_via;
        temp_via=(*ptr_trip).locais;
        while(temp_via!=NULL){
            if(strcmp(temp_via->local.cidade,temp_user->utilizador.local_hot)==0)
                hot++;
            List_pdi temp_pdis;
            temp_pdis=temp_via->local.lista_pdi;
            while(temp_pdis!=NULL){
                List_pdi temp_pdis2;
                temp_pdis2=(*ptr_trip).pontos;
                while(temp_pdis2!=NULL){
                    if(strcmp(temp_pdis->ponto.nome,temp_pdis2->ponto.nome)==0)
                        prefer++;
                    temp_pdis2=temp_pdis2->next;
                }
                temp_pdis=temp_pdis->next;
            }
            temp_via=temp_via->next;
        }
        temp_user=temp_user->next;
    }
    while(temp_locais!=NULL){
        List_local temp_original;
        temp_original=*ptr_original;
        while(temp_original!=NULL){
            List_pdi temp_pdis;
            temp_pdis=temp_original->local.lista_pdi;
            if(strcmp(temp_original->local.cidade,temp_locais->local.cidade)==0){
               printf("%d--->%s\n",i,temp_locais->local.cidade);
               i++;
               while(temp_pdis!=NULL){
                    printf("\t-%s",temp_pdis->ponto.nome);
                    temp_pdis=temp_pdis->next;
                    pdis+=1;
                    if(pdis==3){
                        break;
                    }
               }
               break;
            }
            temp_original=temp_original->next;
        }
        temp_locais=temp_locais->next;
    }
    printf("\n\n");
    media=(((local_favs/cont_users)*100)+((hot/cont_users)*100)+((prefer/(NUM_LOCAIS*NUM_PDIS))*100));
    printf("Avaliacao: %f/100\n",media);
}

void encher_lista_users(List_user *list_utilizadores){
    FILE *fp=fopen("Utilizadores.txt","r");
    char str[MAX_LENGTH];
    while(fgets(str,MAX_LENGTH,fp)!= '\0'){
        if(*list_utilizadores==NULL){
            List_user novo;
            novo=(List_user)malloc(sizeof(List_node_user));
            novo->next=NULL;
            char *token;
            token=strtok(str,",");
            int i=0;
            while(token!=NULL){
                if (i==0)
                    strcpy(novo->utilizador.nome,token);
                else if(i==1)
                    strcpy(novo->utilizador.morada,token);
                else if(i==2){
                    int dia=atoi(token);
                    novo->utilizador.dia=dia;
                }
                else if(i==3){
                    int mes=atoi(token);
                    novo->utilizador.mes=mes;
                }
                else if(i==4){
                    int ano=atoi(token);
                    novo->utilizador.ano=ano;
                }
                else if(i==5){
                    int telefone=atoi(token);
                    novo->utilizador.telefone=telefone;
                    break;
                }

                token=strtok(NULL,",");
                i++;
            }
            *list_utilizadores=novo;
        }
        else{
            List_user temp;
            temp=*list_utilizadores;
            while(temp->next!=NULL)
                temp=temp->next;
            List_user novo;
            novo=(List_user)malloc(sizeof(List_node_user));
            novo->next=NULL;
            char *token;
            token=strtok(str,",");
            int i=0;
            while(token!=NULL){
                if (i==0)
                    strcpy(novo->utilizador.nome,token);
                else if(i==1)
                    strcpy(novo->utilizador.morada,token);
                else if(i==2){
                    int dia=atoi(token);
                    novo->utilizador.dia=dia;
                }
                else if(i==3){
                    int mes=atoi(token);
                    novo->utilizador.mes=mes;
                }
                else if(i==4){
                    int ano=atoi(token);
                    novo->utilizador.ano=ano;
                }
                else if(i==5){
                    int telefone=atoi(token);
                    novo->utilizador.telefone=telefone;
                    break;
                }
                token=strtok(NULL,",");
                i++;
            }
            temp->next=novo;
        }
    }
    fclose(fp);
}

void ver_locais(List_local *ptr_lista_original){
    List_local temp=*ptr_lista_original;
    int i=0;
    while(temp!=NULL){
        i++;
        printf("%d-%s",i,temp->local.cidade);
        temp=temp->next;
    }
    printf("\n\n");
}

void ver_pdis(List_local *ptr_lista_original){
    List_local temp=*ptr_lista_original;
    FILE *fp=fopen("save_projeto.txt","r");
    int numero;
    inicio: printf("Deseja ver os PDIS de que local?\nPara ver tem que escolher o numero do correspondente local\n\nResposta:");
    scanf("%d",&numero);
    if (numero<1 || numero>20){
        printf("\nNumero invalido\n");
        goto inicio;
    }
    printf("\n");
    fseek(fp,0,SEEK_SET);
    char linha[MAX_LENGTH];
    while(!feof(fp)){
        fgets(linha,MAX_LENGTH,fp);
        int n=atoi(linha);
        if (n==numero){
            fgets(linha,MAX_LENGTH,fp);
            printf("Escolheu: %s\n",linha);
            break;
        }
    }
    while(temp!=NULL){
        if(strcmp(temp->local.cidade,linha)==0){
            List_pdi temp2=temp->local.lista_pdi;
            while(temp2!=NULL){
                printf("%s\n",temp2->ponto.nome);
                printf("%s",temp2->ponto.description);
                printf("Aberto:%d\n",temp2->ponto.n.abertura);
                printf("Fecho:%d\n\n",temp2->ponto.n.fecho);
                temp2=temp2->next;
            }
            break;
        }
        temp=temp->next;
    }
    fclose(fp);
}

int main() {
    List_local lista_locais;
    lista_locais=NULL;
    ler_fich(&lista_locais);
    repetir: titulo();
    int a;
    int f = 1;
    int tele_user;
    while (f) {
        printf("1--> Fazer login. \n2--> Registar.\n3--> Encerrar\n\n");

        printf("Introduza o numero correspondente a accao que pretende realizar: ");
        scanf("%d", &a);
        fflush(stdin);

        if (a == 1) {
            f = 0;
            login(&tele_user);
        }
        else if (a == 2) {
            f = 0;
            registo(&tele_user);
        }
        else if(a==3)
            goto fim;
        else {
            printf("\nO numero introduzido e invalido.\n");
        }
    }
    List_user users;
    users=NULL;
    encher_lista_users(&users);
    menu(&lista_locais,tele_user,&users);
    goto repetir;
    fim:printf("\n\nAte a proxima!\n\n");
    return 0;
}
