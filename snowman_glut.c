//comando para rodar no terminal Mac:
//g++ main.cpp -o app -framework GLUT -framework OpenGL -Wno-deprecated && ./app

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <time.h>

#define MAX_PARTICLES 1000

// 1. Estrutura atualizada com estado de "descanso"
struct Particle {
    float x, y, z;
    float velocity;
    float stopY;       // Altura exata em que esta partícula vai parar (gera relevo irregular)
    int restingFrames; // Contador de quanto tempo ela fica no chão
    bool isResting;    // Define se ela está caindo ou parada no chão
};

Particle snow[MAX_PARTICLES];

static GLfloat yRot = 0.0f;

// 2. Nova inicialização
void InitSnow() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        snow[i].x = ((float)rand() / RAND_MAX) * 12.0f - 6.0f;
        snow[i].y = ((float)rand() / RAND_MAX) * 10.0f + 2.0f;
        snow[i].z = ((float)rand() / RAND_MAX) * 15.0f - 12.0f;
        snow[i].velocity = ((float)rand() / RAND_MAX) * 0.015f + 0.005f; 
        
        // Define a altura que vai parar (Y=-1.2 do chão + variação de 0 até 0.3 para simular o acúmulo)
        snow[i].stopY = -1.2f + ((float)rand() / RAND_MAX) * 0.3f; 
        snow[i].isResting = false;
        snow[i].restingFrames = 0;
    }
}

// 3. Nova lógica de física e acúmulo
void UpdateSnow() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!snow[i].isResting) {
            snow[i].y -= snow[i].velocity; // A neve cai
            
            // Verifica se bateu na altura do chão calculada para ela
            if (snow[i].y <= snow[i].stopY) {
                snow[i].isResting = true;
                snow[i].y = snow[i].stopY; // Trava a posição no chão
                
                // Define um tempo aleatório para ficar parada (entre 100 e 350 frames)
                snow[i].restingFrames = 100 + rand() % 250; 
            }
        } else {
            // Se já está no chão, diminui o tempo de vida dela ali
            snow[i].restingFrames--;
            
            // Quando o tempo acaba, ela "derrete" e ressurge lá no topo
            if (snow[i].restingFrames <= 0) {
                snow[i].isResting = false;
                snow[i].y = 5.0f + ((float)rand() / RAND_MAX) * 5.0f; // Volta pro alto
                snow[i].x = ((float)rand() / RAND_MAX) * 12.0f - 6.0f;
                snow[i].z = ((float)rand() / RAND_MAX) * 15.0f - 12.0f;
                snow[i].stopY = -1.2f + ((float)rand() / RAND_MAX) * 0.3f; // Sorteia novo ponto de parada
            }
        }
    }
    glutPostRedisplay();
}

void ChangeSize(int w, int h) {  
    GLfloat fAspect;  
    if(h == 0) h = 1;  
    glViewport(0, 0, w, h);  
    fAspect = (GLfloat)w/(GLfloat)h;  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  
  
void SetupRC(){  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    
    glFrontFace(GL_CCW);        
    glEnable(GL_CULL_FACE);     
  
    glEnable(GL_LIGHTING);  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    glEnable(GL_COLOR_MATERIAL);  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  
}  
  
void SpecialKeys(int key, int x, int y){  
    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  
    glutPostRedisplay();  
}
  
void RenderScene(void){  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // --- DESENHA A NEVE PRIMEIRO ---
    glPushMatrix(); 
    glDisable(GL_LIGHTING); 
    glColor3f(1.0f, 1.0f, 1.0f); 
    glPointSize(2.5f); 
    
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        glVertex3f(snow[i].x, snow[i].y, snow[i].z);
    }
    glEnd();
    
    glEnable(GL_LIGHTING); 
    glPopMatrix(); 

    // --- DESENHA O BONECO E O CHÃO ---
    glPushMatrix();

    glTranslatef(0.0f, -0.5f, -6.0f);  
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

    glColor3f(1.0f, 1.0f, 1.0f);  

    // Floor 
    glPushMatrix();
        glTranslatef(0.0f, -10.7, 0.0f);
        glutSolidCube(20);
    glPopMatrix();

    // Head
    glPushMatrix(); 
        glTranslatef(0.0f, 1.0f, 0.0f);
        glutSolidSphere(0.24f, 26, 13);
    glPopMatrix(); 

    glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.0f);
        glutSolidSphere(0.36f,26,13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -0.24f, 0.0f);
        glutSolidSphere(0.45f,26,13);
    glPopMatrix();

    // Nose
    glColor3f(1.0f, 0.4f, 0.51f);  
    glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.2f);
        glutSolidCone(0.04f, 0.3f, 26, 13);
    glPopMatrix();  

    // Eyes
    glColor3f(0.0f,0.0f,0.0f);
    glPushMatrix();
        glTranslatef(0.075f,1.1f,0.2f);
        glutSolidSphere(0.05f,26,13);
    glPopMatrix();

    glColor3f(0.0f,0.0f,0.0f);
    glPushMatrix();
        glTranslatef(-0.075f,1.1f,0.2f);
        glutSolidSphere(0.05f,26,13);
    glPopMatrix();

    // Hat
    glPushMatrix();
        glTranslatef(0.0f,1.2f,0.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        GLUquadricObj *pObj = gluNewQuadric(); 
        gluQuadricDrawStyle(pObj, GLU_FILL);   
        gluCylinder(pObj, 0.20f,0.20f,0.4f,26,23);
    glPopMatrix();

    glColor3f(1.0f,0.0f,0.0f);
    glPushMatrix();
        glTranslatef(0.0f,1.25f,0.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);   
        gluCylinder(pObj, 0.21f,0.21f,0.1f,26,23);
    glPopMatrix();

    // Hat brim
    glColor3f(0.0f,0.0f,0.0f);
    glPushMatrix();
        glTranslatef(0.0f,1.2,0.0f);
        glScalef(1.0f,0.2f,1.0f);
        glutSolidSphere(0.3f,26,13);
    glPopMatrix();

    // Arms
    glPushMatrix();
        glColor3f(0.4f,0.2f,0.2f);
        glTranslatef(0.3,0.5f,0.0f);
        glRotatef (-90.0f,0.0f,-5.0f,0.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj,0.03f,0.03f,0.4f,26,23);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.4f,0.2f,0.2f);
        glTranslatef(-0.3,0.5f,0.0f);
        glRotatef (-95.0f,0.0f,0.50f,0.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj,0.03f,0.03f,0.4f,26,23);
    glPopMatrix();
          
    glPopMatrix();  
    glutSwapBuffers();  
}    

int main(int argc, char *argv[]){
    srand((unsigned int)time(NULL));
    
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Modeling with Quadrics");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    
    glutIdleFunc(UpdateSnow);
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    InitSnow();
    
    glutMainLoop();  
      
    return 0; 
}
