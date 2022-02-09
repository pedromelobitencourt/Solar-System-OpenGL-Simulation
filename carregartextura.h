/*
Membros do grupo:
    Pedro Vitor Melo Bitencourt (20213001540)
    Rafael Pereira Duarte (20213005146)
    Pedro Veloso Inácio de Oliveira (20213004837)
    Sérgio Henrique Mendes de Assis (20213005182)

Orientador:
    Glender Brás

Texturas usadas:
    https://www.solarsystemscope.com/textures/
*/

#ifndef CARREGAR_TEXTURA_H_INCLUDED
#define CARREGAR_TEXTURA_H_INCLUDED

//A textura que vamos carregar do arquivo
class Textura {
public:
	Textura(char* osPixelsDaTextura, int aLarguraDaTextura, int aAlturaDaTextura);
	~Textura();
	char* pixels;
	int largura;
	int altura;
};

//Ler uma textura (apenas formato BMP)
Textura* carregarImagemBMP(const char* nomeArquivo);

#endif
