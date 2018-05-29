//search a needle in a haystack

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define WORD_WIDTH 32

void rm_extra_space(char *str);
/**
 * size_of_file() reads the length of a file *
 */
long size_of_file(char* file_name, FILE *fp)
{
	int i=0;
	rewind(fp);
	//counting number of chars upto EOF
	while(getc(fp)!=EOF){
		i += 1;
	}
	rewind(fp);
	return i;
}

/**
 * needle: string to search, haystack: string to search from
 * n can be 1 or 0, 1 for strings and 0 for words
 * count_str() counts the number of times a needle can be found
 * in a haystack
 */
long count_str(char* needle, char* haystack, char n)
{
	char temp[WORD_WIDTH];//assuming a word cannot have size larger than 100
	int i = 0;
	long count = 0;
	char ch;
	if(n==0){
		rm_extra_space(haystack); //removing redundant spaces
		while((ch=haystack[i]) != '\0'){
			int j = 0;
			while((ch=haystack[i]) != ' ' && ch != '\n'){
				//printf("%c\n",ch);
				//getchar();
				if(j>=WORD_WIDTH)//preventing overflow
					break;
				temp[j] = ch;
				i += 1;
				if (ch=='\0')
				{
					i -= 1;
					break;
				}
				j += 1;			
			}
			i += 1;
			temp[j] = '\0';//making temp a string	
			if(strcmp(temp,needle) == 0)
				count += 1;
		}
	}else{ 
		int strl = strlen(needle) - 1;//to account for '\0'
		while((ch=haystack[i]) != '\0'){
			int j = 0;
			while (haystack[i] == needle[j])
			{
				if (j == strl)
				{
					count += 1;
					i -= 1;
					break;
				}
				j += 1;
				i += 1;
			}
			i += 1;
		}
	}
	return count;
}


void rm_extra_space(char *str)
{
    char *dest = str;  
    while (*str != '\0')
    {
        while (*str == ' ' && *(str + 1) == ' ')
            str++;  
       *dest++ = *str++;
    }   
    *dest = '\0';
}

/**
 * rp_nl() replaces all newlines in str with a character rp_with
 */
void rp_nl(char *str, char rp_with)
{
	char ch;
	int i = 0;
	while((ch=str[i])!='\0'){
		if (ch == '\n')
			*(str+i) = rp_with;
/*			if (*(str+i) == ' ' && *(str+i+1) == ' ')
			{
				i -= 1;
			}*/
		i += 1;
	}
}

/**
 * count_words() takes a string and returns the number of words in that string
 */
int count_words(char *str)
{
	int i = 0;
	long num_of_words=0;
	char ch;
	while((ch=str[i])!='\0'){
		if (ch == ' ' && str[i+1]!=' ')
		{
			num_of_words += 1;
		}
		i += 1;
	}
	//num_of_words += 1;//counting the last word
	return num_of_words;
}

void rm_extra(char *str, char *new_string)
{
	char temp[WORD_WIDTH];
	temp[0] = '\0';
	int i=0;
	char ch;	
	while((ch=str[i]) != '\0'){
		//getchar();
		int j = 0;
		while((ch=str[i]) != ' ' && ch != '\n'){
			if(j>=WORD_WIDTH)//preventing overflow
				break;
			temp[j] = ch;
			i += 1;
			if (ch=='\0')
			{
				i -= 1;
				break;
			}
			j += 1;			
		}
		i += 1;
		temp[j] = '\0';	
		if (count_str(temp,str,0)==1)
		{
			strcat(new_string,temp);
		}else if(count_str(temp,str,0)>1){
			if(count_str(temp,new_string,0)==0){//checking if word does not exist
				strcat(new_string,temp);					
			}
		}
		strcat(new_string, " ");		
	}
}


int main(int argc, char *argv[])
{
	char temp[WORD_WIDTH];//assuming a word cannot have size larger than 100
	//printf("%ld\n", count_str("hello","hello hellohello hello hello hello hello hello hello hello hello world"));
	FILE *fp;
	int i = 0;
	char ch;
	char file_name[] = "text_file.txt";
	long file_length;
	int num_of_words=0;

	//opening file for reading
	if((fp=fopen(file_name,"r"))==NULL){
		fprintf(stderr, "%s \'%s\'\n", "Fatal Error, missing file:", file_name);
		exit(EXIT_FAILURE);
	}

	file_length = size_of_file(file_name,fp)+1;//+1 to account for '\0'
	char str[file_length];

	//reading into str[]
	i=0;
    while((ch=getc(fp))!=EOF){
    	str[i] = ch;
    	if(i>0){
    		if(str[i-1]==' ' && str[i]==' '){//removing redundant spaces
    		//printf("%s\n", "hello ");
    		i -= 1;
    		//getchar();
    		}
    	}
    	i++;
    }
    str[i] = '\0';
    rp_nl(str, ' ');

    char temp_str[file_length];
    temp_str[0] = '\0';//making it a string
    rm_extra(str,temp_str);
    num_of_words = count_words(temp_str);
    char fpword[num_of_words];//fpword: frequency per word
    char word[num_of_words][WORD_WIDTH];//holds each word read
    char *token;
  /*  printf("%s\n", temp_str);
    printf("%s\n", str);*/
    token = strtok(temp_str," ");
    i = 0;
    //uncomment this lines to get display on screen
   //printf("+----------------------------------------+\n");
    while(token != NULL){
    	strncpy(word[i],token,WORD_WIDTH);
    	fpword[i] = count_str(word[i], str, 0);
    	//you can do your design here or comment this line and use the arrays as wished
    	//printf("| %s:  %d\n", word[i],fpword[i]);
    	token = strtok(NULL," ");
    	i += 1;
    }
    //printf("+----------------------------------------+\n\n");

    if(fclose(fp))
	{
		fprintf(stderr, "%s \'%s\'\n", "Unable to close:",file_name);
		exit(EXIT_FAILURE);
	}

	//opening file for reading
	if((fp=fopen("analysis.txt","w"))==NULL){
		fprintf(stderr, "%s \'%s\'\n", "Fatal Error, missing file:", "analysis.txt");
		exit(EXIT_FAILURE);
	}

	//opening file for reading
	if((fp=fopen("analysis.txt","w"))==NULL){
		fprintf(stderr, "%s \'%s\'\n", "Fatal Error, missing file:", "\'analysis.txt\'");
		exit(EXIT_FAILURE);
	}
	fprintf(fp,"\t\t\tTEXT ANALYSIS RESULT FOR FILE \'%s\'\n\n", file_name);
	fprintf(fp,"#Total number of words analysed:  %d\n\n", num_of_words);
	fprintf(fp,"+----------------------------------------+\n");
	/**
	 *Writing results to external file
	 */
	i = 0;
	for (i = 0; i < num_of_words; i++){

		fprintf(fp, "| %s:  %d\n", word[i],fpword[i]);
		fprintf(fp,"+----------------------------------------+\n");
	}
	if(fclose(fp))
	{
		fprintf(stderr, "%s \'%s\'\n", "Unable to close:",file_name);
		exit(EXIT_FAILURE);
	}

	/**
	 *At this stage, word[] array holds all the words analysed and fpword[] 
	 * holds the corresponding frequency for each word[] analysed
	 */
    return 0;
} 


