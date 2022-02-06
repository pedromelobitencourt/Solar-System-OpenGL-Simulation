#include <GL/glew.h>
#include <GL/freeglut.h>
#include <gl/glut.h>
#include <stdio.h> //Digitar as intruções no prompt de comando
#include <string.h>
#include <math.h> //Talvez tirar
#include "carregartextura.h" //Biblioteca para carregar texturas 3D

#define LARGURA 750 //Ver se está usando
#define ALTURA 500 //Ver se está usando
#define INCREMENTO_PLANO 0.7

//Pedro Vitor Melo Bitencourt e Rafael Pereira Duarte
//Site texturas: https://www.solarsystemscope.com/textures/

///Instruções

/*
'a' -> Ativa ou desativa o plano Orbital
's' -> Liga ou desliga a luz do Sol (Se a iluminação estiver desligada)
'o' -> Ver ou esconder as órbitas dos planetas
'I' -> Mudar o tipo de iluminação (Caso a iluminação esteja ligada)
'i' -> Ligar ou desligar a iluminação
'1' -> Ver ou desver Mercúrio
'2' -> Ver ou desver Venus
'z' -> Mostrar ou esconder os nomes dos planetas
'p' -> Pausar ou despausar a animação
'F1' -> Mexer a câmera Y
'F2' -> Mexer a câmera Y
'PAGE UP' -> Mexer a câmera X
'PAGE DOWN' -> Mexer a câmera X
'END' -> Mexer a câmera Z
'HOME' -> Mexer a câmera Z
'UP' -> Camera1
'DOWN' -> Camera4
'LEFT' -> Camera2
'RIGHT' -> Camera3 //Tem que colocar
'MOUSE ESQUERDO' -> +Zoom
'MOUSE DIREITO' -> -Zoom
*/

//Função para carregar uma textura (tem que estar no formato BMP)
GLuint carregaTextura(Textura* imagemBMP) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagemBMP->altura, imagemBMP->largura, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemBMP->pixels);
	return textureId;
}

///Texturas planetas e luas
GLuint texturaDasEstrelas;
GLuint texturaDoSol;
GLuint texturaSuperficieMercurio;
GLuint texturaPhobos;
GLuint texturaSuperficieVenus;
GLuint texturaAtmosferaVenus;
GLuint texturaSuperficieTerra;
GLuint texturaAtmosferaTerra;
GLuint texturaLua;
GLuint texturaSuperficieMarte;
GLuint texturaSuperficieJupiter;
GLuint texturaSuperficieSaturno;
GLuint texturaSuperficieUrano;
GLuint texturaSuperficieNetuno;

struct EsferasEspaciais{
    double raio;
    double velocidadeDaOrbita; //A velocidade que a esfera "gira" em sua órbita
    double inclinacaoX;
    double anguloRotacaoNoProprioEixo;
    double distanciaAteOSol;
    double orbita;
    char *nome;
    double velocidadeRotacao;
};

EsferasEspaciais sol;
EsferasEspaciais mercurio;
EsferasEspaciais venus;
EsferasEspaciais terra;
EsferasEspaciais lua;
EsferasEspaciais marte;
EsferasEspaciais phobos;
EsferasEspaciais jupiter;
EsferasEspaciais saturno;
EsferasEspaciais titan;
EsferasEspaciais uranos;
EsferasEspaciais netuno;

struct Asteroide{
    double distancia;
    double rotacao;
    double velocidadeRotacao;
    int tipo; //Se 1 == icosaedro, Se 2 == dodecaedro, Se 3 octaedro
};

///Criando os asteroides
Asteroide asteroide1;
Asteroide asteroide2;
Asteroide asteroide3;
Asteroide asteroide4;
Asteroide asteroide5;
Asteroide asteroide6;
Asteroide asteroide7;
Asteroide asteroide8;
Asteroide asteroide9;
Asteroide asteroide10;
Asteroide asteroide11;
Asteroide asteroide12;
Asteroide asteroide13;
Asteroide asteroide14;
Asteroide asteroide15;
Asteroide asteroide16;
Asteroide asteroide17;
Asteroide asteroide18;
Asteroide asteroide19;
Asteroide asteroide20;
Asteroide asteroide21;
Asteroide asteroide22;
Asteroide asteroide23;
Asteroide asteroide24;
Asteroide asteroide25;
Asteroide asteroide26;
Asteroide asteroide27;
Asteroide asteroide28;
Asteroide asteroide29;
Asteroide asteroide30;
Asteroide asteroide31;
Asteroide asteroide32;
Asteroide asteroide33;
Asteroide asteroide34;
Asteroide asteroide35;
Asteroide asteroide36;
Asteroide asteroide37;
Asteroide asteroide38;
Asteroide asteroide39;
Asteroide asteroide40;
Asteroide asteroide41;
Asteroide asteroide42;
Asteroide asteroide43;
Asteroide asteroide44;
Asteroide asteroide45;
Asteroide asteroide46;
Asteroide asteroide47;
Asteroide asteroide48;
Asteroide asteroide49;
Asteroide asteroide50;
Asteroide asteroide51;
Asteroide asteroide52;
Asteroide asteroide53;
Asteroide asteroide54;
Asteroide asteroide55;
Asteroide asteroide56;
Asteroide asteroide57;
Asteroide asteroide58;
Asteroide asteroide59;
Asteroide asteroide60;
Asteroide asteroide61;
Asteroide asteroide62;
Asteroide asteroide63;
Asteroide asteroide64;
Asteroide asteroide65;
Asteroide asteroide66;
Asteroide asteroide67;
Asteroide asteroide68;
Asteroide asteroide69;
Asteroide asteroide70;
Asteroide asteroide71;
Asteroide asteroide72;
Asteroide asteroide73;
Asteroide asteroide74;
Asteroide asteroide75;
Asteroide asteroide76;
Asteroide asteroide77;
Asteroide asteroide78;
Asteroide asteroide79;
Asteroide asteroide80;
Asteroide asteroide81;
Asteroide asteroide82;
Asteroide asteroide83;
Asteroide asteroide84;
Asteroide asteroide85;
Asteroide asteroide86;
Asteroide asteroide87;
Asteroide asteroide88;
Asteroide asteroide89;
Asteroide asteroide90;
Asteroide asteroide91;
Asteroide asteroide92;
Asteroide asteroide93;
Asteroide asteroide94;
Asteroide asteroide95;

GLfloat angle, fAspect;

///Posições câmeras

GLdouble posicaoOlharZ = 0;
GLdouble posicaoOlharY = 0;
GLdouble posicaoOlharX = 0;

GLdouble posicaoCamera1Z = 0;
GLdouble posicaoCamera1Y = 70;
GLdouble posicaoCamera1X = 1;

GLdouble posicaoCamera2Z = 0;
GLdouble posicaoCamera2Y = 7;
GLdouble posicaoCamera2X = -70;

GLdouble posicaoCamera3Z = 0;
GLdouble posicaoCamera3Y = 80;
GLdouble posicaoCamera3X = 75;

GLdouble posicaoCamera4Z = 0;
GLdouble posicaoCamera4Y = 80;
GLdouble posicaoCamera4X = 75;

GLdouble posicaoCameraZ = posicaoCamera4Z;
GLdouble posicaoCameraY = posicaoCamera4Y;
GLdouble posicaoCameraX = posicaoCamera4X;

GLdouble incrementoX = 1;
GLdouble incrementoY = 1;
GLdouble incrementoZ = 1;

GLdouble posicaoCameraX_antigo;
GLdouble posicaoCameraY_antigo;
GLdouble posicaoCameraZ_antigo;

GLdouble distanciaDoPlaneta = 5; //Ver se está usando

///Instruções

bool animacaoOn = true;
bool camera1Ligada = false; //Se deslocar ou não para a câmera 1
bool camera2Ligada = false; //Se deslocar ou não para a câmera 2
bool camera3Ligada = false; //Se deslocar ou não para a câmera 3
bool camera4Ligada = true; //Se deslocar ou não para a câmera 4
bool estaPausado = false; //Não sei se está usando
bool mostrarNomesPlanetas = false; //Mostrar ou esconder nomes dos planetas e luas
bool verOrbitas = true; //Mostrar ou esconder orbitas
bool comLuzDoSolOn = false; //Pode ser ativado quando a iluminação está desligada
bool planoOrbitalAtivado = false; //Mostrar ou esconder plano orbital
bool iluminacaoEstaLigada = false; //Ligar ou desligar iluminação
int tipoIluminacao = 0; //Há três tipos de iluminações que pode ver quando a iluminação está desligada

///Visitar os planetas

bool olharMercurio = false;
bool olharVenus = false;
bool olharTerra = false;
bool olharMarte = false;
bool olharJupiter = false;
bool olharSaturno = false;
bool olharUranos = false;
bool olharNetuno = false;



void Inicializa (void){

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	///Carregando texturas

    Textura* estrelaTextura = carregarImagemBMP("Estrelas_SkyBoxes.bmp");
	texturaDasEstrelas = carregaTextura(estrelaTextura);
	delete estrelaTextura;

	Textura* solTextura = carregarImagemBMP("Sol.bmp");
	texturaDoSol = carregaTextura(solTextura);
	delete solTextura;

    Textura* superficieMercurioTextura = carregarImagemBMP("Mercurio.bmp");
    texturaSuperficieMercurio = carregaTextura(superficieMercurioTextura);
    delete superficieMercurioTextura;

    Textura* superficiePhobostextura = carregarImagemBMP("Phobos.bmp");
    texturaPhobos = carregaTextura(superficiePhobostextura);
    delete superficiePhobostextura;

    Textura* superficieVenusTextura = carregarImagemBMP("Venus.bmp");
    texturaSuperficieVenus = carregaTextura(superficieVenusTextura);
    delete superficieVenusTextura;

    Textura* atmosferaVenusTextura = carregarImagemBMP("AtmosferaVenus.bmp");
    texturaAtmosferaVenus = carregaTextura(atmosferaVenusTextura);
    delete atmosferaVenusTextura;

    Textura* superficieTerraTextura = carregarImagemBMP("Terra.bmp");
    texturaSuperficieTerra = carregaTextura(superficieTerraTextura);
    delete superficieTerraTextura;

    Textura* superficieLuatextura = carregarImagemBMP("Lua.bmp");
    texturaLua = carregaTextura(superficieLuatextura);
    delete superficieLuatextura;

    Textura* atmosferaTerraTextura = carregarImagemBMP("Atmosfera.bmp");
    texturaAtmosferaTerra = carregaTextura(atmosferaTerraTextura);
    delete atmosferaTerraTextura;

    Textura* superficieMarteTextura = carregarImagemBMP("Marte.bmp");
    texturaSuperficieMarte = carregaTextura(superficieMarteTextura);
    delete superficieMarteTextura;

    Textura* superficieJupiterTextura = carregarImagemBMP("Jupiter.bmp");
    texturaSuperficieJupiter = carregaTextura(superficieJupiterTextura);
    delete superficieJupiterTextura;

    Textura* superficieSaturnoTextura = carregarImagemBMP("Saturno.bmp");
    texturaSuperficieSaturno = carregaTextura(superficieSaturnoTextura);
    delete superficieSaturnoTextura;

    Textura* superficieUranoTextura = carregarImagemBMP("Urano.bmp");
    texturaSuperficieUrano = carregaTextura(superficieUranoTextura);
    delete superficieUranoTextura;

    Textura* superficieNetunoTextura = carregarImagemBMP("Netuno.bmp");
    texturaSuperficieNetuno = carregaTextura(superficieNetunoTextura);
    delete superficieNetunoTextura;

    ///Inicializando os valores dos objetos criados

    sol.distanciaAteOSol = 0;
    sol.inclinacaoX = 0;
    sol.raio = 5;
    sol.velocidadeDaOrbita = 0;
    sol.anguloRotacaoNoProprioEixo = 0;
    sol.orbita = 0;
    sol.nome = "Sol";
    sol.velocidadeRotacao = 0.0;

    mercurio.distanciaAteOSol = 7;
    mercurio.inclinacaoX = 2.11;
    mercurio.raio = 1;
    mercurio.velocidadeDaOrbita = 4.74;
    mercurio.anguloRotacaoNoProprioEixo = 0;
    mercurio.orbita = 0;
    mercurio.nome = "Mercurio";
    mercurio.velocidadeRotacao = 0.41;


    venus.distanciaAteOSol = 11;
    venus.inclinacaoX = 177;
    venus.raio = 1.5;
    venus.velocidadeDaOrbita = 3.5;
    venus.anguloRotacaoNoProprioEixo = 0;
    venus.orbita = 0;
    venus.nome = "Venus";
    venus.velocidadeRotacao = 0.1;

    terra.distanciaAteOSol = 16;
    terra.inclinacaoX = 23.44;
    terra.raio = 2;
    terra.velocidadeDaOrbita = 2.98;
    terra.anguloRotacaoNoProprioEixo = 0;
    terra.orbita = 0;
    terra.nome = "Terra";
    terra.velocidadeRotacao = 8.743;

    lua.distanciaAteOSol = terra.distanciaAteOSol + terra.raio + 2;
    lua.inclinacaoX = 0;
    lua.raio = terra.raio * 0.2;
    lua.velocidadeDaOrbita = terra.velocidadeDaOrbita;
    lua.anguloRotacaoNoProprioEixo = 0;
    lua.orbita = 0;
    lua.nome = "Lua";
    lua.velocidadeRotacao = terra.velocidadeRotacao;

    marte.distanciaAteOSol = 21;
    marte.inclinacaoX = 25;
    marte.raio = 1.2;
    marte.velocidadeDaOrbita = 2.41;
    marte.anguloRotacaoNoProprioEixo = 0;
    marte.orbita = 0;
    marte.nome = "Marte";
    //marte.velocidadeRotacao = 23.328;
    marte.velocidadeRotacao = 8.2;

    phobos.distanciaAteOSol = marte.distanciaAteOSol + marte.raio + 0.875;
    phobos.inclinacaoX = 0;
    phobos.raio = marte.raio * 0.157;
    phobos.velocidadeDaOrbita = marte.velocidadeDaOrbita;
    phobos.anguloRotacaoNoProprioEixo = 0;
    phobos.orbita = 0;
    phobos.nome = "Phobos";
    phobos.velocidadeRotacao = marte.velocidadeRotacao;

    jupiter.distanciaAteOSol = 28;
    jupiter.inclinacaoX = 3.13;
    jupiter.raio = 3.5;
    jupiter.velocidadeDaOrbita = 1.31;
    jupiter.anguloRotacaoNoProprioEixo = 0;
    jupiter.orbita = 0;
    jupiter.nome = "Jupiter";
    jupiter.velocidadeRotacao = 58.32;

    saturno.distanciaAteOSol = 37;
    saturno.inclinacaoX = 26.7;
    saturno.raio = 3;
    saturno.velocidadeDaOrbita = 0.97;
    saturno.anguloRotacaoNoProprioEixo = 0;
    saturno.orbita = 0;
    saturno.nome = "Saturno";
    saturno.velocidadeRotacao = 5;
    //saturno.velocidadeRotacao = 53.01;

    titan.distanciaAteOSol = saturno.distanciaAteOSol + saturno.raio + 2.050515;
    titan.inclinacaoX = 0;
    titan.raio = saturno.raio * 0.08;
    titan.velocidadeDaOrbita = saturno.velocidadeDaOrbita;
    titan.anguloRotacaoNoProprioEixo = 0;
    titan.orbita = 0;
    titan.nome = "Tita";
    titan.velocidadeRotacao = saturno.velocidadeRotacao;


    uranos.distanciaAteOSol = 45.5;
    uranos.inclinacaoX = 47;
    uranos.raio = 2.5;
    uranos.velocidadeDaOrbita = 0.68;
    uranos.anguloRotacaoNoProprioEixo = 0;
    uranos.orbita = 0;
    uranos.nome = "Urano";
    uranos.velocidadeRotacao = 34.3;

    netuno.distanciaAteOSol = 53.6;
    netuno.inclinacaoX = 28.32;
    netuno.raio = 2.3;
    netuno.velocidadeDaOrbita = 0.54;
    netuno.anguloRotacaoNoProprioEixo = 0;
    netuno.orbita = 0;
    netuno.nome = "Netuno";
    netuno.velocidadeRotacao = 36.45;


    /// Asteroides

    //A distância dos asteroides deve ficar entre dois planetas - Talvez vao ter que aumentar a distância do sol de alguns planetas
    //Bom ter rotações diferentes para não ter muito asteroide sincronizado
    //Tipo1 => Icosaedro
    //Tipo2 => Dodecaedro
    //Tipo3 => Octaedro

    asteroide1.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1;
    asteroide1.rotacao = 70;
    asteroide1.velocidadeRotacao = 0.875;
    asteroide1.tipo = 1;

    asteroide2.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1;
    asteroide2.rotacao = 150;
    asteroide2.velocidadeRotacao = 0.875;
    asteroide2.tipo = 1;

    asteroide3.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1;
    asteroide3.rotacao = 244;
    asteroide3.velocidadeRotacao = 0.875;
    asteroide3.tipo = 2;

    asteroide4.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.5;
    asteroide4.rotacao = 200;
    asteroide4.velocidadeRotacao = 0.875;
    asteroide4.tipo = 2;

    asteroide5.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide5.rotacao = 5;
    asteroide5.velocidadeRotacao = 0.875;
    asteroide5.tipo = 3;

    asteroide6.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide6.rotacao = 72;
    asteroide6.velocidadeRotacao = 0.875;
    asteroide6.tipo = 1;

    asteroide7.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide7.rotacao = 379;
    asteroide7.velocidadeRotacao = 0.875;
    asteroide7.tipo = 3;

    asteroide8.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide8.rotacao = 37;
    asteroide8.velocidadeRotacao = 0.875;
    asteroide8.tipo = 1;

    asteroide9.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide9.rotacao = 49;
    asteroide9.velocidadeRotacao = 0.875;
    asteroide9.tipo = 2;

    asteroide10.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide10.rotacao = 12;
    asteroide10.velocidadeRotacao = 0.875;
    asteroide10.tipo = 2;

    asteroide11.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide11.rotacao = 125;
    asteroide11.velocidadeRotacao = 0.875;
    asteroide11.tipo = 3;

    asteroide12.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide12.rotacao = 76;
    asteroide12.velocidadeRotacao = 0.875;
    asteroide12.tipo = 1;

    asteroide13.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.8;
    asteroide13.rotacao = 231;
    asteroide13.velocidadeRotacao = 0.875;
    asteroide13.tipo = 3;

    asteroide14.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide14.rotacao = 310;
    asteroide14.velocidadeRotacao = 0.875;
    asteroide14.tipo = 3;

    asteroide15.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide15.rotacao = 7;
    asteroide15.velocidadeRotacao = 0.875;
    asteroide15.tipo = 2;

    asteroide16.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide16.rotacao = 276;
    asteroide16.velocidadeRotacao = 0.875;
    asteroide16.tipo = 2;

    asteroide17.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide17.rotacao = 287;
    asteroide17.velocidadeRotacao = 0.875;
    asteroide17.tipo = 2;

    asteroide18.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide18.rotacao = 124;
    asteroide18.velocidadeRotacao = 0.875;
    asteroide18.tipo = 1;

    asteroide19.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide19.rotacao = 175;
    asteroide19.velocidadeRotacao = 0.875;
    asteroide19.tipo = 3;

    asteroide20.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.4;
    asteroide20.rotacao = 180;
    asteroide20.velocidadeRotacao = 0.875;
    asteroide20.tipo = 1;

    asteroide21.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.4;
    asteroide21.rotacao = 70;
    asteroide21.velocidadeRotacao = 0.875;
    asteroide21.tipo = 2;

    asteroide22.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.2;
    asteroide22.rotacao = 75;
    asteroide22.velocidadeRotacao = 0.875;
    asteroide22.tipo = 1;

    asteroide23.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.6;
    asteroide23.rotacao = 80;
    asteroide23.velocidadeRotacao = 0.875;
    asteroide23.tipo = 3;

    asteroide24.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.7;
    asteroide24.rotacao = 85;
    asteroide24.velocidadeRotacao = 0.875;
    asteroide24.tipo = 3;

    asteroide25.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1;
    asteroide25.rotacao = 90;
    asteroide25.velocidadeRotacao = 0.875;
    asteroide25.tipo = 2;

    asteroide26.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.1;
    asteroide26.rotacao = 95;
    asteroide26.velocidadeRotacao = 0.875;
    asteroide26.tipo = 3;

    asteroide27.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.2;
    asteroide27.rotacao = 100;
    asteroide27.velocidadeRotacao = 0.875;
    asteroide27.tipo = 1;

    asteroide28.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.4;
    asteroide28.rotacao = 105;
    asteroide28.velocidadeRotacao = 0.875;
    asteroide28.tipo = 2;

    asteroide29.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.45;
    asteroide29.rotacao = 110;
    asteroide29.velocidadeRotacao = 0.875;
    asteroide29.tipo = 2;

    asteroide30.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.8;
    asteroide30.rotacao = 115;
    asteroide30.velocidadeRotacao = 0.875;
    asteroide30.tipo = 3;

    asteroide31.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.6;
    asteroide31.rotacao = 120;
    asteroide31.velocidadeRotacao = 0.875;
    asteroide31.tipo = 3;

    asteroide32.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1;
    asteroide32.rotacao = 125;
    asteroide32.velocidadeRotacao = 0.875;
    asteroide32.tipo = 2;

    asteroide33.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.1;
    asteroide33.rotacao = 130;
    asteroide33.velocidadeRotacao = 0.875;
    asteroide33.tipo = 1;

    asteroide34.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.85;
    asteroide34.rotacao = 135;
    asteroide34.velocidadeRotacao = 0.875;
    asteroide34.tipo = 2;

    asteroide35.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.7;
    asteroide35.rotacao = 140;
    asteroide35.velocidadeRotacao = 0.875;
    asteroide35.tipo = 3;

    asteroide36.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.9;
    asteroide36.rotacao = 145;
    asteroide36.velocidadeRotacao = 0.875;
    asteroide36.tipo = 2;

    asteroide37.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.12;
    asteroide37.rotacao = 150;
    asteroide37.velocidadeRotacao = 0.875;
    asteroide37.tipo = 2;

    asteroide38.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.5;
    asteroide38.rotacao = 155;
    asteroide38.velocidadeRotacao = 0.875;
    asteroide38.tipo = 1;

    asteroide39.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.8;
    asteroide39.rotacao = 160;
    asteroide39.velocidadeRotacao = 0.875;
    asteroide39.tipo = 1;

    asteroide40.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1;
    asteroide40.rotacao = 165;
    asteroide40.velocidadeRotacao = 0.875;
    asteroide40.tipo = 2;

    asteroide41.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.45;
    asteroide41.rotacao = 170;
    asteroide41.velocidadeRotacao = 0.875;
    asteroide41.tipo = 3;

    asteroide42.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.9;
    asteroide42.rotacao = 175;
    asteroide42.velocidadeRotacao = 0.875;
    asteroide42.tipo = 3;

    asteroide43.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1;
    asteroide43.rotacao = 180;
    asteroide43.velocidadeRotacao = 0.875;
    asteroide43.tipo = 2;

    asteroide44.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.46;
    asteroide44.rotacao = 185;
    asteroide44.velocidadeRotacao = 0.875;
    asteroide44.tipo = 2;

    asteroide45.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.9;
    asteroide45.rotacao = 190;
    asteroide45.velocidadeRotacao = 0.875;
    asteroide45.tipo = 3;

    asteroide46.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.3;
    asteroide46.rotacao = 195;
    asteroide46.velocidadeRotacao = 0.875;
    asteroide46.tipo = 3;

    asteroide47.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.8;
    asteroide47.rotacao = 200;
    asteroide47.velocidadeRotacao = 0.875;
    asteroide47.tipo = 3;

    asteroide48.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1;
    asteroide48.rotacao = 205;
    asteroide48.velocidadeRotacao = 0.875;
    asteroide48.tipo = 3;

    asteroide49.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) +- 1.2;
    asteroide49.rotacao = 210;
    asteroide49.velocidadeRotacao = 0.875;
    asteroide49.tipo = 2;

    asteroide50.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) +- 0.45;
    asteroide50.rotacao = 215;
    asteroide50.velocidadeRotacao = 0.875;
    asteroide50.tipo = 1;

    asteroide51.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1;
    asteroide51.rotacao = 220;
    asteroide51.velocidadeRotacao = 0.875;
    asteroide51.tipo = 1;

    asteroide52.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.7;
    asteroide52.rotacao = 225;
    asteroide52.velocidadeRotacao = 0.875;
    asteroide52.tipo = 2;

    asteroide53.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) +-0.9;
    asteroide53.rotacao = 230;
    asteroide53.velocidadeRotacao = 0.875;
    asteroide53.tipo = 3;

    asteroide54.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.6;
    asteroide54.rotacao = 235;
    asteroide54.velocidadeRotacao = 0.875;
    asteroide54.tipo = 3;

    asteroide55.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.2;
    asteroide55.rotacao = 240;
    asteroide55.velocidadeRotacao = 0.875;
    asteroide55.tipo = 2;

    asteroide56.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.2;
    asteroide56.rotacao = 245;
    asteroide56.velocidadeRotacao = 0.875;
    asteroide56.tipo = 1;

    asteroide57.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.45;
    asteroide57.rotacao = 250;
    asteroide57.velocidadeRotacao = 0.875;
    asteroide57.tipo = 1;

    asteroide58.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.67;
    asteroide58.rotacao = 255;
    asteroide58.velocidadeRotacao = 0.875;
    asteroide58.tipo = 3;

    asteroide59.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.1;
    asteroide59.rotacao = 260;
    asteroide59.velocidadeRotacao = 0.875;
    asteroide59.tipo = 2;

    asteroide60.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.2;
    asteroide60.rotacao = 265;
    asteroide60.velocidadeRotacao = 0.875;
    asteroide60.tipo = 2;

    asteroide61.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.1;
    asteroide61.rotacao = 270;
    asteroide61.velocidadeRotacao = 0.875;
    asteroide61.tipo = 3;

    asteroide62.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.2;
    asteroide62.rotacao = 275;
    asteroide62.velocidadeRotacao = 0.875;
    asteroide62.tipo = 2;

    asteroide63.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.49;
    asteroide63.rotacao = 280;
    asteroide63.velocidadeRotacao = 0.875;
    asteroide63.tipo = 1;

    asteroide64.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.67;
    asteroide64.rotacao = 285;
    asteroide64.velocidadeRotacao = 0.875;
    asteroide64.tipo = 3;

    asteroide65.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.9;
    asteroide65.rotacao = 290;
    asteroide65.velocidadeRotacao = 0.875;
    asteroide65.tipo = 2;

    asteroide66.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1;
    asteroide66.rotacao = 295;
    asteroide66.velocidadeRotacao = 0.875;
    asteroide66.tipo = 3;

    asteroide67.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.45;
    asteroide67.rotacao = 300;
    asteroide67.velocidadeRotacao = 0.875;
    asteroide67.tipo = 1;

    asteroide68.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.1;
    asteroide68.rotacao = 305;
    asteroide68.velocidadeRotacao = 0.875;
    asteroide68.tipo = 2;

    asteroide69.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.56;
    asteroide69.rotacao = 310;
    asteroide69.velocidadeRotacao = 0.875;
    asteroide69.tipo = 2;

    asteroide70.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -1.2;
    asteroide70.rotacao = 315;
    asteroide70.velocidadeRotacao = 0.875;
    asteroide70.tipo = 3;

    asteroide71.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.1;
    asteroide71.rotacao = 320;
    asteroide71.velocidadeRotacao = 0.875;
    asteroide71.tipo = 2;

    asteroide72.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.1;
    asteroide72.rotacao = 325;
    asteroide72.velocidadeRotacao = 0.875;
    asteroide72.tipo = 3;

    asteroide73.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.56;
    asteroide73.rotacao = 330;
    asteroide73.velocidadeRotacao = 0.875;
    asteroide73.tipo = 1;

    asteroide74.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.4;
    asteroide74.rotacao = 335;
    asteroide74.velocidadeRotacao = 0.875;
    asteroide74.tipo = 1;

    asteroide75.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.2;
    asteroide75.rotacao = 340;
    asteroide75.velocidadeRotacao = 0.875;
    asteroide75.tipo = 2;

    asteroide76.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.49;
    asteroide76.rotacao = 345;
    asteroide76.velocidadeRotacao = 0.875;
    asteroide76.tipo = 1;

    asteroide77.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.2;
    asteroide77.rotacao = 350;
    asteroide77.velocidadeRotacao = 0.875;
    asteroide77.tipo = 3;

    asteroide78.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.57;
    asteroide78.rotacao = 355;
    asteroide78.velocidadeRotacao = 0.875;
    asteroide78.tipo = 3;

    asteroide79.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.1;
    asteroide79.rotacao = 360;
    asteroide79.velocidadeRotacao = 0.875;
    asteroide79.tipo = 3;

    asteroide80.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.46;
    asteroide80.rotacao = 365;
    asteroide80.velocidadeRotacao = 0.875;
    asteroide80.tipo = 1;

    asteroide81.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.78;
    asteroide81.rotacao = 370;
    asteroide81.velocidadeRotacao = 0.875;
    asteroide81.tipo = 2;

    asteroide82.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.6;
    asteroide82.rotacao = 375;
    asteroide82.velocidadeRotacao = 0.875;
    asteroide82.tipo = 3;

    asteroide83.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.9;
    asteroide83.rotacao = 380;
    asteroide83.velocidadeRotacao = 0.875;
    asteroide83.tipo = 1;

    asteroide84.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.47;
    asteroide84.rotacao = 385;
    asteroide84.velocidadeRotacao = 0.875;
    asteroide84.tipo = 1;

    asteroide85.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.1;
    asteroide85.rotacao = 390;
    asteroide85.velocidadeRotacao = 0.875;
    asteroide85.tipo = 2;

    asteroide86.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.49;
    asteroide86.rotacao = 395;
    asteroide86.velocidadeRotacao = 0.875;
    asteroide86.tipo = 1;

    asteroide87.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1;
    asteroide87.rotacao = 400;
    asteroide87.velocidadeRotacao = 0.875;
    asteroide87.tipo = 3;

    asteroide88.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.7;
    asteroide88.rotacao = 405;
    asteroide88.velocidadeRotacao = 0.875;
    asteroide88.tipo = 3;

    asteroide89.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.8;
    asteroide89.rotacao = 410;
    asteroide89.velocidadeRotacao = 0.875;
    asteroide89.tipo = 3;

    asteroide90.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.5;
    asteroide90.rotacao = 415;
    asteroide90.velocidadeRotacao = 0.875;
    asteroide90.tipo = 1;

    asteroide91.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1.1;
    asteroide91.rotacao = 420;
    asteroide91.velocidadeRotacao = 0.875;
    asteroide91.tipo = 2;

    asteroide92.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.67;
    asteroide92.rotacao = 425;
    asteroide92.velocidadeRotacao = 0.875;
    asteroide92.tipo = 1;

    asteroide93.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + -0.47;
    asteroide93.rotacao = 430;
    asteroide93.velocidadeRotacao = 0.875;
    asteroide93.tipo = 2;

    asteroide94.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 1;
    asteroide94.rotacao = 435;
    asteroide94.velocidadeRotacao = 0.875;
    asteroide94.tipo = 3;

    asteroide95.distancia = ((marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2) + 0.1;
    asteroide95.rotacao = 440;
    asteroide95.velocidadeRotacao = 0.875;
    asteroide95.tipo = 3;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    angle = 80;
}

void desenharSkyboxes(){
    if(!planoOrbitalAtivado){
        ///Plano do lado direito (no início - caso não se desloque) do Sistema Solar
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaDasEstrelas);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin(GL_POLYGON);
        glTexCoord2f(-1.0, 0.0); glVertex3f(-200, -200, -100);
        glTexCoord2f(2.0, 0.0); glVertex3f(200, -200, -100);
        glTexCoord2f(2.0, 2.0); glVertex3f(200, 200, -100);
        glTexCoord2f(-1.0, 2.0); glVertex3f(-200, 200, -100);
        glEnd();

        ///Plano do lado esquerdo (no início - caso não se desloque) do Sistema Solar
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaDasEstrelas);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin(GL_POLYGON);
        glTexCoord2f(-1.0, 0.0); glVertex3f(-200, -200, 100);
        glTexCoord2f(2.0, 0.0); glVertex3f(200, -200, 100);
        glTexCoord2f(2.0, 2.0); glVertex3f(200, 200, 100);
        glTexCoord2f(-1.0, 2.0); glVertex3f(-200, 200, 100);
        glEnd();



        ///Plano da frente (no início - caso não se desloque) do Sistema Solar
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaDasEstrelas);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex3f(-100, -90, -900);
        glTexCoord2f(8.0, 0.0); glVertex3f(-100, -90, 900);
        glTexCoord2f(8.0, 8.0); glVertex3f(-100, 90, -900);
        glTexCoord2f(0.0, 8.0); glVertex3f(-100, 90, 900);
        glEnd();

        ///Plano abaixo (no início - caso não se desloque) do Sistema Solar
        glBindTexture(GL_TEXTURE_2D, texturaDasEstrelas);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex3f(-100, -90, 200);
        glTexCoord2f(8.0, 0.0); glVertex3f(100, -90, 200);
        glTexCoord2f(8.0, 8.0); glVertex3f(100, -90, -200);
        glTexCoord2f(0.0, 8.0); glVertex3f(-100, -90, -200);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        ///Plano atrás (no início - caso não se desloque) do Sistema Solar
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaDasEstrelas);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin(GL_POLYGON);
            glTexCoord2f(-1.0, 0.0); glVertex3f(90, -90, -200);
            glTexCoord2f(2.0, 2.0); glVertex3f(90, -90, 200);
            glTexCoord2f(-1.0, 2.0); glVertex3f(90, 120, 200);
            glTexCoord2f(2.0, 0.0); glVertex3f(90, 120, -200);
        glEnd();
        glDisable(GL_TEXTURE_2D);

    }
}

void desenharEsfera(double raio, double distancia, double inclinacaoX, double anguloRotacaoNoProprioEixo, double orbita, char *nome, bool verEsfera){

    glPushMatrix(); //Sistema padrão de coordenadas
    glColor3f(0, 1, 0);
    glRotatef(orbita, 0, 1, 0); //rotacionar em volta da estrela (Movimento de translação)
    glTranslatef(distancia, 0, 0);
    glPushMatrix();
    glRotatef(inclinacaoX, 1, 0, 0); //Sua inclinação
    glRotatef(anguloRotacaoNoProprioEixo, 0, 1, 0); //Movimento de rotação
    glRotatef(90, 1, 0, 0);
    glPushMatrix();

    if(verEsfera){
        //glPushMatrix();
        //double z = -sin(orbita * 180 * 3.1415) + distancia;
        double z = distancia * sin(((orbita) * 3.141592) / 180);
        //double x = -sin(orbita * 180 * 3.1415) + distancia;
        double x = distancia * cos(((orbita) * 3.141592) / 180);
        double y = -sin(orbita * 180 * 3.1415);
        //posicaoCameraX = raio + distanciaDoPlaneta;
        posicaoCameraX = 1.4 * x;
        posicaoCameraY = 0;
        posicaoCameraZ = z * 1.4;
        posicaoOlharZ = 0;
        posicaoOlharY = 0;
        posicaoOlharX = 0;
        //posicaoOlharX = distancia - raio;
        //posicaoCameraY = 0;
        //posicaoCameraZ = 0;
        //posicaoOlharZ = 0;
        //posicaoOlharY = 0;
        //posicaoOlharX = 0;
    }

    ///Atribuindo textura

    if(strcmp(nome, "Sol") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);

        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaDoSol);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);

        glDisable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);

        glColor4f(1, 0, 0, 0.1475);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gluSphere(quadric, raio * 1.075, 20, 20);

        glEnable(GL_BLEND);

        glColor4f(1, 1, 0, 0.15);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gluSphere(quadric, raio * 1.025, 20, 20);

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
    else if(strcmp(nome, "Mercurio") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieMercurio);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
        }

    else if(strcmp(nome, "Venus") == 0){
        //texturaSuperficieTerra

        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieVenus);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
	   glEnable(GL_BLEND);

        //texturaAtmosferaVenus

        glColor4f(1, 1, 0, 0.20);
        glBindTexture(GL_TEXTURE_2D, texturaAtmosferaVenus);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gluSphere(quadric, raio * 1.12, 20, 20);

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        }
    else if(strcmp(nome, "Terra") == 0){
        //texturaSuperficieTerra

        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieTerra);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);

        //texturaAtmosferaTerra

        glEnable(GL_BLEND);
        glColor4f(1, 1, 0, 0.20);
        glBindTexture(GL_TEXTURE_2D, texturaAtmosferaTerra);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gluSphere(quadric, raio * 1.12, 20, 20);

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
    else if(strcmp(nome, "Marte") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieMarte);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
        }

    else if(strcmp(nome, "Jupiter") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieJupiter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
        }

    else if(strcmp(nome, "Saturno") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieSaturno);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
        }

    else if(strcmp(nome, "Urano") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieUrano);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
        }

    else if(strcmp(nome, "Netuno") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieNetuno);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
        }

    else{
        glutSolidSphere(raio, 180, 180);
    }

    ///Desenhando os anéis dos planetas

    if(strcmp(nome, "Saturno") == 0){
        glColor3f(0.5, 0.35, 0.15);
        //glRotatef(90, 1, 0, 0);
        glutWireTorus(0.235, raio + 0.8, 100, 100);
    }

    if(strcmp(nome, "Netuno") == 0){
        glColor3f(0, 0.85, 1);
        glutWireTorus(0.08, raio + 0.43, 100, 100);
    }

    if(strcmp(nome, "Jupiter") == 0){
        glColor3f(1.0, 0.5, 0);
        glutWireTorus(0.11, raio + 0.4, 100, 100);
    }

    if(strcmp(nome, "Urano") == 0){
        glColor3f(0, 0, 1);
        //glRotatef(90, 1, 0, 0);
        glutWireTorus(0.07, raio + 0.38, 100, 100);
    }

    glPopMatrix();
    glPopMatrix();

    glColor3f(0, 1, 1);

    ///Mostrar ou esconder os nomes dos planetas

    if(mostrarNomesPlanetas){
        glRasterPos3f(0, raio + 2, 0);
        for(int i = 0; i < strlen(nome); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nome[i]);
        }
    }

    glPopMatrix();
}

void desenharSatelitesNaturais(double raio, double distancia, double inclinacaoX, double anguloRotacaoNoProprioEixo, double orbita, char *nome, EsferasEspaciais planetaMae){
    glPushMatrix(); //Sistema padrão de coordenadas
    glColor3f(1, 1, 1);
    glRotatef(orbita, 0, 1, 0);
    glTranslatef(planetaMae.distanciaAteOSol, 0, 0);

    glRotatef(planetaMae.anguloRotacaoNoProprioEixo, 0, 1, 0);  //Temos que ver qual é melhor
    //glRotatef(orbita, 0, 1, 0);                               //o segundo Rotacionar deve ser o angulo do planetaMae primeiro ou a orbita

    glTranslatef(distancia - planetaMae.distanciaAteOSol, 0, 0);

    glRotatef(orbita, 0, 1, 0);
    //glRotatef(planetaMae.anguloRotacaoNoProprioEixo, 0, 1, 0);

    glPushMatrix();

    ///Atribuindo textura

    if(strcmp(nome, "Lua") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaLua);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
        }
    else if(strcmp(nome, "Phobos") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, texturaPhobos);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        glDisable(GL_TEXTURE_2D);
    }

    //hmm

    glutSolidSphere(raio, 180, 180);

    glPopMatrix();

    //Mostrando nome dos satélites naturais

    glColor3f(0, 1, 1);
    if(mostrarNomesPlanetas){
        glRasterPos3f(0, raio + 2, 0);
        for(int i = 0; i < strlen(nome); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nome[i]);
        }
    }

    glPopMatrix();
}

void desenharAsteroides(double distancia, double rotacao, int tipo){
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glRotatef(rotacao, 0, 1, 0);
    glTranslatef(distancia, 0, 0);
    glScalef(0.3, 0.3, 0.3);

    if(tipo == 1){
        glutSolidIcosahedron();
    }
    else if(tipo == 2){
        glutSolidDodecahedron();
    }
    else if(tipo == 3){
        glutSolidOctahedron();
    }
    glPopMatrix();
}

void desenharOrbitas(){
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(90, 1, 0, 0);
    glutWireTorus(0.005, mercurio.distanciaAteOSol, 100, 100);
    glutWireTorus(.005, venus.distanciaAteOSol, 100, 100);
    glutWireTorus(.005, terra.distanciaAteOSol, 100, 100);
    glutWireTorus(.005, marte.distanciaAteOSol, 100, 100);
    glutWireTorus(.005, jupiter.distanciaAteOSol, 100, 100);
    glutWireTorus(.005, saturno.distanciaAteOSol, 100, 100);
    glutWireTorus(.005, uranos.distanciaAteOSol, 100, 100);
    glutWireTorus(.005, netuno.distanciaAteOSol, 100, 100);
    glPopMatrix();
}

void desenharPlanoOrbital(){
    int controleTempo = 0;
    int controleTempo1 = 0;
    double Xc = -100;
    double Zc = -190;

    double Xc_antigo = Xc;
    double Zc_antigo = Zc;

    double A[] = {Xc, 0, Zc};
    double B[] = {Xc, 0, Zc + INCREMENTO_PLANO};
    double C[] = {Xc + INCREMENTO_PLANO, 0, Zc};
    glColor3f(1, 1, 1);

    //Vertical
    for(int i = 0; i < 120; i++){
        for(int j = 0; j < 600; j++){
            glBegin(GL_TRIANGLE_STRIP);
                if(controleTempo % 2 == 0){
                    glVertex3f(A[0], A[1], A[2]);
                    glVertex3f(B[0], B[1], B[2]);
                    glVertex3f(C[0], C[1], C[2]);

                    A[0] = B[0] + INCREMENTO_PLANO;
                    A[2] = B[2];
                }
                if(controleTempo % 2 != 0){
                    glVertex3f(A[0], A[1], A[2]);
                    glVertex3f(B[0], B[1], B[2]);
                    glVertex3f(C[0], C[1], C[2]);

                    B[0] = A[0];
                    B[2] = A[2];

                    A[0] = C[0];
                    A[2] = C[2];

                    C[0] += INCREMENTO_PLANO;
                }
            glEnd();
            controleTempo++;
        }
        Zc += INCREMENTO_PLANO * 5;

        A[0] = Xc;
        A[1] = 0;
        A[2] = Zc;

        B[0] = Xc;
        B[1] = 0;
        B[2] = Zc + INCREMENTO_PLANO;

        C[0] = Xc + INCREMENTO_PLANO;
        C[1] = 0;
        C[2] = Zc;
        controleTempo = 0;
    }

    //Horizontal

    A[0] = Xc_antigo;
    A[1] = 0;
    A[2] = Zc_antigo;

    B[0] = Xc_antigo;
    B[1] = 0;
    B[2] = Zc_antigo + INCREMENTO_PLANO;

    C[0] = Xc_antigo + INCREMENTO_PLANO;
    C[1] = 0;
    C[2] = Zc_antigo;

    for(int k = 0; k < 60; k++){
        for(int l = 0; l < 1200; l++){
            glBegin(GL_TRIANGLE_STRIP);

            if(controleTempo1 % 2 == 0){
                glVertex3f(A[0], A[1], A[2]);
                glVertex3f(B[0], B[1], B[2]);
                glVertex3f(C[0], C[1], C[2]);

                A[0] = C[0];
                C[2] = C[0] + INCREMENTO_PLANO;
            }
            if(controleTempo1 % 2 != 0){
                glVertex3f(A[0], A[1], A[2]);
                glVertex3f(B[0], B[1], B[2]);
                glVertex3f(C[0], C[1], C[2]);

                A[0] = B[0];
                A[2] = B[2];

                B[2] += INCREMENTO_PLANO;
            }
            glEnd();
            controleTempo1++;
        }
        Xc_antigo += INCREMENTO_PLANO * 5;

        A[0] = Xc_antigo;
        A[1] = 0;
        A[2] = Zc_antigo;

        B[0] = Xc_antigo;
        B[1] = 0;
        B[2] = Zc_antigo + INCREMENTO_PLANO;

        C[0] = Xc_antigo + INCREMENTO_PLANO;
        C[1] = 0;
        C[2] = Zc_antigo;

        controleTempo1 = 0;
    }
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar a tela para que não tenha as antigas esferas que antes foram desenhadas

	desenharSkyboxes();

	if(planoOrbitalAtivado){
        desenharPlanoOrbital();
	}

    if(verOrbitas){
        desenharOrbitas();
    }

	desenharEsfera(mercurio.raio, mercurio.distanciaAteOSol, mercurio.inclinacaoX, mercurio.anguloRotacaoNoProprioEixo, mercurio.orbita, mercurio.nome, olharMercurio);
	desenharEsfera(venus.raio, venus.distanciaAteOSol, venus.inclinacaoX, venus.anguloRotacaoNoProprioEixo, venus.orbita, venus.nome, olharVenus);
	desenharEsfera(terra.raio, terra.distanciaAteOSol, terra.inclinacaoX, terra.anguloRotacaoNoProprioEixo, terra.orbita, terra.nome, olharTerra);
	desenharSatelitesNaturais(lua.raio, lua.distanciaAteOSol, lua.inclinacaoX, lua.anguloRotacaoNoProprioEixo, lua.orbita, lua.nome, terra);
	desenharEsfera(marte.raio, marte.distanciaAteOSol, marte.inclinacaoX, marte.anguloRotacaoNoProprioEixo, marte.orbita, marte.nome, olharMarte);
	desenharSatelitesNaturais(phobos.raio, phobos.distanciaAteOSol, phobos.inclinacaoX, phobos.anguloRotacaoNoProprioEixo, phobos.orbita, phobos.nome, marte);
	desenharEsfera(jupiter.raio, jupiter.distanciaAteOSol, jupiter.inclinacaoX, jupiter.anguloRotacaoNoProprioEixo, jupiter.orbita, jupiter.nome, olharJupiter);
	desenharEsfera(saturno.raio, saturno.distanciaAteOSol, saturno.inclinacaoX, saturno.anguloRotacaoNoProprioEixo, saturno.orbita, saturno.nome, olharSaturno);
	desenharSatelitesNaturais(titan.raio, titan.distanciaAteOSol, titan.inclinacaoX, titan.anguloRotacaoNoProprioEixo, titan.orbita, titan.nome, saturno);
	desenharEsfera(uranos.raio, uranos.distanciaAteOSol, uranos.inclinacaoX, uranos.anguloRotacaoNoProprioEixo, uranos.orbita, uranos.nome, olharUranos);
	desenharEsfera(netuno.raio, netuno.distanciaAteOSol, netuno.inclinacaoX, netuno.anguloRotacaoNoProprioEixo, netuno.orbita, netuno.nome, olharNetuno);
	desenharEsfera(sol.raio, sol.distanciaAteOSol, sol.inclinacaoX, sol.anguloRotacaoNoProprioEixo, sol.orbita, sol.nome, false);

	desenharAsteroides(asteroide1.distancia, asteroide1.rotacao, asteroide1.tipo);
	desenharAsteroides(asteroide2.distancia, asteroide2.rotacao, asteroide2.tipo);
	desenharAsteroides(asteroide3.distancia, asteroide3.rotacao, asteroide3.tipo);
	desenharAsteroides(asteroide4.distancia, asteroide4.rotacao, asteroide4.tipo);
	desenharAsteroides(asteroide5.distancia, asteroide5.rotacao, asteroide5.tipo);
	desenharAsteroides(asteroide6.distancia, asteroide6.rotacao, asteroide6.tipo);
	desenharAsteroides(asteroide7.distancia, asteroide7.rotacao, asteroide6.tipo);
	desenharAsteroides(asteroide8.distancia, asteroide8.rotacao, asteroide8.tipo);
	desenharAsteroides(asteroide9.distancia, asteroide9.rotacao, asteroide9.tipo);
	desenharAsteroides(asteroide10.distancia, asteroide10.rotacao, asteroide10.tipo);
	desenharAsteroides(asteroide11.distancia, asteroide11.rotacao, asteroide11.tipo);
	desenharAsteroides(asteroide12.distancia, asteroide12.rotacao, asteroide12.tipo);
	desenharAsteroides(asteroide13.distancia, asteroide13.rotacao, asteroide13.tipo);
	desenharAsteroides(asteroide14.distancia, asteroide14.rotacao, asteroide14.tipo);
	desenharAsteroides(asteroide15.distancia, asteroide15.rotacao, asteroide15.tipo);
	desenharAsteroides(asteroide16.distancia, asteroide16.rotacao, asteroide16.tipo);
	desenharAsteroides(asteroide17.distancia, asteroide17.rotacao, asteroide17.tipo);
	desenharAsteroides(asteroide18.distancia, asteroide18.rotacao, asteroide18.tipo);
	desenharAsteroides(asteroide19.distancia, asteroide19.rotacao, asteroide19.tipo);
	desenharAsteroides(asteroide20.distancia, asteroide20.rotacao, asteroide20.tipo);
	desenharAsteroides(asteroide21.distancia, asteroide21.rotacao, asteroide21.tipo);
	desenharAsteroides(asteroide22.distancia, asteroide22.rotacao, asteroide22.tipo);
	desenharAsteroides(asteroide23.distancia, asteroide23.rotacao, asteroide23.tipo);
	desenharAsteroides(asteroide24.distancia, asteroide24.rotacao, asteroide24.tipo);
	desenharAsteroides(asteroide25.distancia, asteroide25.rotacao, asteroide25.tipo);
	desenharAsteroides(asteroide26.distancia, asteroide26.rotacao, asteroide26.tipo);
	desenharAsteroides(asteroide27.distancia, asteroide27.rotacao, asteroide27.tipo);
	desenharAsteroides(asteroide28.distancia, asteroide28.rotacao, asteroide28.tipo);
	desenharAsteroides(asteroide29.distancia, asteroide29.rotacao, asteroide29.tipo);
	desenharAsteroides(asteroide30.distancia, asteroide30.rotacao, asteroide30.tipo);
	desenharAsteroides(asteroide31.distancia, asteroide31.rotacao, asteroide31.tipo);
	desenharAsteroides(asteroide32.distancia, asteroide32.rotacao, asteroide32.tipo);
	desenharAsteroides(asteroide33.distancia, asteroide33.rotacao, asteroide33.tipo);
	desenharAsteroides(asteroide34.distancia, asteroide34.rotacao, asteroide34.tipo);
	desenharAsteroides(asteroide35.distancia, asteroide35.rotacao, asteroide35.tipo);
	desenharAsteroides(asteroide36.distancia, asteroide36.rotacao, asteroide36.tipo);
	desenharAsteroides(asteroide37.distancia, asteroide37.rotacao, asteroide37.tipo);
	desenharAsteroides(asteroide38.distancia, asteroide38.rotacao, asteroide38.tipo);
	desenharAsteroides(asteroide39.distancia, asteroide39.rotacao, asteroide39.tipo);
	desenharAsteroides(asteroide40.distancia, asteroide40.rotacao, asteroide40.tipo);
	desenharAsteroides(asteroide41.distancia, asteroide41.rotacao, asteroide41.tipo);
	desenharAsteroides(asteroide42.distancia, asteroide42.rotacao, asteroide42.tipo);
	desenharAsteroides(asteroide43.distancia, asteroide43.rotacao, asteroide43.tipo);
	desenharAsteroides(asteroide44.distancia, asteroide44.rotacao, asteroide44.tipo);
	desenharAsteroides(asteroide45.distancia, asteroide45.rotacao, asteroide45.tipo);
	desenharAsteroides(asteroide46.distancia, asteroide46.rotacao, asteroide46.tipo);
	desenharAsteroides(asteroide47.distancia, asteroide47.rotacao, asteroide47.tipo);
	desenharAsteroides(asteroide48.distancia, asteroide48.rotacao, asteroide48.tipo);
	desenharAsteroides(asteroide49.distancia, asteroide49.rotacao, asteroide49.tipo);
	desenharAsteroides(asteroide50.distancia, asteroide50.rotacao, asteroide50.tipo);
	desenharAsteroides(asteroide51.distancia, asteroide51.rotacao, asteroide51.tipo);
	desenharAsteroides(asteroide52.distancia, asteroide52.rotacao, asteroide52.tipo);
	desenharAsteroides(asteroide53.distancia, asteroide53.rotacao, asteroide53.tipo);
	desenharAsteroides(asteroide54.distancia, asteroide54.rotacao, asteroide54.tipo);
	desenharAsteroides(asteroide55.distancia, asteroide55.rotacao, asteroide55.tipo);
	desenharAsteroides(asteroide56.distancia, asteroide56.rotacao, asteroide56.tipo);
	desenharAsteroides(asteroide57.distancia, asteroide57.rotacao, asteroide57.tipo);
	desenharAsteroides(asteroide58.distancia, asteroide58.rotacao, asteroide58.tipo);
	desenharAsteroides(asteroide59.distancia, asteroide59.rotacao, asteroide59.tipo);
	desenharAsteroides(asteroide60.distancia, asteroide60.rotacao, asteroide60.tipo);
	desenharAsteroides(asteroide61.distancia, asteroide61.rotacao, asteroide61.tipo);
	desenharAsteroides(asteroide62.distancia, asteroide62.rotacao, asteroide62.tipo);
	desenharAsteroides(asteroide63.distancia, asteroide63.rotacao, asteroide63.tipo);
	desenharAsteroides(asteroide64.distancia, asteroide64.rotacao, asteroide64.tipo);
	desenharAsteroides(asteroide65.distancia, asteroide65.rotacao, asteroide65.tipo);
	desenharAsteroides(asteroide66.distancia, asteroide66.rotacao, asteroide66.tipo);
	desenharAsteroides(asteroide67.distancia, asteroide67.rotacao, asteroide67.tipo);
	desenharAsteroides(asteroide68.distancia, asteroide68.rotacao, asteroide68.tipo);
	desenharAsteroides(asteroide69.distancia, asteroide69.rotacao, asteroide69.tipo);
	desenharAsteroides(asteroide70.distancia, asteroide70.rotacao, asteroide70.tipo);
	desenharAsteroides(asteroide71.distancia, asteroide71.rotacao, asteroide71.tipo);
	desenharAsteroides(asteroide72.distancia, asteroide72.rotacao, asteroide72.tipo);
	desenharAsteroides(asteroide73.distancia, asteroide73.rotacao, asteroide73.tipo);
	desenharAsteroides(asteroide74.distancia, asteroide74.rotacao, asteroide74.tipo);
	desenharAsteroides(asteroide75.distancia, asteroide75.rotacao, asteroide75.tipo);
	desenharAsteroides(asteroide76.distancia, asteroide76.rotacao, asteroide76.tipo);
	desenharAsteroides(asteroide77.distancia, asteroide77.rotacao, asteroide77.tipo);
	desenharAsteroides(asteroide78.distancia, asteroide78.rotacao, asteroide78.tipo);
	desenharAsteroides(asteroide79.distancia, asteroide79.rotacao, asteroide79.tipo);
	desenharAsteroides(asteroide80.distancia, asteroide80.rotacao, asteroide80.tipo);
	desenharAsteroides(asteroide81.distancia, asteroide81.rotacao, asteroide81.tipo);
	desenharAsteroides(asteroide82.distancia, asteroide82.rotacao, asteroide82.tipo);
	desenharAsteroides(asteroide83.distancia, asteroide83.rotacao, asteroide83.tipo);
	desenharAsteroides(asteroide84.distancia, asteroide84.rotacao, asteroide84.tipo);
	desenharAsteroides(asteroide85.distancia, asteroide85.rotacao, asteroide85.tipo);
	desenharAsteroides(asteroide86.distancia, asteroide86.rotacao, asteroide86.tipo);
	desenharAsteroides(asteroide87.distancia, asteroide87.rotacao, asteroide87.tipo);
	desenharAsteroides(asteroide88.distancia, asteroide88.rotacao, asteroide88.tipo);
	desenharAsteroides(asteroide89.distancia, asteroide89.rotacao, asteroide89.tipo);
	desenharAsteroides(asteroide90.distancia, asteroide90.rotacao, asteroide90.tipo);
	desenharAsteroides(asteroide91.distancia, asteroide91.rotacao, asteroide90.tipo);
	desenharAsteroides(asteroide92.distancia, asteroide92.rotacao, asteroide90.tipo);
	desenharAsteroides(asteroide93.distancia, asteroide93.rotacao, asteroide90.tipo);
	desenharAsteroides(asteroide94.distancia, asteroide94.rotacao, asteroide90.tipo);
	desenharAsteroides(asteroide95.distancia, asteroide95.rotacao, asteroide90.tipo);

	glutSwapBuffers();
 }


void Redimensiona(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void){

	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle, fAspect, 0.1, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	//gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
	gluLookAt(posicaoCameraX, posicaoCameraY, posicaoCameraZ, posicaoOlharX, posicaoOlharY, posicaoOlharZ, 0, 1, 0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void ligaDesligaMudaIluminacao(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Parâmetros para definir a fonte de luz

    float iluminacaoDifusaEEspecular[] = {0, 0, 0, 0};
    float iluminacaoAmbiente[] = {0, 0, 0, 0};
    float iluminacaoEmissiva[] = {0, 0, 0, 0};
    float posicaoDaIluminacao[] = {0, 0, 0, 0};
    float direcaoDaLuzNaIluminacao[] = {0, 0, 0};
    float anguloFonteDeLuz = 0;
    float atenuacaoDaIluminacao = 0;

    if(iluminacaoEstaLigada){
        if(tipoIluminacao == 0){ //Iluminação ligada e tipoIluminação escolhido
            iluminacaoDifusaEEspecular[0] = 1;
            iluminacaoDifusaEEspecular[1] = 1;
            iluminacaoDifusaEEspecular[2] = 1;
            iluminacaoDifusaEEspecular[3] = 1;

            iluminacaoAmbiente[0] = 0;
            iluminacaoAmbiente[1] = 0;
            iluminacaoAmbiente[2] = 0;
            iluminacaoAmbiente[3] = 1;

            iluminacaoEmissiva[0] = 0.5;
            iluminacaoEmissiva[1] = 0.5;
            iluminacaoEmissiva[2] = 0.5;
            iluminacaoEmissiva[3] = 1;

            posicaoDaIluminacao[0] = 0;
            posicaoDaIluminacao[1] = 85;
            posicaoDaIluminacao[2] = 12;
            posicaoDaIluminacao[3] = 0;

            direcaoDaLuzNaIluminacao[0] = 1;
            direcaoDaLuzNaIluminacao[1] = 0;
            direcaoDaLuzNaIluminacao[2] = 0;

            anguloFonteDeLuz = 120;
            atenuacaoDaIluminacao = 0.75;

            glLightfv(GL_LIGHT0, GL_SPECULAR, iluminacaoDifusaEEspecular);
            glLightfv(GL_LIGHT0, GL_AMBIENT, iluminacaoAmbiente);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, iluminacaoDifusaEEspecular);

            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, iluminacaoEmissiva);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
            glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

            glLightfv(GL_LIGHT0, GL_POSITION, posicaoDaIluminacao);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcaoDaLuzNaIluminacao);
            glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, anguloFonteDeLuz);
            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atenuacaoDaIluminacao);
        }
        else if(tipoIluminacao == 1){ //Iluminação ligada e tipoIluminação1 escolhido
            iluminacaoDifusaEEspecular[0] = 1;
            iluminacaoDifusaEEspecular[1] = 1;
            iluminacaoDifusaEEspecular[2] = 1;
            iluminacaoDifusaEEspecular[3] = 1;

            iluminacaoAmbiente[0] = 0;
            iluminacaoAmbiente[1] = 0;
            iluminacaoAmbiente[2] = 0;
            iluminacaoAmbiente[3] = 1;

            iluminacaoEmissiva[0] = 0.5;
            iluminacaoEmissiva[1] = 0.5;
            iluminacaoEmissiva[2] = 0.5;
            iluminacaoEmissiva[3] = 1;

            posicaoDaIluminacao[0] = 2;
            posicaoDaIluminacao[1] = 40;
            posicaoDaIluminacao[2] = 55;
            posicaoDaIluminacao[3] = 0;

            direcaoDaLuzNaIluminacao[0] = 1;
            direcaoDaLuzNaIluminacao[1] = 0;
            direcaoDaLuzNaIluminacao[2] = 0;

            anguloFonteDeLuz = 100;
            atenuacaoDaIluminacao = 1;

            glLightfv(GL_LIGHT0, GL_SPECULAR, iluminacaoDifusaEEspecular);
            glLightfv(GL_LIGHT0, GL_AMBIENT, iluminacaoAmbiente);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, iluminacaoDifusaEEspecular);

            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, iluminacaoEmissiva);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
            glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

            glLightfv(GL_LIGHT0, GL_POSITION, posicaoDaIluminacao);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcaoDaLuzNaIluminacao);
            glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, anguloFonteDeLuz);
            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atenuacaoDaIluminacao);
        }
        else if(tipoIluminacao == 2){ //Iluminação ligada e tipoIluminação 2 escolhido
            iluminacaoDifusaEEspecular[0] = 1;
            iluminacaoDifusaEEspecular[1] = 1;
            iluminacaoDifusaEEspecular[2] = 1;
            iluminacaoDifusaEEspecular[3] = 1;

            iluminacaoAmbiente[0] = 0;
            iluminacaoAmbiente[1] = 0;
            iluminacaoAmbiente[2] = 0;
            iluminacaoAmbiente[3] = 1;

            iluminacaoEmissiva[0] = 0.5;
            iluminacaoEmissiva[1] = 0.5;
            iluminacaoEmissiva[2] = 0.5;
            iluminacaoEmissiva[3] = 1;

            posicaoDaIluminacao[0] = 45;
            posicaoDaIluminacao[1] = 70;
            posicaoDaIluminacao[2] = 0.2;
            posicaoDaIluminacao[3] = 0;

            direcaoDaLuzNaIluminacao[0] = 1;
            direcaoDaLuzNaIluminacao[1] = 1;
            direcaoDaLuzNaIluminacao[2] = 1;

            anguloFonteDeLuz = 120;
            atenuacaoDaIluminacao = 0.75;

            glLightfv(GL_LIGHT0, GL_SPECULAR, iluminacaoDifusaEEspecular);
            glLightfv(GL_LIGHT0, GL_AMBIENT, iluminacaoAmbiente);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, iluminacaoDifusaEEspecular);

            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, iluminacaoEmissiva);
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
            glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

            glLightfv(GL_LIGHT0, GL_POSITION, posicaoDaIluminacao);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcaoDaLuzNaIluminacao);
            glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, anguloFonteDeLuz);
            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atenuacaoDaIluminacao);

        }
    }
    else if(!iluminacaoEstaLigada && comLuzDoSolOn == true){ //Iluminação desligada e luz do Sol ligada
        iluminacaoDifusaEEspecular[0] = 1;
        iluminacaoDifusaEEspecular[1] = 1;
        iluminacaoDifusaEEspecular[2] = 1;
        iluminacaoDifusaEEspecular[3] = 1;

        iluminacaoAmbiente[0] = 0;
        iluminacaoAmbiente[1] = 0;
        iluminacaoAmbiente[2] = 0;
        iluminacaoAmbiente[3] = 1;

        iluminacaoEmissiva[0] = 0.5;
        iluminacaoEmissiva[1] = 0.5;
        iluminacaoEmissiva[2] = 0.5;
        iluminacaoEmissiva[3] = 1;

        posicaoDaIluminacao[0] = 0;
        posicaoDaIluminacao[1] = 1;
        posicaoDaIluminacao[2] = 0;
        posicaoDaIluminacao[3] = 0;

        direcaoDaLuzNaIluminacao[0] = 0;
        direcaoDaLuzNaIluminacao[1] = 1;
        direcaoDaLuzNaIluminacao[2] = 0;

        anguloFonteDeLuz = 220;
        atenuacaoDaIluminacao = 0.3785;

        glLightfv(GL_LIGHT0, GL_SPECULAR, iluminacaoDifusaEEspecular);
        glLightfv(GL_LIGHT0, GL_AMBIENT, iluminacaoAmbiente);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, iluminacaoDifusaEEspecular);

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, iluminacaoEmissiva);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

        glLightfv(GL_LIGHT0, GL_POSITION, posicaoDaIluminacao);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcaoDaLuzNaIluminacao);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, anguloFonteDeLuz);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atenuacaoDaIluminacao);

    }
    else if(!iluminacaoEstaLigada && !comLuzDoSolOn){ //Iluminação desligada e iluminação do Sol desligada
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Animacao(int periodo){

    ligaDesligaMudaIluminacao();

    if(animacaoOn == true){

        ///Promovendo a animação (o movimento)

        mercurio.orbita += mercurio.velocidadeDaOrbita;
        mercurio.anguloRotacaoNoProprioEixo += mercurio.velocidadeRotacao;

        venus.orbita += venus.velocidadeDaOrbita;
        venus.anguloRotacaoNoProprioEixo += venus.velocidadeRotacao;

        terra.orbita += terra.velocidadeDaOrbita;
        terra.anguloRotacaoNoProprioEixo += terra.velocidadeRotacao;

        lua.orbita += lua.velocidadeDaOrbita;
        lua.anguloRotacaoNoProprioEixo += lua.velocidadeRotacao;

        marte.orbita += marte.velocidadeDaOrbita;
        marte.anguloRotacaoNoProprioEixo += marte.velocidadeRotacao;

        phobos.orbita += phobos.velocidadeDaOrbita;
        phobos.anguloRotacaoNoProprioEixo += phobos.velocidadeRotacao;

        jupiter.orbita += jupiter.velocidadeDaOrbita;
        jupiter.anguloRotacaoNoProprioEixo += jupiter.velocidadeRotacao;

        saturno.orbita += saturno.velocidadeDaOrbita;
        saturno.anguloRotacaoNoProprioEixo += saturno.velocidadeRotacao;

        titan.orbita += titan.velocidadeDaOrbita;
        titan.anguloRotacaoNoProprioEixo += titan.velocidadeRotacao;

        uranos.orbita += uranos.velocidadeDaOrbita;
        uranos.anguloRotacaoNoProprioEixo += uranos.velocidadeRotacao;

        netuno.orbita += netuno.velocidadeDaOrbita;
        netuno.anguloRotacaoNoProprioEixo += netuno.velocidadeRotacao;

        asteroide1.rotacao += asteroide1.velocidadeRotacao;
        asteroide2.rotacao += asteroide2.velocidadeRotacao;
        asteroide3.rotacao += asteroide3.velocidadeRotacao;
        asteroide4.rotacao += asteroide4.velocidadeRotacao;
        asteroide5.rotacao += asteroide5.velocidadeRotacao;
        asteroide6.rotacao += asteroide6.velocidadeRotacao;
        asteroide7.rotacao += asteroide7.velocidadeRotacao;
        asteroide8.rotacao += asteroide8.velocidadeRotacao;
        asteroide9.rotacao += asteroide9.velocidadeRotacao;
        asteroide10.rotacao += asteroide10.velocidadeRotacao;
        asteroide11.rotacao += asteroide11.velocidadeRotacao;
        asteroide12.rotacao += asteroide12.velocidadeRotacao;
        asteroide13.rotacao += asteroide13.velocidadeRotacao;
        asteroide14.rotacao += asteroide14.velocidadeRotacao;
        asteroide15.rotacao += asteroide15.velocidadeRotacao;
        asteroide16.rotacao += asteroide16.velocidadeRotacao;
        asteroide17.rotacao += asteroide17.velocidadeRotacao;
        asteroide18.rotacao += asteroide18.velocidadeRotacao;
        asteroide19.rotacao += asteroide19.velocidadeRotacao;
        asteroide20.rotacao += asteroide20.velocidadeRotacao;
        asteroide21.rotacao += asteroide21.velocidadeRotacao;
        asteroide22.rotacao += asteroide22.velocidadeRotacao;
        asteroide23.rotacao += asteroide23.velocidadeRotacao;
        asteroide24.rotacao += asteroide24.velocidadeRotacao;
        asteroide25.rotacao += asteroide25.velocidadeRotacao;
        asteroide26.rotacao += asteroide26.velocidadeRotacao;
        asteroide27.rotacao += asteroide27.velocidadeRotacao;
        asteroide28.rotacao += asteroide28.velocidadeRotacao;
        asteroide29.rotacao += asteroide29.velocidadeRotacao;
        asteroide30.rotacao += asteroide30.velocidadeRotacao;
        asteroide31.rotacao += asteroide31.velocidadeRotacao;
        asteroide32.rotacao += asteroide32.velocidadeRotacao;
        asteroide33.rotacao += asteroide33.velocidadeRotacao;
        asteroide34.rotacao += asteroide34.velocidadeRotacao;
        asteroide35.rotacao += asteroide35.velocidadeRotacao;
        asteroide36.rotacao += asteroide36.velocidadeRotacao;
        asteroide37.rotacao += asteroide37.velocidadeRotacao;
        asteroide38.rotacao += asteroide38.velocidadeRotacao;
        asteroide39.rotacao += asteroide39.velocidadeRotacao;
        asteroide40.rotacao += asteroide40.velocidadeRotacao;
        asteroide41.rotacao += asteroide41.velocidadeRotacao;
        asteroide42.rotacao += asteroide42.velocidadeRotacao;
        asteroide43.rotacao += asteroide43.velocidadeRotacao;
        asteroide44.rotacao += asteroide44.velocidadeRotacao;
        asteroide45.rotacao += asteroide45.velocidadeRotacao;
        asteroide46.rotacao += asteroide46.velocidadeRotacao;
        asteroide47.rotacao += asteroide47.velocidadeRotacao;
        asteroide48.rotacao += asteroide48.velocidadeRotacao;
        asteroide49.rotacao += asteroide49.velocidadeRotacao;
        asteroide50.rotacao += asteroide50.velocidadeRotacao;
        asteroide50.rotacao += asteroide50.velocidadeRotacao;
        asteroide51.rotacao += asteroide51.velocidadeRotacao;
        asteroide52.rotacao += asteroide52.velocidadeRotacao;
        asteroide53.rotacao += asteroide53.velocidadeRotacao;
        asteroide54.rotacao += asteroide54.velocidadeRotacao;
        asteroide55.rotacao += asteroide55.velocidadeRotacao;
        asteroide56.rotacao += asteroide56.velocidadeRotacao;
        asteroide57.rotacao += asteroide57.velocidadeRotacao;
        asteroide58.rotacao += asteroide58.velocidadeRotacao;
        asteroide59.rotacao += asteroide59.velocidadeRotacao;
        asteroide60.rotacao += asteroide60.velocidadeRotacao;
        asteroide61.rotacao += asteroide61.velocidadeRotacao;
        asteroide62.rotacao += asteroide62.velocidadeRotacao;
        asteroide63.rotacao += asteroide63.velocidadeRotacao;
        asteroide64.rotacao += asteroide64.velocidadeRotacao;
        asteroide65.rotacao += asteroide65.velocidadeRotacao;
        asteroide66.rotacao += asteroide66.velocidadeRotacao;
        asteroide67.rotacao += asteroide67.velocidadeRotacao;
        asteroide68.rotacao += asteroide68.velocidadeRotacao;
        asteroide69.rotacao += asteroide69.velocidadeRotacao;
        asteroide70.rotacao += asteroide70.velocidadeRotacao;
        asteroide71.rotacao += asteroide71.velocidadeRotacao;
        asteroide72.rotacao += asteroide72.velocidadeRotacao;
        asteroide73.rotacao += asteroide73.velocidadeRotacao;
        asteroide74.rotacao += asteroide74.velocidadeRotacao;
        asteroide75.rotacao += asteroide75.velocidadeRotacao;
        asteroide76.rotacao += asteroide76.velocidadeRotacao;
        asteroide77.rotacao += asteroide77.velocidadeRotacao;
        asteroide78.rotacao += asteroide78.velocidadeRotacao;
        asteroide79.rotacao += asteroide79.velocidadeRotacao;
        asteroide80.rotacao += asteroide80.velocidadeRotacao;
        asteroide81.rotacao += asteroide81.velocidadeRotacao;
        asteroide82.rotacao += asteroide82.velocidadeRotacao;
        asteroide83.rotacao += asteroide83.velocidadeRotacao;
        asteroide84.rotacao += asteroide84.velocidadeRotacao;
        asteroide85.rotacao += asteroide85.velocidadeRotacao;
        asteroide86.rotacao += asteroide86.velocidadeRotacao;
        asteroide87.rotacao += asteroide87.velocidadeRotacao;
        asteroide88.rotacao += asteroide88.velocidadeRotacao;
        asteroide89.rotacao += asteroide89.velocidadeRotacao;
        asteroide90.rotacao += asteroide90.velocidadeRotacao;
        asteroide91.rotacao += asteroide91.velocidadeRotacao;
        asteroide92.rotacao += asteroide92.velocidadeRotacao;
        asteroide93.rotacao += asteroide93.velocidadeRotacao;
        asteroide94.rotacao += asteroide94.velocidadeRotacao;
        asteroide95.rotacao += asteroide95.velocidadeRotacao;

        Desenha();
    }

    desenharOrbitas();

    //Deslocamento para camera 4
    if(camera4Ligada == true && (posicaoCameraX != posicaoCamera4X || posicaoCameraY != posicaoCamera4Y || posicaoCameraZ != posicaoCamera4Z)){
            if(posicaoCameraX < posicaoCamera4X){
                posicaoCameraX += incrementoX;
            }
            else if(posicaoCameraX > posicaoCamera4X){
                posicaoCameraX -= incrementoX;
            }
            if(posicaoCameraZ < posicaoCamera4Z){
                posicaoCameraZ += incrementoZ;
            }
            else if(posicaoCameraZ > posicaoCamera4Z){
                posicaoCameraZ -= incrementoZ;
            }
            if(posicaoCameraY < posicaoCamera4Y){
                posicaoCameraY += incrementoY;
            }
            else if(posicaoCameraY > posicaoCamera4Y){
                posicaoCameraY -= incrementoY;
            }
        }

        //Deslocamento para camera 1
        if(camera1Ligada == true && (posicaoCameraX != posicaoCamera1X || posicaoCameraY != posicaoCamera1Y || posicaoCameraZ != posicaoCamera1Z)){
            if(posicaoCameraX < posicaoCamera1X){
                posicaoCameraX += incrementoX;
            }
            else if(posicaoCameraX > posicaoCamera1X){
                posicaoCameraX -= incrementoX;
            }
            if(posicaoCameraZ < posicaoCamera1Z){
                posicaoCameraZ += incrementoZ;
            }
            else if(posicaoCameraZ > posicaoCamera1Z){
                posicaoCameraZ -= incrementoZ;
            }
            if(posicaoCameraY < posicaoCamera1Y){
                posicaoCameraY += incrementoY;
            }
            else if(posicaoCameraY > posicaoCamera1Y){
                posicaoCameraY -= incrementoY;
            }
        }

        //Deslocamento para camera 2
        if(camera2Ligada == true && (posicaoCameraX != posicaoCamera2X || posicaoCameraY != posicaoCamera2Y || posicaoCameraZ != posicaoCamera2Z)){
            if(posicaoCameraX < posicaoCamera2X){
                posicaoCameraX += incrementoX;
            }
            else if(posicaoCameraX > posicaoCamera2X){
                posicaoCameraX -= incrementoX;
            }
            if(posicaoCameraZ < posicaoCamera2Z){
                posicaoCameraZ += incrementoZ;
            }
            else if(posicaoCameraZ > posicaoCamera2Z){
                posicaoCameraZ -= incrementoZ;
            }
            if(posicaoCameraY < posicaoCamera2Y){
                posicaoCameraY += incrementoY;
            }
            else if(posicaoCameraY > posicaoCamera2Y){
                posicaoCameraY -= incrementoY;
            }
        }


    EspecificaParametrosVisualizacao();
    glutPostRedisplay();


    glutTimerFunc(periodo, Animacao, periodo);
}

void teclado(unsigned char key, int x, int y) {
   switch(key){
       case 'p':
           if(animacaoOn == true){
                animacaoOn = false;
           }
           else if(animacaoOn == false && olharJupiter == false && olharMarte == false && olharMercurio == false && olharNetuno == false
                   && olharSaturno == false && olharTerra == false && olharUranos == false && olharVenus == false){
                animacaoOn = true;
           }
        break;

       case 'z':
           if(mostrarNomesPlanetas == true){
                mostrarNomesPlanetas = false;
           }
           else{
                mostrarNomesPlanetas = true;
           }
        break;

       case 49: //1
            if(olharMercurio){
                olharMercurio = false;
                posicaoCameraX = posicaoCameraX_antigo;
                posicaoCameraY = posicaoCameraY_antigo;
                posicaoCameraZ = posicaoCameraZ_antigo;
            }
            else{
                olharMercurio = true;
                posicaoCameraX_antigo = posicaoCameraX;
                posicaoCameraY_antigo = posicaoCameraY;
                posicaoCameraZ_antigo = posicaoCameraZ;
                animacaoOn = false;
                olharVenus = false;
            }
        break;

       case 50: //2
            if(olharVenus){
                olharMercurio = false;
                posicaoCameraX = posicaoCameraX_antigo;
                posicaoCameraY = posicaoCameraY_antigo;
                posicaoCameraZ = posicaoCameraZ_antigo;
            }
            else{
                olharVenus = true;
                posicaoCameraX_antigo = posicaoCameraX;
                posicaoCameraY_antigo = posicaoCameraY;
                posicaoCameraZ_antigo = posicaoCameraZ;
                animacaoOn = false;
                olharMercurio = false;
            }
            break;

       case 'i':
            if(iluminacaoEstaLigada){
                iluminacaoEstaLigada = false;
                comLuzDoSolOn = false;
            }
            else{
                iluminacaoEstaLigada = true;
            }
            break;

       case 'I':
           if(iluminacaoEstaLigada){
                tipoIluminacao++;
                if(tipoIluminacao == 3){
                    tipoIluminacao = 0;
                }
           }
            break;

       case 'o':
        if(verOrbitas == true){
            verOrbitas = false;
        }
        else{
            verOrbitas = true;
        }
        break;

       case 's':
        if(comLuzDoSolOn && !iluminacaoEstaLigada){
            comLuzDoSolOn = false;
        }
        else if(!comLuzDoSolOn && !iluminacaoEstaLigada){
            comLuzDoSolOn = true;
        }
        break;

       case 'a':
        if(planoOrbitalAtivado){
            planoOrbitalAtivado = false;
        }
        else{
            planoOrbitalAtivado = true;
        }
        break;
   }

   glutPostRedisplay();
}

void teclasEspeciais(int key, int x, int y){ //Função que nos permite usar teclas especiais, como, neste caso, as setas
    if(key == GLUT_KEY_UP){
        camera1Ligada = true;
        camera4Ligada = false;
        camera3Ligada = false;
        camera2Ligada = false;
        posicaoOlharX = 0;
        posicaoOlharY = 0;
        posicaoOlharZ = 0;
    }
    if(key == GLUT_KEY_DOWN){
        camera4Ligada = true;
        camera3Ligada = false;
        camera2Ligada = false;
        camera1Ligada = false;
        posicaoOlharX = 0;
        posicaoOlharY = 0;
        posicaoOlharZ = 0;
    }
    if(key == GLUT_KEY_LEFT){
        camera4Ligada = false;
        camera3Ligada = false;
        camera2Ligada = true;
        camera1Ligada = false;
        posicaoOlharX = 0;
        posicaoOlharY = 0;
        posicaoOlharZ = 0;
    }
    if(key == GLUT_KEY_HOME){
        if(posicaoOlharZ < 100){
            posicaoOlharZ += 5;
            camera1Ligada = false;
            camera2Ligada = false;
            camera3Ligada = false;
            camera4Ligada = false;
        }
    }

    if(key == GLUT_KEY_END){
        if(posicaoOlharZ > -50){
            posicaoOlharZ -= 5;
            camera1Ligada = false;
            camera2Ligada = false;
            camera3Ligada = false;
            camera4Ligada = false;
        }
    }

    if(key == GLUT_KEY_PAGE_DOWN){
        if(posicaoOlharX > -20){
            posicaoOlharX -= 5;
            camera1Ligada = false;
            camera2Ligada = false;
            camera3Ligada = false;
            camera4Ligada = false;
        }
    }

    if(key == GLUT_KEY_PAGE_UP){
        if(posicaoOlharX < 100){
            posicaoOlharX += 5;
            camera1Ligada = false;
            camera2Ligada = false;
            camera3Ligada = false;
            camera4Ligada = false;
        }
    }

    if(key == GLUT_KEY_F2){
        if(posicaoOlharY > -20){
            posicaoOlharY -= 5;
            camera1Ligada = false;
            camera2Ligada = false;
            camera3Ligada = false;
            camera4Ligada = false;
        }
    }

    if(key == GLUT_KEY_F1){
        if(posicaoOlharY < 100){
            posicaoOlharY += 5;
            camera1Ligada = false;
            camera2Ligada = false;
            camera3Ligada = false;
            camera4Ligada = false;
        }
    }

    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 20) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 100) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Programa Principal
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
	glutInitWindowSize(750, 500);
	glutCreateWindow("TP2 - Sistema Solar");
	glShadeModel(GL_SMOOTH);
	Inicializa();
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasEspeciais);
	glutMouseFunc(GerenciaMouse);
	glutTimerFunc(0, Animacao, 30);

	glutMainLoop();
	return 0;
}
