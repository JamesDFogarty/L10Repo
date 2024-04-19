#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
int count;
struct Trie* next[26];
};

struct Trie *createTrie()
{
struct Trie * newTrie = (struct Trie*)malloc(sizeof(struct Trie));
newTrie->count=0;
for (int i=0;i<26;i++) {
	newTrie->next[i]=NULL;
}
return newTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
// Down to the end, insert the word.
if (*(word+1)=='\0') {
pTrie->count++;
return;
}
// See if the next place to go exists, if not, create it.
int nextIndex = *word - 'a';
if (pTrie->next[nextIndex] == NULL)
pTrie->next[nextIndex] = createTrie();
insert(pTrie->next[nextIndex], (word+1));
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
printf("%s \n",word);
printf("%c%c%c \n",*(word+1),*(word+2),*(word+3));
int rval = 0;
if (pTrie->next[*word-'a']!=NULL) {
    
    if ((*((word)+1))=='\0') {
		rval=pTrie->count;
		printf("adding %d to the count for %c \n",pTrie->count,word+1);
		}
    else rval=numberOfOccurances(pTrie->next[*word-'a'],(word+1));
}
return rval;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
for (int i=0;i<26;i++) {
    if (pTrie->next[i]!=NULL) deallocateTrie(pTrie->next[i]);
}
pTrie=NULL;
free(pTrie);
}

// Initializes a trie structure


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
FILE * fp = fopen(filename,"r");
if (fp==NULL) return 0;
int wordcount=0;
fscanf(fp,"%d",&wordcount);
char input[30];
for (int i=0;i<wordcount;i++) {
	fscanf(fp,"%s",input);
	pInWords[i]=(char*)malloc(sizeof(char)*(strlen(input)+1));
	strcpy(pInWords[i],input);
}
return wordcount;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}