#ifndef TRIE_H
#define TRIE_H

struct trie {
    char *childs;
    struct trie **list;
    char *word;
    char *value;
};

struct trie *trie_init();
void         trie_destroy();
int          trie_search(struct trie *root, char *word);
struct trie *trie_insert(struct trie *root, char *word);
void         trie_delete(struct trie *root, char *word);

#endif
