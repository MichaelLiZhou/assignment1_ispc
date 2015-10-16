export void Jsqrt(uniform float random_array[], uniform float output_array[]){

//        for(uniform int i = 0; i < 2000; i++){

	foreach (index = 1 ... 10000) {
                float A = random_array[index];
                float x;
                if(A <=(float)1){
                        x = 1;
                }
                if(A > 1 && A <= (float)2){
                        x = 2;
                }
                if(A > 2 && A <= (float)3){
                        x = 3;
                }

                float diff;
                float x_next;
                diff = 1;

		
                while (diff > 0.0001){
                        x_next = 0.5*(x + (A/x));
                        diff = x_next - x;
                        if ( diff < 0){
                                diff *= -1;
                        }
                        x = x_next;
                }


/*
		for (uniform int i = 0; i < 1000; i++){
			x_next = 0.5*(x + (A/x));
                        diff = x_next - x;
                        if ( diff < 0){
                                diff *= -1;
                        }
                        x = x_next;
			if(diff < 0.0001){
				break;
			}	
		}	
*/ 
                output_array[index] = x;
        }
}




