main (void) {
    int f = 0;
    int g = 1;
    int i = 0;
    int stored_g = 0;

    for (i = 0; i <= 40; i++){
        printf("%d", g);
        stored_g = g;
        g += f;
        f = stored_g;
        if (i%5 == 0){
            printf("\n");
        }
    }
    
}
