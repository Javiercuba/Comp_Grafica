#include "functions.h"



void init(void)
{
int j,i;
    MOUSE_SELECIONADO = false;
    numero_vertices = 0;
    tipoPoligono = GL_POINTS;
 
    
    
    for( i=0; i<numero_vertices; i++)
	{
		float ang = (float)(i) * (2.0 * PHI)/((float)(numero_vertices));
		circulo(70.0, ang, pvertex[i].v);
	}
	for(i=0; i<MAXVERTEXS; i++)
	{
		pvertex[i].v[0] = 0.0f;
		pvertex[i].v[1] = 0.0f;
		pvertex[i].v[2] = 1.0f;
	}
	gAng = (2.0f * PHI)/180.0f;
}

static void Key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    }
}

void processMenuEvents(int option)
{
	
    switch (option)
    {	
    case 2:
    	init();
        break;
    }
    
    glutPostRedisplay();
}


void processSubMenuEvents(int option)
{

	switch(option){
		case 0:
			
		tipoPoligono = GL_POINTS;
		break;
		
		case 1:
		tipoPoligono = GL_LINE_LOOP;
        MOUSE_SELECIONADO = true;
		break;	
		case 2:
		
		break;
	}
    glutPostRedisplay();
}


void subMenu2Events(int option) 
{
	tipo_operacao = option;
	glutPostRedisplay();
}  

static void Args(int argc, char **argv)
{
    GLint i;

    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-sb") == 0)
        {
            doubleBuffer = GL_FALSE;
        }
        else if (strcmp(argv[i], "-db") == 0)
        {
            doubleBuffer = GL_TRUE;
        }
    }
}


void createGLUTMenus()
{
    int menu, submenu,submenu2;

    submenu = glutCreateMenu(processSubMenuEvents);
    glutAddMenuEntry("Pontos", 0);
    glutAddMenuEntry("Poligono Mouse", 1);
    
    submenu2 = glutCreateMenu(subMenu2Events);
	glutAddMenuEntry("Translation",1);
	glutAddMenuEntry("Rotation",2);	
	glutAddMenuEntry("Scale",3);	
	glutAddMenuEntry("Shear",4);
	glutAddMenuEntry("Reflect",5);

    menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Limpar", 2);
    glutAddSubMenu("Tipo Objeto", submenu);
    glutAddSubMenu("Transformacao", submenu2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
	
}


void mouse(int button, int state, int x, int y)
{ 
	if(state == GLUT_UP)       //  botão SOLTO
	{
		if(button == GLUT_LEFT_BUTTON) 
		{
			if(!MOUSE_SELECIONADO)       // ainda não definido o polígono
			{
				x = x - largura_janela; 
				y = altura_janela - y;

				glPointSize(3);

				pvertex[numero_vertices].v[0] = (float)x;
				pvertex[numero_vertices].v[1] = (float)y;
				pvertex[numero_vertices].v[2] = 1.0f;
				numero_vertices++;
			}
		} 		
	}
	else  // state == GLUT_DOWN  --> Botão pressionado
	{
		if(MOUSE_SELECIONADO) {					// polígono já definido
			if(tipo_operacao) {				// Uma ransformacao selecionada
				if(  button == GLUT_LEFT_BUTTON) {
					x = x - largura_janela; 
					y = altura_janela - y;
					// clipingVertex
					gIndVert = clipVertex(x, y);    // verificar e identificar um vértice selecionado
				}
			}
		}
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);
    Args(argc, argv);

    type = GLUT_RGB;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;

    glutInitDisplayMode(type);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Basic Program Using Glut and Gl");

    init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);

    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    //	glutIdleFunc(idle);

    createGLUTMenus();

    glutMainLoop();

    return (0);
}
