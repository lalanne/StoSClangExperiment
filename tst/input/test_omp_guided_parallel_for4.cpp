
int main(){
#pragma omp parallel for schedule(    guided    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }

#pragma omp parallel for schedule(    guided)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(guided)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    guided    ,                              33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    guided      )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    guided     )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    guided  ,1  )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(guided)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(guided,3322222)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    guided,33                       )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel                         for schedule(    guided    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp                              parallel for schedule(    guided    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
}
