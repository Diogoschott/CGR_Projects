//comando para rodar no terminal Mac:
//g++ main.cpp -o app -framework GLUT -framework OpenGL -Wno-deprecated && ./app

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
  
// Rotation
static GLfloat yRot = 0.0f;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h)  
    {  
    GLfloat fAspect;  
    
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    }  
  
  
// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

}  
  
// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  
}
  
// Called to draw scene  
void RenderScene(void){  

    int i;

    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

    // Move object back and do in place rotation  
    glTranslatef(0.0f, 0.0f, -23.0f);  
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

    // Draw something  

    // GRAY
    glColor3f(0.70f, 0.70f, 0.70f);  

    // Main Body  

    glPushMatrix();
        GLUquadricObj *pObj = gluNewQuadric();
        gluQuadricDrawStyle(pObj, GLU_FILL);

        glTranslatef(0.0f, -2.2f, 0.0f);

        // CORPO
        glPushMatrix(); 
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(pObj, 0.8f, 1.0f, 3.0f, 26, 23);

            //OMBRO 1
            glPushMatrix();
                glTranslatef(1.0f, 0.0f, 2.6f); 
                gluSphere(pObj, 0.25, 32, 10);

                //BRAÇO 1
                glPushMatrix();
                    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
                    gluCylinder(pObj, 0.2, 0.2, 1.7, 32, 10);
                    
                    //MARCAS DO BRAÇO
                    glColor3f(.5, .5, .5);
                    for(i = 0; i < 5; i++){
                        glPushMatrix();
                            glTranslatef(0.0, 0.0, 0.2 + 0.30 * i);
                            gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                        glPopMatrix();
                    }
                    glColor3f(0.70f, 0.70f, 0.70f); 

                    //COTOVELO 1
                    glPushMatrix();
                        glTranslatef(0.0f, 0.0f, 1.7f);
                        gluSphere(pObj, 0.2, 31, 10);

                        //ANTEBRAÇO 1
                        glPushMatrix();
                            gluCylinder(pObj, 0.2, 0.2, 1.5, 32, 10);

                            //MARCAS NO ANTEBRAÇO
                            glColor3f(.5, .5, .5);
                            for(i = 0; i < 4; i++){
                                glPushMatrix();
                                    glTranslatef(0.0, 0.0, 0.1 + 0.3 * i);
                                    gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                                glPopMatrix();
                            }

                            //Mao 1 
                            glPushMatrix();
                                glRotatef(180,1.0,0.0,0.0);
                                glTranslatef(0.0,0.0,-1.5);
                                gluCylinder(pObj,0.41,0.21,0.25,26,14);

                                //Palma 1
                                glPushMatrix();
                                    glRotatef(180,1.0,.0,.0);
                                    gluDisk(pObj,.0,.41,32,10);
                                glPopMatrix();

                            glPopMatrix();

                            glColor3f(0.70f, 0.70f, 0.70f); 

                        glPopMatrix();
                    glPopMatrix();

                glPopMatrix();
            glPopMatrix();

            //OMBRO 2
            glPushMatrix();
                glTranslatef(-1.0f, 0.0f, 2.6f); 
                gluSphere(pObj, 0.25, 32, 10);

                //BRAÇO 2
                glPushMatrix();
                    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); 
                    gluCylinder(pObj, 0.2, 0.2, 1.7, 32, 10);
                    
                    //MARCAS DO BRAÇO
                    glColor3f(.5, .5, .5);
                    for(i = 0; i < 5; i++){
                        glPushMatrix();
                            glTranslatef(0.0, 0.0, 0.2 + 0.30 * i);
                            gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                        glPopMatrix();
                    }
                    glColor3f(0.70f, 0.70f, 0.70f); 

                    //COTOVELO 2
                    glPushMatrix();
                        glTranslatef(0.0f, 0.0f, 1.7f);
                        gluSphere(pObj, 0.2, 31, 10);

                        //ANTEBRAÇO 2
                        glPushMatrix();
                            gluCylinder(pObj, 0.2, 0.2, 1.5, 32, 10);

                            //MARCAS NO ANTEBRAÇO
                            glColor3f(.5, .5, .5);
                            for(i = 0; i < 4; i++){
                                glPushMatrix();
                                    glTranslatef(0.0, 0.0, 0.1 + 0.3 * i);
                                    gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                                glPopMatrix();
                            }

                            //Mao 2 
                            glPushMatrix();
                                glRotatef(180,1.0,0.0,0.0);
                                glTranslatef(0.0,0.0,-1.5);
                                gluCylinder(pObj,0.41,0.21,0.25,26,14);

                                glPushMatrix();
                                    glRotatef(180.,1.0,.0,.0);
                                    gluDisk(pObj,.0,.42,32,10);
                                glPopMatrix();
                            glPopMatrix();

                            glColor3f(0.70f, 0.70f, 0.70f); 

                        glPopMatrix();
                    glPopMatrix();

                glPopMatrix();
            glPopMatrix();
            
            //QUADRICEPS 1
            glPushMatrix();
                glTranslatef(-0.3,0.0,0.0);
                glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
                gluCylinder(pObj, 0.2, 0.2, 1.7, 32, 10);
                    
                    //MARCAS DO BRAÇO
                    glColor3f(.5, .5, .5);
                    for(i = 0; i < 5; i++){
                        glPushMatrix();
                            glTranslatef(0.0, 0.0, 0.2 + 0.30 * i);
                            gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                        glPopMatrix();
                    }
                    glColor3f(0.70f, 0.70f, 0.70f); 
                    
                    //JOELHO 1
                    glPushMatrix();
                        glTranslatef(0.0f, 0.0f, 1.7f);
                        gluSphere(pObj, 0.2, 31, 10);

                        //PANTURRILHA 1
                        glPushMatrix();
                            glRotatef(0.0f, 0.0f, 1.0f, 0.0f); 
                            gluCylinder(pObj, 0.2, 0.2, 1.7, 32, 10);
                    
                            //MARCAS DA PANTURRILHA
                            glColor3f(.5, .5, .5);
                            for(i = 0; i < 5; i++){
                                glPushMatrix();
                                    glTranslatef(0.0, 0.0, 0.2 + 0.30 * i);
                                    gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                                glPopMatrix();
                            }   

                            
                            glPushMatrix();
                                glTranslatef(.0,.0,1.7);
                                gluCylinder(pObj,.21,.5,.3,32,10);
                            glPopMatrix();

                            glColor3f(0.70f, 0.70f, 0.70f); 
                        glPopMatrix();

                    glPopMatrix();
            glPopMatrix();


            //QUADRICEPS 2
            glPushMatrix();
                glTranslatef(0.3,0.0,0.0);
                glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
                gluCylinder(pObj, 0.2, 0.2, 1.7, 32, 10);
                    
                    //MARCAS DA PERNA
                    glColor3f(.5, .5, .5);
                    for(i = 0; i < 5; i++){
                        glPushMatrix();
                            glTranslatef(0.0, 0.0, 0.2 + 0.30 * i);
                            gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                        glPopMatrix();
                    }
                    glColor3f(0.70f, 0.70f, 0.70f); 

                    //JOELHO 2
                    glPushMatrix();
                        glTranslatef(0.0f, 0.0f, 1.7f);
                        gluSphere(pObj, 0.2, 31, 10);

                        //PANTURRILHA 2
                        glPushMatrix();
                            glRotatef(0.0f, 0.0f, 1.0f, 0.0f); 
                            gluCylinder(pObj, 0.2, 0.2, 1.7, 32, 10);
                    
                            //MARCAS DA PANTURRILHA
                            glColor3f(.5, .5, .5);
                            for(i = 0; i < 5; i++){
                                glPushMatrix();
                                    glTranslatef(0.0, 0.0, 0.2 + 0.30 * i);
                                    gluCylinder(pObj, 0.21, 0.21, 0.1, 32, 10);
                                glPopMatrix();
                            }

                        glPushMatrix();
                            glTranslatef(.0,.0,1.7);
                            gluCylinder(pObj,.21,.5,.3,32,10);
                        glPopMatrix();

                    glPopMatrix();

                glPopMatrix();

            glPopMatrix();

        glPopMatrix();

        glTranslatef(0.0f, 3.2f, 0.0f);
        
        //Cinza Claro
        glColor3f(0.70f, 0.70f, 0.70f); 

        glPushMatrix();
            // PESCOÇO
            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 
                gluCylinder(pObj, 0.50f, 1.0f, 0.2f, 26, 23);
            glPopMatrix();

            glTranslatef(0.0f, 1.0f, 0.0f);

            glPushMatrix();
                // LATA DA FACE
                glPushMatrix();
                    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 
                    gluCylinder(pObj, 0.60f, 0.60f, 1.0f, 26, 23);

                    //PARTE DOS OLHOS
                    glPushMatrix();
                        glTranslatef(0.0f, 0.3f, 0.0f);
                        
                        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
                        
                        glScalef(1.8f, 1.0f, 1.0f);
                        gluCylinder(pObj, 0.3, 0.3, 0.5, 32, 10);

                        //ESCURO ATRAS DOS OLHOS
                        glPushMatrix();
                            glColor3f(0.0f, 0.0f, 0.0f); // Preto
                            glTranslatef(0.0f, 0.0f, 0.3f);
                            gluDisk(pObj, 0.0, 0.30, 32, 10);
                        glPopMatrix();
                    
                        glScalef(0.5555f, 1.0f, 1.0f);

                        //OLHO 1 (Direito)
                        glPushMatrix();
                            //IRIS AMARELAS
                            glColor3f(1.0f, 0.999f, 0.64f);
                            // Separa os olhos lado a lado no eixo X
                            glTranslatef(0.23f, 0.0f, 0.3f);
                            gluSphere(pObj, 0.23, 32, 10);

                            //PUPILA
                            glColor3f(0.0f, 0.0f, 0.0f);
                            glTranslatef(0.0f, 0.0f, 0.18f);
                            gluSphere(pObj, 0.1, 10, 10);
                        glPopMatrix();
                        
                        //OLHO 2 (Esquerdo)
                        glPushMatrix();
                            //IRIS AMARELAS
                            glColor3f(1.0f, 0.999f, 0.64f);
                            glTranslatef(-0.23f, 0.0f, 0.3f);
                            gluSphere(pObj, 0.23, 32, 10);

                            //PUPILA
                            glColor3f(0.0f, 0.0f, 0.0f);
                            glTranslatef(0.0f, 0.0f, 0.18f);
                            gluSphere(pObj, 0.1, 10, 10);
                        glPopMatrix();
                    glPopMatrix();

                    //Gray again
                    glColor3f(0.70f, 0.70f, 0.70f);  

                glPopMatrix();

                // TOPO DA CABECA
                glPushMatrix();
                    glutSolidSphere(0.6, 26, 13);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0.0f, 0.5f, 0.0f);

                    // ANTENA
                    glPushMatrix();
                        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 
                        gluCylinder(pObj, 0.15f, 0.11f, 0.8f, 10, 23);

                        //BOLA DA ANTENA
                            glPushMatrix();
                                glTranslatef(0.0f,0.0f,0.9f);
                                glutSolidSphere(0.13,32,10);
                            glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix(); 
        glPopMatrix(); 

        gluDeleteQuadric(pObj); // Sempre delete para evitar vazamento de memória
    glPopMatrix(); 

    // Head
    
    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  
}    

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Modeling with Quadrics");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}