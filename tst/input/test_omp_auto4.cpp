
int main(){
#pragma omp parallel for schedule(    auto    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }

#pragma omp parallel for schedule(    auto)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(auto)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    auto    ,                              33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    auto      )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    auto     )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    auto  ,1  )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(auto)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(auto,3322222)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel for schedule(    auto,33                       )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp parallel                         for schedule(    auto    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
#pragma omp                              parallel for schedule(    auto    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
}
