#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <openssl/md5.h>
#include <errno.h>
void scanner();
void virus_detect();
int main(int argc, char **argv)
{
   scanner();
	while(1)
		{
			sleep(5);
			printf("Scanning for virus\n");
			virus_detect();
		}
return 0;
}

void scanner()
{
 DIR* FD;
    struct dirent* in_file;
    FILE    *output;
    FILE    *input;
    FD=opendir(".");
    output = fopen("md5hash.txt", "w");
    while ((in_file = readdir(FD)))
    {

        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))
            continue;

        input = fopen(in_file->d_name, "rw");
        if (input == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file\n");
            fclose(output);

        }


    unsigned char md[MD5_DIGEST_LENGTH];
    int i;
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];
    MD5_Init (&mdContext);

    while ((bytes = fread (data, 1, 1024, input)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (md,&mdContext);
    fprintf(output,"%s\n",in_file->d_name);
    for(i = 0; i < MD5_DIGEST_LENGTH; i++)
        fprintf (output,"%02x", md[i]);
	fputc('\n',output);
    fclose (input);
    }
    fclose(output);
    //closedir(FD);

}
void virus_detect()
{
	char buf[500],buf2[500],buf3[500],k;
    DIR* FD;
    struct dirent* in_file;
    FILE    *output,*input,*infect,*out;
    FD=opendir(".");
    output = fopen("new.txt", "w");
    while ((in_file = readdir(FD)))
    {

        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))
            continue;

        input = fopen(in_file->d_name, "rw");
        if (input == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file\n");
            fclose(output);

        }


    unsigned char md[MD5_DIGEST_LENGTH];
    int i;
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];
    MD5_Init (&mdContext);

    while ((bytes = fread (data, 1, 1024, input)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (md,&mdContext);
    fprintf(output,"%s\n",in_file->d_name);
    for(i = 0; i < MD5_DIGEST_LENGTH; i++)
        fprintf (output,"%02x", md[i]);
	fputc('\n',output);

    while(fgets(buf,500,output)!=NULL)
	{
		//printf("%s",buf);
	out = fopen("md5hash.txt", "r");
        fgets(buf2,500,out);

        if(strcmp(buf,buf2)==0)
        printf("no change");
        else
        {
         infect=fopen(in_file->d_name,"r");
         while((fgets(buf3,500,infect)) != NULL) {
	 if(strstr(buf3,"DEADBEEFDEAD"))
         {
		printf("file infected\n %s",in_file->d_name);
                printf("press Q to kill the process\n");
		scanf("%c",&k);
	        if(k=='q')
		exit(0);
         }


        fclose(infect);
       }
       }
        fclose (input);
}       
    }
    fclose(output);
    //closedir(FD);

}
