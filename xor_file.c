#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error (char *msg){
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

	FILE *fh;
	FILE *fh2;
	unsigned int *buffer;
	char *key = argv[1];
	unsigned int *encrypted;
	unsigned int c;
	
	if (argc !=4){
		usage();
	}


	fh = fopen(argv[2], "rb");
	fh2 = fopen(argv[3], "wb");

	//SET MALLOC
	buffer = malloc(sizeof(argv[2]));
  memset(buffer,0,sizeof(argv[2]));

  encrypted = malloc(sizeof(argv[3]));
	memset(encrypted,0,sizeof(argv[3]));
	//END

	while(fread(buffer,sizeof(*buffer),1,fh)){
		
		encrypted = func_encrypt(buffer,key);
	
		fwrite(encrypted,1,sizeof(*encrypted),fh2);
	}

	
  fclose(fh2);
	fclose(fh);

  free(encrypted);
  free(buffer);
											    
	return 0;

}
