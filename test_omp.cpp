

#define MAX 10000

int main(){
    
#pragma omp parallel     
    for(unsigned int i=0; i<10000; ++i){
        int x = i + 5;
    }

#pragma omp parallel for schedule(static)
    for(unsigned int i=0; i<200; ++i){
        int m = i*i;
    }
}
