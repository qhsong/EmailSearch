#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

static char *trie_root_value = "#";
static struct trie *trie_find_prefix(struct trie *root, char *word, int *len_word, int *len_common);
static struct trie *trie_insert_node(struct trie *node, char *value);
static struct trie *trie_divide_node(struct trie *node, int len_common);
static struct trie *trie_new_node(char *value);
static char *trie_strcpy(char *str);
static int trie_index(char *str, char c);

struct trie *
trie_init()
{
    struct trie *t;
    if ((t = malloc(sizeof(struct trie))) == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }
    
    t->childs = NULL;
    t->list = NULL;
    t->value = trie_root_value;
    
    return t;
}

void
trie_destroy()
{
    
}

int
trie_search(struct trie *root, char *word)
{
    struct trie *prefix;
    int len_word, len_common;
    
    if (!root || !word || strlen(word) == 0)
        return 0;
    if ((prefix = trie_find_prefix(root, word, &len_word, &len_common)) == NULL)
        return 0;
    if (strlen(word) != len_word)
        return 0;
    if (prefix->word == NULL)
        return 0;
    return 1;
}

struct trie *
trie_insert(struct trie *root, char *word)
{
    struct trie *prefix, *node_tmp;
    int len_word, len_common;
    
    if (!root || !word || strlen(word) == 0)
        return NULL;
    
    prefix = trie_find_prefix(root, word, &len_word, &len_common);
    if (strcmp(prefix->value, trie_root_value) == 0) {
        prefix = trie_insert_node(prefix, word);
        prefix->word = trie_strcpy(word);
        return prefix;
    }
    if (len_word == strlen(word) && len_common == strlen(prefix->value)) {
        if (prefix->word == NULL)
            prefix->word = trie_strcpy(word);
    } else if (len_word == strlen(word)) {
        prefix = trie_divide_node(prefix, len_common);
        prefix->word = trie_strcpy(word);
    } else if (len_common == strlen(prefix->value)) {
        prefix = trie_insert_node(prefix, word+len_word);
        prefix->word = trie_strcpy(word);
    } else {
        prefix = trie_divide_node(prefix, len_common);
        node_tmp = trie_insert_node(prefix, word+len_word);
        node_tmp->word = trie_strcpy(word);
        node_tmp->value = trie_strcpy(word+len_word);
        return node_tmp;
    }
    
    return prefix;
}

static struct trie *
trie_find_prefix(struct trie *root, char *word, int *len_word, int *len_common)
{
    struct trie *node;
    int index, i;
    
    (*len_word) = 0;
    node = root;
    while ((*len_word) < strlen(word)) {
        (*len_common) = 0;
        if (strcmp(node->value, trie_root_value) != 0) {
            for (i = 0; i < strlen(node->value) && (*len_word) < strlen(word); ++i) {
                if (node->value[i] != word[*len_word])
                    return node;
                (*len_word)++;
                (*len_common)++;
            }
            if ((*len_word) == strlen(word))
                return node;
        }
        if ((index = trie_index(node->childs, word[*len_word])) == -1)
            break;
        node = node->list[index];
    }
    return node;
}

static struct trie *trie_insert_node(struct trie *node, char *value)
{
    int len, i;
    
    if (node->childs == NULL)
        len = 0;
    else
        len = strlen(node->childs);
    
    node->childs = realloc(node->childs, len+2);
    if (node->childs == NULL) {
        fputs("realloc error\n", stderr);
        exit(1);
    }
    node->childs[len+1] = '\0';
    for (i = len-1; i >= 0 && node->childs[i] > value[0]; --i)
        node->childs[i+1] = node->childs[i];
    node->childs[i+1] = value[0];
    node->list = (struct trie **)realloc(node->list, sizeof(struct trie *) * (len+1));
    if (node->list == NULL) {
        fputs("realloc error\n", stderr);
        exit(1);
    }
    while (len > i+1) {
        node->list[len] = node->list[len-1];
        --len;
    }
    node->list[len] = trie_new_node(value);
    
    return node->list[len];
}

static struct trie *
trie_divide_node(struct trie *node, int len_common)
{
    struct trie *new_node;
    
    new_node = trie_new_node(node->value+len_common);
    new_node->childs = node->childs;
    new_node->list = node->list;
    new_node->word = node->word;
    
    node->childs = NULL;
    node->list = NULL;
    node->word = NULL;
    
    node->childs = malloc(2);
    if (node->childs == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }
    node->childs[0] = node->value[len_common];
    node->childs[1] = '\0';
    
    node->list = (struct trie **)malloc(sizeof(struct trie *));
    if (node->list == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }
    node->list[0] = new_node;
    node->value[len_common] = '\0';
    
    return node;
}

static struct trie *trie_new_node(char *value)
{
    struct trie *node;
    if ((node = malloc(sizeof(struct trie))) == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }
    
    node->childs = NULL;
    node->list = NULL;
    node->word = NULL;
    node->value = trie_strcpy(value);
    
    return node;
}

static char *
trie_strcpy(char *str)
{
    int len;
    char *new_str;
    
    len = strlen(str);
    if ((new_str = malloc(len + 1)) == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }
    
    strcpy(new_str, str);
    return new_str;
}

static int
trie_index(char *str, char c)
{
    int i;
    
    if (str == NULL)
        return -1;
    for (i = 0; i < strlen(str); ++i)
        if (c == str[i])
            return i;
    return -1;
}
