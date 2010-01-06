//
// artificial neural network (ann) eXclusive OR example
//

#include <stdio.h>
#include <time.h>

#include "liquid.internal.h"

#define OUTPUT_FILENAME "ann_example.m"

int main() {
    srand(time(NULL));
    // options

    // create network structure:
    //      2 inputs, 4 hidden neurons, 1 output
    unsigned int structure[3] = {2, 2, 1};

    // binary input sequence
    float x[8] = {-1,-1,    // 0 0
                  -1, 1,    // 0 1
                   1,-1,    // 1 0
                   1, 1     // 1 1
    };

    // binary output sequence
    float y[4] = {  -0.5, 0.5, 0.5, -0.5 };
    float y_hat;

    // create network
    ann q = ann_create(structure, 3);
    ann_init_random_weights(q);

    //ann_evaluate(q,x,&y_hat);
    //ann_print(q);

    unsigned int i;
    // evaluate network
    for (i=0; i<4; i++) {
        ann_evaluate(q,&x[2*i],&y_hat);
        printf("%6.3f %6.3f > %6.3f (%12.8f)\n",
                x[2*i+0], x[2*i+1], y[i], y_hat);
    }

    unsigned int num_training_patterns = 4;
    float error_tolerance = 0.0f;
    unsigned int max_trials = 8000;

    printf("training...\n");
    ann_train(q,x,y,num_training_patterns,error_tolerance,max_trials);
    printf("done.\n");

    for (i=0; i<4; i++) {
        ann_evaluate(q,&x[2*i],&y_hat);
        //ann_print(q);
        printf("%6.3f %6.3f > %6.3f (%12.8f)\n",
                x[2*i+0], x[2*i+1], y[i], y_hat);
    }
#if 0
    float x0[2] = {-1, 1};
    float y0[1] = {0.5};
    for (i=0; i<100; i++)
    ann_train_bp(q,x0,y0);
#endif

#if 0
    FILE* fid = fopen(OUTPUT_FILENAME,"w");
    fprintf(fid,"%% %s: auto-generated file\n\n",OUTPUT_FILENAME);
    fprintf(fid,"clear all;\nclose all;\n\n");

    fclose(fid);
    printf("results written to %s\n", OUTPUT_FILENAME);
#endif
    
    ann_destroy(q);

    printf("done.\n");
    return 0;
}

