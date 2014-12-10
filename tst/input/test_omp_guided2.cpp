
int main(){
#pragma omp parallel for schedule(guided, 3)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
}
