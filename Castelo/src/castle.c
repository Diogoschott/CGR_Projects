#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h> 

GLuint loadTexture(const char *file);
void drawDoor(float l , float hBase);
void ChangeSize(int w, int h);
void SetupRC();
void SpecialKeys(int key, int x, int y);
void RenderScene(void);

// Rotation
static GLfloat yRot = 0.0f;
static GLuint textureWood;
static GLuint textureBricks;
static GLuint textureTile;

GLuint loadTexture(const char *file){
    GLuint idTexture;

    glGenTextures(1 , &idTexture);

    glBindTexture(GL_TEXTURE_2D , idTexture);

    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

    int l , h , c;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(file , &l , &h , &c , 0);

    if(data){
        GLenum format = (c == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D , 0 , format , l , h , 0 , format , GL_UNSIGNED_BYTE , data);

        stbi_image_free(data);
    }else
        printf("Error at loading texture %s : %s \n" , file , stbi_failure_reason());

    return idTexture;

} 


void drawDoor(float l , float hBase){
    float radius = l /2.0f , totalHeight = hBase + radius;
    int archesFaces = 20 , i;

    glEnable(GL_TEXTURE_2D); 

    glBindTexture(GL_TEXTURE_2D , textureWood);

    glColor3f(1.0f,1.0f,1.0f);

    glBegin(GL_POLYGON);
    glNormal3f(0.0f,0.0f,1.0f);

    glTexCoord2f(1.0f,0.0f);
    glVertex3f(radius , 0.0f , 0.0f);

    for(i = 0;i <= archesFaces;i++){

        float angle = i * (M_PI/archesFaces);

        float x = radius * cos(angle);
        float y = hBase + (radius * sin(angle));

        float u = (x + radius) / l;
        float v = y / totalHeight;

        glTexCoord2f(u , v);
        glVertex3f(x , y , 0.0f);
    }

    glTexCoord2f(0.0f , 0.0f);
    glVertex3f(-radius , 0.0f , 0.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

}

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

    glEnable(GL_NORMALIZE);
  
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

    textureWood = loadTexture("textures/6464298.jpg");
    textureBricks = loadTexture("textures/bricks.jpg");
    textureTile = loadTexture("textures/telhas.jpg");

}  
  
// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_LEFT)  
        yRot += 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot -= 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);
  
    // Refresh the Window  
    glutPostRedisplay();  
}
  
// Called to draw scene  
void RenderScene(void){
    
    float wallsHeight = 0.8 , bigTowerHeight = 1.3 , littleTowerHeight = 0.7;
    int i , j;

    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -0.8f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

	// Draw something

    //Green
	glColor3f(0.0f , 0.58 , 0.0f);
    
    glPushMatrix();
        glTranslatef(0.0f,-0.2f,0.0f);
        glScalef(4.0f,0.2f,4.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    //LightGray
    glColor3f(0.5f,0.5f,0.5f);

    //Wall1
    glPushMatrix();
        glTranslatef(0.0f,0.1f,1.0f);
        glScalef(2.0f,wallsHeight,0.1f);
        glutSolidCube(1.0f);
    glPopMatrix();

    //Wall2, paralel to 1

    glPushMatrix();
        glTranslatef(0.0f,0.1f,-1.0f);
        glScalef(2.0f,wallsHeight,0.1f);
        glutSolidCube(1.0f);
    glPopMatrix();

    //wall3

    glPushMatrix();
        glTranslatef(1.0f,0.1f,0.0f);
        glScalef(0.1f,wallsHeight,2.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    //wall4, paralel to wall3

    glPushMatrix();
        glTranslatef(-1.0f,0.1f,0.0f);
        glScalef(0.1f,wallsHeight,2.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    //DarkGray

    glColor3f(0.3f,0.3f,0.3f);

    //bricks Wall1 and Wall2

    for(i = 0;i < 13;i++){

        for(j = 0;j < 5;j++){
            glPushMatrix();
                glTranslatef(-0.9f + i * 0.15f,-0.05f + j*0.12f,1.0f);
                glScalef(0.2f , 0.1f , 0.3f);
                glutSolidCube(0.4f);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-0.9f + i * 0.15f,-0.05f + j*0.12f,-1.0f);
                glScalef(0.2f , 0.1f , 0.3f);
                glutSolidCube(0.4f);
            glPopMatrix();
        }

    }

    //bricks Wall3 and Wall4

    for(i = 0;i < 13;i++){

        for(j = 0;j < 5;j++){
            glPushMatrix();
                glTranslatef(1.0f, -0.05f + j*0.12f , -0.9f + i * 0.15f);
                glScalef(0.3f , 0.1f , 0.2f);
                glutSolidCube(0.4f);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(-1.0f, -0.05f + j*0.12f , -0.9f + i * 0.15f);
                glScalef(0.3f , 0.1f , 0.2f);
                glutSolidCube(0.4f);
            glPopMatrix();
        }

    }

    //towers

    GLUquadric *quad = gluNewQuadric();

    gluQuadricTexture(quad , GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D , textureBricks);

    glColor3f(1.0f,1.0f,1.0f);

    glPushMatrix();
        glTranslatef(1.0f,-0.1f,1.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluCylinder(quad , 0.3f , 0.3f , bigTowerHeight , 32 , 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0f,-0.1f,-1.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluCylinder(quad , 0.3f , 0.3f , bigTowerHeight , 32 , 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.0f,-0.1f,-1.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluCylinder(quad , 0.3f , 0.3f , littleTowerHeight , 32 , 1);
    glPopMatrix();
        
    glPushMatrix();
        glTranslatef(-1.0f,-0.1f,1.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluCylinder(quad , 0.3f , 0.3f , littleTowerHeight , 32 , 1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3f(0.3f,0.3f,0.3f);

    glPushMatrix();
        glTranslatef(1.0f,littleTowerHeight - 0.1f,-1.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluDisk(quad , 0.0f , 0.3f , 32 , 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0f,littleTowerHeight - 0.1f,1.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        gluDisk(quad , 0.0f , 0.3f , 32 , 1);
    glPopMatrix();

    //DarkBrown
    glColor3f(0.7f,0.14f,0.0f);

    
    gluQuadricTexture(quad , GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D , textureTile);

    //towers cap

    glPushMatrix();
        glTranslatef(1.0f,bigTowerHeight - 0.2f,1.0f);
        glRotatef(-90.0f , 1.0f , 0.0f ,0.0f);
        gluCylinder(quad , 0.35f , 0.0f , 1.0f , 32 , 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.0f,bigTowerHeight - 0.2f,1.0f);
        glRotatef(90.0f,1.0f,0.0f,0.0f);
        gluDisk(quad , 0.0f , 0.35f , 32 , 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0f,bigTowerHeight - 0.2f,-1.0f);
        glRotatef(-90.0f , 1.0f , 0.0f ,0.0f);
        gluCylinder(quad , 0.35f , 0.0f , 1.0f , 32 , 1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0f,bigTowerHeight - 0.2f,-1.0f);
        glRotatef(90.0f,1.0f,0.0f,0.0f);
        gluDisk(quad , 0.0f , 0.35f , 32 , 1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
        glTranslatef(0.0f,-0.1f,1.16f);
        drawDoor(0.6f,0.5f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,-0.1f,1.15f);
        glRotatef(180.0,0.0f,1.0f,0.0f);
        drawDoor(0.6f,0.5f);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D , 0);

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
