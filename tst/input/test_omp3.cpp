
int main(){
#pragma omp parallel for schedule(    static    , 33   )
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
}
