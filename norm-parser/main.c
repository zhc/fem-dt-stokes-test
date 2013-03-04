#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#define PATH_MAX 256

void print_norm(int nx, float dt, char* time, char* scheme, double norm, char *var){
    printf("%snorm=%lf nx=%d dt=%f time=%s scheme=%s\n", var, norm, nx, dt, time, scheme);
}

void scan_result_p(char* dir, int nx, float dt, char *scheme, char* exact_dir){
    printf("%s %s %d %f\n", dir, scheme, nx, dt);
    char *dts[] = { "0.05", "0.1", "0.15", "0.2" };
    int ndts = 4;
    float hx,hy;
    hx = hy = 0.0125;
    int i;
    char fname[PATH_MAX];
    char exact_fname[PATH_MAX];
    double rx, ry, p, ex_p;
    double norm = 0;
    for(i=0; i<ndts; i++){
        sprintf(fname, "%s/p.%s.txt", dir, dts[i]);
        sprintf(exact_fname, "%s/p.%s.txt", exact_dir, dts[i]);
        FILE* f = fopen(fname, "r");
        FILE* ex_f = fopen(exact_fname, "r");
        int ok;
        do {
            ok = fscanf(f, "%lf %lf %lf", &rx, &ry, &p);
            ok = fscanf(ex_f, "%lf %lf %lf", &rx, &ry, &ex_p);
            norm += (p - ex_p)*(p-ex_p);
        } while(ok != EOF);
        fclose(f);
        fclose(ex_f);
        norm = sqrt(norm*hx*hy);
        print_norm(nx, dt, dts[i], scheme, norm, "p");
    }
}

void scan_result_u(char* dir, int nx, float dt, char *scheme, char* exact_dir){
    printf("%s %s %d %f\n", dir, scheme, nx, dt);
    char *dts[] = { "0.05", "0.1", "0.15", "0.2" };
    int ndts = 4;
    float hx,hy;
    hx = hy = 0.0125;
    int i;
    char fname[PATH_MAX];
    char exact_fname[PATH_MAX];
    double rx, ry, px, ex_px, py, ex_py;
    double norm = 0;
    for(i=0; i<ndts; i++){
        sprintf(fname, "%s/u.%s.txt", dir, dts[i]);
        sprintf(exact_fname, "%s/u.%s.txt", exact_dir, dts[i]);
        FILE* f = fopen(fname, "r");
        FILE* ex_f = fopen(exact_fname, "r");
        int ok;
        do {
            ok = fscanf(f, "%lf %lf %lf %lf", &rx, &ry, &px, &py);
            ok = fscanf(ex_f, "%lf %lf %lf %lf", &rx, &ry, &ex_px, &ex_py);
            norm += (px - ex_px)*(px-ex_px) + (py - ex_py)*(py-ex_py);
        } while(ok != EOF);
        fclose(f);
        fclose(ex_f);
        norm = sqrt(norm*hx*hy);
        print_norm(nx, dt, dts[i], scheme, norm, "u");
    }
}

int main(void)
{
    char cwd[PATH_MAX];
    if (!getcwd(cwd, PATH_MAX)){
        printf("Failed to get current directory\n");
        return -1;
    }
    DIR* cwd_dir = opendir(cwd);
    if (!cwd_dir){
        printf("Failed to open %s\n", cwd);
        return -1;
    }
    struct dirent* d;
    while( (d = readdir(cwd_dir)) != NULL ) {
        if (strstr(d->d_name, "results")){
            int nx;
            float dt;
            char scheme[10];
            sscanf(d->d_name, "results_%d_%f_%s", &nx, &dt, scheme);
            scan_result_p(d->d_name, nx, dt, scheme, "results_80_0.0001_im");
            scan_result_u(d->d_name, nx, dt, scheme, "results_80_0.0001_im");
        }
    }
    closedir(cwd_dir);
    return 0;
}
