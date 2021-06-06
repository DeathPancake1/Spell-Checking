#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* data;
    struct node *left,*right;
} node;

node * newNode(char* val)
{
    node* n=malloc(sizeof(node));
    n->data=malloc(sizeof(char)*(strlen(val)+1));
    strcpy(n->data,val);
    n->left=NULL;
    n->right=NULL;
    return n;
}
int max(int a, int b)
{
    return a>b?a:b;
}
int height(node *root)
{
    if ( root == NULL)
        return -1;
    else
        return 1 + max(height(root->left),height(root->right));
}
int count(node *root)
{
    if ( root == NULL)
        return 0;
    else
        return 1 + count(root->left) + count(root->right);
}
node* search(node *t,char* val)
{
    if(strcasecmp(val,t->data)==0){
        return t;
    }
    else if(strcasecmp(t->data, val) > 0){
        if(t->left==NULL)
            return t;
        return search(t->left,val);
    }
    else{
        if(t->right==NULL)
            return t;
        return search(t->right,val);
    }
}
node* insert(node* node, char* key)
{
    if (node == NULL)
        return newNode(key);
    if (strcasecmp(node->data,key)<0)
        node->right = insert(node->right, key);
    else if (strcasecmp(node->data,key)>0)
        node->left = insert(node->left, key);
    return node;
}
void findPreSuc(node* root, node** pre, node** suc, char* key){
    if(root==NULL)
        return;
    if(strcasecmp(root->data,key)==0){
        if(root->left !=NULL){
            node* temp = root->left;
            while(temp->right){
                temp=temp->right;
            }
            *pre = temp;
        }
        if(root->right!=NULL){
            node *temp = root->right;
            while(temp->left){
                temp=temp->left;
            }
            *suc=temp;
        }
        return;
    }
    if (strcasecmp(root->data,key)>0){
        *suc = root ;
        findPreSuc(root->left, pre, suc, key) ;
    }
    else{
        *pre = root ;
        findPreSuc(root->right, pre, suc, key) ;
    }
}
void process(node* root,char* key){
    char* tok=strtok(key," ");
    while(tok){
        node *n=search(root,tok);
        if(strcasecmp(tok,n->data)==0){
            printf("%s - Correct\n", tok);
        }
        else{
            node* pre = NULL, *suc = NULL;
            findPreSuc(root, &pre, &suc, n->data);
            printf("%s - Incorrect, Suggestions: %s ", tok, n->data);
            printf("%s ", pre->data);
            printf("%s \n", suc->data);
        }
        tok=strtok(NULL," ");
    }
}
node* loadFile(char *filename){
    node* root=NULL;
    char buffer[50];
    FILE *f=fopen(filename,"r");
    if(f){
        printf("Dictionary Loaded Succefully ....!\n");
        printf(".....................................\n");
        while(!feof(f)){
            fscanf(f, "%s", buffer);
            root = insert(root,buffer);
        }
    }
    else{
        return NULL;
    }
    return root;
}
int main()
{
    char words[256];
    node*root=loadFile("EN-US-Dictionary.txt");
    printf("size = %d\n",count(root));
    printf(".....................................\n");
    printf("height = %d\n",height(root));
    printf(".....................................\n");
    printf("Enter a sentence:\n");
    while (fgets(words, 256, stdin)){
        words[strlen(words) - 1] = '\0';
        process(root, words);
        printf("Enter a sentence:\n");
    }
    return 0;
}
