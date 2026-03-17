#include <GL/glut.h>
  
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
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

	// Draw something  

	// white
	glColor3f(0.0f, 1.0f, 0.0f);  

	// Main Body  
	// ...

	// floor
	glPushMatrix(); // save transform matrix state
		glTranslatef(0.0f, -1.30f, 0.0f);
		glutSolidCube(3.0f);
      glRotatef(30,0.0f,0.0f,0.0f);
      glTranslatef(0.0f, -2.7f, 0.0f);
      glutSolidCube(8.0);
	glPopMatrix(); // restore transform matrix state

	// walls
	glColor3f(0.5f, 0.5f, 0.5f);  
	glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.5f);
      glScalef(2.0f, 1.0f, 0.5f); 
      glutWireCube(0.5f);

	glPopMatrix();  

   glColor3f(0.5f, 0.5f, 0.5f);  
	glPushMatrix();
		glTranslatef(0.0f, 0.5f, -0.5f);
      glScalef(2.0f, 1.0f, 0.5f); 
      glutWireCube(0.5f);
	glPopMatrix();  

   glPushMatrix();
   glTranslated(0.48f,0.78f,-0.4f);
   glutSolidCube(0.05);
      for (float i = 0; i < 1.0; i = i+0.1374)
      {
         glPushMatrix();
         glTranslatef(-i,0.0f,0.0f);
         glutSolidCube(0.05);
         glPopMatrix();
         
         
      }

   glPopMatrix();

      glPushMatrix();
   glTranslated(0.48f,0.78f,-0.6f);
   glutSolidCube(0.05);
      for (float i = 0; i < 1.0; i = i+0.1374)
      {
         glPushMatrix();
         glTranslatef(-i,0.0f,0.0f);
         glutSolidCube(0.05);
         glPopMatrix();
         
         
      }

   glPopMatrix();

	// Eyes (black)
// glColor, glPushMatrix,...

	// Hat

	// Hat brim
          
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

