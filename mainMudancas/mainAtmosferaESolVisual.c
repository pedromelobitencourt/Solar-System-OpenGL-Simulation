#include <GL/glew.h>
#include <GL/freeglut.h>
#include <gl/glut.h>
#include <stdio.h>
#include <string.h>
#include <math.h> //Tava tentando usar para camera mover junto com o planeta escolhido
#include "carregartextura.h"

#define LARGURA 750
#define ALTURA 500
#define INCREMENTO_PLANO 0.7


//Pedro Vitor Melo Bitencourt
//Site texturas: https://www.solarsystemscope.com/textures/

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

GLfloat angle, fAspect;

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
GLdouble posicaoCamera4X = 75;//

GLdouble posicaoCameraZ = posicaoCamera4Z;
GLdouble posicaoCameraY = posicaoCamera4Y;
GLdouble posicaoCameraX = posicaoCamera4X;

GLdouble incrementoX = 1;
GLdouble incrementoY = 1;
GLdouble incrementoZ = 1;

GLdouble distanciaDoPlaneta = 5;

bool animacaoOn = true;
bool camera1Ligada = false;
bool camera2Ligada = false;
bool camera3Ligada = false;
bool camera4Ligada = true;
bool precisaRotacionar = false;
bool estaPausado = false;

bool mostrarNomesPlanetas = false;

GLdouble posicaoCameraX_antigo;
GLdouble posicaoCameraY_antigo;
GLdouble posicaoCameraZ_antigo;

///Visitar os planetas

bool olharMercurio = false;
bool olharVenus = false;
bool olharTerra = false;
bool olharMarte = false;
bool olharJupiter = false;
bool olharSaturno = false;
bool olharUranos = false;
bool olharNetuno = false;

///

bool verOrbitas = true;

bool comLuzDoSolOn = false;

bool planoOrbitalAtivado = false;

bool iluminacaoEstaLigada = false;
int tipoIluminacao = 0;

GLuint texturaDoSol;
GLuint texturaDasEstrelas; //Fundo
GLuint texturaSuperficieTerra;
GLuint texturaAtmosferaTerra;



GLuint carregaTextura(Textura* imagemBMP) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagemBMP->altura, imagemBMP->largura, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemBMP->pixels);
	return textureId;
}

void fazerPlano(){ //Tem que arrumar certinho
    int controleTempo = 0;
    int controleTempo1 = 0;
    double Xc = -100;
    double Zc = -100;

    double Xc_antigo = Xc;
    double Zc_antigo = Zc;

    double A[] = {Xc, 0, Zc};
    double B[] = {Xc, 0, Zc + INCREMENTO_PLANO};
    double C[] = {Xc + INCREMENTO_PLANO, 0, Zc};
    glColor3f(1, 1, 1);

    ///Horizontal
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 700; j++){
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
        //double A[] = {Xc, 0, Zc};
        //double B[] = {Xc, 0, Zc + incremento};
        //double C[] = {Xc + incremento, 0, Zc};
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

    ///Vertical

    A[0] = Xc_antigo;
    A[1] = 0;
    A[2] = Zc_antigo;

    B[0] = Xc_antigo;
    B[1] = 0;
    B[2] = Zc_antigo + INCREMENTO_PLANO;

    C[0] = Xc_antigo + INCREMENTO_PLANO;
    C[1] = 0;
    C[2] = Zc_antigo;

    for(int k = 0; k < 500; k++){
        for(int l = 0; l < 600; l++){
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

    //glutSwapBuffers();
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
    }

    ///Plano atrás do Sistema Solar
    //Não estou conseguindo arrumar (aperta seta para esquerda e tem buracos. Caso não veja, aperta 'a')
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaDasEstrelas);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin(GL_POLYGON);
            glTexCoord2f(-1.0, 0.0); glVertex3f(90, -90, -200);
            glTexCoord2f(2.0, 2.0); glVertex3f(90, -90, 200);
            glTexCoord2f(2.0, 0.0); glVertex3f(90, 120, -200);
            glTexCoord2f(-1.0, 2.0); glVertex3f(90, 120, 200);
        glEnd();
        glDisable(GL_TEXTURE_2D);


}

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
EsferasEspaciais marte;
EsferasEspaciais jupiter;
EsferasEspaciais saturno;
EsferasEspaciais uranos;
EsferasEspaciais netuno;
EsferasEspaciais lua;

struct Asteroide{
    double distancia;
    double rotacao;
    double velocidadeRotacao;
    int tipo; //Se 1 == icosaedro, Se 2 == ..., Se 3 == ...
};

Asteroide asteroide1;
Asteroide asteroide2;
Asteroide asteroide3;
Asteroide asteroide4;
Asteroide asteroide5;
Asteroide asteroide6;



void desenharSatelitesNaturais(double raio, double distancia, double inclinacaoX, double anguloRotacaoNoProprioEixo, double orbita, char *nome, bool verEsfera){
    glPushMatrix(); //Sistema padrão de coordenadas
    glColor3f(1, 1, 1);
    glRotatef(orbita, 0, 1, 0);
    glTranslatef(distancia , 0, 0);//angulo, x, y, z

    glPushMatrix();
    glPopMatrix();


    //glTranslatef(2, 0, 0);
    glRotatef(anguloRotacaoNoProprioEixo, 0, 1, 0);
    //glRotatef(orbita, 0, 1, 0);

    glutSolidSphere(raio, 180, 180);




    //glColor3f(1.0, 1.0, 1.0);

    //glutSolidSphere(raio, 180, 180);

    //glPopMatrix();
    glPopMatrix();

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

void desenharEsfera(double raio, double distancia, double inclinacaoX, double anguloRotacaoNoProprioEixo, double orbita, char *nome, bool verEsfera){
    //g//lMatrixMode(GL_TEXTURE);
    //glLoadIdentity();
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); //Sistema padrão de coordenadas
    glColor3f(0, 1, 0);
    glRotatef(orbita, 0, 1, 0);
    glTranslatef(distancia , 0, 0);//angulo, x, y, z

    //Colocar if's para ver qual esfera é para carregar as texturas e cores certas

    glPushMatrix();

    //glColor3f(0, 1, 0);
    glRotatef(inclinacaoX, 1, 0, 0); //angulo, x, y, z
    glRotatef(anguloRotacaoNoProprioEixo, 0, 1, 0);
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


     //Colocamos textura

    if(strcmp(nome, "Sol") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        //glEnable(GL_TEXTURE_2D);
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


        //glDisable(GL_BLEND);
        //glDisable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);

        glColor4f(1, 1, 0, 0.15);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gluSphere(quadric, raio * 1.025, 20, 20);


        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
    else if(strcmp(nome, "Terra") == 0){
        GLUquadric *quadric = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0, 1.0, 1.0);
        //glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturaSuperficieTerra);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(quadric, 1);
        gluSphere(quadric, raio, 20, 20);
        //glDisable(GL_TEXTURE_2D);


        //glDisable(GL_BLEND);
        //glDisable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);
        //texturaAtmosferaTerra
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


    //glColor3f(1.0, 1.0, 1.0);

    //glutSolidSphere(raio, 180, 180);

    glPopMatrix();
    glPopMatrix();



    glColor3f(0, 1, 1);
    if(mostrarNomesPlanetas){
        glRasterPos3f(0, raio + 2, 0);
        for(int i = 0; i < strlen(nome); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, nome[i]);
        }
    }

    glPopMatrix();
}

///Escrever alguma coisa na tela, slá
// Tá piscando, queria escrever slá: "Passaram-se 3 dias e 2 horas" ou se está pausado, com iluminação on ou off
void escreverNaTela(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0, ALTURA, 0, LARGURA);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(200, 200);
    char texte[] = "Eita"; //Testando
    for(int i = 0; i < strlen(texte); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texte[i]);
    }

    //glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void desenharOrbitas(){
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(90, 1, 0, 0);
    //glPushMatrix();
        //glRotatef(90, 1, 0, 0);
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

// Função callback chamada para fazer o desenho
void Desenha(void)
{

    //glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpar a tela para que não tenha as antigas esferas que antes foram desenhadas
	//glColor3f(0.0f, 0.0f, 1.0f);

	desenharSkyboxes();
	if(planoOrbitalAtivado){
        fazerPlano();
	}
    if(verOrbitas){
        desenharOrbitas();
    }


	desenharEsfera(mercurio.raio, mercurio.distanciaAteOSol, mercurio.inclinacaoX, mercurio.anguloRotacaoNoProprioEixo, mercurio.orbita, mercurio.nome, olharMercurio);
	desenharEsfera(venus.raio, venus.distanciaAteOSol, venus.inclinacaoX, venus.anguloRotacaoNoProprioEixo, venus.orbita, venus.nome, olharVenus);
	desenharEsfera(terra.raio, terra.distanciaAteOSol, terra.inclinacaoX, terra.anguloRotacaoNoProprioEixo, terra.orbita, terra.nome, olharTerra);
	desenharSatelitesNaturais(lua.raio, lua.distanciaAteOSol, lua.inclinacaoX, lua.anguloRotacaoNoProprioEixo, lua.orbita, lua.nome, false);
	desenharEsfera(marte.raio, marte.distanciaAteOSol, marte.inclinacaoX, marte.anguloRotacaoNoProprioEixo, marte.orbita, marte.nome, olharMarte);
	desenharEsfera(jupiter.raio, jupiter.distanciaAteOSol, jupiter.inclinacaoX, jupiter.anguloRotacaoNoProprioEixo, jupiter.orbita, jupiter.nome, olharJupiter);
	desenharEsfera(saturno.raio, saturno.distanciaAteOSol, saturno.inclinacaoX, saturno.anguloRotacaoNoProprioEixo, saturno.orbita, saturno.nome, olharSaturno);
	desenharEsfera(uranos.raio, uranos.distanciaAteOSol, uranos.inclinacaoX, uranos.anguloRotacaoNoProprioEixo, uranos.orbita, uranos.nome, olharUranos);
	desenharEsfera(netuno.raio, netuno.distanciaAteOSol, netuno.inclinacaoX, netuno.anguloRotacaoNoProprioEixo, netuno.orbita, netuno.nome, olharNetuno);
	desenharEsfera(sol.raio, sol.distanciaAteOSol, sol.inclinacaoX, sol.anguloRotacaoNoProprioEixo, sol.orbita, sol.nome, false);

	desenharAsteroides(asteroide1.distancia, asteroide1.rotacao, asteroide1.tipo);
	desenharAsteroides(asteroide2.distancia, asteroide2.rotacao, asteroide2.tipo);
	desenharAsteroides(asteroide3.distancia, asteroide3.rotacao, asteroide3.tipo);
	desenharAsteroides(asteroide4.distancia, asteroide4.rotacao, asteroide4.tipo);
	desenharAsteroides(asteroide5.distancia, asteroide5.rotacao, asteroide5.tipo);
	desenharAsteroides(asteroide6.distancia, asteroide6.rotacao, asteroide6.tipo);

    //escreverNaTela();
	// Executa os comandos OpenGL
	glutSwapBuffers();
 }

// Inicializa parâmetros de rendering
void Inicializa (void){

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Textura* solTextura = carregarImagemBMP("Sol.bmp");
	texturaDoSol = carregaTextura(solTextura);
	delete solTextura;

	Textura* estrelaTextura = carregarImagemBMP("Estrelas_SkyBoxes.bmp");
	texturaDasEstrelas = carregaTextura(estrelaTextura);
	delete estrelaTextura;

	//texturaMarteAtmosfera

    Textura* superficieTerraTextura = carregarImagemBMP("Terra.bmp");
    texturaSuperficieTerra = carregaTextura(superficieTerraTextura);
    delete superficieTerraTextura;

    Textura* atmosferaTerraTextura = carregarImagemBMP("Atmosfera.bmp");
    texturaAtmosferaTerra = carregaTextura(atmosferaTerraTextura);
    delete atmosferaTerraTextura;

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
    //terra.velocidadeRotacao = 24.3;

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
    marte.velocidadeRotacao = 23.328;

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
    saturno.velocidadeRotacao = 53.01;

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

    asteroide1.distancia = (marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2;
    asteroide1.rotacao = 0;
    asteroide1.velocidadeRotacao = 0.875;
    asteroide1.tipo = 1;

    asteroide2.distancia = (marte.distanciaAteOSol + jupiter.distanciaAteOSol)/2;
    asteroide2.rotacao = 20;
    asteroide2.velocidadeRotacao = 0.875;
    asteroide2.tipo = 1;

    asteroide3.distancia = (saturno.distanciaAteOSol + jupiter.distanciaAteOSol)/2;
    asteroide3.rotacao = 93;
    asteroide3.velocidadeRotacao = 0.875;
    asteroide3.tipo = 2;

    asteroide4.distancia = (saturno.distanciaAteOSol + jupiter.distanciaAteOSol)/2;
    asteroide4.rotacao = 47;
    asteroide4.velocidadeRotacao = 0.875;
    asteroide4.tipo = 2;

    asteroide5.distancia = (saturno.distanciaAteOSol + uranos.distanciaAteOSol)/2;
    asteroide5.rotacao = 23;
    asteroide5.velocidadeRotacao = 0.875;
    asteroide5.tipo = 3;

    asteroide6.distancia = (saturno.distanciaAteOSol + uranos.distanciaAteOSol)/2;
    asteroide6.rotacao = 70;
    asteroide6.velocidadeRotacao = 0.875;
    asteroide6.tipo = 1;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    angle = 80;
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

/*void ligaDesligaMudaIluminacao(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float iluminacaoDifusaEEspecular[] = {1, 1, 1, 1};
    float iluminacaoAmbiente[] = {0, 0, 0, 1};
    float iluminacaoEmissiva[] = {0.5, 0.5, 0.5, 1};
    float posicaoDaIluminacao[] = {0, -2, 85, 1};
    float direcaoDaLuzNaIluminacao[] = {1, 0, 0};
    float anguloFonteDeLuz = 150;
    float atenuacaoDaIluminacao = 1.0;

    //glEnable(GL_LIGHT0);
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}*/

void ligaDesligaMudaIluminacao(){
    /*if(iluminacaoEstaLigada){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else{
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        }*/

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float iluminacaoDifusaEEspecular[] = {0, 0, 0, 0};
    float iluminacaoAmbiente[] = {0, 0, 0, 0};
    float iluminacaoEmissiva[] = {0, 0, 0, 0};
    float posicaoDaIluminacao[] = {0, 0, 0, 0};
    float direcaoDaLuzNaIluminacao[] = {0, 0, 0};
    float anguloFonteDeLuz = 0;
    float atenuacaoDaIluminacao = 0;

    if(iluminacaoEstaLigada){
        if(tipoIluminacao == 0){
            printf("Chegou iluminacao 0");
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

            //iluminacaoDifusaEEspecular = {1, 1, 1, 1};
            //iluminacaoAmbiente = {0, 0, 0, 1};
            //iluminacaoEmissiva = {0.5, 0.5, 0.5, 1};
            //posicaoDaIluminacao = {0, 85, 12, 0};
            //direcaoDaLuzNaIluminacao = {1, 0, 0};

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
        else if(tipoIluminacao == 1){
            printf("Chegou iluminacao 1");
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
        else if(tipoIluminacao == 2){
            printf("Chegou iluminacao 2");
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
    else if(!iluminacaoEstaLigada && comLuzDoSolOn == true){
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
    else if(!iluminacaoEstaLigada && !comLuzDoSolOn){
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }



    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Animacao(int periodo){
    //glMatrixMode(GL_PROJECTION);

    ligaDesligaMudaIluminacao();

    if(animacaoOn == true){
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

        jupiter.orbita += jupiter.velocidadeDaOrbita;
        jupiter.anguloRotacaoNoProprioEixo += jupiter.velocidadeRotacao;

        saturno.orbita += saturno.velocidadeDaOrbita;
        saturno.anguloRotacaoNoProprioEixo += saturno.velocidadeRotacao;

        uranos.orbita += uranos.velocidadeDaOrbita;
        uranos.anguloRotacaoNoProprioEixo += uranos.velocidadeRotacao;

        netuno.orbita += netuno.velocidadeDaOrbita;
        netuno.anguloRotacaoNoProprioEixo += netuno.velocidadeRotacao;

        asteroide1.rotacao += asteroide1.velocidadeRotacao;
        asteroide2.rotacao += asteroide2.velocidadeRotacao;
        asteroide3.rotacao += asteroide2.velocidadeRotacao;
        asteroide4.rotacao += asteroide2.velocidadeRotacao;
        asteroide5.rotacao += asteroide2.velocidadeRotacao;
        asteroide6.rotacao += asteroide2.velocidadeRotacao;

        Desenha();


        //EspecificaParametrosVisualizacao();
        //glutPostRedisplay();
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

// Programa Principal
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
	glutInitWindowSize(750, 500);
	glutCreateWindow("Visualizacao 3D");
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
