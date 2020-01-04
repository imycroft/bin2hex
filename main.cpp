#include <stdio.h>

bool verifyBin(FILE* file);
int main (int argc, char* argv[])
{
    FILE *ptr;
    FILE *ptrw;
    if(argc != 3) {
        printf("Usage: %s [exeFile] [hexFile]\n", argv[0]);
        return -1;
    }
    ptr = fopen(argv[1],"rb");
    if(!ptr){
        printf("File %s not found", argv[1]);
        return -2;
    }
    if(!verifyBin(ptr)){
        printf("%s is not a valid executable file", argv[1]);
        return -3;
    }
    rewind(ptr);
    ptrw = fopen(argv[2],"wb");
    if(!ptrw){
        printf("Could not create file %s ", argv[2]);
        return -3;
    }
    unsigned char c;
    while(true)
    {
        fread(&c, sizeof(unsigned char),1, ptr);
        if(feof(ptr))
            break;
        fprintf(ptrw,"%02x", (unsigned char)c );
        //fwrite(&c, sizeof(char), 1, ptrw);
    }
    fclose (ptr);
    fclose (ptrw);
}
bool verifyBin(FILE* file){
    unsigned char c;
    fread(&c, sizeof(unsigned char),1, file);
    if(c != 'M')
        return false;
    fread(&c, sizeof(unsigned char),1, file);
    if(c != 'Z')
        return false;
    return true;
}
