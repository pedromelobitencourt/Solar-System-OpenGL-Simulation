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

