/***************************************************************************
Poliane Brito de Oliveira & Samuel Soares Pereira Costa

v1.0.0
Descrição da estratégia de movimentação: 

    Analisar inicialmente as 4 direções principais para decidir qual a mais 
vantajosa para a situação, caso nenhuma seja vantajosa aumentar a região de
busca e mudar de estratégia.  Serão  analizadas  as  aréas acima, abaixo, a 
direita e a esquerda do barco, para as áreas acima e a baixo suas dimensões
(LxA) serão correspondentes a L=(2*C)+1 e A=C,  já  as áreas à esquerda e à 
direita terão dimensões L=C e A=(2*C)+1,  considerando C igual ao numero de 
posiçõees  de  distancia  do  nosso barco que desejamos "olhar" para buscar 
alguma coisa.  Vale ressaltar que C será incrementado de um em um caso nada
seja encontrado dentro das 4 áreas.
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR 50

#define PTAINHA 100
#define PCIOBA 150
#define PROBALO 200
#define CARGAMAX 10

#define CIMA 0
#define BAIXO 1
#define DIR 2
#define ESQ 3

typedef struct {
    int value;
    int boat; //há ou não barco
} Celula;

typedef struct meuBarco{
	int px; int py;
    int casaAtual;
    int inicio;
    int mullet; 
    int snapper;
    int seabass;
    int qntPeixe;
} Barco;

Barco atualizarBarco(Barco barco, int x, int y, int atual){
	barco.px=y;
    barco.py=x;
    /*============================================================
    //Ressalva//
    Os valores de X e Y estão inicialmente invertidos MAS a intenção 
    durante o desenvolvimento da lógica da movimentação do barco dentro das 
    dimensões do mapa é planejar a movimentação mentalizando o mapa 
    como um plano cartesiano, semelhante a uma batalha naval, 
    com X representando o deslocamento horizontal e Y representando o descocamento vertical.
    ============================================================*/
    if (barco.inicio==0){
        barco.mullet=0; 
        barco.snapper=0;
        barco.seabass=0;
        barco.qntPeixe=0;
    }
    barco.casaAtual=atual;
    return barco;
} //Salva/Atualiza os dados do boat a cada rodada

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
Barco readData(Barco barco, int h, int w, char* myId, Celula ***lerMapa) {
	char id[MAX_STR];
	int n, x, y;

    Celula **mapa;
    mapa=malloc(h*sizeof(Celula*));
    for (int i = 0; i < h; i++){
        mapa[i]=malloc(w*sizeof(Celula));
    }

	// lê os dados da área de pesca
	for (int i = 0; i < h; i++) {   
		for (int j = 0; j < w; j++) {
			// scanf("%i", &v); //Original
            scanf("%i", &mapa[i][j].value);
            mapa[i][j].boat=0;
		}
	}

	// lê os dados dos bots
	scanf(" BOTS %i", &n);
	// o " " antes de BOTS é necessário para ler o '\n' da linha anterior
	for (int i = 0; i < n; i++) {
		scanf("%s %i %i", id, &x, &y);
        int ret =strcmp(myId, id);
        if (ret==0){
            barco=atualizarBarco(barco, x, y, mapa[x][y].value);
        }else{
            mapa[x][y].boat=1;
            //outros bots
        }
        // fprintf(stderr, "To na posicao (%d,%d)\n", y, x); 
	}
    *lerMapa=mapa;
    return barco;
}

// 0:cima  1:baixo    2:direita   3:esquerda
// 4:cimaesquerda  5:cimadireita    6:baixoesquerda   7:baixodireita
void direcao(int decisao){
    // int boatD=mapa[barco.px+1][barco.py].boat; int portoD=mapa[barco.px+1][barco.py].value;
    // int boatE=mapa[barco.px-1][barco.py].boat; int portoE=mapa[barco.px-1][barco.py].value;
    // int boatC=mapa[barco.px][barco.py+1].boat; int portoC=mapa[barco.px][barco.py+1].value;
    // int boatB=mapa[barco.px][barco.py-1].boat; int portoB=mapa[barco.px][barco.py-1].value;
    
    if (decisao==0){printf("UP\n");
    }else if(decisao==1){printf("DOWN\n");
    }else if(decisao==2){printf("RIGHT\n");
    }else if(decisao==3){printf("LEFT\n");}
}

void varrerArea(int *direcoes, Barco barco, int h, int w, Celula **mapa, int acao, int casas){
    // if (barco.py>0){printf("UP\n");
    // }else{printf("DOWN\n");}
    fprintf(stderr, "CASAS\n: %d\n",casas);
    int portos[4];
    for (int i = 0; i < 4; i++){direcoes[i]=0;}
    for (int i = 0; i < 4; i++){portos[i]=0;}

    int dmax=0; 
    int dc, db, de, dd=0;
    dc=barco.py; db=h-barco.py-1; de=barco.px; dd=w-barco.px-1;
    int maxvet[4]; maxvet[0]=dc; maxvet[1]=db; maxvet[2]=de; maxvet[3]=dd; 
    for (int i = 0; i < 4; i++){
        if (maxvet[i]>dmax){
            dmax=maxvet[i];
        }
    }

    //CONFERIR AREA ACIMA
    if (((barco.py)-casas)>=0){
        int soma=0; int dir=0; int min=0; int max=w; int ymin=((barco.py)-casas); int ymax=barco.py; int valor=0;
        // if (((barco.py)-casas)>0){ymin=((barco.py)-casas);}
        for (int i = ymin; i < ymax; i++){
            if (((barco.px)-casas)>0){min=((barco.px)-casas);}// fprintf(stderr, "min: %d\n",min);
            if (((barco.px)+casas)<w){max=((barco.px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaCima: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosCima: %d\n",portos[dir]);
    }else if((barco.py)!=0){
        int soma=0; int dir=0; int min=0; int max=w; int ymin=0; int ymax=h; int valor=0;
        // if (((barco.py)-casas)>0){ymin=((barco.py)-casas);}
        // if (((barco.py)+casas)<h){ymax=((barco.py)+casas)+1;}//74703
        for (int i = (barco.py)-1; i < (barco.py); i++){
            if (((barco.px)-casas)>0){min=((barco.px)-casas);}// fprintf(stderr, "min: %d\n",min);
            if (((barco.px)+casas)<w){max=((barco.px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaCima: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosCima: %d\n",portos[dir]);
    }

    //CONFERIR AREA ABAIXO
    if (((barco.py)+casas)<=(h-1)){
        int soma=0; int dir=1; int min=0; int max=w; int ymin=barco.py+1; int ymax=((barco.py)+casas)+1; int valor=0;
        for (int i = ymin; i < ymax; i++){
            if (((barco.px)-casas)>0){min=((barco.px)-casas);}
            if (((barco.px)+casas)<w){max=((barco.px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "Areabaixo: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosBaixo: %d\n",portos[dir]);
    }else if((barco.py)!=(h-1)){
        int soma=0; int dir=1; int min=0; int max=w; int valor=0;
        for (int i = ((barco.py)+1); i < ((barco.py)+2); i++){
            if (((barco.px)-casas)>0){min=((barco.px)-casas);}
            if (((barco.px)+casas)<w){max=((barco.px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "Areabaixo: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosBaixo: %d\n",portos[dir]);
    }

    //CONFERIR AREA DIREITA
    if (((barco.px)+casas)<=(w-1)){
        int soma=0; int dir=2; int xmin=(barco.px+1); int xmax=w; int ymin=0; int ymax=h; int valor=0;
        if (((barco.py)-casas)>0){ymin=((barco.py)-casas);}
        if (((barco.py)+casas)<h){ymax=((barco.py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            // if (((barco.px)-casas)>0){xmin=((barco.px)-casas);}
            if (((barco.px)+casas)<w){xmax=((barco.px)+casas)+1;}
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "Areadireita: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosDireita: %d\n",portos[dir]);
    }
    // else if(((barco.py)+casas-1)<=(h-1)){
    //     int soma=0; int dir=1; int min=0; int max=w; int valor=0;
    //     for (int i = ((barco.py)+1); i < ((barco.py)+(casas)); i++){
    //         if (((barco.px)-casas)>0){min=((barco.px)-casas);}
    //         if (((barco.px)+casas)<w){max=((barco.px)+casas)+1;}
    //         for (int j = min; j < max; j++){
    //             if (mapa[i][j].boat==0){ valor=(mapa[i][j].value);
    //                 if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
    //             }
    //             if (valor==1){portos[dir]=portos[dir]+1;}
    //         }
    //     }direcoes[dir]=soma;
    //     fprintf(stderr, "Areabaixo: %d\n",direcoes[dir]);
    //     fprintf(stderr, "PortosBaixo: %d\n",portos[dir]);
    // }

    //CONFERIR AREA ESQUERDA
    if (((barco.px)-casas)>=0){
        int soma=0; int dir=3; int xmin=0; int xmax=barco.px; int ymin=0; int ymax=h; int valor=0;
        if (((barco.py)-casas)>0){ymin=((barco.py)-casas);}
        if (((barco.py)+casas)<h){ymax=((barco.py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            if (((barco.px)-casas)>0){xmin=((barco.px)-casas);}
            // if (((barco.px)-casas)<w){xmax=((barco.px)+casas)+1;}
            // fprintf(stderr, "min: %d\n",xmin);
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){fprintf(stderr, "OPA\n");portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaEsquerda: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosEsquerda: %d\n",portos[dir]);
    }else if(((barco.px)!=0)>=0){
        int soma=0; int dir=3; int xmin=barco.px-1; int xmax=barco.px; int ymin=0; int ymax=h; int valor=0;
        if (((barco.py)-casas)>0){ymin=((barco.py)-casas);}
        if (((barco.py)+casas)<h){ymax=((barco.py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            // if (((barco.px)-casas)>0){xmin=((barco.px)-casas);}
            // if (((barco.px)-casas)<w){xmax=((barco.px)+casas)+1;}
            // fprintf(stderr, "min: %d\n",xmin);
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaEsquerda: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosEsquerda: %d\n",portos[dir]);
    }

    int decisao=0;
    if (acao==0){ //PESCA
        //Quero o maior valor pois quero pescar
        int max=0;
        for (int i = 0; i < 4; i++){
            if (direcoes[i]>max){
                max=direcoes[i];
                decisao=i;
            }
        }
        // fprintf(stderr, "A decisao eh: %d\n", decisao);
        //Decidir posicao
        if (max==0){
            // varrerArea(direcoes, barco, h, w, mapa, acao, casas+1);
            int porto=0;
            for (int i = 0; i < 4; i++){
                if (portos[i]==1){
                    porto=porto+1;
                    decisao=i;
                }
            }
            if ((porto>0)&&(barco.qntPeixe>0)){
                // if(decisao!=0){
                // if (porto>1){
                //     //Condicao para a melhor direcao caso duas direcoes tenham porto
                // }else{
                    direcao(decisao);
                // }
            }else{
                fprintf(stderr, "\nTa complicado");
                if (casas==dmax){
                    fprintf(stderr, "\nErro");
                }else{
                    varrerArea(direcoes, barco, h, w, mapa, acao, casas+1);
                }
            }
        }else{
            //Comando para direcao da area mais valiosa
            direcao(decisao);
        }
    }else{
        //Quero 1 para vender carga
        int porto=0;
        int maxporto=0;
        for (int i = 0; i < 4; i++){
            if (portos[i]>0){
                porto=porto+portos[i];
                if (portos[i]>maxporto){
                    maxporto=portos[i];
                    decisao=i;
                }
            }
        }
        // if ((decisao==0)&&(barco.py==0)){
        //     varrerArea(direcoes, barco, h, w, mapa, acao, casas+1);
        // }else{
        //     direcao(decisao);
        // }
        fprintf(stderr, "Porto: %d\n", porto);
        //Decidir posicao
        if (porto>0){
            // if(decisao!=0){
                fprintf(stderr, "A decisao de area eh: %d\n", decisao);
            direcao(decisao);
            // }else{
            //     fprintf(stderr, "\nTa complicado");
            //     varrerArea(direcoes, barco, h, w, mapa, acao, casas+1);
            // }
        }else{
            // if((decisao==0)&&(barco.py==0)){
                fprintf(stderr, "\nTa complicado");
                if (casas==dmax){
                    // if (barco.py==0){
                    //     direcao(3);
                    // }else{
                    //     direcao(0);
                    // }
                    fprintf(stderr, "\nErro");
                }else{
                    // fprintf(stderr, "\nErro2");
                    varrerArea(direcoes, barco, h, w, mapa, acao, casas+1);
                }
            // }else{
            //     direcao(decisao);
            // }
        }
    }
}

/**********************************************************************************************************
***********************************************************************************************************
================== FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO ========================
***********************************************************************************************************
O parametro acao indica o que eu tenho intencao de fazer:**************************************************
[0: pescar // 1: vender]***********************************************************************************
***********************************************************************************************************/
void movimentacao(int *direcoes, Barco barco, char* line, int h, int w, Celula **mapa, int acao, int casas){ 
    /* movimentacao no mar*/
    for (int i = 0; i < 4; i++){direcoes[i]=0;}

    //Analisar posicoes acima, abaixo, a direita e a esquerda
    // 0:cima  1:baixo    2:direita   3:esquerda
    //CONFERIR DIRECAO ACIMA
    int espaco=CARGAMAX-(barco.qntPeixe);
    if ((barco.py-casas)>=0){
        //0:cima
        int qtdPeixe=0;
        int cima = mapa[(barco.py)-casas][barco.px].value;
        int cimabot = mapa[(barco.py)-casas][barco.px].boat;
        if (cimabot>0){if (cima==1){direcoes[CIMA]=1;}else{direcoes[CIMA]=0;}
        }else if (cima==0){direcoes[CIMA]=0;
        }else if(cima==1){direcoes[CIMA]=1;
        }else if((cima>11) && (cima<20)){
            //tainha nessa direcao
            qtdPeixe=cima-11;
            if (espaco>qtdPeixe){direcoes[CIMA]=qtdPeixe*PTAINHA;
            }else{direcoes[CIMA]=espaco*PTAINHA;}
        }else if((cima>21) && (cima<30)){
            //cioba nessa direcao
            qtdPeixe=cima-21;
            if (espaco>qtdPeixe){direcoes[CIMA]=qtdPeixe*PCIOBA;
            }else{direcoes[CIMA]=espaco*PCIOBA;}
        }else if(cima>31){
            //ROBALO nessa direcao
            qtdPeixe=cima-31;
            if (espaco>qtdPeixe){direcoes[CIMA]=qtdPeixe*PROBALO;
            }else{direcoes[CIMA]=espaco*PROBALO;}
        }else{
            direcoes[CIMA]=0;
        }
        // fprintf(stderr, "Cima: %d", direcoes[CIMA]);
    }   

    //CONFERIR DIRECAO ABAIXO
    if ((barco.py+casas)<=(h-1)){
        //1:baixo
        int qtdPeixe=0;
        int baixo = mapa[(barco.py)+casas][barco.px].value;
        int baixobot = mapa[(barco.py)+casas][barco.px].boat;
        if (baixobot>0){if (baixo==1){direcoes[BAIXO]=1;}else{direcoes[BAIXO]=0;}
        }else if (baixo==0){direcoes[BAIXO]=0;
        }else if(baixo==1){direcoes[BAIXO]=1;
        }else if((baixo>11) && (baixo<20)){
            //tainha nessa direcao
            qtdPeixe=baixo-11;
            if (espaco>qtdPeixe){direcoes[BAIXO]=qtdPeixe*PTAINHA;
            }else{direcoes[BAIXO]=espaco*PTAINHA;}
        }else if((baixo>21) && (baixo<30)){
            //cioba nessa direcao
            qtdPeixe=baixo-21;
            if (espaco>qtdPeixe){direcoes[BAIXO]=qtdPeixe*PCIOBA;
            }else{direcoes[BAIXO]=espaco*PCIOBA;}
        }else if(baixo>31){
            //ROBALO nessa direcao
            qtdPeixe=baixo-31;
            if (espaco>qtdPeixe){direcoes[BAIXO]=qtdPeixe*PROBALO;
            }else{direcoes[BAIXO]=espaco*PROBALO;}
        }else{
            direcoes[BAIXO]=0;
        }
        // fprintf(stderr, "Baixo: %d", direcoes[BAIXO]);
    }  

    //CONFERIR DIRECAO A DIREITA
    if ((barco.px+casas)<=(w-1)){
        //2:direita
        int qtdPeixe=0;
        int direita = mapa[barco.py][(barco.px)+casas].value;
        int direitabot = mapa[barco.py][(barco.px)+casas].boat;
        if (direitabot>0){if (direita==1){direcoes[DIR]=1;}else{direcoes[DIR]=0;}
        }else if (direita==0){direcoes[DIR]=0;
        }else if(direita==1){direcoes[DIR]=1;
        }else if((direita>11) && (direita<20)){
            //tainha nessa direcao
            qtdPeixe=direita-11;
            if (espaco>qtdPeixe){direcoes[DIR]=qtdPeixe*PTAINHA;
            }else{direcoes[DIR]=espaco*PTAINHA;}
        }else if((direita>21) && (direita<30)){
            //cioba nessa direcao
            qtdPeixe=direita-21;
            if (espaco>qtdPeixe){direcoes[DIR]=qtdPeixe*PCIOBA;
            }else{direcoes[DIR]=espaco*PCIOBA;}
        }else if(direita>31){
            //ROBALO nessa direcao
            qtdPeixe=direita-31;
            if (espaco>qtdPeixe){direcoes[DIR]=qtdPeixe*PROBALO;
            }else{direcoes[DIR]=espaco*PROBALO;}
        }else{
            direcoes[DIR]=0;
        }
        // fprintf(stderr, "Direita: %d",direcoes[DIR]);
    }   

    //CONFERIR DIRECAO A ESQUERDA
    if ((barco.px-casas)>=0){
        //3:esquerda
        int qtdPeixe=0;
        int esquerda = mapa[barco.py][(barco.px)-casas].value;
        int esquerdabot = mapa[barco.py][(barco.px)-casas].boat;
        if (esquerdabot>0){if (esquerda==1){direcoes[ESQ]=1;}else{direcoes[ESQ]=0;}
        }else if (esquerda==0){direcoes[ESQ]=0;
        }else if(esquerda==1){direcoes[ESQ]=1;
        }else if((esquerda>11) && (esquerda<20)){
            //tainha nessa direcao
            qtdPeixe=esquerda-11;
            if (espaco>qtdPeixe){direcoes[ESQ]=qtdPeixe*PTAINHA;
            }else{direcoes[ESQ]=espaco*PTAINHA;}
        }else if((esquerda>21) && (esquerda<30)){
            //cioba nessa direcao
            qtdPeixe=esquerda-21;
            if (espaco>qtdPeixe){direcoes[ESQ]=qtdPeixe*PCIOBA;
            }else{direcoes[ESQ]=espaco*PCIOBA;}
        }else if(esquerda>31){
            //ROBALO nessa direcao
            qtdPeixe=esquerda-31;
            if (espaco>qtdPeixe){direcoes[ESQ]=qtdPeixe*PROBALO;
            }else{direcoes[ESQ]=espaco*PROBALO;}
        }else{
            direcoes[ESQ]=0;
        }
        // fprintf(stderr, "Esquerda: %d",direcoes[ESQ]);
    }   
    for (int i = 0; i < 4; i++){fprintf(stderr, "%d: %d",i, direcoes[i]);}
    
    // printf("UP\n"); //teste - comentar
    int decisao=0;
    if (acao==0){ //PESCA
        //Quero o maior valor pois quero pescar
        int max=0;
        for (int i = 0; i < 4; i++){
            if (direcoes[i]>max){
                max=direcoes[i];
                decisao=i;
            }
        }
        //Decidir posicao
        if (max==0){
            // Conferir diagonais´
            varrerArea(direcoes, barco, h, w, mapa, acao, casas);
            // movimentacaoDiag(direcoes, barco, h, w, mapa, 0, 1);
        }else if(max==1){
            if (barco.qntPeixe>0){
                //Comando para direcao do porto
                direcao(decisao);
            }else{
                varrerArea(direcoes, barco, h, w, mapa, acao, casas);
                // movimentacaoDiag(direcoes, barco, h, w, mapa, 0, 1);
            }
        }else{
            //Comando para direcao do peixe mais valioso
            direcao(decisao);
        }
    }else{
        //Quero 1 para vender carga
        int porto=0;
        for (int i = 0; i < 4; i++){
            if (direcoes[i]==1){
                porto=1;
                decisao=i;
            }
        }
        //Decidir posicao
        if (porto==1){
            direcao(decisao);
        }else{
            varrerArea(direcoes, barco, h, w, mapa, acao, casas);
            // movimentacaoDiag(direcoes, barco, h, w, mapa, 1, 1);
        }
    }
    scanf("%s", line);
}
/**********************************************************************************************************
***********************************************************************************************************
***********************************************************************************************************
================== FIM DA FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO =================
***********************************************************************************************************
***********************************************************************************************************
***********************************************************************************************************/

// === MAIN ===
// === INICIO DA PARTIDA === 
int main() {
	char line[MAX_STR];   // dados temporários
	char myId[MAX_STR];   // identificador do bot em questão

	setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
	setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
	setbuf(stderr, NULL);

	// === INÍCIO DA PARTIDA ===
	int h, w;
	scanf("AREA %i %i", &h, &w);  // lê a dimensão da área de pesca: altura (h) x largura (w)
	scanf(" ID %s", myId);        // ...e o id do bot
	// obs: o " " antes de ID é necessário para ler o '\n' da linha anterior
	fprintf(stderr, "Meu id = %s\n", myId); //Exemplo de erro enviado para o terminal

    Barco barco;
    Celula **mapa;
    int direcoes[4];
    
	// O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
	// o processo quando o jogo terminar.
	while (1) {
		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		barco=readData(barco, h, w, myId, &mapa);
        // fprintf(stderr, "Tô em: %d\n", barco.casaAtual);
        
		// ABAIXO TODAS AS POSSIBILIDADES PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
        if (barco.casaAtual==0){
            if (barco.qntPeixe<10){
                movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
            }else{
                movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);
            }
        }else if(barco.casaAtual==1){
            if (barco.inicio==0){
                barco.inicio=1;
                movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
            }else{
                if (barco.qntPeixe>0){
                    printf("SELL\n");
                    scanf("%s", line);
                    if (atoi(line)>0){
                        barco.mullet=0; 
                        barco.snapper=0;
                        barco.seabass=0;
                        barco.qntPeixe=0;
                    }
                }else{movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);}
            }
        }else{
            if (((barco.casaAtual>11) && (barco.casaAtual<20))||((barco.casaAtual>21) && (barco.casaAtual<30))||(barco.casaAtual>31)){
                fprintf(stderr, "NUMERO %d (%d,%d)", barco.casaAtual, barco.px, barco.py);
                if (barco.qntPeixe<10){
                    printf("FISH\n");
                    scanf("%s", line);
                    int ret=0;
                    ret=strcmp(line, "MULLET");
                    if (ret==0){
                        barco.mullet=barco.mullet+1;
                    }else {
                        ret=strcmp(line, "SNAPPER");
                        if (ret==0){
                            barco.snapper=barco.snapper+1;
                        }else{
                            ret=strcmp(line, "SEABASS");
                            if (ret==0){
                                barco.seabass=barco.seabass+1;
                            }
                        }
                    }
                    ret=strcmp(line, "NONE"); 
                    if (ret!=0){
                        barco.qntPeixe=barco.mullet+barco.snapper+barco.seabass;
                    }
                }else{
                    fprintf(stderr, "Capacidade maxima\n"); 
                    movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);
                }
            }else{
                if (barco.qntPeixe<10){movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
                }else{movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);}
            }
        }
        //Fim do while
	}

	return 0;
}