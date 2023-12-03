#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<stdbool.h>
#define BUF_SIZE 256

/**
 * A program to generate a random playlist that allows users to find more info about each song.
 *
 * @Authors Danton Dang, Wilson Diep, Evan Doan, Nathan Ervin
 */


// function to count line
int countLines(FILE* file);

// removes new lines and white spaces
void trimws(char* str);

// checks if a song is in the final playlist already
int existsAlready(int nums[], int target, int max);

// define a struct for song with 3 members
typedef struct songStruct {
	char title[50];
	char artist[50];
	char length[50];
} Song;

int main()
{
	// opens source file with pointer
	FILE* file = fopen("songsInfo.txt", "r");
	
	// computes the number of songs from the number of lines in the source file
	int numLines = countLines(file);
	int numSongs = (numLines % 3 > 0) ? (numLines / 3 + 1) : (numLines /3);
	
	// init 3 arr of char to hold information from the file
	char titles[numSongs][50];
	char artists[numSongs][50];
	char length[numSongs][50];
	
	
	fseek(file, 0, SEEK_SET);
	
	
	int status = 1; // 1 is title; 2 is artist; 3 is length
	int pos = 0;
	char line[50];

	// read, clean, and store the info from the file
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
	
	// prompts user for the number of songs in the new playlist
	int playlistLength;
	printf("\nHow many songs to put in the new list (Enter a value less than total songs): ");
	scanf("%d", &playlistLength);

	srand(time(NULL));

	// opens a new file pointer to write to the new text file output
	FILE* newF = fopen("newsongs.txt", "w+");
	
	// a loop to populate the arr of used indexes with place holder values
	int usedIndex[playlistLength];
	for (int i = 0; i < playlistLength; i+=1)
	{
		usedIndex[i] = -1;
	}
	
	// init an arr of song objects that have name, artist, and length
	// creates a Song object with dynamic memory allocation
	Song* usedSongs = (Song*)malloc(playlistLength * sizeof(Song));
	
	int index = 0;
	
	// populates Song arr object with Song objects from file data
	while (index < playlistLength)
	{
		int songNum = rand() % numSongs;
		
		if (existsAlready(usedIndex, songNum, playlistLength) == 0)
		{
			fprintf(newF, strcat(titles[songNum],"\n"));
			usedIndex[index] = songNum;
			strcpy(usedSongs[index].title, titles[songNum]);
			strcpy(usedSongs[index].artist, artists[songNum]);
			strcpy(usedSongs[index].length, length[songNum]);
			
			index +=1;
		}
	}
	
	// while program is not over, prompt user if they want to end, then ask for a song title, then print out info about that song
	while (1)
	{
		char answer = ' ';
		printf("\nNow that the playlist is done, do you want to look at any of these songs? (Y/N)\n");
		scanf(" %c", &answer);
		
		if (answer == 'N')
		{
			printf("Okay program ending... bye.\n");
			break;
		}
		
		char input[50] = "";
		
		for (int i = 0; i < playlistLength; i +=1)
		{
			printf("%s", usedSongs[i].title);
		}
		
		printf("\nEnter the name of the song you'd like to look at: \n");
		scanf(" %[^\n]", input);
		strcat(input, "\n");
		
		for (int i = 0; i < playlistLength; i +=1)
		{
			if (strcmp(input, usedSongs[i].title) == 0) 
			{
				printf("Title: %sArist: %s\nLength (sec): %s\n", usedSongs[i].title, usedSongs[i].artist, usedSongs[i].length);
				break;
			}

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

USE THIS FOR THE DYNAMIC MEMORY
int *evenNums = malloc(8 * sizeof(int)); // or int evenNums[8];

*/