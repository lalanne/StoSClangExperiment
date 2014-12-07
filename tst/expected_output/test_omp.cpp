
// Begin function main returning int
int main(){
#pragma omp parallel for schedule(     runtime     ,    3     )
    for(unsigned int i=0; i<200; ++i)// 'for' loop detected!!
    {
        int m = i*i;
    }
}
// End function main
