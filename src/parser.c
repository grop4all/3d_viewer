#include "parser.h"


int main(){
    parsline("test_sample/airboat.obj");
    return 0;
}

int parsline(char* filename) {

    FILE* file;
    fpos_t pos;
    data_t data = { 
        .count_of_facets = 0,
        .count_of_vertexes = 0,
        .matrix_3d ={NULL, 0 , 0},
        .polygons = NULL,
    };
    int ans;
    int tmp;
    char* currline;
    size_t len;
    char* buff_line;

    if ( NULL == (file = fopen(filename, "r"))) {ans = 1;}
    
    len = 128;
    ans = 0;
    buff_line = NULL;
    currline = NULL;


    fgetpos(file, &pos);
    int puff;
    while(EOF !=(tmp = getc(file))) {
        if ('f' == tmp) {
            puff = getc(file);
            if (puff == ' ')
                data.count_of_facets += 1; 
        }
        if ('v' == tmp) {
            puff = getc(file);
            if (puff == ' ')
                data.count_of_vertexes += 1;
        }
    }
    printf("v = %d, f = %d ", data.count_of_vertexes, data.count_of_facets);
    
    fsetpos(file, &pos);

    init_data(&data);
    int v = 1, f = 1;
    while (!feof(file))
    {
        tmp = getc(file);
        if ('v' == tmp ) {
            puff = getc(file);
            if (puff == ' ') {    
                fscanf(file, "%lf%lf%lf", &data.matrix_3d.matrix[v][0],&data.matrix_3d.matrix[v][1],&data.matrix_3d.matrix[v][2]);
                // printf("%lf%lf%lf\n", data.matrix_3d.matrix[v][0], data.matrix_3d.matrix[v][1], data.matrix_3d.matrix[v][2]);
                ++v;
            }
            }
        if ('f' == tmp) {
            puff = getc(file);
            if (puff == ' ')  {
            getline(&currline, &len, file);
            buff_line = malloc(len);
            for(int i = 0; currline[i] != '\0'; ++i) buff_line[i] = currline[i]; 
            init_polygon(&data, buff_line, f);
            ++f;
            free(buff_line);}
        }
    }
    free(currline);
    destroy_data(&data);
    fclose(file);
    return ans;
}


void init_data(data_t* data) {
    //подсчет с 1

    data->matrix_3d.rows = data->count_of_vertexes + 1;
    data->matrix_3d.cols = 3;
    data->matrix_3d.matrix = (double**) malloc(sizeof(double*) *
                                     data->matrix_3d.rows);

    for(int i = 0; i < data->matrix_3d.rows; ++i)
        data->matrix_3d.matrix[i] = (double*) malloc(sizeof(double) * data->matrix_3d.cols);

    for (int i = 1; i < data->matrix_3d.rows; ++i)
        for (int j = 0; j < 3; ++j)
            data->matrix_3d.matrix[i][j] = 0;   
    
    data->polygons = malloc(sizeof(polygon_t) * (data->count_of_facets + 1));
    data->polygons[0].vertexes = malloc(1);
}


void init_polygon(data_t* data, char* line, int index) {

    int count = 1;
    char* buff_line = NULL;
    buff_line =  malloc(strlen(line) + 1);
    char* tmp = NULL;
    char* delim = " ";

    strcpy(buff_line, line);
    strtok(buff_line, delim); 
    for(; strtok(NULL, delim) != NULL ; ++count);
    
    data->polygons[index].numbers_of_vertexes_in_facets = count;
    data->polygons[index].vertexes = malloc(sizeof(int) * count);

    strcpy(buff_line, line);
    tmp = strtok(buff_line, delim);
    for (int i = 0; i < data->polygons[index].numbers_of_vertexes_in_facets; ++i){
        data->polygons[index].vertexes[i] = atoi(tmp);
        tmp = strtok(NULL, delim);
    }
    free(tmp);
    free(buff_line);
}

void destroy_data(data_t * data) {
    
    for(int i = 0; i <= data->count_of_facets; ++i) 
        free(data->polygons[i].vertexes);
    free(data->polygons);
    for(int i = 0; i < data->matrix_3d.rows; ++i)
        free(data->matrix_3d.matrix[i]);
    free(data->matrix_3d.matrix);    
}
