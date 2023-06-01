/*We need to design a data structure for music player. A linked list can store the database of all 
music listings. Each music listing will have attributes like singer, lyricist, album/film, 
composer, genre, duration of the song and any other you may choose. We need to define 
following operations*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define SIZE 25
typedef struct node_tag{
	char name[25];
	char singer[25];
	char lyricist[25];
	char album[25];
	char composer[25];
	char genre[25];
	char duration[20];
	struct node_tag* next;
	struct node_tag* prev;
}node;
typedef struct accessTable_tag
{
    node *head;
    node *tail;
}accessTable;


node* input(){
    node* head,*current;
	FILE *fptr=fopen("dspd_input.txt", "r");
	head=NULL;
	int i,c=0;
	for(i=1;i<=25;i++){
	  node*newSong;
      newSong = (node*) malloc(sizeof(node));
      newSong->prev=NULL;
      newSong->next=NULL;
      fgets(newSong->name,SIZE,fptr);
      fgets(newSong->singer,SIZE,fptr);
      fgets(newSong->lyricist,SIZE,fptr);
      fgets(newSong->album,SIZE,fptr);
      fgets(newSong->composer,SIZE,fptr);
      fgets(newSong->genre,SIZE,fptr);
      fgets(newSong->duration,SIZE,fptr);
      if (head == NULL) {
            head = newSong;
            current=head;
        } else {
        	newSong->prev = current;
            current->next = newSong;
            current=newSong;
        }
        
        c++;
	}
	current->next=NULL;
	fclose(fptr);
    return head;
}
void print(node* head) {
    
   
    node* current;
    current=head;
    int c=1;
    while(current!=NULL){
	    printf("--------------------------------------------------------------------------------------------------\n");
        printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,current->name, current->singer, current->lyricist, current->album, current->composer, current->genre, current->duration);
        c++;
        current=current->next;
	    
	}
}

node* insert_song(node* head){
	node* new_song;
	
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
	new_song->next=NULL;
	new_song->prev=NULL;
	node*tail=head;
	while(tail->next!=NULL){
		tail=tail->next;
		
	}
	new_song->prev=tail;
	tail->next=new_song;
	tail=new_song;
	tail->next=NULL;
	return head;
}
node* remove_duplicates(node*head){
	node*p, *q;
	p=head;
	while(p!=NULL){
		q=p->next;
		while(q!=NULL){
			if(strcmp(p->name,q->name)==0){
				q->next->prev=q->prev;
				q->prev->next=q->next;
				node*t=q;
				q=q->next;
				free(t);
			}else{
				q=q->next;
			}
		}
		p=p->next;
	}
	return head;
}
node* delete_by_name(node*head, char* str){
	node *p;
	p=head;
    while(p!=NULL){
    	if(strcmp(p->name,str)==0){
    		    p->next->prev=p->prev;
				p->prev->next=p->next;
				node* t=p;
				p=p->next;
				free(t);	
		}else{
			p=p->next;
		}
	}
	return head;
}
node* delete_by_artist(node*head, char* str){
	node *p;
	p=head;
    while(p!=NULL){
    	if(strcmp(p->singer,str)==0){
    		    p->next->prev=p->prev;
				p->prev->next=p->next;
				node* t=p;
				p=p->next;
				free(t);	
		}else{
			p=p->next;
		}
	}
	return head;
}
node* Bucket_Sort(node *head,int k)
{
    node *finalhead = head;
    int i=k-1,j;
    while(i>=0)
    {
        accessTable at[26];
        for(j=0;j<26;j++)
        {
        at[j].head=at[j].tail=NULL;
        }

       node *ptr = finalhead;
       while(ptr != NULL)
       {
          int index = ptr->name[i]-'a';
          if(at[index].head == NULL)
          {
              at[index].head=at[index].tail=ptr;
          }
          else
          {
              at[index].tail->next = ptr;
              at[index].tail = ptr;
          }
          ptr=ptr->next;
       }
       node *fhead=NULL,*ftail=NULL;
       for( j=0;j<26;j++)
       {
           if(at[j].head != NULL)
           {
                if(fhead == NULL)
                {
                    fhead=at[j].head;
                    ftail=at[j].tail;
                }
                else
                {
                    ftail->next = at[j].head;
                    ftail = at[j].tail;
                }
           }
       }
       finalhead = fhead;
       ftail->next = NULL;
       i--;
       
    }
    return finalhead;
}
void printplaylist(node*head,int c){
	
	if(head==NULL){
		printf("****************************************************");
	}else{
	printf("%d) song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,head->name, head->singer, head->lyricist, head->album, head->composer, head->genre, head->duration);
        
	printplaylist(head->next,c+1);
	printf("%d) song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,head->name, head->singer, head->lyricist, head->album, head->composer, head->genre, head->duration);
      
   
    }
}
void q6(node*head){
	print(head);
	int k;
	printf("\nenter serial number of song:");
	scanf("%d", &k);
	node*p=head;
	int c=1;
	while(c<k){
		p=p->next;
		c++;
	}
	if(p->prev!=NULL&&p->next!=NULL){
		printf("\nprev:- %s", p->prev->name);
	 printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
        
        printf("\nnext:- %s", p->next->name);
		
	}
	 if(p->prev==NULL&&p->next!=NULL){
	 printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
        
        printf("\nnext:- %s", p->next->name);
	 }
	 if(p->prev!=NULL&&p->next==NULL){
	 	printf("\nprev:- %s", p->prev->name);
		printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
        
	 }
	 int a;
	 printf("\nenter 0 for previous song and 1 for next song: ");
	 scanf("%d", &a);
	 if(a==1){
	 	p=p->next;
	 	printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
        
	 }else if(a==0){
	 	p=p->prev;
	 	printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
        
	 }
	 
}
void q7(node*head,int n){
	node*p=head;
	int c=1;
	while(c<n){
		p=p->next;
		c++;
    }
    int k,a,c1=0;
    printf("\nenter the value of k:");
    scanf("%d", &k);
    printf("\nenter 0 for up and 1 for down:");
    scanf("%d", &a);
    if(a==0){
    	while(c1<k){
    		p=p->prev;
    		c1++;
		}
		printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c-c1,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
        
    	
	}else{
		while(c1<k){
    		p=p->next;
    		c1++;
		}
		printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c+c1,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
        
	}
   
	

	
}
void playinloop(node*head,int k){
	int c;
	for(c=1;c<=k;c++){
		print(head);
	}
}
struct strings{
	char s[25];
};

node* create_playlist(node*head){
	int n,i,k;
	
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
	node *p, *newhead,*tail,*t;
	p=head;
	newhead;

	while(p!=NULL){
		
		int c=0;
	
		for(i=0;i<n;i++){
		    printf("\n%s,%s,%d", p->singer,str[i].s, strcmp(str[i].s,p->singer) );
		    
			if((strcmp(str[i].s,p->singer)==0)||(strcmp(p->lyricist,str[i].s)==0)||(strcmp(p->album,str[i].s)==0)||(strcmp(p->composer,str[i].s)==0)||(strcmp(p->genre,str[i].s)==0)){
				c++;
			printf("\ninhn");	
			}
		}
		if(c==n){
		
			t=(node*)malloc(sizeof(node));
				strcpy(t->name,p->name);
				strcpy(t->singer,p->singer);
				strcpy(t->lyricist,p->lyricist);
				strcpy(t->album,p->album);
				strcpy(t->composer,p->composer);
				strcpy(t->genre,p->genre);
				strcpy(t->duration,p->duration);
				t->prev=NULL;
				t->next=NULL;
			if(newhead==NULL){
				newhead=t;
				tail=newhead;
				
			}else{
				t->prev=tail;
				tail->next=t;
				tail=t;
				
			}
			
		}
		p=p->next;
		 
	}
	
	return newhead;
	
}
node* q9(node*head, char*str){
	node *p, *newhead,*tail,*t;
	p=head;
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
				t->prev=NULL;
				t->next=NULL;
			if(newhead==NULL){
				newhead=t;
				tail=newhead;
				
			}else{
				t->prev=tail;
				tail->next=t;
				tail=t;
				
			}
			
		}
		
	}
	return newhead;
	
}
 
 node* q8(node* head){
 	int c,k;
 	node*p;
 	print(head);
	printf("\nenter serial number of song:");
	scanf("%d", &k);
	c=1;
	p=head;
	while(c<k){
		p=p->next;
		c++;
	}
	printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
    node* newhead=create_playlist(head);
	return newhead;    
	
 }
 void play(node* head, int k,char* str){
 	node* p=head;
 	int c=1;
 	while(c<k){
 		p=p->next;
 		c++;
	}if(strcmp(p->name,str)!=0){
	
	printf(" %d)song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",c,p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
    }
 }
 void q11(node*head){
 node* newhead=create_playlist(head);
 print(newhead);
 char str[25];
 printf("\nenter song name:");
 scanf("%s", str);
 int i;
 for(i=0;i<24;i++){
 int k=rand()%25+1;
 play(head,k,str);
	
 }
 node*p=head;
 while(p!=NULL){
 	
 if(strcmp(p->name,str)==0){
 
 printf(" song name: %s\n singer: %s \n lyricist %s\n album: %s\n composer: %s\n genre: %s\n duration: %s\n",p->name, p->singer, p->lyricist, p->album, p->composer, p->genre, p->duration);
 }
 p=p->next;
 }
}


int	main(){
	node* head=input();
	print(head);
	int q,k,i,j,c=0;
	node*newpl,*p;

	for(j=1;j<=11;j++){
	
	printf("\nenter question number:");
	scanf("%d", &q);
	char str[25];
	
	switch(q){
		/*Write a function, InsertSong(), which reads a song from user and insert into a linked list 
of structures. Add a new song at the end in the list*/
		case 1:
			  head=insert_song(head);
			  print(head);
			break;
		/*2. Write a function removeDuplicates() to remove the duplicate entries from the records.*/
		case 2:
			head=remove_duplicates(head);
			print(head);
			break;
		/*3. Write a function to printPlaylist() which prints the records in the linked list in ascending 
as well as in descending order.*/
		case 3:
			
			printplaylist(head,1);
			break;
		/*4. Write a function to DeleteSong() to delete the particular song details from the linked list 
as per the song_name and also as per the name of the artist provided by the user and 
deletes all the entries with that artist*/
		case 4:
			
			printf("\nenter 0 for song name, 1 for artist");
			scanf("%d", &k);
			char str[25];
			if(k==0){
				printf("\nenter song name:");
				scanf("%s", str);
			  head=delete_by_name(head,str);
			  print(head);
			}
			if(k==1){
				printf("\nenter song artist:");
				scanf("%s", str);
			  head=delete_by_artist(head,str);
			  print(head);
			}
			break;
		/*5. Create a play-list based on the attribute and its value given. For example, if “singer” 
attribute is provided and “Kishor Kumar” is the name of the singer, then a new play-list is 
created containing all the songs belonging to Kishore Kumar. The songs for the same 
singer to be sorted based on lexicographic order of the songs. Multiple attributes and their 
values can also be provided to create the play-list. For example if attributes given are 
“singer” and “film” and corresponding values provided are “Kishor Kumar” and 
“Sholay”, then all songs belonging to Kishore Kumar in Sholay are added into the playlist and likewise. */
		case 5:
			newpl=create_playlist(head);
			print(newpl);
			break;
		/*6. (Dis)Play a song in a play-list. In our setting this will mean, given a play-list as input, 
show/print all songs in the play-list indexed with serial numbers. User can select a serial 
number of the song, and data corresponding to the selected song is required to be 
displayed. At the same time, name of the previous as well as next song is also displayed. 
User is provided an option to select “Next” or “Prev” song. By selecting one of the 
options either “Next” or “Prev”, respectively data for next and previous song is displayed. */
		case 6:
			q6(head);
			break;
		/*7. Given a play-list and the serial number of the song, display details of the song. At this 
point, given an integer offset “k” and direction “up” or “down”, display the details of kth
previous or kth next song, from the current song, respectively, in the play-list.*/
		case 7:
			printf("\nenter serial number:");
			scanf("%d", &k);
			q7(head,k);
			break;
		/*8. Given a play-list and the serial number of the song, display details of the song. Provide an 
option to the user to select one or many attributes of this “current” song and create a playlist for these attribute values from the original database*/
		case 8:
			
			p=q8(head);
			print(p);
			break;
		/*9. Filter the playlist. Given a play-list and an attribute value, filter all songs in the playlist 
matching the attribute value. For example, if play-list is for “Kishore Kumar” and 
attribute value is given for genre as “comedy”, all songs in the current playlist with genre 
as “comedy” will be chosen. */
		case 9:
			newpl=create_playlist(head);
			printf("\nenter an attribute:");
			scanf("%s", str);
			p=q9(newpl,str);
			print(p);
			break;
		/*10. Play-in-loop. Of the available play-lists, select a play-list and take an integer k as input. 
Display details of play-list in a loop k times, as if the play-list is being played k times in 
loop. */
		case 10:
			printf("\nenter value of k:");
			scanf("%d", &k);
			playinloop(head,k);
			break;
		/*11. Shuffle to something else. Take a set of attributes and their values as inputs. Randomly 
select any song from the original database matching all the attribute values provided. 
Mark it using FLAG so that it doesn’t get a chance again till all other songs in the playlist 
are played randomly*/
		case 11:
			q11(head);
			
			break;
		default:
		    printf("\ninvalid question number");
			break;									
	}
}
   
	return 0;
}
