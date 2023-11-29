#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct songStruct {
	char name[50];
	char artist[50];
	int length;
} song;

//int countLines(FILE* file);

song createSong(FILE* file);

int mainTest()
{	
	char* filename = "songsInfo.txt";
	FILE* file = fopen(filename, "r");

	int num = countLines(file);
	printf("%d", num);
	return 0;
}


int main()
{
	char* filename = "songsInfo.txt";
	FILE* file = fopen(filename, "r");
	
	if (file == NULL)
	{
		printf("Error: can't find or open file %s\n", filename);
		return 1;
	}

	int PLAYLIST_LENGTH;
	printf("\nPlaylist length? ");
	scanf("%d", &PLAYLIST_LENGTH);
	
	// creates a list of song objects
	// assume valid int value
	song playlist[PLAYLIST_LENGTH];

	int test = countLines(file);
	printf("\n%d", test);
	
	// need to reset the pointer's location
	rewind(file);
	
	song song1 = createSong(file);
	
	printf("\n%s, %s, %d seconds", song1.name, song1.artist, song1.length);

	
	/*
	printf("T"); // TEST FLAG

	playlist[0] = song1;
	printf("\n%s, %s, %d seconds", *(playlist[0].name), *(playlist[0].artist), playlist[0].length);
	*/
	
	
	fclose(file);
	return 0;
}

#define BUF_SIZE 256
int countLines(FILE* file)
{
	printf("T"); // TEST FLAG
    char buf[BUF_SIZE];
    int counter = 0;
    for(;;)
    {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file)) {return -1;}

        int i;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n') {counter++;}

        if (feof(file)) {break;}
    }

    return counter;
}

song createSong(FILE* file)
{
	printf("T"); // TEST FLAG

	song newSong;
	
	
	/*
	// dynamically allocate memory for the song name
	char* name = (char*) malloc(sizeof(newSong.name));
	fgets(name, 256, file);
	strcpy(newSong.name, name);
	
	char* artist = (char*) malloc(sizeof(newSong.artist));
	fgets(artist, 256, file);
	strcpy(newSong.artist, artist);	
	
	
	char* length = (char*) malloc(sizeof(newSong.artist));
	fgets(length, 256, file);
	
	int length_ = atoi(length);
	newSong.length = length_;
	*/
	return newSong;
}

#define MAX_LEN 256

int getLines(void)
{
    FILE* fp;
    fp = fopen("file.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

    char buffer[MAX_LEN];
    while (fgets(buffer, MAX_LEN, fp))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        printf("%s\n", buffer);
    }

    fclose(fp);
    return 0;
}
