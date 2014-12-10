
int main(){
#pragma omp parallel for schedule(    runtime    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }

#pragma omp parallel for schedule(    runtime)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(runtime)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    runtime    ,                              33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    runtime      )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    runtime     )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    runtime  ,1  )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(runtime)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(runtime,3322222)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    runtime,33                       )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel                         for schedule(    runtime    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp                              parallel for schedule(    runtime    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
}
