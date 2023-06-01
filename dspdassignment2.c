/*We need to design a data structure for music player. A tree database can store the database of 
all music listings. Each music listing will have attributes like singer, lyricist, album/film, 
composer, genre, duration of the song and any other you may choose. We need to define 
following operations:
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 25
#include<time.h>
#define MAX_LINE_LENGTH 256

typedef struct Node{
	
	char name[25];
	char singer[25];
	char lyricist[25];
	char album[25];
	char composer[25];
	char genre[25];
	char duration[20];
	int height;
	struct Node* left;
	struct Node* right;
}node;
struct strings{
	char s[25];
};
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left),  
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
 node* insert(node* nnode, node* newnode)
{
    /* 1.  Perform the normal BST insertion */
    if (nnode == NULL)
        return(newnode);
 
    if (strcmp(newnode->name,nnode->name)<0)
        nnode->left  = insert(nnode->left, newnode);
    else if (strcmp(newnode->name,nnode->name)>0)
        nnode->right = insert(nnode->right, newnode);
    else // Equal keys are not allowed in BST
        return nnode;
 
    /* 2. Update height of this ancestor node */
    nnode->height = 1 + max(height(nnode->left),
                        height(nnode->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(nnode);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(newnode->name,nnode->name)<0)
        return rightRotate(nnode);
 
    // Right Right Case
    if (balance < -1 && strcmp(newnode->name,nnode->name)>0)
        return leftRotate(nnode);
 
    // Left Right Case
    if (balance > 1 && strcmp(newnode->name,nnode->name)>0)
    {
        nnode->left =  leftRotate(nnode->left);
        return rightRotate(nnode);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(newnode->name,nnode->right->name)<0)
    {
        nnode->right = rightRotate(nnode->right);
        return leftRotate(nnode);
    }
 
    /* return the (unchanged) node pointer */
    return nnode;
}
void inorder(node* root){
	if(root==NULL){
		
	}else{
		inorder(root->left);
		printf(" song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
        printf("\n*************\n");
		inorder(root->right);
	}
}
void preorder(node* root){
	if(root==NULL){
		
	}else{
		printf(" song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
        
		preorder(root->left);
		preorder(root->right);
	}
}
void postorder(node* root){
	if(root==NULL){
		
	}else{
		
		postorder(root->left);
		postorder(root->right);
		printf(" song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
        
	}
}
void descending(node* root){
 	if(root==NULL){
 		return;
	 }else{
	 
        descending(root->right);
        printf("\n****************************************************\n");
        printf(" song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
        descending(root->left);
	 }
 }

 


node* input(){
    node* root,*current;
	FILE *fptr=fopen("input (2).txt", "r");
	root=NULL;
	int i,c=0;
	for(i=1;i<=25;i++){
	  node*newsong;
      newsong = (node*) malloc(sizeof(node));
      newsong->right=NULL;
      newsong->left=NULL;
      fscanf(fptr,"\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",newsong->name,newsong->singer,newsong->lyricist,newsong->album,newsong->composer,newsong->genre,newsong->duration);
      root=insert(root,newsong);  
	}
	return root;
	
}

node* q1(node* root){
	node* new_song=(node*)malloc(sizeof(node));
	
	printf("\nenter song name:");
	scanf("%s",new_song->name);
	printf("\nenter  singer :");
	scanf("%s",new_song->singer);
	printf("\nenter song lyricist:");
	scanf("%s",new_song->lyricist);
	printf("\nenter song album:");
	scanf("%s",new_song->album);
	printf("\nenter song composer:");
	scanf("%s",new_song->composer);
	printf("\nenter song genre:");
	scanf("%s",new_song->genre);
	printf("\nenter song duration:");
	scanf("%s",new_song->duration);
	new_song->left=NULL;
	new_song->right=NULL;
	
	root=insert(root,new_song);
	return root;
}
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, char* s)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( strcmp(s,root->name)==-1 )
        root->left = deleteNode(root->left, s);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( strcmp(s,root->name)==-1 )
        root->right = deleteNode(root->right, s);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            
            strcpy(temp->name,root->name);
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->name);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
node* delete_by_name(node* root){
	char s[25];
	printf("\nenter name of song that you want to delete:");
	scanf("%s", s);
	root=deleteNode(root, s);
}int cnt=0;
void search_artist(node* root,struct strings* str,char* s){
	if(root==NULL){
		
	}else{
		if(strcmp(root->singer,s)==0){
			strcpy(str[cnt].s,root->name);
			cnt++;
		}
		search_artist(root->left,str,s);
		search_artist(root->right,str,s);
	}
}
node* delete_by_artist(node* root){
	struct strings str[22];
	cnt=0;
	char s[25];
	printf("\nenter name of artist you want to delete:");
	scanf("%s", s);
	search_artist(root,str,s);
	int i;
	for(i=0;i<cnt;i++){
		root=deleteNode(root,str[i].s);
	}
	return root;
}


int count=0;

struct strings names[25];
void check_tree(node* root,struct strings* str, int n){
	if(root==NULL){
		return;
	}else{
	    int c=0,i;
		for(i=0;i<n;i++){
			
			if((strcmp(str[i].s,root->singer)==0)||(strcmp(root->lyricist,str[i].s)==0)||(strcmp(root->album,str[i].s)==0)||(strcmp(root->composer,str[i].s)==0)||(strcmp(root->genre,str[i].s)==0)){
				c++;
			
			}
		}
		if(c==n){
			strcpy(names[count].s,root->name);
			count++;
		}
		check_tree(root->left,str,n);
		check_tree(root->right,str,n);
	}
}
node* find_node(node*root,char* s){
	if(root==NULL){
		return NULL; 
	}else if(strcmp(root->name,s)==0){
		return root;
	}else if(strcmp(s,root->name)<0){
		return find_node(root->left,s);
	}else{
		return find_node(root->right,s);
	}
		
	
}
node* create_playlist(node* root){
	int i,k;
	int n;
	printf("\nenter number of attributes:");
	scanf("%d", &n);
	struct strings str[n];
	for(i=0;i<n;i++){
		printf("\nenter 1 for singer,  2 for lyricist, 3 for album, 4 for composer, 5 for genre:");
		scanf("%d", &k);
		switch(k){
			case 1:
				printf("\nenter name of singer:");
				scanf("%s", str[i].s);
				break;
		    case 2:
				printf("\nenter name of lyricist:");
				scanf("%s", str[i].s);
				break;
			case 3:
				printf("\nenter name of album:");
				scanf("%s", str[i].s);
				break;
			case 4:
				printf("\nenter name of composer:");
				scanf("%s", str[i].s);
				break;	
			case 5:
				printf("\nenter name of genre:");
				scanf("%s", str[i].s);
				break;	
			default:
				printf("\nenter correct attribute:");
				
				break;						
		}
	}
	node* newroot = NULL;
	node* t;
	t->left=NULL;
	t->right=NULL;
	
	node* p= root;
	count=0;
	check_tree(root,str,n);

	for(i=0;i<count;i++){
		node* p=find_node(root, names[i].s);
		t=(node*)malloc(sizeof(node));
		
				strcpy(t->name,p->name);
				strcpy(t->singer,p->singer);
				strcpy(t->lyricist,p->lyricist);
				strcpy(t->album,p->album);
				strcpy(t->composer,p->composer);
				strcpy(t->genre,p->genre);
				strcpy(t->duration,p->duration);
				newroot = insert(newroot,t);
	}
    

	
	
	return newroot;
	
}
int a=0;
void inorderserial(node* root){
	if(root==NULL){
		return;
	}else{
		
		inorderserial(root->left);
		
	    a++;
		printf(" %d) song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",a,root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
        
        
	    inorderserial(root->right);
	    
	   
	}
}
void inorder_node(node* root,int k){
	if(root==NULL){
		
	}else{
		
		
		inorder_node(root->left,k);
		a++;
		 if(a==k){
			printf(" %d) song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",a,root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
            
	    }
		
	    inorder_node(root->right,k);
	    
	}
}

void q6(node* root){
	a=0;
    inorderserial(root);
	int k;
	printf("\nenter serial number of song:");
	scanf("%d", &k);
	
	if(k>a){
		printf("\nenter correct serial number");
	}else{
		if(k==a){
			printf(" prev is:");
			a=0;
			inorder_node(root,k-1);
			a=0;
			inorder_node(root,k);
			printf("\nnext doesnot exist\n");
		
		}
		else if(k==1){
			printf("\nprev doesnot exist\n");
			a=0;
			inorder_node(root,k);
			printf(" next is:");
			a=0;
			inorder_node(root,k+1);
		}else{
			printf(" prev is:");
			a=0;
			inorder_node(root,k-1);
			a=0;
			inorder_node(root,k);
			printf(" next is:");
			a=0;
			inorder_node(root,k+1);
		}
	}

}
void q7(node*root){
	node*p=root;
	int c=1;
	a=0;
	inorderserial(root);
	int y=a;
    int k,x,c1=0;
    int n;
    printf("\nenter serial number:");
    scanf("%d", &n);
    printf("\nenter the value of k:");
    scanf("%d", &k);
    a=0;
    inorder_node(root, n);
    
    printf("\nenter 0 for up and 1 for down:");
    scanf("%d", &x);
    if(x==0){
    	if(n-k>0){
		a=0;
    	inorder_node(root, n-k);
	}else{
		printf("\ndoesnot exist\n");
	}
    	
	}else{
		if(n+k<y){
			
		a=0;
	    inorder_node(root, n+k);
	}else{
			printf("\ndoesnot exist\n");
	}
		
	}
	
}


node* q9(node* root){
	node *p, *newroot=NULL,*t;
	char str[25];
	printf("\nenter an attribute:");
	scanf("%s", str);
	p=root;
	while(p!=NULL){
		
		    
			if(strcmp(p->singer,str)==0||strcmp(p->lyricist,str)==0||strcmp(p->album,str)==0||strcmp(p->composer,str)==0||strcmp(p->genre,str)==0){
				t=(node*)malloc(sizeof(node));
				strcpy(t->name,p->name);
				strcpy(t->singer,p->singer);
				strcpy(t->lyricist,p->lyricist);
				strcpy(t->album,p->album);
				strcpy(t->composer,p->composer);
				strcpy(t->genre,p->genre);
				strcpy(t->duration,p->duration);
				newroot = insert(newroot,t);
				
			}
		
			
		}
		
	
	return newroot;
	
}

void play(node* root,char* str){
    
    if(root==NULL){
		return;
	}else{
		node* p=root;
		play(root->left, str);
		if(strcmp(root->name,str)==0){
	
		printf("\n song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
    	}
        play(root->right,str);
	}
 }
 void random_play(node* root,int k,char* s){
	if(root==NULL){
		
	}else{
		
		
		random_play(root->left,k,s);
		a++;
		 if(a==k&&strcmp(root->name,s)!=0){
			printf(" %d) song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",a,root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
            
	    }
		
	    random_play(root->right,k,s);
	    
	}
}
void q10(node* root){
	int i,k,y;
	char str[25];
	a=0;
	inorderserial(root);
	y=a;
	printf("\nenter song name:");
	scanf("%s", str);
	for(i=0;i<21;i++){
		k=rand();
		k=k%y+1;
		a=0;
		random_play(root,k,str);
	}
	
	play(root,str);
 
}

 node* insert_bysinger(node* nnode, node* newnode)
{
    /* 1.  Perform the normal BST insertion */
    if (nnode == NULL)
        return(newnode);
 
    if (strcmp(newnode->singer,nnode->singer)<0)
        nnode->left  = insert_bysinger(nnode->left, newnode);
    else if (strcmp(newnode->singer,nnode->singer)>0)
        nnode->right = insert_bysinger(nnode->right, newnode);
    else // Equal keys are not allowed in BST
        return nnode;
 
    /* 2. Update height of this ancestor node */
    nnode->height = 1 + max(height(nnode->left),
                        height(nnode->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(nnode);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(newnode->singer,nnode->singer)<0)
        return rightRotate(nnode);
 
    // Right Right Case
    if (balance < -1 && strcmp(newnode->singer,nnode->singer)>0)
        return leftRotate(nnode);
 
    // Left Right Case
    if (balance > 1 && strcmp(newnode->singer,nnode->singer)>0)
    {
        nnode->left =  leftRotate(nnode->left);
        return rightRotate(nnode);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(newnode->singer,nnode->right->singer)<0)
    {
        nnode->right = rightRotate(nnode->right);
        return leftRotate(nnode);
    }
 
    /* return the (unchanged) node pointer */
    return nnode;
}
node* input_bysinger(){
    node* root,*current;
	FILE *fptr=fopen("input (2).txt", "r");
	root=NULL;
	int i,c=0;
	for(i=1;i<=25;i++){
	  node*newsong;
      newsong = (node*) malloc(sizeof(node));
      newsong->right=NULL;
      newsong->left=NULL;
      fscanf(fptr,"\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",newsong->name,newsong->singer,newsong->lyricist,newsong->album,newsong->composer,newsong->genre,newsong->duration);
      root=insert_bysinger(root,newsong);  
	}
	fclose(fptr);
	return root;
	
}
void q11(node* root, char* s1, char *s2){
	if(root==NULL){
		
	}else{
		q11(root->left,s1,s2);
		if(strcmp(root->singer,s1)>=0&&strcmp(root->singer,s2)<=0){
			    printf("\n********************************************************\n");
				printf(" singer name: %s\n song name: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",root->singer, root->name, root->lyricist, root->album, root->composer, root->genre, root->duration);
        
		}
		q11(root->right,s1,s2);
	}
}
/*1. Write a function, InsertSong(), which reads a song from user and insert into a tree 
database of structures.

2. Write a function removeDuplicates() to remove the duplicate entries from the records.

3. Write a function to printPlaylist() which prints the records in the tree database in
ascending as well as in descending order.

4. Write a function to DeleteSong() to delete the particular song details from the treedatabase as per the song_name and also as per the name of the artist provided by the user 
and deletes all the entries with that artist.

5. Create a play-list (using a tree data structure) based on the attribute and its value given. 
For example, if “singer” attribute is provided and “Kishor Kumar” is the name of the 
singer, then a new play-list is created containing all the songs belonging to Kishore 
Kumar. The songs for the same singer to be sorted based on lexicographic order of the 
songs. Multiple attributes and their values can also be provided to create the play-list. For 
example if attributes given are “singer” and “film” and corresponding values provided are 
“Kishor Kumar” and “Sholay”, then all songs belonging to Kishore Kumar in Sholay are 
added into the play-list and likewise.
 
6. (Dis)Play a song in a play-list. In our setting this will mean, given a play-list as input, 
show/print all songs in the play-list indexed with serial numbers. User can select a serial 
number of the song, and data corresponding to the selected song is required to be 
displayed. At the same time, name of the previous as well as next song is also displayed. 
User is provided an option to select “Next” or “Prev” song. By selecting one of the 
options either “Next” or “Prev”, respectively data for next and previous song is displayed. 

7. Given a play-list and the serial number of the song, display details of the song. At this 
point, given an integer offset “k” and direction “up” or “down”, display the details of kth
previous or kth next song, from the current song, respectively, in the play-list. 

8. Given a play-list and the serial number of the song, display details of the song. Provide an 
option to the user to select one or many attributes of this “current” song and create a playlist for these attribute values from the original database. 

9. Filter the playlist. Given a play-list and an attribute value, filter all songs in the playlist 
matching the attribute value. For example, if play-list is for “Kishore Kumar” and 
attribute value is given for genre as “comedy”, all songs in the current playlist with genre 
as “comedy” will be chosen. 

10. Shuffle to something else. Take a set of attributes and their values as inputs. Randomly 
select any song from the original database matching all the attribute values provided. 
Mark it using FLAG so that it doesn’t get a chance again till all other songs in the playlist 
are played randomly.

11. Range-search – Search songs belonging to singers whose names are in-between singername-1 and singer-name-2, in lexicographic sorting sens
*/


int main(){
	node* root=input();
	inorder(root);
	
	int j,q,k;
	
	node* newpl,*p;
	for(j=1;j<=11;j++){
	char s1[25], s2[25];
	printf("\nenter question number:");
	scanf("%d", &q);
	char str[25];
	
	switch(q){
		
		case 1:
			  root=q1(root);
			  inorder(root);
			break;
		case 2:
			inorder(root);
			
			break;
		case 3:
			inorder(root);
			descending(root);
			
			break;
		case 4:
			
			printf("\nenter 0 for song name, 1 for artist: ");
			scanf("%d", &k);
		
			if(k==0){
				
			  root=delete_by_name(root);
			  inorder(root);
			}
			if(k==1){
				
			  root=delete_by_artist(root);
			  inorder(root);
			}
			break;
		case 5:
			newpl=create_playlist(root);
			
			inorder(newpl);
			break;
		case 6:
			q6(root);
			break;
		case 7:
			q7(root);
			break;
		case 8:
			a=0;
			p=root;
			inorderserial(p);
			printf("\nenter serial number of song:");
			scanf("%d", &k);
			a=0;
			inorder_node(p, k);
			printf("%s", p->name);
			newpl=create_playlist(p);
			
			inorder(newpl);
			break;
		case 9:
			newpl=create_playlist(root);
			
			p=create_playlist(newpl);
		    inorder(p);
			break;
		case 10:
			q10(root);
			break;
		case 11:
			newpl=input_bysinger();
			inorder(newpl);
			printf("\nenter 1st singer name:");
			scanf("%s", s1);
			printf("\nenter 2nd singer name:");
			scanf("%s", s2);
			q11(root,s1,s2);
			break;
		default:
		    printf("\ninvalid question number");
			break;									
	}
	
    }
	return 0;
}
