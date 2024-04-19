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
int i, len = strlen(word); //get strlen of word
for (i=0;i<len;i++) { //traverse node structure creating nodes when needed
	if (pTrie->next[word[i]-'a'] == NULL) pTrie->next[word[i]-'a'] = createTrie();
	pTrie=pTrie->next[word[i]-'a'];
}
pTrie->count++; //increment count at last node
}


// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
int i, len = strlen(word); //get length

 for (i=0; i<len; i++) {

 if (pTrie->next[word[i]-'a'] == NULL) return 0; //if you hit a null, return 0

 
 pTrie = pTrie->next[word[i]-'a']; //traverse
 }

 return pTrie->count; //if you reached the end successfully, return its count

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
for (int i=0;i<26;i++) {
    if (pTrie->next[i]!=NULL) deallocateTrie(pTrie->next[i]); //deallocate trie array recursively
}
pTrie=NULL;
free(pTrie); //deallocate trie
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