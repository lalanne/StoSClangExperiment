
int main(){
#pragma omp parallel for schedule(    static    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }

#pragma omp parallel for schedule(    static)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(static)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    static    ,                              33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    static      )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    static     )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    static  ,1  )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(static)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(static,3322222)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    static,33                       )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel                         for schedule(    static    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp                              parallel for schedule(    static    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
}
