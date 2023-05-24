#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SHAPES 50

/* type definitions come here */
typedef struct point_t{
    double x;
    double y;

} point_t;

typedef struct square_t{
    point_t bottom_left_corner;
    point_t bottom_right_corner;
    point_t upper_left_corner;
    point_t upper_right_corner;
    double side;
} square_t;

/* function prototypes*/
int scanShape(FILE *filep, square_t *objp);
int loadSquares(square_t shapes[]);
void printShape(const square_t *objp);
void centerDistance(const point_t *ptp, const square_t *objp);

int main()
{
    square_t shapes[MAX_SHAPES];
    int numOfShapes = loadSquares(shapes);

    printf("\nSquares:\n");
    for (int i = 0; i < numOfShapes; i++) {
        printf("Square %d: ", i);
        printShape(&shapes[i]);

    }
    point_t pt;
    printf("\nEnter x and y coordinate of the point: ");
    scanf("%lf %lf",&pt.x,&pt.y);
    printf("\nCenter distances are:\n");
    for (int i = 0; i < numOfShapes; i++) {
        printf("Square %d: ",i +1);
        centerDistance(&pt,&shapes[i]);
    }
    return 0;
}
static int currentLine = 0;

int scanShape(FILE *filep, square_t *objp){
    char line[32];
    int currentLineValueBeforeWhileLoop = currentLine;
    while(fgets(line, sizeof(line), filep)) {
        //Splitting the current line by " " and storing elements in *array
        char *p = strtok(line, " ");
        char *array[4];
        int i = 0;
        while (p != NULL) {
            array[i++] = p;
            p = strtok(NULL, " ");
        }
        //Splitting the current line by " "  and storing elements in *array

        int center_x_coordinate = atoi(array[1]);
        int center_y_coordinate = atoi(array[2]);
        double side_length = atof(array[3]);;

        objp->bottom_left_corner.x = center_x_coordinate - side_length / 2;
        objp->bottom_left_corner.y = center_y_coordinate - side_length / 2;

        objp->bottom_right_corner.x = center_x_coordinate + side_length / 2;
        objp->bottom_right_corner.y = center_y_coordinate - side_length / 2;

        objp->upper_right_corner.x = center_x_coordinate + side_length / 2;
        objp->upper_right_corner.y = center_y_coordinate + side_length / 2;

        objp->upper_left_corner.x = center_x_coordinate - side_length / 2;
        objp->upper_left_corner.y = center_y_coordinate + side_length / 2;

        objp->side = side_length;
        currentLine++;
        break;
    }

    if(currentLineValueBeforeWhileLoop == currentLine) return 0;

    return 1;
}

int loadSquares(square_t shapes[]){
    char fileName[30];
    printf("Enter the file name to read: ");
    scanf("%s", fileName);
    printf("Opening %s \n", fileName);

    FILE *ptr;
    ptr = fopen(fileName, "r");
    printf("Loading complete \n");

    int current = 0;
    while (scanShape(ptr, &shapes[current]) != 0){
        current++;
    }

    printf("Closing %s \n", fileName);
    fclose(ptr);
    return current;
}

void printShape(const square_t *objp){
    printf("<%.2lf %.2lf> <%.2lf %.2lf> <%.2lf %.2lf> <%.2lf %.2lf> <%.2lf> \n",
           objp->bottom_left_corner.x, objp->bottom_left_corner.y, objp->bottom_right_corner.x, objp->bottom_right_corner.y, objp->upper_left_corner.x,
           objp->upper_left_corner.y, objp->upper_right_corner.x, objp->upper_right_corner.y, objp->side);
}

void centerDistance(const point_t *ptp, const square_t *objp){
    double x1 = ptp->x;
    double y1 = ptp->y;
    double x2 = objp->bottom_left_corner.x + ((objp->bottom_right_corner.x - objp->bottom_left_corner.x)/2);
    double y2 = objp->bottom_right_corner.y + ((objp->upper_right_corner.y - objp->upper_right_corner.y)/2);

    double result = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));

    printf("%.2lf \n", result);
}

