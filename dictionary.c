/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <cs50.h>
#include "dictionary.h"
#include <ctype.h>
trie_node* trie_root=NULL;
unsigned int no_words = 0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    int len = strlen(word);
    char ch;
    trie_node* trav = trie_root ;
    for( int i = 0 , idx; i<len ;i++)
    {
        ch = word[i];
        if( ch == '\'')
            idx = 26;
        else
        {
            ch = tolower(ch);
            idx = ch - 97 ;
        }
        if( ! (trav->letter[idx]) )
            return false;  
        trav = trav->letter[idx] ;  
    }
    if ( trav->is_word)
        return true;
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    FILE* fp = fopen(dictionary,"r");
    if ( fp == NULL )
    {
        printf("file: %s: Cannot open file\n",dictionary);
        exit(1);
    }
    if( trie_root == NULL)
        trie_root = malloc(sizeof(trie_node));
    trie_node* trav = trie_root ;
    char ch;
    int idx=0;
    while( ( ch=fgetc(fp) ) != EOF)
    {
        // end of word and start of new word
        if( ch == '\n' )
        {
            trav->is_word = true;
            trav = trie_root ;
            no_words++;
            continue;
        }
        else
        {
        //calc alphabetic index of letter & '(aphostrophe)
            if( ch == '\'' )
                idx = 26 ;
            else
                idx = ch - 97 ;
            
            if ( !(trav->letter[idx]) )
            {
                trie_node* new_letter =  malloc(sizeof(trie_node));
                trav->letter[idx] = new_letter ;
            }
            trav = trav->letter[idx] ;
        }
        
    }
    if(ferror(fp))
    {
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return no_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return unload_helper(trie_root);
}
bool unload_helper( trie_node* root )
{
    for( int i = 0 ; i < 27 ; i++ )
    {
        if( root->letter[i] )
        {
            unload_helper(root->letter[i]);
        }    
    }
    free(root);  
    return true; 
}
