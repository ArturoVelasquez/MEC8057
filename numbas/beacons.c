/* This program finds the intersection of three circles that represent beacons
localitation. It asumes that all the circles just intersec at one point.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float x,y;

float ** get_circles();
void direct_calculation(float circle_1[3],float circle_2[3],float circle_3[3]);
void indirect_calculation(float circle_1[3],float circle_2[3],float circle_3[3]);
void python_print(float circle_1[3],float circle_2[3],float circle_3[3], float x, float y);

int main(){

  float **circle;

  circle = get_circles();

  float circle_1[3]={circle[0][0],circle[0][1],circle[0][2]};
  float circle_2[3]={circle[1][0],circle[1][1],circle[1][2]};
  float circle_3[3]={circle[2][00],circle[2][1],circle[2][2]};

  if (circle_3[0]-circle_1[0]==0 && circle_3[0]-circle_2[0]!=0){
    direct_calculation(circle_1,circle_2,circle_3);
  }
  else if(circle_3[0]-circle_2[0]==0 && circle_3[0]-circle_1[0]!=0){
    direct_calculation(circle_2,circle_1,circle_3);
  }
  else{
    indirect_calculation(circle_1,circle_2,circle_3);
  }
  printf("The point of intersection is ( %f , %f )\n", x, y );
  python_print(circle_1,circle_2,circle_3,x,y);
  return 0;
}


/* This function is to create a 2d array where each row represents a circles
   and the columna are x pisition, y poistion, circle radius.
*/
float ** get_circles(){
  float **circles;
  circles=malloc(sizeof(float*)*3);

  for(int i = 0; i < 3; i++) {
        circles[i] = malloc(sizeof(int*) * 3);
    }

  for(int i=0; i<3;i++){
    printf("Enter X origin position for circle %i. \n",  i+1);
    scanf("%f", &circles[i][0]);
    printf("Enter Y origin position for circle %i. \n", i+1 );
    scanf("%f", &circles[i][1]);
    printf("Enter radius for circle %i. \n", i+1 );
    scanf("%f", &circles[i][2]);
  }
  return circles ;
}

/* This is the general calculation to find the intersection of 3 circles. It is
obtained by writing the circle equation ((x-a)+(y-b)-r=0 where a and b are the
central cordinates of the circle and r the radious) for the three circles. Then
substracting the third equeation from the other two equations.Next solving both
for 'x' and groupng the constant values as a,b,c,d. Lastly equating 'x' to find
'y' and also 'y' to find 'x'.
*/

void indirect_calculation(float circle_1[3],float circle_2[3],float circle_3[3]){
  float a,b,c,d;
  a=(circle_1[1]-circle_3[1])/(circle_3[0]-circle_1[0]);
  c=(circle_2[1]-circle_3[1])/(circle_3[0]-circle_2[0]);
  b=((circle_3[0]*circle_3[0])+(circle_3[1]*circle_3[1])+(circle_1[2]*circle_1[2])-(circle_1[0]*circle_1[0])-(circle_1[1]*circle_1[1])-(circle_3[2]*circle_3[2]))/(2*(circle_3[0]-circle_1[0]));
  d=((circle_3[0]*circle_3[0])+(circle_3[1]*circle_3[1])+(circle_2[2]*circle_2[2])-(circle_2[0]*circle_2[0])-(circle_2[1]*circle_2[1])-(circle_3[2]*circle_3[2]))/(2*(circle_3[0]-circle_2[0]));
  x = (c*b-a*d)/(c-a);
  y = (d-b)/(a-c);
}

/* This function calculates the intersention point for the three imaginary
circle created by the beacons in two of them (third any other) have the same X
coordinate.
The calculation becomes simpler this way also could be done for Y but its not
necesary. The main issue solved by this function is a 0/0 that rises by the
general calculation if is solved for y first.
*/
void direct_calculation(float circle_1[3],float circle_2[3],float circle_3[3]){
  y = ((circle_1[0]*circle_1[0])+(circle_1[1]*circle_1[1])+(circle_3[2]*circle_3[2])-(circle_3[0]*circle_3[0])-(circle_3[1]*circle_3[1])-(circle_1[2]*circle_1[2]))/(2*(circle_1[1]-circle_3[1]));
  x = ((circle_3[0]*circle_3[0])+(circle_3[1]*circle_3[1])+(circle_2[2]*circle_2[2])-(circle_2[0]*circle_2[0])-(circle_2[1]*circle_2[1])-(circle_3[2]*circle_3[2])-y*2*(circle_3[1]-circle_2[1]))/(2*(circle_3[0]-circle_2[0]));
}

void python_print(float circle_1[3],float circle_2[3],float circle_3[3], float x, float y){
  char run_this[200]="python3 beacons.py ";
  char circle_str_1[60],circle_str_2[60],circle_str_3[60],x_position[15],y_position[15];

  float *c1=&circle_1[0];
  float *c2=&circle_2[0];
  float *c3=&circle_3[0];

  sprintf(circle_str_1," %g %g %g", *c1,*(c1+1),*(c1+2));
  sprintf(circle_str_2," %g %g %g", *c2,*(c2+1),*(c2+2));
  sprintf(circle_str_3," %g %g %g", *c3,*(c3+1),*(c3+2));

  sprintf(x_position," %g",x);
  sprintf(y_position," %g",y);

  // printf("The three circles you enteres are: \n");
  // puts(circle_str_1);
  // puts(circle_str_2);
  // puts(circle_str_3);
  //
  // printf("This intersect at X position: \n");
  // puts(x_position);
  // printf("And at Y position: \n" );
  // puts(y_position);

  strcat(run_this, circle_str_1);
  strcat(run_this, circle_str_2);
  strcat(run_this, circle_str_3);
  strcat(run_this, x_position);
  strcat(run_this, y_position);
  printf("Generating graphs on Python. \n" );
  system(run_this);
}
