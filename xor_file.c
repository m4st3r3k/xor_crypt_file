#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int error(char *msg){
if (msg !=NULL)
fprintf(stderr, "%s\n", msg);
}

void usage(void){
printf("Usage: [key] + [input file] + [output file]\n");
error(NULL);
}


int *func_encrypt(int *message, char *key) {
	//size_t messagelen = strlen(message);

	size_t keylen = strlen(key);

	unsigned int *encrypted = malloc(sizeof(*message));

 	
	for(int i = 0; i < sizeof(*message); i++){
		
		encrypted[i] = message[i] ^ key[i % keylen];
																   
 	}

													   
 	return encrypted;

}


int main(int argc, char *argv[]) {

	FILE *fh1;
	FILE *fh2;
	unsigned int fh1_size;
	unsigned int fh2_size;
	unsigned int *buffer;
	char *key = argv[1];
	unsigned int *encrypted;
	unsigned int c;
	
	if (argc !=4){
		usage();
		return 1;
	}

    //FILES
	fh1 = fopen(argv[2], "rb");
	fh2 = fopen(argv[3], "wb");
	//END

	//SET MALLOC
	fseek(fh1,0, SEEK_END);
	fh1_size = ftell(fh1);
	buffer = malloc(fh1_size);
	fseek(fh1,0, SEEK_SET);
    memset(buffer,0,fh1_size);
    
    fseek(fh2,0, SEEK_SET);
    fh2_size = ftell(fh2);
    encrypted = malloc(fh2_size);
	memset(encrypted,0,fh2_size);
	//END

	while(fread(buffer,sizeof(*buffer),1,fh1)){
		
		encrypted = func_encrypt(buffer,key);
	
		fwrite(encrypted,1,sizeof(*encrypted),fh2);
	}

	
  fclose(fh2);
	fclose(fh1);

  free(encrypted);
  free(buffer);
											    
	return 0;

}
