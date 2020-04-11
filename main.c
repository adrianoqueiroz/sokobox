#include <allegro.h>
#include <alfont.h>
#include <stdio.h>

#define PIXELS 30 /*tamanho do piso*/
#define LINHAS 16
#define COLUNAS 16

#define PISO 0
#define PAREDE 1
#define CAIXA 2
#define DESTINO 3
#define CAIXA_DESTINO 4
#define JOGADOR 5
#define JOGADOR_DESTINO 6
#define LIXEIRA 7
#define BORRACHA 9


#define CIMA 1
#define BAIXO 2
#define ESQUERDA 3
#define DIREITA 4

/*botoes menu principal*/
#define BOTAO_JOGAR (mouse_x > 75 && mouse_y > 160) && (mouse_x < 215 && mouse_y < 175)
#define BOTAO_MINHAS_FASES (mouse_x > 75 && mouse_y > 220) && (mouse_x<390 && mouse_y<235)
#define BOTAO_INSTRUCOES (mouse_x > 75 && mouse_y > 270) && (mouse_x<320 && mouse_y<295)
#define BOTAO_OPCOES (mouse_x > 75 && mouse_y >330) && (mouse_x < 255 && mouse_y<355)
#define BOTAO_CREDITOS (mouse_x > 75 && mouse_y > 390) && (mouse_x<290 && mouse_y<415)
#define BOTAO_SAIR (mouse_x > 75 && mouse_y > 450) && (mouse_x<175 && mouse_y < 475)

/*botoes menu opcoes*/
#define BOTAO_SKIN (mouse_x > 75 && mouse_y > 212) && (mouse_x<185 && mouse_y < 235)
#define BOTAO_SOM (mouse_x > 75 && mouse_y > 272) && (mouse_x<175 && mouse_y < 295)
#define BOTAO_TELA_CHEIA (mouse_x > 75 && mouse_y > 330) && (mouse_x<330 && mouse_y < 355)
#define BOTAO_REPLAY (mouse_x > 75 && mouse_y > 392) && (mouse_x<255 && mouse_y < 415)
#define BOTAO_VOLTAR (mouse_x > 75 && mouse_y > 450) && (mouse_x<252 && mouse_y < 475)

#define SKIN 1
#define SOM 2
#define TELA_CHEIA 3
#define REPLAY 4
#define VOLTAR 5

/*botoes minhas fases*/
#define BOTAO_JOGAR_MF (mouse_x > 75 && mouse_y > 212) && (mouse_x<185 && mouse_y < 235)
#define BOTAO_CRIAR_FASE (mouse_x > 75 && mouse_y > 272) && (mouse_x<175 && mouse_y < 295)
#define BOTAO_APAGAR_REGISTROS (mouse_x > 75 && mouse_y > 330) && (mouse_x<330 && mouse_y < 355)
#define BOTAO_VOLTAR_MF (mouse_x > 75 && mouse_y > 392) && (mouse_x<255 && mouse_y < 415)

#define JOGAR_MF 1
#define CRIAR_FASE 2
#define APAGAR_REGISTROS 3
#define VOLTAR_MF 4
/*botoes editor*/

/*botoes jogo*/
#define BOTAO_PROXIMA_FASE (mouse_x > 570 && mouse_y > 130) && (mouse_x<600 && mouse_y < 160)
#define BOTAO_VOLTAR_FASE (mouse_x > 515 && mouse_y > 130) && (mouse_x<545 && mouse_y < 160)
#define BOTAO_REINICIAR (mouse_x > 495 && mouse_y > 265) && (mouse_x<625 && mouse_y < 275)
#define BOTAO_VOLTAR_MOVIMENTO (mouse_x > 515 && mouse_y > 210) && (mouse_x<545 && mouse_y < 230)
#define BOTAO_PROXIMO_MOVIMENTO (mouse_x > 570 && mouse_y > 210) && (mouse_x<600 && mouse_y < 240)
#define BOTAO_RECORDE (mouse_x > 490 && mouse_y > 320) && (mouse_x<630 && mouse_y < 340)
#define BOTAO_SAIR_JOGO (mouse_x > 530 && mouse_y > 420) && (mouse_x<590 && mouse_y < 440)

#define JOGAR 1
#define MINHAS_FASES 2
#define INSTRUCOES 3
#define OPCOES 4
#define CREDITOS 5
#define SAIR 6

/*skins*/
#define OFICIAL 0

    int matriz[20][20];
    int xJogador, yJogador;
    int origemFase, passouFase=0, moveu=0;
    int skinSelecionada = OFICIAL;
    int telaCheia=0, opcaoReplay=1, som=1, quantidadeFases, fase=1;
    int verificacao=0, executandoReplay=0;
    
	BITMAP *fundo, *caixa, *destinoCaixa, *destinoComCaixa, *parede, *piso, *vazio;
    BITMAP *jogadorCima, *jogadorBaixo, *jogadorEsquerda, *jogadorEsquerdaAnda, *jogadorDireita, *jogadorDireitaAnda;
    BITMAP *jogadorCimaAnda1, *jogadorCimaAnda2, *jogadorBaixoAnda1, *jogadorBaixoAnda2;
    BITMAP *jogadorEsquerdaEmpurra, *jogadorEsquerdaAndaEmpurra, *jogadorDireitaEmpurra, *jogadorDireitaAndaEmpurra;
    BITMAP *skins, *skinJogo, *mascote, *buffer;
    BITMAP *menu, *pisoMenu, *borracha, *lixeira;
    BITMAP *faseCompleta, *linha;
    ALFONT_FONT *comic, *doom;
    MIDI *temaMenu, *temaJogo, *finalFase;
    SAMPLE *mouse;
    
    DATAFILE *imagens, *sons;

void textoMenuJogo();
void executaJogo();

    
void liberaMemoria(void){
    destroy_bitmap(caixa);
    destroy_bitmap(destinoCaixa);
    destroy_bitmap(destinoComCaixa);
    destroy_bitmap(parede);
    destroy_bitmap(piso);
    destroy_bitmap(vazio);
    destroy_bitmap(jogadorCima);
    destroy_bitmap(jogadorBaixo);
    destroy_bitmap(jogadorEsquerda);
    destroy_bitmap(jogadorDireita);
    destroy_bitmap(skins);
    destroy_bitmap(skinJogo);
    destroy_bitmap(borracha);
    destroy_bitmap(lixeira);
    
    destroy_bitmap(buffer);
    destroy_bitmap(menu);
    destroy_bitmap(faseCompleta);
    destroy_bitmap(linha);

    destroy_midi(temaMenu);
    destroy_midi(temaJogo);
    destroy_midi(finalFase);
    
    destroy_sample(mouse);
    
    alfont_destroy_font(comic);
    alfont_destroy_font(doom);
}

void instalaComponentes(void){
    allegro_init();
    alfont_init(); 
    install_timer();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_uformat(U_ASCII);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0);
    set_window_title("SokoBox - Laboratório de Programação I");
}
    
void carregaImagens(void){
    packfile_password("582634");
    imagens = load_datafile("data\\imagens.dat");
    menu = create_bitmap(640,480);
    fundo = create_bitmap(640,480);
    skins = create_bitmap(640,480);
    
    fundo = (BITMAP *)imagens[0].dat;    
    menu = (BITMAP *)imagens[1].dat;
    skins = (BITMAP *)imagens[2].dat;
    packfile_password(NULL);

    buffer = create_bitmap(640,480);
    if (!menu || !fundo || !skins)
        allegro_message("erro ao carregar imagens");
    
    skinJogo = create_bitmap(240, 400);
    jogadorBaixo = create_bitmap(PIXELS, PIXELS);
    jogadorBaixoAnda1 = create_bitmap(PIXELS, PIXELS);
    jogadorBaixoAnda2 = create_bitmap(PIXELS, PIXELS);
    jogadorCima = create_bitmap(PIXELS, PIXELS);
    jogadorCimaAnda1 = create_bitmap(PIXELS, PIXELS);
    jogadorCimaAnda2 = create_bitmap(PIXELS, PIXELS);
    jogadorEsquerda = create_bitmap(PIXELS, PIXELS);
    jogadorEsquerdaAnda = create_bitmap(PIXELS, PIXELS);
    jogadorEsquerdaEmpurra = create_bitmap(PIXELS, PIXELS);
    jogadorEsquerdaAndaEmpurra = create_bitmap(PIXELS, PIXELS);
    jogadorDireita = create_bitmap(PIXELS, PIXELS);
    jogadorDireitaAnda = create_bitmap(PIXELS, PIXELS);
    jogadorDireitaEmpurra = create_bitmap(PIXELS, PIXELS);
    jogadorDireitaAndaEmpurra = create_bitmap(PIXELS, PIXELS);
    caixa = create_bitmap(PIXELS, PIXELS);
    destinoCaixa = create_bitmap(PIXELS, PIXELS);
    destinoComCaixa = create_bitmap(PIXELS, PIXELS);
    parede = create_bitmap(PIXELS, PIXELS);
    piso = create_bitmap(PIXELS, PIXELS);
    pisoMenu = create_bitmap(PIXELS, PIXELS);
    vazio = create_bitmap(PIXELS, PIXELS);
    borracha = create_bitmap(PIXELS, PIXELS);
    lixeira = create_bitmap(PIXELS, PIXELS);
    mascote = create_bitmap(240,310);
    
    blit(skins, skinJogo, skinSelecionada*240, 0, 0, 0, 240, 400);
    blit(skinJogo, mascote, 0,90, 0, 0, 240, 310);
    
    blit(skinJogo, jogadorBaixo, 0*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorBaixoAnda1, 1*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorBaixoAnda2, 2*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorCima, 3*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorCimaAnda1, 4*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorCimaAnda2, 5*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorDireita, 6*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorDireitaAnda, 7*PIXELS, 0*PIXELS, 0, 0, PIXELS, PIXELS);

    blit(skinJogo, jogadorDireitaEmpurra, 0*PIXELS, 1*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorDireitaAndaEmpurra, 1*PIXELS, 1*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorEsquerda, 2*PIXELS, 1*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorEsquerdaAnda, 3*PIXELS, 1*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorEsquerdaEmpurra, 4*PIXELS, 1*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, jogadorEsquerdaAndaEmpurra, 5*PIXELS, 1*PIXELS, 0, 0, PIXELS, PIXELS);


    blit(skinJogo, caixa, 0*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, destinoComCaixa, 1*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, piso, 2*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, destinoCaixa, 3*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, parede, 4*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, vazio, 5*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, borracha, 6*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
    blit(skinJogo, lixeira, 7*PIXELS, 2*PIXELS, 0, 0, PIXELS, PIXELS);
} 

void carregaSons(void){
    packfile_password("582634");
    sons = load_datafile("data\\sons.dat");
    mouse =  (SAMPLE *)sons[0].dat;
    packfile_password(NULL);

    switch (skinSelecionada){
        case OFICIAL:
            temaJogo = (MIDI *)sons[3].dat;    
            temaMenu = (MIDI *)sons[4].dat;
            break;
        default:
            temaJogo = (MIDI *)sons[3].dat;    
            temaMenu = (MIDI *)sons[4].dat;
            break;     
    }
    
    if (!temaMenu || !temaJogo || !mouse){
        allegro_message("erro ao carregar o audio\n Por favor, reinstale o programa!");
        exit(1);
    }
}

void carregaFontes(void){
    comic = alfont_load_font("data\\comic.ttf");
    doom = alfont_load_font("data\\doom.ttf");
}

void carregaFase(int numeroFase) {
    int l, c, numero;
    FILE *fases;
    int contador=1;
    
    if (origemFase == MINHAS_FASES)
        fases = fopen ("data\\minhas fases.dat", "rb");
    else
        fases = fopen ("data\\fases.dat", "rb");
    
    while (fscanf(fases, "%d", &numero) != EOF)
        contador++;
    quantidadeFases = contador/256;
    fclose(fases);
    
    if (quantidadeFases){
        if (origemFase == MINHAS_FASES)
            fases = fopen ("data\\minhas fases.dat", "rb");
        else
            fases = fopen ("data\\fases.dat", "rb");

        contador=1;    
        while ((contador++)<(numeroFase-1)*256)
            fscanf(fases, "%d", &numero);
        
        for (l=0; l < LINHAS; l++)
            for (c=0; c < COLUNAS; c++)
                if  (fscanf(fases, "%d", &numero) != EOF)
                    matriz[l][c] = numero;

        fclose(fases);
    }
}

void imprimir(int linha, int coluna) {
    switch (matriz[linha][coluna]) {
        case PISO:
            draw_sprite(buffer, piso, linha*PIXELS, coluna*PIXELS);            
            break;
        case PAREDE:
            draw_sprite(buffer, parede, linha*PIXELS, coluna*PIXELS);            
            break;
        case CAIXA:
            draw_sprite(buffer, caixa, linha*PIXELS, coluna*PIXELS);
            break;
        case DESTINO:    
            draw_sprite(buffer, destinoCaixa, linha*PIXELS, coluna*PIXELS);
            break;
        case CAIXA_DESTINO:
            draw_sprite(buffer, destinoComCaixa, linha*PIXELS, coluna*PIXELS);
            break;
        case JOGADOR:
        case JOGADOR_DESTINO:
            draw_sprite(buffer, piso, linha*PIXELS, coluna*PIXELS);
            draw_sprite(buffer, jogadorBaixo, linha*PIXELS, coluna*PIXELS);
            break;
        default:
            break;
    }
}

void imprimeFase(int mostrarNaTela) {
    int linha, coluna;
    
    draw_sprite(buffer, fundo, 0, 0);
    for (linha=0; linha < LINHAS; linha++) 
        for (coluna=0; coluna < COLUNAS; coluna++) {            
            if(matriz[linha][coluna]==JOGADOR || matriz[linha][coluna] == JOGADOR_DESTINO){
                xJogador=linha; yJogador=coluna;
            }   
	        imprimir(linha, coluna);
		}
        if (mostrarNaTela)
            draw_sprite(screen, buffer, 0, 0);    
}

int entradaMovimento(void) {
    if(keypressed()) {
        if(key[KEY_UP]) 
            return CIMA;
        else if(key[KEY_DOWN])
            return BAIXO;
        else if(key[KEY_LEFT])
            return ESQUERDA;
        else if(key[KEY_RIGHT])
            return DIREITA;
        else{
             sleep(20);
            return 0;
        }
    }
}

void incrementar(int direcao) {
    switch (direcao) {
        case CIMA: yJogador--;
        break;
        case BAIXO: yJogador++;
        break;
        case ESQUERDA: xJogador--;
        break;
        case DIREITA: xJogador++;
        break;
    }        
}

int verificaPosicao(int direcao, int incremento) {
    switch (direcao) {
        case CIMA:
            return matriz[xJogador][yJogador-incremento];
        case BAIXO:
            return matriz[xJogador][yJogador+incremento];
        case ESQUERDA:
	    return matriz[xJogador-incremento][yJogador];
        case DIREITA:
  	        return matriz[xJogador+incremento][yJogador];
		default:
		    return 0;
	}
}

void executaMovimento(int direcao, int *movimentos, int *numeroMovimentos, int gravarMovimento) {
    int primeiraCasa, segundaCasa;
    int xInc1, xInc2, yInc1, yInc2;
    
    switch (direcao) {
        case CIMA: 
            xInc1 = xJogador; xInc2 = xJogador; yInc1 = yJogador-1; yInc2 = yJogador-2;
            break;
        case BAIXO: 
            xInc1 = xJogador; xInc2 = xJogador; yInc1 = yJogador+1; yInc2 = yJogador+2;
            break;
        case ESQUERDA: 
            xInc1 = xJogador-1; xInc2 = xJogador-2; yInc1 = yJogador; yInc2 = yJogador;
            break;
        case DIREITA: 
            xInc1 = xJogador+1; xInc2 = xJogador+2; yInc1 = yJogador; yInc2 = yJogador;
            break;
        default:
            break;
    }
    
    primeiraCasa= verificaPosicao(direcao, 1);/*primeira casa ao lado do jogador*/
    segundaCasa = verificaPosicao(direcao, 2);
    switch (primeiraCasa) {
        case PISO:
            matriz[xInc1][yInc1] = JOGADOR;
       	    moveu =1;
            break;
        case DESTINO:
            matriz[xInc1][yInc1] = JOGADOR_DESTINO;
            moveu =3;
            break;
        case CAIXA:  
            if (segundaCasa == PISO) {
                matriz[xInc1][yInc1]=JOGADOR;
                matriz[xInc2][yInc2]=CAIXA;
                moveu =5;
            }
            else if (segundaCasa == DESTINO) {
                matriz[xInc1][yInc1] = JOGADOR;
                matriz[xInc2][yInc2]=CAIXA_DESTINO;
                moveu =7;
            }
            break;
        case CAIXA_DESTINO: 
            if (segundaCasa == PISO) {
                matriz[xInc1][yInc1]=JOGADOR_DESTINO;
                matriz[xInc2][yInc2]=CAIXA;
                moveu =5;
            }
            else if (segundaCasa == DESTINO) {
                matriz[xInc1][yInc1] = JOGADOR_DESTINO;
                matriz[xInc2][yInc2] = CAIXA_DESTINO;              
                moveu =7;
            }
            break;
        default:
            moveu =0;
            break;
    }

    if (moveu){ 
       if (matriz[xJogador][yJogador] == JOGADOR)
            matriz[xJogador][yJogador] = PISO;
        else{ 
            moveu+=1;
            matriz[xJogador][yJogador] = DESTINO;        
        }
        incrementar(direcao);
   
        if(gravarMovimento) 
            movimentos[(*numeroMovimentos)++]=direcao;
    }
}

void imprimirMovimento(int direcao, int numeroMovimentos){
    int i;
    int xSentido=0, ySentido=0;
    int xAnterior, yAnterior;
    BITMAP *imagemJogador, *imagemJogadorAnda, *imagemJogadorEmpurra, *imagemJogadorAndaEmpurra;
    BITMAP *imagemJogadorAux;
    
    switch (direcao) {
        case CIMA: 
            xAnterior = xJogador; yAnterior = yJogador+1; ySentido = -1;
            imagemJogadorAux = jogadorCima;
            imagemJogador = jogadorCimaAnda1;
            imagemJogadorAnda = jogadorCimaAnda2;
            imagemJogadorEmpurra = jogadorCimaAnda1;
            imagemJogadorAndaEmpurra = jogadorCimaAnda2;
            break;
        case BAIXO: 
            xAnterior = xJogador; yAnterior = yJogador-1; ySentido =1;
            imagemJogadorAux = jogadorBaixo;
            imagemJogador = jogadorBaixoAnda1;
            imagemJogadorAnda = jogadorBaixoAnda2;
            imagemJogadorEmpurra = jogadorBaixoAnda1;
            imagemJogadorAndaEmpurra = jogadorBaixoAnda2;
            break;
        case ESQUERDA: 
            xAnterior = xJogador+1; yAnterior = yJogador; xSentido = -1;
            imagemJogador = jogadorEsquerda;
            imagemJogadorAnda = jogadorEsquerdaAnda;
            imagemJogadorEmpurra = jogadorEsquerdaEmpurra;
            imagemJogadorAndaEmpurra = jogadorEsquerdaAndaEmpurra;
            break;
        case DIREITA: 
            xAnterior = xJogador-1; yAnterior = yJogador; xSentido = 1;
            imagemJogador = jogadorDireita;
            imagemJogadorAnda = jogadorDireitaAnda;
            imagemJogadorEmpurra = jogadorDireitaEmpurra;
            imagemJogadorAndaEmpurra = jogadorDireitaAndaEmpurra;
            break;
    }

    for (i=0; i<=PIXELS; i+=6, sleep(30)) {
        /*imprime o piso onde o jogador estava*/
        if (moveu%2)
            draw_sprite(buffer, piso, xAnterior*PIXELS, yAnterior*PIXELS); 
        else 
            draw_sprite(buffer, destinoCaixa, xAnterior*PIXELS, yAnterior*PIXELS);
        
        /*impreme o piso pra onde ele vai*/    
        if (matriz[xJogador][yJogador] == JOGADOR)          
            draw_sprite(buffer, piso, xJogador*PIXELS, yJogador*PIXELS);
        else
            draw_sprite(buffer, destinoCaixa, xJogador*PIXELS, yJogador*PIXELS);

        /*imprime o boneco sem empurrar*/
        if (moveu<5){
            if((direcao == CIMA || direcao==BAIXO) && i==30)
                draw_sprite(buffer, imagemJogadorAux, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
            else if (i==30)
                draw_sprite(buffer, imagemJogador, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);

            else if (i==0 ||i==3 || i==12 ||i==15 || i==24){
                draw_sprite(buffer, imagemJogadorAnda, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
            }
            else if(i==6 || i==9 || i==18 || i==21){
                draw_sprite(buffer, imagemJogador, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
            }

        }
        else
        /*imprime o boneco empurrando a caixa*/
        switch (moveu){
            case 5:
            case 6:
                if((direcao == CIMA || direcao==BAIXO) && i==30)
                    draw_sprite(buffer, imagemJogadorAux, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                else if (i==30)
                    draw_sprite(buffer, imagemJogadorEmpurra, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                
                else if (i==0 ||i==3 || i==12 ||i==15 || i==24)
                    draw_sprite(buffer, imagemJogadorAndaEmpurra, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                else if(i==6 || i==9 || i==18 || i==21)
                    draw_sprite(buffer, imagemJogadorEmpurra, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                
                draw_sprite(buffer, caixa, xJogador*PIXELS+i*xSentido, yJogador*PIXELS+i*ySentido);
                break;
            case 7:
            case 8:
                if((direcao == CIMA || direcao==BAIXO) && i==30)
                    draw_sprite(buffer, imagemJogadorAux, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                else if (i==30)
                    draw_sprite(buffer, imagemJogadorEmpurra, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                
                else{ 
                    if (i==0 ||i==3 || i==12 ||i==15 || i==24 || i==27)
                        draw_sprite(buffer, imagemJogadorAndaEmpurra, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                    else if(i==6 || i==9 || i==18 || i==21)
                        draw_sprite(buffer, imagemJogadorEmpurra, xAnterior*PIXELS+i*xSentido, yAnterior*PIXELS+i*ySentido);
                
                }
                draw_sprite(buffer, destinoComCaixa, xJogador*PIXELS+i*xSentido, yJogador*PIXELS+i*ySentido);
                break;                
        }
        alfont_set_font_size(doom, 21);
        draw_sprite(screen, buffer, 0,0);
        alfont_textprintf_centre_aa_ex(buffer, doom, 560, 140, makecol(255,255,255), -1, "%d", fase);
        alfont_textprintf_centre_aa_ex(screen, doom, 560, 210, makecol(255,255,255), -1, "%d", numeroMovimentos);
        textoMenuJogo();
    }
}


int verificaFim(void) {
    int contador=0, l, c;
    
    for (l=0; l < LINHAS; l++) 
        for (c=0; c < COLUNAS; c++)
            if(matriz[l][c] == CAIXA)
                contador++;
    return contador;
}

void centralizarMatriz(void){
    int matrizCentralizada[LINHAS][COLUNAS], l, c;
    int pc, mc, pl, ml;
    int menorLinha=LINHAS, maiorLinha=0, menorColuna=COLUNAS, maiorColuna=0;
    int primeiraLinha, primeiraColuna, ultimaLinha, ultimaColuna;
    int deltaLinha, deltaColuna;
    
    for(l=0;l<LINHAS;l++) {
        for(c=0;c<COLUNAS;c++) {
            matrizCentralizada[l][c]=9;
            
            if (matriz[l][c]!=9){
                if(l<menorLinha)
                    menorLinha = l;
                if (c<menorColuna)
                    menorColuna=c;
                if(l>maiorLinha)
                    maiorLinha=l;
                if (c>maiorColuna)
                    maiorColuna=c;
            }
        }
    }

    deltaColuna = maiorColuna - menorColuna;
    deltaLinha = maiorLinha - menorLinha;
    
    primeiraLinha = (LINHAS - deltaLinha)/2;
    primeiraColuna = (COLUNAS - deltaColuna)/2;

    for(pl=primeiraLinha, ml= menorLinha; ml<=maiorLinha;pl++, ml++)
        for(pc=primeiraColuna, mc=menorColuna ; mc<=maiorColuna; pc++, mc++)
            matrizCentralizada[pl][pc]=matriz[ml][mc];
    
    for(l=0;l<LINHAS;l++) 
        for(c=0;c<COLUNAS;c++) 
            matriz[l][c] = matrizCentralizada[l][c];
}

void criarFase(void){
    int item = PAREDE, itemSelecionado = PAREDE, salvarFase=0;
    int i, j, l, c;
    int numero, contador=1, faseCriada;
    FILE *fases;

void novaFase(void){
    draw_sprite(buffer, fundo, 0,0);
    for (i=0; i<LINHAS;i++)
        for(j=0; j<COLUNAS; j++){
            matriz[i][j]=9;
            draw_sprite(buffer, vazio, i*PIXELS, j*PIXELS);            
        }
}

void verificaNovaFase(int *verificacao) {
    int qtCaixas=0, qtDestinos=0, qtJogador=0;
    int i, j;  

    for(i=0;i<18;i++) {
        for(j=0;j<18;j++) {
            if(matriz[i][j]==CAIXA)
                qtCaixas++;
            if(matriz[i][j]==DESTINO)
                qtDestinos++;
            if(matriz[i][j]==JOGADOR)
                qtJogador++;  
        }  
    }
    
    if((qtCaixas==qtDestinos) && (qtJogador==1)) 
        *verificacao = 1;
    else *verificacao = 0;
}

void imprimirBotoes(void){
    if(itemSelecionado==PAREDE) 
        draw_sprite(buffer, parede, 540, 120);
    else if(itemSelecionado==BORRACHA)
        draw_sprite(buffer, borracha, 540, 120);
    
    draw_sprite(buffer, piso, 510,180);
    draw_sprite(buffer, jogadorBaixo, 510,180);
    draw_sprite(buffer, piso, 570,180);
    draw_sprite(buffer, caixa, 510,240);
    draw_sprite(buffer, destinoComCaixa, 570,240);
    draw_sprite(buffer, parede, 510,300);
    draw_sprite(buffer, destinoCaixa, 570,300);
    draw_sprite(buffer, borracha, 510,360);
    draw_sprite(buffer, lixeira, 570,360);
    
    alfont_set_font_size(doom, 23);
    alfont_textprintf_centre_aa_ex(buffer, doom, 560, 420, makecol(79,79,79), -1, "SALVAR");
    alfont_textprintf_centre_aa_ex(buffer, doom, 560, 450, makecol(79,79,79), -1, "SAIR");
    draw_sprite(screen, buffer, 0,0);
}
    carregaImagens();
    novaFase();
    imprimirBotoes();
    show_mouse(screen);
    
    for ( ; ;sleep(100)){
        if (mouse_x > 480 && mouse_y > 0) {
            if ((mouse_x > 570 && mouse_y > 180) && (mouse_x < 600 && mouse_y < 210)){ 
                if (item != PISO)
                    item = PISO;
            }
            else if ((mouse_x > 510 && mouse_y > 300) && (mouse_x < 540 && mouse_y < 330)){ 
                if (item != PAREDE)
                    item = PAREDE;
            }         
            else if ((mouse_x > 510 && mouse_y > 250) && (mouse_x < 540 && mouse_y < 270)){
                if (item != CAIXA)
                    item = CAIXA;
            }         
            else if ((mouse_x > 570 && mouse_y > 250) && (mouse_x < 600 && mouse_y < 270)){
                if (item != CAIXA_DESTINO)
                    item = CAIXA_DESTINO;
            }         
            else if ((mouse_x > 570 && mouse_y > 300) && (mouse_x < 600 && mouse_y < 330)){
                if (item != DESTINO)
                    item = DESTINO;
            }         
            else if ((mouse_x > 510 && mouse_y > 180) && (mouse_x < 540 && mouse_y < 210)){
                if (item != JOGADOR)
                    item = JOGADOR;
            }
            else if ((mouse_x > 510 && mouse_y > 360) && (mouse_x < 540 && mouse_y < 390)){
                if (item != BORRACHA)
                    item = BORRACHA;
            }
            else if ((mouse_x > 570 && mouse_y > 360) && (mouse_x < 600 && mouse_y < 390)){
                if (item != LIXEIRA)
                    item = LIXEIRA;
            }
            else if (item!=-1)
                item = -1;
                
            else if ((mouse_x > 500 && mouse_y > 420) && (mouse_x < 625 && mouse_y < 440)){
                    /*salvar a fase*/
                    if ((mouse_b & 1) && (verificacao)){
                    
                        while(mouse_b &1){
                        }
                        
                        centralizarMatriz();
    
                        fases = fopen("data\\minhas fases.dat","a+");
                        for(l=0;l<LINHAS;l++) {
                            for(c=0;c<COLUNAS;c++) {
                                fprintf(fases, "%d ", matriz[l][c]);
                            }
                            fprintf(fases,  "\n");
                        }
                        fprintf(fases,  "\n");
    
                        fclose(fases);


                        fases = fopen ("data\\minhas fases.dat", "r");
    
                        while (fscanf(fases, "%d", &numero) != EOF)
                            contador++;
                        faseCriada = contador/256;
                        fclose(fases);

                        imprimeFase(faseCriada);
                        itemSelecionado=PAREDE;
                        imprimirBotoes();
                        sleep(2000);
                        alfont_set_font_size(doom, 42);
                        alfont_textprintf_centre_aa_ex(screen, doom, 240, 200, makecol(100,100,100), -1, "FASE %d", faseCriada);
                        alfont_textprintf_centre_aa_ex(screen, doom, 240, 230, makecol(100,100,100), -1, "SALVO!");

                        sleep(1500);
                
                        contador=1;
                        itemSelecionado=PAREDE;               
                        novaFase();
                        imprimirBotoes();
                    }
            }
            else if ((mouse_x > 520 && mouse_y > 445) && (mouse_x < 600 && mouse_y < 470)){
                if (mouse_b & 1){
                    break;
					show_mouse(NULL);
				}
            }         
               
            if ((mouse_b & 1) && (item!=-1)) {
                play_sample(mouse,255,90,1000,0);
                while(mouse_b & 1){
                }
                
                if (item==LIXEIRA){
                    itemSelecionado=PAREDE;               
                    novaFase();
                    imprimirBotoes();
                }
                
                else {
                    itemSelecionado = item;
                    matriz[18][4]= itemSelecionado;
                    if (itemSelecionado==BORRACHA){
                        draw_sprite(buffer, piso, 18*PIXELS, 4*PIXELS);
                        draw_sprite(buffer, borracha, 18*PIXELS, 4*PIXELS);

                    }
                    else
                        imprimir(18,4);
                    draw_sprite(screen, buffer, 0, 0);
                }
            } 
       }
       else if (mouse_b & 1) {
           if (itemSelecionado== BORRACHA){
               matriz[mouse_x/PIXELS][mouse_y/PIXELS]=itemSelecionado;
               blit(fundo, pisoMenu, (mouse_x/PIXELS)*PIXELS, (mouse_y/PIXELS)*PIXELS, 0, 0, PIXELS, PIXELS);
               draw_sprite(buffer, pisoMenu, (mouse_x/PIXELS)*PIXELS, (mouse_y/PIXELS)*PIXELS);
               draw_sprite(buffer, vazio, (mouse_x/PIXELS)*PIXELS, (mouse_y/PIXELS)*PIXELS);
           }
           else{
               matriz[mouse_x/PIXELS][mouse_y/PIXELS]=itemSelecionado;
               imprimir(mouse_x/PIXELS, mouse_y/PIXELS);
           }
           draw_sprite(screen, buffer, 0,0);
       } 
       verificaNovaFase(&verificacao); 
    }  
}

int minhasFases(void){
    int posicaoX=1, posicaoY=7, XAnterior=1, YAnterior=7;
    int mudouOpcao=-1, opcao=1;

    FILE *fases, *replay;
void menuMF(void){
    draw_sprite(buffer, menu, 0, 0);
    alfont_set_font_size(doom, 50);
    alfont_textprintf_aa_ex(buffer, doom, 75, 135, makecol(90,230,90), -1, "MINHAS FASES");
    alfont_set_font_size(doom, 30);
    alfont_textprintf_aa_ex(buffer, doom, 75, 205, makecol(79,79,79), -1, "JOGAR");
    alfont_textprintf_aa_ex(buffer, doom, 75, 265, makecol(79,79,79), -1, "CRIAR FASE");
    alfont_textprintf_aa_ex(buffer, doom, 75, 325, makecol(79,79,79), -1, "APAGAR REGISTROS");
    alfont_textprintf_aa_ex(buffer, doom, 75, 385, makecol(79,79,79), -1, "VOLTAR");
    draw_sprite(screen, buffer, 0, 0);
    show_mouse(screen);
}
    menuMF();

    for( ; ; sleep(20)) {    
        if (BOTAO_JOGAR_MF) {
            if (opcao != JOGAR_MF){
                opcao = JOGAR_MF;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=7;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_CRIAR_FASE) { 
            if (opcao != CRIAR_FASE) {
                opcao = CRIAR_FASE;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=9;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_APAGAR_REGISTROS) { 
            if (opcao != APAGAR_REGISTROS) {
                opcao = APAGAR_REGISTROS;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=11;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_VOLTAR_MF) { 
            if (opcao != VOLTAR_MF){
                opcao = VOLTAR_MF;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=13;
                mudouOpcao=1;
            }
        }
        
        clear_keybuf();
        if(key[KEY_UP]){
            if (opcao>JOGAR_MF){
                opcao-=1;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY-=2;
                mudouOpcao=1;
                sleep(150);
            }
        }
        else if(key[KEY_DOWN]){
            if (opcao<VOLTAR_MF){
                opcao+=1;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY+=2;
                mudouOpcao=1;
                sleep(150);
            }
        }
        
        if (mudouOpcao){
            if (mudouOpcao!=-1)
                play_sample(mouse,255,90,1000,0);
            
            blit(menu, pisoMenu, XAnterior*PIXELS, YAnterior*PIXELS, 0, 0, PIXELS, PIXELS);
            draw_sprite(screen, pisoMenu, XAnterior*PIXELS, YAnterior*PIXELS);
            draw_sprite(screen, jogadorBaixo, posicaoX*PIXELS, posicaoY*PIXELS);
            mudouOpcao=0;
        }
        
        if ( ( (mouse_b & 1)&& (BOTAO_JOGAR_MF || BOTAO_CRIAR_FASE || BOTAO_APAGAR_REGISTROS 
        || BOTAO_VOLTAR_MF)) || key[KEY_ENTER]){
            play_sample(mouse,255,90,1000,0);

            while (mouse_b & 1){
            }
            while(key[KEY_ENTER]){
            }           
            switch(opcao){
                case JOGAR_MF:
                    origemFase = MINHAS_FASES;
                    executaJogo();
                    menuMF();
                    mudouOpcao=1;
                    break;
                case CRIAR_FASE:
                     origemFase = MINHAS_FASES;
                     criarFase();
                     menuMF();
                     mudouOpcao=1;
                     break;
                case APAGAR_REGISTROS:
                     fases = fopen ("data\\minhas fases.dat", "w");
                     replay = fopen ("data\\minhas fases.dat", "w");
                     fprintf(fases, " ");
                     fprintf(replay, " ");
                     fclose(fases);
                     fclose(replay);
                     menuMF();
                     mudouOpcao=1;
                     break;
                case VOLTAR_MF:
                     passouFase=0;
                     return 0;
            }
		}
    }
    show_mouse(NULL);
}

void instrucoes(void){
     
    draw_sprite(buffer, menu, 0, 0);
    alfont_set_font_size(doom, 50);
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 150, makecol(90,230,90), -1, "INSTRUCOES");
    alfont_textprintf_centre_aa_ex(buffer, doom, 370, 180, makecol(90,230,90), -1, "'");
    alfont_textprintf_centre_aa_ex(buffer, doom, 415, 140, makecol(90,230,90), -1, "~");
    
    alfont_set_font_size(doom, 30);
    alfont_textprintf_aa_ex(buffer, doom, 75, 220, makecol(79,79,79), -1, "Movimente o assistente com os ");
    alfont_textprintf_aa_ex(buffer, doom, 75, 260, makecol(79,79,79), -1, "direcionais, para colocar todas as ");
    alfont_textprintf_aa_ex(buffer, doom, 75, 300, makecol(79,79,79), -1, "caixas no lugar.");   
    alfont_textprintf_aa_ex(buffer, doom, 75, 340, makecol(79,79,79), -1, "O assistente so e capaz de "); 
    alfont_textprintf_aa_ex(buffer, doom, 315, 337, makecol(79,79,79), -1, "'  '"); 
    alfont_textprintf_aa_ex(buffer, doom, 75, 380, makecol(79,79,79), -1, "empurrar as caixas para completar ");
    alfont_textprintf_aa_ex(buffer, doom, 75, 420, makecol(79,79,79), -1, "o servico. TECLE ESC");
    alfont_textprintf_aa_ex(buffer, doom, 196, 435, makecol(79,79,79), -1, "'"); 
    draw_sprite(screen, buffer, 0, 0);
    show_mouse(screen);  
    clear_keybuf();
    while(!keypressed()){
    }
    if (key[KEY_ENTER])
        criarFase();

    show_mouse(NULL);
}

int menuOpcoes(void){
    int posicaoX=1, posicaoY=7, XAnterior=1, YAnterior=7;
    int mudouOpcao=-1, opcao=1;
void textoOpcoes(){    
    draw_sprite(buffer, menu, 0, 0);
    alfont_set_font_size(doom, 50);
    alfont_textprintf_centre_aa_ex(buffer, doom, 300, 160, makecol(90,230,90), -1, "'");
    alfont_textprintf_centre_aa_ex(buffer, doom, 345, 125, makecol(90,230,90), -1, "~");
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 135, makecol(90,230,90), -1, "OPCOES");
    alfont_set_font_size(doom, 35);
    switch(skinSelecionada){
        case OFICIAL:
            alfont_textprintf_aa_ex(buffer, doom, 75, 205, makecol(79,79,79), -1, "SKIN - OFICIAL");
            break;
    }
    alfont_textprintf_aa_ex(buffer, doom, 75, 265, makecol(79,79,79), -1, som ? "SOM - LIGADO" : "SOM - DESLIGADO");
    alfont_textprintf_aa_ex(buffer, doom, 75, 325, makecol(79,79,79), -1, telaCheia ? "TELA CHEIA - LIGADO" : "TELA CHEIA - DESLIGADO");
    alfont_textprintf_aa_ex(buffer, doom, 75, 385, makecol(79,79,79), -1, opcaoReplay ? "REPLAY - LIGADO" : "REPLAY - DESLIGADO");
    alfont_textprintf_aa_ex(buffer, doom, 75, 445, makecol(79,79,79), -1, "VOLTAR");
    draw_sprite(screen, buffer, 0, 0);    
}
    textoOpcoes();
    show_mouse(screen);

    for( ; ; sleep(20)) {    
        if (BOTAO_SKIN) {
            if (opcao != SKIN){
                opcao = SKIN;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=7;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_SOM) { 
            if (opcao != 2) {
                opcao = 2;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=9;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_TELA_CHEIA) { 
            if (opcao != 3) {
                opcao = 3;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=11;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_REPLAY) { 
            if (opcao != 4){
                opcao = 4;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=13;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_VOLTAR){
            if (opcao != 5) {
                opcao = 5;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=15;
                mudouOpcao=1;
            }
        } 
        
        clear_keybuf();
        if(key[KEY_UP]){
            if (opcao>1){
                opcao-=1;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY-=2;
                mudouOpcao=1;
                sleep(150);
            }
        }
        else if(key[KEY_DOWN]){
            if (opcao<5){
                opcao+=1;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY+=2;
                mudouOpcao=1;
                sleep(150);
            }
        }
        
        if (mudouOpcao){
            if (mudouOpcao!=-1)
                play_sample(mouse,255,90,1000,0);
            
            blit(menu, pisoMenu, XAnterior*PIXELS, YAnterior*PIXELS, 0, 0, PIXELS, PIXELS);
            draw_sprite(screen, pisoMenu, XAnterior*PIXELS, YAnterior*PIXELS);
            draw_sprite(screen, jogadorBaixo, posicaoX*PIXELS, posicaoY*PIXELS);
            mudouOpcao=0;
        }
        
        if ( ( (mouse_b & 1)&& (BOTAO_SKIN || BOTAO_SOM || BOTAO_TELA_CHEIA 
        || BOTAO_REPLAY || BOTAO_VOLTAR)) || key[KEY_ENTER]){
            play_sample(mouse,255,90,1000,0);

            while (mouse_b & 1){
            }
            while(key[KEY_ENTER]){
            }

            switch (opcao){
                case SKIN:/*desativado, não incrementa*/
                    if(skinSelecionada<3)
                        skinSelecionada;
                    else
                        skinSelecionada=0;
                    carregaImagens();
                    carregaSons();
                    mudouOpcao=1;
                    som= !som ? 1:0;
                case SOM:
                    if (som){
                        som=0;
                        stop_midi();
                    }
                    else{
                        som=1;
                        play_midi(temaMenu,1);
                    }
                    textoOpcoes();
                    mudouOpcao=1;
                    break;
                case TELA_CHEIA:
                     if(telaCheia){
                         set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0);
                         telaCheia=0;
                     }
                     else{
                         set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,640,480,0,0);
                         telaCheia=1;
                     }
                     textoOpcoes();
                     show_mouse(screen);
                     mudouOpcao=1;
                     break;
                case REPLAY:
                    if(opcaoReplay)
                        opcaoReplay=0;
                    else opcaoReplay=1;
                    textoOpcoes();
                    mudouOpcao=1;
                    break;
                       
                case VOLTAR:
                    show_mouse(NULL);
                    return 1; 
            }
		}
    }
}

void creditos(void){
    draw_sprite(buffer, menu, 0, 0);
    alfont_set_font_size(doom, 50);
    alfont_textprintf_centre_aa_ex(buffer, doom, 270, 140, makecol(79,229,79), -1, "'");
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 150, makecol(79,229,79), -1, "CREDITOS");
    alfont_set_font_size(doom, 30);
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 220, makecol(79,79,79), -1, "PROGRAMADORES:");
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 260, makecol(79,79,79), -1, "ADRIANO QUEIROZ");
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 300, makecol(79,79,79), -1, "TITO GARDEL");
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 340, makecol(79,79,79), -1, "");
    alfont_set_font_size(doom, 25);
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 400, makecol(79,79,79), -1, "TECLE ESC");
    alfont_textprintf_centre_aa_ex(buffer, doom, 320, 450, makecol(255,10,10), -1, "SOKOBOX - 2009: Obrigado por Jogar!");
    draw_sprite(screen, buffer, 0, 0);    
    
    show_mouse(screen);
    
    clear_keybuf();
    while(!(key[KEY_ESC]) && !((mouse_b & 1) && BOTAO_VOLTAR)){
    }
    show_mouse(NULL);
}


int menuPrincipal(void) {
    int posicaoX=1, posicaoY=5, XAnterior=1, YAnterior=5;
    int mudouOpcao=-1, opcao=JOGAR;
    
    if(som)
        play_midi(temaMenu,1);

    draw_sprite(buffer, menu, 0, 0);
    draw_sprite(buffer, mascote,400, 160);

    alfont_set_font_size(doom, 35);
    alfont_textprintf_aa_ex(buffer, doom, 75, 145, makecol(79,79,79), -1, "JOGAR");
    alfont_textprintf_aa_ex(buffer, doom, 75, 205, makecol(79,79,79), -1, "MINHAS FASES");
    alfont_textprintf_aa_ex(buffer, doom, 283, 255, makecol(79,79,79), -1, "~");
    alfont_textprintf_aa_ex(buffer, doom, 75, 265, makecol(79,79,79), -1, "INSTRUCOES");
    alfont_textprintf_aa_ex(buffer, doom, 255, 285, makecol(79,79,79), -1, "'");
    alfont_textprintf_aa_ex(buffer, doom, 183, 310, makecol(79,79,79), -1, "~");
    alfont_textprintf_aa_ex(buffer, doom, 75, 320, makecol(79,79,79), -1, "OPCOES");
    alfont_textprintf_aa_ex(buffer, doom, 155, 340, makecol(79,79,79), -1, "'");
    alfont_textprintf_aa_ex(buffer, doom, 150, 375, makecol(79,79,79), -1, "'");
    alfont_textprintf_aa_ex(buffer, doom, 75, 385, makecol(79,79,79), -1, "CREDITOS");
    alfont_textprintf_aa_ex(buffer, doom, 75, 445, makecol(79,79,79), -1, "SAIR");
    draw_sprite(screen, buffer, 0, 0);
    
    show_mouse(screen);

    for( ; ; sleep(20)) {    
        if (BOTAO_JOGAR) {
            if (opcao != JOGAR){
                opcao = JOGAR;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=5;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_MINHAS_FASES) { 
            if (opcao != MINHAS_FASES) {
                opcao = MINHAS_FASES;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=7;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_INSTRUCOES) { 
            if (opcao != INSTRUCOES) {
                opcao = INSTRUCOES;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=9;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_OPCOES) { 
            if (opcao != OPCOES){
                opcao = OPCOES;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=11;
                mudouOpcao=1;
            }
        }
        else if (BOTAO_CREDITOS) { 
            if (opcao != CREDITOS) {
                opcao = CREDITOS;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=13;
                mudouOpcao=1;
            }
        } 
        else if (BOTAO_SAIR) { 
            if (opcao != SAIR){  
                opcao = SAIR;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY=15;
                mudouOpcao=1;
            }
        }
        
        if(key[KEY_UP]){
            if (opcao>JOGAR){
                opcao-=1;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY-=2;
                mudouOpcao=1;
                sleep(150);
            }
        }
        else if(key[KEY_DOWN]){
            if (opcao<SAIR){
                opcao+=1;
                XAnterior=posicaoX; YAnterior = posicaoY;
                posicaoX=1; posicaoY+=2;
                mudouOpcao=1;
                sleep(150);
            }
        }
        
        if (mudouOpcao){
            if (mudouOpcao!=-1)
                play_sample(mouse,255,90,1000,0);
            
            blit(menu, pisoMenu, XAnterior*PIXELS, YAnterior*PIXELS, 0, 0, PIXELS, PIXELS);
            draw_sprite(screen, pisoMenu, XAnterior*PIXELS, YAnterior*PIXELS);
            draw_sprite(screen, jogadorBaixo, posicaoX*PIXELS, posicaoY*PIXELS);
            mudouOpcao=0;
        }
        
        if ( ( (mouse_b & 1)&& (BOTAO_JOGAR || BOTAO_MINHAS_FASES || BOTAO_INSTRUCOES 
        || BOTAO_OPCOES || BOTAO_CREDITOS || BOTAO_SAIR)) || key[KEY_ENTER]){
            play_sample(mouse,255,90,1000,0);
            while (mouse_b & 1){
            }
            while(key[KEY_ENTER]){
            }
			show_mouse(NULL);
            return opcao;
		}
    }
}

void textoMenuJogo(void){
    FILE *replay;
    int recorde = 0, inutil;
    char pula;
    
    int i, j, sujeira;
    
    if(origemFase==MINHAS_FASES)
        replay = fopen("data\\replay minhas fases.dat","r");
    else
        replay = fopen("data\\replay.dat","r");
    for(i=0; i<fase; i++) {
        if(fscanf(replay,"%d%d", &recorde, &sujeira)==EOF){
            recorde=0;
            sujeira=0;
            break;
        }
        fseek(replay,((recorde+sujeira)*2)+1,SEEK_CUR);
    }
    fclose(replay);
    
    alfont_set_font_size(doom, 21);
    alfont_textprintf_centre_aa_ex(fundo, doom, 560, 100, makecol(79,79,79), -1, "FASE");
    alfont_textprintf_centre_aa_ex(fundo, doom, 560, 140, makecol(255,255,255), -1, "<      >");

    alfont_textprintf_centre_aa_ex(fundo, doom, 560, 180, makecol(79,79,79), -1, "PASSOS");
    alfont_textprintf_centre_aa_ex(fundo, doom, 560, 210, makecol(255,255,255), -1, "<      >");

    alfont_textprintf_centre_aa_ex(fundo, doom, 560, 260, makecol(79,79,79), -1, "REINICIAR");
    alfont_textprintf_centre_aa_ex(fundo, doom, 560, 320, makecol(79,79,79), -1, "RECORDE");
   if(!recorde)
        alfont_textprintf_centre_aa_ex(screen, doom, 560, 350, makecol(255,255,255), -1, "N/A");
    else    alfont_textprintf_centre_aa_ex(screen, doom, 560, 350, makecol(255,255,255), -1, "%d", recorde);
    alfont_textprintf_centre_aa_ex(fundo, doom, 560, 420, makecol(79,79,79), -1, "SAIR");
}

void variaveisMenuJogo(){
}
    

void atualizaPosicao(int *movimentos, int numeroPassos, int numeroFase){
    int i; 
    
    carregaFase(numeroFase);
    imprimeFase(0);
    
    for (i=0; i<numeroPassos && !key[KEY_ESC]; i++){
        executaMovimento(movimentos[i], movimentos, &numeroPassos, 0);
    }    
    imprimeFase(1);    
    textoMenuJogo();
    alfont_textprintf_centre_aa_ex(screen, doom, 560, 140, makecol(255,255,255), -1, "%d", fase);
    alfont_textprintf_centre_aa_ex(screen, doom, 560, 210, makecol(255,255,255), -1, "%d", numeroPassos);
}

void liberarFase(int *faseLiberada) {
    FILE *replay;
    int qtMovimentos, qtSujeira;
    int i;

    if (origemFase == MINHAS_FASES)
        replay = fopen("data\\replay minhas fases.dat","r");
    else
        replay = fopen("data\\replay.dat","r");
    for(i=1;i!=fase;i++) {
        if(fscanf(replay,"%d %d", &qtMovimentos, &qtSujeira)==EOF) break;
        fseek(replay, 2*(qtMovimentos+qtSujeira)+1, SEEK_CUR);
    }
    if(fscanf(replay,"%d %d", &qtMovimentos, &qtSujeira) == EOF) {
        *faseLiberada = 0;
    }   
    else {
        *faseLiberada = 1;
    }
    fclose(replay);
}

void replay(int *movimentos, int numeroPassos, int numeroFase){
    int i; 
    
    carregaFase(numeroFase);
    imprimeFase(1);    

    for (i=0; i<numeroPassos && !key[KEY_ESC]; i++){
        executaMovimento(movimentos[i], movimentos, &numeroPassos, 0);
        imprimirMovimento(movimentos[i], i);
    }    
}

int botoesMenuJogo(int *movimentos, int *numeroMovimentos, int maiorPasso, int *finalJogo){
    int faseLiberada;
    int i, j, k=0, recorde, sujeira;
    int leitura;
    FILE *arquivoReplay;

    liberarFase(&faseLiberada);
    textoMenuJogo();
    if (BOTAO_PROXIMA_FASE && (fase<quantidadeFases)){
        if(faseLiberada) {
            fase++;
            carregaFase(fase);
            imprimeFase(1);
            *numeroMovimentos=0;
            alfont_textprintf_centre_aa_ex(screen, doom, 560, 140, makecol(255,255,255), -1, "%d", fase);
            alfont_textprintf_centre_aa_ex(screen, doom, 560, 210, makecol(255,255,255), -1, "%d", *numeroMovimentos);
            textoMenuJogo();
        }
    }
    else if(BOTAO_VOLTAR_FASE && (fase>1)){     
         fase--;
         carregaFase(fase);
         imprimeFase(1);
         *numeroMovimentos=0;
         alfont_textprintf_centre_aa_ex(screen, doom, 560, 140, makecol(255,255,255), -1, "%d", fase);
         alfont_textprintf_centre_aa_ex(screen, doom, 560, 210, makecol(255,255,255), -1, "%d", *numeroMovimentos);
         textoMenuJogo();
    }
    if (BOTAO_PROXIMO_MOVIMENTO && *numeroMovimentos<maiorPasso){
        *numeroMovimentos+=1;
         atualizaPosicao(movimentos, *numeroMovimentos, fase);
    }
    else if(BOTAO_VOLTAR_MOVIMENTO && (*numeroMovimentos>0)){     
         *numeroMovimentos-=1;
         atualizaPosicao(movimentos, *numeroMovimentos, fase);
    }

    else if ( BOTAO_REINICIAR){ 
        carregaFase(fase);
        imprimeFase(1);
        *numeroMovimentos=0;
        alfont_textprintf_centre_aa_ex(screen, doom, 560, 140, makecol(255,255,255), -1, "%d", fase);
        alfont_textprintf_centre_aa_ex(screen, doom, 560, 210, makecol(255,255,255), -1, "%d", *numeroMovimentos);
        textoMenuJogo();
    }
    else if(BOTAO_RECORDE){
     
        if(origemFase==MINHAS_FASES)
            arquivoReplay = fopen("data\\replay minhas fases.dat","r");
        else
            arquivoReplay = fopen("data\\replay.dat","r");

        for(i=0; i<fase; i++) { 
            if(fscanf(arquivoReplay,"%d %d", numeroMovimentos, &sujeira)==EOF){
                *numeroMovimentos=0;
                return 0;
            }
            movimentos = malloc((*numeroMovimentos)*sizeof(int*));
            for (k=0; k<(*numeroMovimentos); k++){
                fscanf(arquivoReplay, "%d", &leitura);
                movimentos[k]=leitura;
            }
        } 
        fclose(arquivoReplay);
        executandoReplay=1;
        replay(movimentos, *numeroMovimentos, fase);
        sleep(1000);
        *numeroMovimentos=0;
        if (fase<quantidadeFases){
            passouFase=1;
        }
    }
    else if(BOTAO_SAIR_JOGO){
         passouFase=0;
        fase=1;
        *finalJogo=1;
        *numeroMovimentos=0;
    } 
    show_mouse(screen);
}

int gravaReplay(int *movimentos, int numeroMovimentos, int fase) {
    int qtMovimentos=0, qtSujeira=0, novaqtSujeira=0;
    int i;
    char pulaLinha;
    FILE *replay;
    
    if (origemFase == MINHAS_FASES)
        replay = fopen("data\\replay minhas fases.dat","r+");
    else
        replay = fopen("data\\replay.dat","r+");

    for(i=1;i!=fase;i++) {
        if(fscanf(replay,"%d %d", &qtMovimentos, &qtSujeira)==EOF) break;
        fseek(replay, 2*(qtMovimentos+qtSujeira)+1, SEEK_CUR);
    }
    if(fscanf(replay,"%d %d", &qtMovimentos, &qtSujeira)!=EOF) {
        if(numeroMovimentos < qtMovimentos) {
            novaqtSujeira = qtMovimentos - numeroMovimentos;
            rewind(replay);
            for(i=1;i!=fase;i++) {
                if(fscanf(replay,"%d %d", &qtMovimentos, &qtSujeira)==EOF) break;
                fseek(replay,qtMovimentos+qtSujeira+1,SEEK_CUR);
            }  
            fprintf(replay,"%d %d ", numeroMovimentos, novaqtSujeira);
            for(i=0;i<numeroMovimentos;i++)
                fprintf(replay,"%d ",movimentos[i]);
            fprintf(replay,"\n");
        } 
    }
    else {
        fprintf(replay,"%d %d ", numeroMovimentos, novaqtSujeira);
        for(i=0;i<numeroMovimentos;i++)
            fprintf(replay,"%d ",movimentos[i]);
        fprintf(replay,"\n");
    }  
    fclose(replay); 
}

void executaJogo(void){
    int quantidadeCaixas, numeroMovimentos=0, maiorPasso=0;
    int opcaoMenu;
    int direcaoMovimento=0;
	int *movimentos = malloc(100*sizeof(int));
    int  finalJogo=0;
    
    carregaImagens();
    carregaFase(fase);
    textoMenuJogo();
    imprimeFase(1);
    alfont_textprintf_centre_aa_ex(screen, doom, 560, 140, makecol(255,255,255), -1, "%d", fase);
    alfont_textprintf_centre_aa_ex(screen, doom, 560, 210, makecol(255,255,255), -1, "%d", numeroMovimentos);
    textoMenuJogo();

    show_mouse(screen);         
               
    if (som && !(passouFase))
        play_midi(temaJogo,1);
           
    while (!finalJogo) {
        textoMenuJogo();
        if(keypressed()){
            if(key[KEY_ESC]){
                finalJogo=1;
                passouFase=0;
            }
            
            direcaoMovimento = entradaMovimento();
                     
            if (direcaoMovimento) {
                switch (direcaoMovimento) {
                    case CIMA:
                    case BAIXO:
                    case ESQUERDA:
                    case DIREITA:    
                        moveu = 0;
                        executaMovimento(direcaoMovimento, movimentos, &numeroMovimentos, 1);
                        if (moveu){
                            maiorPasso = numeroMovimentos;
                            imprimirMovimento(direcaoMovimento, numeroMovimentos);
                            textoMenuJogo();
                        }
                        break;
                }
                direcaoMovimento=0;
            }
        }
        if ((mouse_b & 1) && mouse_x > 479){
            while(mouse_b & 1){
            }
            botoesMenuJogo(movimentos, &numeroMovimentos, maiorPasso, &finalJogo);
        }
                   
        quantidadeCaixas = verificaFim();
        if(!quantidadeCaixas) {
            alfont_set_font_size(doom, 42);
            alfont_textprintf_centre_aa_ex(screen, doom, 240, 210, makecol(100,100,100), -1, "FASE COMPLETA");
            sleep(1000);
            
            if(!executandoReplay)
                gravaReplay(movimentos, numeroMovimentos, fase);
            if(opcaoReplay)
                replay(movimentos, numeroMovimentos, fase);
            executandoReplay=0;
            sleep(1000);
            numeroMovimentos=0;
            if (fase<quantidadeFases){
                passouFase=1;
  			    fase++;
            }
            break;
        }
					
     	if (!(numeroMovimentos%100))
		    movimentos = (int*) realloc (movimentos, (numeroMovimentos+100) * sizeof(int));    
				
	}
   	show_mouse(NULL);
    free(movimentos);
}

int main (void) {
    int opcaoMenuPrincipal;
    instalaComponentes();
    carregaImagens();
    carregaSons();
    carregaFontes();

    for( ; ; ){
        if(!passouFase)
            opcaoMenuPrincipal = menuPrincipal();

        switch (opcaoMenuPrincipal) {
            case JOGAR:
                origemFase=JOGAR;
                executaJogo();
                break;
            case MINHAS_FASES:
                minhasFases();
                break;
            case INSTRUCOES:
                 instrucoes();
                 break;
            case OPCOES:
                 menuOpcoes();
                 break;
            case CREDITOS:
                 creditos();
                 break;
            case SAIR:
                creditos();
                liberaMemoria(); 
                allegro_exit();
                exit(1);
        }
    }
    return 0;
}
END_OF_MAIN();

