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

    for(int k = 0; k < 55; k++){
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
