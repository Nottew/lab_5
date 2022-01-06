#include <stdio.h>
#include <stdlib.h>

double funct(double x)
{
    return x*x*x;
}
void output(double **arr,FILE *f_out,int N);

int main()
{
    FILE *f_in, *f_out, *fb_out;
    f_in=fopen("input.dat","r");
    if(f_in==NULL)
    {
        printf("Error! File not found\n");
        return 0;
    }
    char group[10];
    double a,b,delta;
    int N;
    fscanf(f_in,"%s",group);
    fscanf(f_in,"%lf",&a);
    fscanf(f_in,"%lf",&b);
    fscanf(f_in,"%u",&N);
    fscanf(f_in,"%lf",&delta);

    double x=a,y;
    if(N==0)
    {
        N=(b-a)/delta;
    }
    double **arr;
    arr=malloc(2*sizeof(double *));
    arr[0]=malloc(N*sizeof(double));  //ox
    arr[1]=malloc(N*sizeof(double));  //oy
    for(int i=0;i<N;i++)
    {
        arr[0][i]=x;
        arr[1][i]=funct(x);
        x+=delta;
    }

    output(arr,f_out,N);

    fb_out=fopen("result.bin","wb");
    fwrite(&N,sizeof(int),1,fb_out);
    for(int i=0;i<N;i++)
    {
        fwrite(&arr[0][i],sizeof(double),1,fb_out);
        fwrite(&arr[1][i],sizeof(double),1,fb_out);

    }
    free(arr[0]);
    free(arr[1]);
    free(arr);
    fclose(f_in);
    fclose(f_out);
    fclose(fb_out);

    fb_out=fopen("result.bin","rb");
    if(fb_out==NULL)
    {
        printf("Error! File not found\n");
        return 0;
    }
    fread(&N,sizeof(int),1,fb_out);
    printf("Amount of points = %u\n",N);
    printf("       x           y\n");
     for(int i=0;i<N;i++)
    {
        fread(&x,sizeof(double),1,fb_out);
        fread(&y,sizeof(double),1,fb_out);
        printf("%10.2lf %10.2lf\n",x,y);

    }
    return 0;
}


void output(double **arr,FILE *f_out,int N){
f_out=fopen("result.txt","w");
    fprintf(f_out,"Amount of points %u\n",N);
    for(int i=0;i<N;i++)
    {
        fprintf(f_out,"%10.2lf %10.2lf\n",arr[0][i], arr[1][i]);
    }
}
