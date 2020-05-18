#include <stdio.h>
#include <GL/glut.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
char **argv;
int max(int a, int b){
	return a > b ? a:b;
}
int min(int a,int b){
	return a > b ? b:a;
}
void _read(int fd,void *buf,int n){
	int r = 0;
	while(r < n){
		int c= 0x10;
//		while(write(fd,&c,1) != 1);
//		printf("Reading\n");
a:;int cr =read(fd,buf + r,2);
  //		printf("0x%x\n",*(uint16_t *)(buf + r));
		r+=cr;
	
	}
}
void drawFunc(unsigned short *buf,int n){
	glBegin(GL_POINTS);
	int k = 0;
	for(int i = 0; i < n-1;i++){
		glColor3f(0,0,0);
		uint16_t a = buf[i]*5.0/1023.0*10;
		uint16_t b = buf[i+1]*5.0/1023.0*10;
		if(a*5.0/1023.0*10 > 50 || b*5.0/1023.0*10 > 50)
			continue;
		k++;
		for(int j = a; j < b;j+=a > b ? -1 : 1)
			glVertex2i(k,j+250);
		glVertex2i(k,a+250);
	}
	glEnd();
}


//Add a timer callback to post a redisplay every now and again:

void timer( int value )
{
    glutPostRedisplay();
    glutTimerFunc( 16, timer, 0 );
}
void Display();
int argcg;
int pos = 0;
int main(int argc,char **a){
	argv = a;
	FILE *clr;
	if(argc > 3)
		clr = fopen(a[3],"wb");
	if(clr)
		fclose(clr);
	argcg = argc;
	glutInit(&argc,a);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Osciliscope");
	glutDisplayFunc(Display);
	glutTimerFunc( 0, timer, 0 );
	glutMainLoop();

};

void Display(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(5.0f);
	FILE * log = 0;
	int fd = open(argv[1],O_RDWR);
	lseek(fd,pos,SEEK_SET);
	uint8_t *buf = malloc(1000*sizeof(uint16_t));
	int n = read(fd,buf,1000*sizeof(uint16_t));
	pos+=n;;
	if(n == 0)
		pos=0;
	uint16_t *points = malloc(1000*sizeof(uint16_t));
	bzero(points,1000*sizeof(*points));
	for(int i = 0; i < 500;i++){
		points[i] = buf[i*2] << 8 | buf[i*2+1];
	}
	
//	for(int i = 0; i < 500;i++){
//		if(!(i % (int)read == 0)){
//			points[i] = points[i-i%(int)read];
//		}
//	}


	usleep(10000);
	glColor3f(1.0,1.0,1.0);
	glPointSize(1.0f);
	uint8_t *zb = malloc(500*sizeof(uint16_t));
	bzero(zb,1000);
	drawFunc(points,500*sizeof(uint16_t));
	glFlush();
	free(buf);
	free(points);
	
}
