#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

#define Creditos (strcmp(inp, "7") == 0 ? 1 : 0)
#define Admin (strcmp(inp, "7777777") == 0 ? 1 : 0)

// INICIA A TELA GRAFICA
DWORD sx = GetSystemMetrics(SM_CXSCREEN); // Coordenada maxima X da tela
DWORD sy = GetSystemMetrics(SM_CYSCREEN); // Coordenada maxima Y da tela
int graph = initwindow(sx, sy, "CONTROLE DOS CONTROLES", -3, -3); // Abre a tela gráfica



//////////////////////////////////////////////////////////////////////////////////////
// VARIAVEIS GLOBAIS
//////////////////////////////////////////////////////////////////////////////////////

int num_controles = 0;
int num_abobroes = 0;
int num_chaves = 0;
int total_itens;

char log[1000];
char inp[13]; // Guarda o texto final
char matricula[13];
char nome[50];
char dataehora[200];
char dia[4];
int posicao;
int acogrande;
int item;
int codigo;

// MEDIDAS - CARACTERE QUALQUER
char l[2] = "a";
int lsizex = textwidth(l); // Salva a largura em pixels de um carctere
int lsizey = textheight(l); // Salva a altura em pixels de um carctere

//COORDENADAS - DEVEM SER MEDIDAS EM CADA PC NOVO

// RETANGULOS MAIORES

int y0 = 261; //topo
int y1 = 859; //base

// 0 - esquerda | 1 - direita //

int r1x0 = 80;
int r1x1 = 610;

int r2x0 = 700;
int r2x1 = 1230;

int r3x0 = 1310;
int r3x1 = 1840;

// BARRAS

// CAIXA DE TEXTO

int c_x = 458;
int c_y = 962;

// GUIA DE AÇÃO

int c_x_a = 84;
int c_x_m_a = 256;
int c_y_a = 964;

// INFO

int c_x_i = 122;
int c_y_i = 924;

//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// EXIBE A IMAGEM DE FUNDO
//////////////////////////////////////////////////////////////////////////////////////
void fundo(){

readimagefile("cdc.jpg", 0, 0, sx, sy);

}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// LE O NUM DE ITENS E SALVAS OS VALORES GLOBALMENTE
//////////////////////////////////////////////////////////////////////////////////////
void get_num_itens(){

FILE *f;
int num = 0;
char Linha[100];

f = fopen("FILES\\ITENS\\CONTROLES.txt", "r");
while(!feof(f)){
    fgets(Linha, 100, f);
    num++;
} num_controles = num;
fclose(f);

num = 0;

f = fopen("FILES\\ITENS\\ABOBROES.txt", "r");
while(!feof(f)){
    fgets(Linha, 100, f);
    num++;
} num_abobroes = num;
fclose(f);

num = 0;

f = fopen("FILES\\ITENS\\CHAVES.txt", "r");
while(!feof(f)){
    fgets(Linha, 100, f);
    num++;
} num_chaves = num;
fclose(f);

total_itens = num_controles+num_abobroes+num_chaves;

}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// LERITENS - LE OS ITENS DO ARQUIVO ITENS.TXT
//////////////////////////////////////////////////////////////////////////////////////
void ler_itens(){

get_num_itens();

char cnome[num_controles][100];
char anome[num_abobroes][100];
char knome[num_chaves][100];

char cestado[num_controles][100];
char aestado[num_abobroes][100];
char kestado[num_chaves][100];

char ctxt[num_controles][100];
char atxt[num_abobroes][100];
char ktxt[num_chaves][100];


FILE *f;

f = fopen("FILES\\ITENS\\CONTROLES.txt", "r"); for(int i = 0; i < num_controles; i++) fgets(cnome[i], 100, f); fclose(f);
f = fopen("FILES\\ESTADOS\\ESTADO_CONTROLES.txt", "r"); for(int i = 0; i < num_controles; i++) fgets(cestado[i], 100, f); fclose(f);

for(int i = 0; i < num_controles; i++){

    strcpy(ctxt[i], cnome[i]);
    int j = 0;
    while(ctxt[i][j] != '\n') j++;
    ctxt[i][j] = '\0';
    strcat(ctxt[i], " - ");
    if(cestado[i][0] != 10){
    char Emprestado[100] = "Com ";
    strcat(Emprestado, cestado[i]);
    strcat(ctxt[i], Emprestado);}
    else strcat(ctxt[i], "Disponivel");
    //puts(ctxt[i]); // teste
}

f = fopen("FILES\\ITENS\\ABOBROES.txt", "r"); for(int i = 0; i < num_abobroes; i++) fgets(anome[i], 100, f); fclose(f);
f = fopen("FILES\\ESTADOS\\ESTADO_ABOBROES.txt", "r"); for(int i = 0; i < num_abobroes; i++) fgets(aestado[i], 100, f); fclose(f);

for(int i = 0; i < num_abobroes; i++){

    strcpy(atxt[i], anome[i]);
    int j = 0;
    while(atxt[i][j] != '\n') j++;
    atxt[i][j] = '\0';
    strcat(atxt[i], " - ");
    if(aestado[i][0] != 10){
    char Emprestado[100] = "Com ";
    strcat(Emprestado, aestado[i]);
    strcat(atxt[i], Emprestado);}
    else strcat(atxt[i], "Disponivel");
    //puts(atxt[i]); // teste

}

f = fopen("FILES\\ITENS\\CHAVES.txt", "r"); for(int i = 0; i < num_chaves; i++) fgets(knome[i], 100, f); fclose(f);
f = fopen("FILES\\ESTADOS\\ESTADO_CHAVES.txt", "r"); for(int i = 0; i < num_chaves; i++) fgets(kestado[i], 100, f); fclose(f);

for(int i = 0; i < num_chaves; i++){

    strcpy(ktxt[i], knome[i]);
    int j = 0;
    while(ktxt[i][j] != '\n') j++;
    ktxt[i][j] = '\0';
    strcat(ktxt[i], " - ");
    if(kestado[i][0] != 10){
    char Emprestado[100] = "Com ";
    strcat(Emprestado, kestado[i]);
    strcat(ktxt[i], Emprestado);}
    else strcat(ktxt[i], "Disponivel");
    //puts(ktxt[i]); // teste

}


// AGORA VEM A PARTE VISUAL

int y = y0+lsizey;
int meiox1 = ((r1x1-r1x0)/2)+r1x0;
int meiox2 = ((r2x1-r2x0)/2)+r2x0;
int meiox3 = ((r3x1-r3x0)/2)+r3x0;

settextstyle(8, 0, 2);

int i;


for(i = 0; i < num_controles; i++){

    int x = meiox1-(textwidth(ctxt[i])/2);
    outtextxy(x, y+lsizey*i*3, ctxt[i]);

}

for(i = 0; i < num_abobroes; i++){

    int x = meiox2-(textwidth(atxt[i])/2);
    outtextxy(x, y+lsizey*i*3, atxt[i]);

}


for(i = 0; i < num_chaves; i++){

    int x = meiox3-(textwidth(ktxt[i])/2);
    outtextxy(x, y+lsizey*i*3, ktxt[i]);
}


}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// CAIXA DE TEXTO
//////////////////////////////////////////////////////////////////////////////////////
void c_txt(){

char c = 0; // Guarda o caractere digitado
int cont = 0; // Indice do caractere  ultimo caractere valido digitado atual da matrícula
int n = 0; // Flag do numero de caracteres validos digitados
int cx = c_x; // Coordenada x do inicio do texto
int cy = c_y; // Coordenada y do texto
int cxm; // Coordenada x atual do caractere
char space[2] = " ";

settextstyle(8, 0, 2); // define o tamanho e fonte do texto para encaixar no retangulo

while(c != 13){

    c = getch(); // caractere atual
    char sc[2] = {c, '\0'}; // transforma c em string pra usar na função outtextxy(int, int, char*)

    if(c == 13) inp[cont] = '\0'; // Enter - fecha a string

    else if( (c >= '0') && (c <= '9') ) {

        // Se for numero é valido

        cxm = cx+(cont*lsizex*2); // posição do caractere
        outtextxy(cxm, cy, sc); // imprime o numero
        inp[cont] = c; // adiciona a string
        cont++; // caractere
        n++;   // valido
              // :)

    }


    else if((c == 45 && n > 0)){

        // - pressionado e tem algo escrito? Valido

        cont--; // volta
        n--; // volta
        cxm = cx+(cont*lsizex*2);// local anterior
        outtextxy(cxm, cy, space); // "APAGA"

    }


}

// LIMPA A CAIXA DE TEXTO

while(n > 0)  {

    cont--;
    n--;
    delay(10);
    cxm = cx+(cont*lsizex*2);
    outtextxy(cxm, cy, space);

}


}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// CREDITOS - TA NO NOME - NO LUGAR DA MATRICULA DIGITAR:  000000000000 ( 12 ZEROS )
//////////////////////////////////////////////////////////////////////////////////////
void creditos(){

    cleardevice();

    char c[] = "CREDITOS";
    outtextxy(777, 777, c);

    getch();


}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// ADM - TA NO NOME - NO LUGAR DA MATRICULA DIGITAR:  777777700000 ( 7 SETES )
//////////////////////////////////////////////////////////////////////////////////////
void admin(){

    cleardevice();

    int linha, coluna, lmais;
    char title[] = "PAINEL ADMIN";
    char Dia[] = "LOG DO DIA: ";
    char str[1000];

    outtextxy(sx/2-textwidth(title), lsizey*3, title);

    linha = lsizey*7;
    coluna = lsizex*3;

    FILE *file;

    file = fopen("FILES\\LOGHOJE.txt", "r");
    fgets(str, 1000, file);
    strcat(Dia, str);
    outtextxy(lsizex*3, lsizey*4, Dia);
    settextstyle(8, 0, 1);
    setcolor(LIGHTGREEN);

    while(!feof(file)){

        fgets(str, 1000, file);
        outtextxy(coluna, linha, str);
        linha += lsizey;

        fgets(str, 1000, file);
        outtextxy(coluna, linha, str);
        linha += lsizey;

        fgets(str, 1000, file);
        outtextxy(coluna, linha, str);
        linha += lsizey;

        fgets(str, 1000, file);
        outtextxy(coluna, linha, str);
        linha += lsizey;

        fgets(str, 1000, file);
        outtextxy(coluna, linha, str);
        linha += lsizey;
        lmais = textwidth(str)+10;

        fgets(str, 1000, file); // linha em branco

        int m = sy-lsizey*7;

        if(linha < m) linha += lsizey*2;

        else{
        linha = lsizey*7;
        coluna += lmais;

        }

    }

    settextstyle(8, 0, 1);
    setcolor(WHITE);

getch();

}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// CHECARMATRICULA - RECEBE A MATRICULA LIDA E PROCURA NO BANCO DE MATRICULAS MATRIUCLA.TXT
//////////////////////////////////////////////////////////////////////////////////////
int checar_matricula(){

int c, d;
char linha[100];

FILE *file;

file = fopen("FILES\\MATRICULAS_SERVIDORES.txt", "r");

while(!feof(file)){

    fgets(linha, 100, file);

    for(c = 0; linha[c] != ' '; c++) matricula[c] = linha[c]; matricula[c] = '\0';

    if(strcmp(inp, matricula) == 0){

        fclose(file);

        c++;

        //int s;
        //for(d = 0, s = 0; s <= 3; c++, d++) { if(linha[c] == ' ') s++; nome[d] = linha[c]; } nome[d] = '\0';

        for(d = 0; linha[c] != '\n'; c++, d++) nome[d] = linha[c]; nome[d] = '\0';

        puts(nome);

        return 1;

    }

}

file = fopen("FILES\\MATRICULAS_BOLSISTAS.txt", "r");

while(!feof(file)){

    fgets(linha, 100, file);

    for(c = 0; linha[c] != ' '; c++) matricula[c] = linha[c]; matricula[c] = '\0';

    if(strcmp(inp, matricula) == 0){

        fclose(file);

        c++;

        for(d = 0; linha[c] != '\n'; c++, d++) nome[d] = linha[c]; nome[d] = '\0';

        return 2;

    }

}

return 0;

}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// LOGIN - TELA PESSOAL
//////////////////////////////////////////////////////////////////////////////////////
void login(int *pega_chave, int *pode_k, int *pode_c_a){

if(posicao == 1) *pode_c_a = 1;
else *pode_c_a = 0;

FILE *f;
char linha[100];
char check_matricula[20];
char char_chave[3];
int int_chave;
int i;
int j;

f = fopen("FILES\\MATRICULAS_CHAVES.txt", "r");

while(!feof(f)){
    fgets(linha, 100, f);
    for(i = 0; linha[i] != ' '; i++) check_matricula[i] = linha[i]; check_matricula[i] = '\0'; i++;
    for(j = 0; linha[i]; j++, i++) char_chave[j] = linha[i]; char_chave[j] = '\0';
    int_chave = atoi(char_chave);
    if(strcmp(check_matricula, matricula) == 0) { pode_k[int_chave] = 1237497321; *pega_chave = 1;}
    //else pode_k[int_chave] = 0;
}
fclose(f);


// PARTE VISUAL


cleardevice();
fundo();

int y = y0+lsizey;
int meiox1 = ((r1x1-r1x0)/2)+r1x0;
int meiox2 = ((r2x1-r2x0)/2)+r2x0;
int meiox3 = ((r3x1-r3x0)/2)+r3x0;
settextstyle(8, 0, 2);

if(*pode_c_a == 1){
char cnome[num_controles][100];
char cestado[num_controles][100];
char ctxt[num_controles][100];

char anome[num_abobroes][100];
char aestado[num_abobroes][100];
char atxt[num_abobroes][100];

f = fopen("FILES\\ITENS\\CONTROLES.txt", "r"); for(i = 0; i < num_controles; i++) fgets(cnome[i], 100, f); fclose(f);
f = fopen("FILES\\ESTADOS\\ESTADO_CONTROLES.txt", "r"); for(i = 0; i < num_controles; i++) fgets(cestado[i], 100, f); fclose(f);

for(i = 0; i < num_controles; i++){

    strcpy(ctxt[i], cnome[i]);
    int j = 0;
    while(ctxt[i][j] != '\n') j++;
    ctxt[i][j] = '\0';
    strcat(ctxt[i], " - ");
    if(cestado[i][0] != 10){
    char Emprestado[100] = "Com ";
    strcat(Emprestado, cestado[i]);
    strcat(ctxt[i], Emprestado);}
    else strcat(ctxt[i], "Disponivel");
}

f = fopen("FILES\\ITENS\\ABOBROES.txt", "r"); for(i = 0; i < num_abobroes; i++) fgets(anome[i], 100, f); fclose(f);
f = fopen("FILES\\ESTADOS\\ESTADO_ABOBROES.txt", "r"); for(i = 0; i < num_abobroes; i++) fgets(aestado[i], 100, f); fclose(f);

for(i = 0; i < num_abobroes; i++){

    strcpy(atxt[i], anome[i]);
    int j = 0;
    while(atxt[i][j] != '\n') j++;
    atxt[i][j] = '\0';
    strcat(atxt[i], " - ");
    if(aestado[i][0] != 10){
    char Emprestado[100] = "Com ";
    strcat(Emprestado, aestado[i]);
    strcat(atxt[i], Emprestado);}
    else strcat(atxt[i], "Disponivel");

}


for(i = 0; i < num_controles; i++){

    int x = meiox1-(textwidth(ctxt[i])/2);
    outtextxy(x, y+lsizey*i*3, ctxt[i]);

}

for(i = 0; i < num_abobroes; i++){

    int x = meiox2-(textwidth(atxt[i])/2);
    outtextxy(x, y+lsizey*i*3, atxt[i]);

}

}

if(*pega_chave == 1){

char knome[num_chaves][100];
char kestado[num_chaves][100];
char ktxt[num_chaves][100];

f = fopen("FILES\\ITENS\\CHAVES.txt", "r"); for(i = 0; i < num_chaves; i++) fgets(knome[i], 100, f); fclose(f);
f = fopen("FILES\\ESTADOS\\ESTADO_CHAVES.txt", "r"); for(i = 0; i < num_chaves; i++) fgets(kestado[i], 100, f); fclose(f);

for(i = 0; i < num_chaves; i++){

    strcpy(ktxt[i], knome[i]);
    int j = 0;
    while(ktxt[i][j] != '\n') j++;
    ktxt[i][j] = '\0';
    strcat(ktxt[i], " - ");
    if(kestado[i][0] != 10){
    char Emprestado[100] = "Com ";
    strcat(Emprestado, kestado[i]);
    strcat(ktxt[i], Emprestado);}
    else strcat(ktxt[i], "Disponivel");

}


for(i = 0, j = 0; i < num_chaves; i++){


    if(pode_k[i] == 1237497321){
    int x = meiox3-(textwidth(ktxt[i])/2);
    outtextxy(x, y+lsizey*j*3, ktxt[i]);

    j++;
    }

}



}


}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// VE SE O ITEM ESTA LIVRE
//////////////////////////////////////////////////////////////////////////////////////
int isfree(){

FILE *f;

char arquivo[3][100] = {
"FILES\\ESTADOS\\ESTADO_CONTROLES.txt",
"FILES\\ESTADOS\\ESTADO_ABOBROES.txt",
"FILES\\ESTADOS\\ESTADO_CHAVES.txt",
};

f = fopen(arquivo[item-1], "r");

char linha[100];
char nada[] = "\n";

int i;

for( i = 0; i <= codigo; i++ ) fgets(linha, 100, f); fclose(f);
if(strcmp(linha, nada) == 0) return 1;

return 0;

}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// VE SE O ITEM ESTA COM A PESSOA
//////////////////////////////////////////////////////////////////////////////////////
int ta_com_ela(){

FILE *f;

char arquivo[3][100] = {
"FILES\\ESTADOS\\ESTADO_CONTROLES.txt",
"FILES\\ESTADOS\\ESTADO_ABOBROES.txt",
"FILES\\ESTADOS\\ESTADO_CHAVES.txt",
};

f = fopen(arquivo[item-1], "r");

char linha[100];

int i;

for( i = 0; i <= codigo; i++ ) fgets(linha, 100, f); fclose(f);
for(i = 0; linha[i]; i++); linha[i-1] = '\0';

printf("\n| (%s) (%s) |\n", nome, linha); // pra testar
if(strcmp(linha, nome) == 0) return 1;

return 0;
}
//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
// DEVOLVER
//////////////////////////////////////////////////////////////////////////////////////
int devolver(){


if(isfree() || !ta_com_ela()) return 0;

char arquivo[3][100] = {
"FILES\\ESTADOS\\ESTADO_CONTROLES.txt",
"FILES\\ESTADOS\\ESTADO_ABOBROES.txt",
"FILES\\ESTADOS\\ESTADO_CHAVES.txt",
};

char linha[100];
char nada[] = "\n";

int i = 0;


FILE *temp, *orig;



orig = fopen(arquivo[item-1], "r");
temp = fopen("TEMP.txt", "w");

while(!feof(orig)){

    fgets(linha, 100, orig);
    fputs(linha, temp);

} fclose(orig); fclose(temp);

orig = fopen(arquivo[item-1], "w");
temp = fopen("TEMP.txt", "r");

while(!feof(temp)){

    fgets(linha, 100, temp);
    fputs(i == codigo? nada : linha, orig);

    i++;

} fclose(orig); fclose(temp);

remove("TEMP.txt");
return 1;


}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// DEVOLVER
//////////////////////////////////////////////////////////////////////////////////////
int pegar(){

if(!isfree()) return 0;

char arquivo[3][100] = {
"FILES\\ESTADOS\\ESTADO_CONTROLES.txt",
"FILES\\ESTADOS\\ESTADO_ABOBROES.txt",
"FILES\\ESTADOS\\ESTADO_CHAVES.txt",
};

char linha[100];


int i = 0;

FILE *temp, *orig;

orig = fopen(arquivo[item-1], "r");
temp = fopen("TEMP.txt", "w");

while(!feof(orig)){

    fgets(linha, 100, orig);
    fputs(linha, temp);

} fclose(orig); fclose(temp);

orig = fopen(arquivo[item-1], "w");
temp = fopen("TEMP.txt", "r");

while(!feof(temp)){

    fgets(linha, 100, temp);
    fputs(i == codigo? nome : linha, orig);

    i++;

} fclose(orig); fclose(temp);

remove("TEMP.txt");
return 1;

}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// GUIA DE ACAO
//////////////////////////////////////////////////////////////////////////////////////
void acao(int tela){ // guia do que tem que digitar

settextstyle(8, 0, 2);

int n = 11;

char acoes[n][100] = {

    "INSIRA O NÚMERO DA MATRÍCULA",
    "MATRICULA INVALIDA",
    "ESCOLHA UMA ACAO",
    "TIPO DO ITEM",
    "DIGITE O CODIGO DO ITEM",
    "CONFIRME A MATRICULA",
    "OK",
    "APERTE QUALQUER TECLA...",
    "SEM PERMISSAO",
    "INVALIDO",
    "DIGITE O CODIGO DA CHAVE"

};


if(tela >= 0 && tela < n) {

    char limpo[100] = "                              ";
    outtextxy(c_x_a, c_y_a, limpo);
    outtextxy(c_x_m_a-textwidth(acoes[tela])/2, 964, acoes[tela]);

}

}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// GETDATAEHORA - TA NO NOME
//////////////////////////////////////////////////////////////////////////////////////
void get_dataehora(){

time_t rawTime;
struct tm * currentTime;

rawTime = time(NULL);
currentTime = localtime(&rawTime);

strftime(dataehora, 100, "AS %I:%M:%S %p DO DIA %d DE %b DE %Y (%a)", currentTime);


}
//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
// GETDIA - TA NO NOME
//////////////////////////////////////////////////////////////////////////////////////
void get_dia(){

time_t rawTime;
struct tm * currentTime;

rawTime = time(NULL);
currentTime = localtime(&rawTime);

strftime(dia, 4, "%d", currentTime);

}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// TODAYSLOG - CONTROLA O LOG DO DIA
//////////////////////////////////////////////////////////////////////////////////////
void loghoje(){

get_dia();


char dialog[4];
int i;

puts(log);

FILE *file;

file = fopen("FILES\\LOGHOJE.txt", "r");

fgets(dialog, 4, file);

for(i = 0; dialog[i] != '\n'; i++); dialog[i] = '\0'; // pra tirar o \n

fclose(file);
rewind(file);

if(strcmp(dia, dialog) == 0){

file = fopen("FILES\\LOGHOJE.txt", "a");

fputs(log, file);

fclose(file);


}

else{

file = fopen("FILES\\LOGHOJE.txt", "w");

fputs(dia, file);
fputs("\n", file);
fputs(log, file);

fclose(file);



}



}
//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
// ATUALIZA - SALVA TUDO NO LOG, DESLOGA E VOLTA PRO INICIO
//////////////////////////////////////////////////////////////////////////////////////
void atualiza(){

// LE AS VARIAVEIS QUE GUARDAM A MATRICULA, A ACAO, E O ITEM
// JUNTA NUM STRING E SALVA NO LOG

get_dataehora();

char actiones[2][10] = {"PEGAR", "DEVOLVER"};

char i[3][10] = {"CONTROLE", "ABOBRAO", "CHAVE"};

sprintf(log,"MATRICULA: %s\nNOME: %s\nACAO: %s\nITEM: %s %d\n%s\n\n", matricula, nome, actiones[acogrande-1], i[item-1], codigo, dataehora);

FILE *file;
file = fopen("FILES\\LOG.txt", "a");
fputs(log, file);
fclose(file);

loghoje();

}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// BARRA DE INFORMACOES
//////////////////////////////////////////////////////////////////////////////////////
void info(int tela){

int x = c_x_i;
int y = c_y_i;

char infos[8][500] = {

    "| CREDITOS: 7 | -  APAGA |",
    "",
    "| CODIGO AO LADO DO NOME DO ITEM |",
    "| APENAS UMA MEDIDA DE SEGURANCA |",
    "",
    "| 0 - CANCELAR | 1 - CONTROLE | 2 - ABOBRAO | 3 - CHAVE |",
    "| APERTE QUALQUER TECLA PARA SAIR E VOLTAR A TELA INICIAL |",
    "| 0 - CANCELAR | 1 - CONTROLE | 2 - ABOBRAO |"

    };

    //char global_nome[10] = "Iago";

    sprintf(infos[1], "| OLA %s ! | 0 - SAIR | 1 - PEGAR ITEM | 2 - DEVOLVER ITEM |", nome);
    sprintf(infos[4], "| TUDO CERTO %s ! | APERTE QUALQUER TECLA PARA SAIR E VOLTAR A TELA INICIAL |", nome);

if(tela >= 0 && tela <= 8) {

    char limpo[] = "                                                                                                                   ";
    outtextxy(x, y, limpo);
    outtextxy(x, y, infos[tela]);

    }

}
//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
// CONTROLA A EXIBICAO DAS INFORMACOES
//////////////////////////////////////////////////////////////////////////////////////
void infos(int tela){

if(tela == 0) { acao(0); info(0); }

else if(tela == 1) { acao(1); info(6); }

else if(tela == 2) { acao(2); info(1);}

else if(tela == 3) { acao(9); info(6);}

else if(tela == 4) { acao(7); info(6);}

else if(tela == 5) { acao(10); info(2);}

else if(tela == 6) { acao(3); info(5);}

else if(tela == 7) { acao(4); info(2);}

else if(tela == 8) { acao(3); info(7);}

}
//////////////////////////////////////////////////////////////////////////////////////




int main(){

inicio:

//_strdate(dia);

delay(50);

printf("\nTELA INICIAL\n");
fundo();
ler_itens();

infos(0);
c_txt();
printf("\nFOI DIGITADO: %s\n", inp);

if(Creditos) { printf("\nCREDITOS\n"); creditos(); goto inicio; }
if(Admin) { printf("ADMIN"); admin(); goto inicio; }

printf("\nPESQUISANDO MATRICULA\n");
posicao = checar_matricula();
if(!posicao) { printf("\nMATRICULA INEXISTENTE!\n"); infos(1); getch(); goto inicio; }

int pega_chave = 0;
int pode_k[num_chaves];
int pode_c_a;

login(&pega_chave, &pode_k[0], &pode_c_a);
infos(2);

c_txt();
acogrande = atoi(inp);

if(acogrande > 2) { infos(3); getch(); goto inicio; }

if(acogrande == 0) { infos(4); getch(); goto inicio; }

if(posicao == 2){


    infos(5);
    c_txt();
    item = 3;
    codigo = atoi(inp);

    if(codigo >= num_chaves) { infos(3); getch(); goto inicio; }

    if(acogrande == 1)  { if(!pegar()) { infos(3); getch(); goto inicio; } }
    else if(!devolver()) { infos(3); getch(); goto inicio; }

}

else if(pega_chave == 1){

    infos(6);
    c_txt();
    item = atoi(inp);
    if(item == 0) { infos(4); getch(); goto inicio; }
    if(item > 3) { infos(3); getch(); goto inicio; }

    infos(7);
    c_txt();
    codigo = atoi(inp);

    int nums[3] = {num_controles, num_abobroes, num_chaves};

    if(codigo >= nums[item-1]) { infos(3); getch(); goto inicio; }

    if(acogrande == 1)  { if(!pegar()) { infos(3); getch(); goto inicio; } }
    else if(!devolver()) { infos(3); getch(); goto inicio; }

}

else {

    infos(8);
    c_txt();
    item = atoi(inp);
    if(item == 0) { infos(4); getch(); goto inicio; }
    if(item > 2) { infos(3); getch(); goto inicio; }

    infos(7);
    c_txt();
    codigo = atoi(inp);

    int nums[2] = {num_controles, num_abobroes};

    if(codigo >= nums[item-1]) { infos(3); getch(); goto inicio; }

    if(acogrande == 1)  { if(!pegar()) { infos(3); getch(); goto inicio; } }
    else if(!devolver()) { infos(3); getch(); goto inicio; }

}



atualiza();

goto inicio;

getch();
closegraph();

}
