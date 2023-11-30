#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>
#define BUF_SIZE 256


int countLines(FILE* file);
void trimws(char* str);
int existsAlready(int nums[], int target, int max);

int main()
{
	//char* filename = "songsInfo.txt";
	FILE* file = fopen("songsInfo.txt", "r");
	
	// size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

	int numLines = countLines(file);
	int numSongs = (numLines % 3 > 0) ? (numLines / 3 + 1) : (numLines /3);
	
	char titles[numSongs][50];
	char artists[numSongs][50];
	//int length[numSongs];
	char length[numSongs][50];
	
	// [title1, title2, title3]
	
	fseek(file, 0, SEEK_SET);
	
	
	int status = 1; // 1 is title; 2 is artist; 3 is length
	int pos = 0;
	char line[50];

	// Read the content and print it
	while(fgets(line, 50, file)) {
		
		if (status == 1)
		{
			//line[strcspn(line, "\n")] = 0;
			trimws(line);
			strcpy(titles[pos], line);
			status += 1;
		}
		else if (status == 2)
		{
			//line[strcspn(line, "\n")] = 0;
			trimws(line);
			strcpy(artists[pos], line);
			status += 1;
		}
		else if (status == 3)
		{
			//line[strcspn(line, "\n")] = 0;
			trimws(line);
			strcpy(length[pos], line);
			pos +=1;
			status = 1;
		}
	}
	
	printf("There are %d total songs.", numSongs);
	
	int playlistLength;
	//do 
	printf("\nHow many songs to put in the new list (Enter a value less than total songs): ");
	scanf("%d", &playlistLength);
	 
	//while(playlistLength > numSongs && playlistLength > 0);
	
	//printf("\nNow enter a name (you get one shot don't mess up): ");

	//char playlistName[50];
	/*
	scanf("%s", playlistName);
	
	strcat(playlistName, ".txt");
	printf("%s", playlistName);
	*/
	srand(1);

	FILE* newF = fopen("newsongs.txt", "w+");
	
	int usedIndex[playlistLength];
	for (int i = 0; i < playlistLength; i+=1)
	{
		usedIndex[i] = -1;
	}
	
	int index = 0;
	while (index < playlistLength)
	{
		int songNum = rand() % numSongs;
		
		if (existsAlready(usedIndex, songNum, playlistLength) == 0)
		{
			fprintf(newF, strcat(titles[songNum],"\n"));
			usedIndex[index] = songNum;
			index +=1;
		}
	}
	
	
	
	fclose(file);
	fclose(newF);
	
	//printf("%d", numLines);

	return 0;
}

int countLines(FILE* file)
{
    char buf[BUF_SIZE];
    int counter = 0;
    for(;;) // while (1)
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

void trimws(char* str) {
	int length = strlen(str);
	int x;
	if (length == 0) return;
	x = length - 1;
	while (isspace(str[x]) && (x >= 0)) {
		str[x] = '\0';
		x -= 1;
	}
}

int existsAlready(int nums[], int target, int max)
{
	for (int i = 0; i < max; i+=1)
	{
		//nums = [1, 2, -1, -1]
		if (nums[i] == target)
		{
			return 1;
		}
	}
	
	return 0;
}


/*
Given a text file of song titles, the program would select a number (decided by user input) of random songs and generate a playlist of them. 

The output could be to a new text file or to the console. 

The program will allow you to find more information about each song such as the title, the song length in seconds, and the artist.


open file X

count lines set to var X

get info into 3 parallel arr X

char[][] title X
char[][] artist X
int [] length X

prompt for new playlist length X
if (invalid length) X
try again

when successful prompt for playlist name X 
-> name will be used for textfile name X

create new playlist (text file) with length from user X

to make the playlist X
for i until length X
   rand % songs in library X
   (figure out how to prevent dupes) X
   append to songs title file X

select random lines from source file (every 3rd line is the song title) X


write while program not over // TODO NEXT STEP MAKE THIS A WHILE LOOP UNTIL USER DECIDES TO END PROGRAM
prompt with a menu
user can select to search song info

quit program


*/