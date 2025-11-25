#include<stdio.h>
#include<string.h>

void admin_control(char candidate_name[][50],char candidate_id[][10],char candidate_logo[][2],int *Rcandidate,char voter_id[][8],int *voterCount,char voter_logo[][2],int no_of_votes[10],char voter_name[][50]);
void voting(char voter_id[][8],int *voterCount,char voter_logo[][2],int Rcandidate,char candidate_logo[][2],int no_of_votes[10],char voter_name[][50]);
void saveFiles(int Rcandidate,int voterCount,char candidate_name[][50],char candidate_id[][10],char candidate_logo[][2],int no_of_votes[10],char voter_id[][8],char voter_name[][50],char voter_logo[][2]);
void loadFiles(int *Rcandidate,int *voterCount,char candidate_name[][50],char candidate_id[][10],char candidate_logo[][2],int no_of_votes[10],char voter_id[][8],char voter_name[][50],char voter_logo[][2]);


char password[]="ADMIN123";

int main(){
    char candidate_name[10][50];
    char candidate_id[10][10];
    char candidate_logo[10][2];
    char voter_id[500][8];
    char voter_logo[500][2]={0};
    char voter_name[500][50];
    int no_of_votes[10]={0};

    int Rcandidate=0;
    int voterCount=0;

    loadFiles(&Rcandidate,&voterCount,candidate_name,candidate_id,candidate_logo,no_of_votes,voter_id,voter_name,voter_logo);

   int option=0;
   char passkey[9];
   while(option!=3){
   printf("\n==========Welcome to E-voting Machine============\n");
   printf("Select if you are an admin or a voter:\n");
   printf("1.Admin\n2.Voter\n3. --exit-- the process of voting\n Enter:");
   scanf(" %d", &option);

   switch(option){
    case 1: printf("\nEnter the password for ADMIN:\n--->");
            scanf("%s",passkey);
            if(strcmp(password,passkey)==0){
                admin_control(candidate_name,candidate_id,candidate_logo,& Rcandidate,voter_id,& voterCount,voter_logo,no_of_votes,voter_name);
            }else{
                printf("incorrect password entered\n");
            }
    break;
    case 2: printf("\n============ Voting Booth ============\n");
            voting(voter_id,& voterCount,voter_logo,Rcandidate,candidate_logo,no_of_votes,voter_name);
    break;
    case 3: printf("Saving data and exiting...");
            saveFiles(Rcandidate,voterCount,candidate_name,candidate_id,candidate_logo,no_of_votes,voter_id,voter_name,voter_logo);
    break;
    default:printf("Invalid option selected");
    break;

   }
 }
}

void admin_control(char candidate_name[][50],char candidate_id[][10],char candidate_logo[][2],int *Rcandidate,char voter_id[][8],int *voterCount,char voter_logo[][2],int no_of_votes[10],char voter_name[][50]){
    int options,i,j,idresult,total_votes=0,MaxNoVotes;
    char temp_id[10];
    do{
    printf("\n======Admin Controls=======\n");
    printf("Enter which option you want to select:\n1.Register a new candidate\n2.Register a new voter\n3.Display candidate Information\n4.Display voter information\n5.Announce the winner\n6.Exit\nEnter--->");
    scanf(" %d", &options);

    switch(options){
        case 1: do{
                    idresult=0;
                printf("Enter the id (9 DIGITS) of the candidate:");
                scanf(" %9[^\n]",temp_id);

                for(i=0;i<*Rcandidate;i++){
                       if(strcmp(temp_id,candidate_id[i])==0){
                        printf("the candidate exists already! Enter again...");
                        idresult=1;
                        break;
                       }                               
                }
                if(idresult==0){
                    strcpy(candidate_id[*Rcandidate],temp_id);
                }
                }while(idresult==1);

                printf("Enter the name of the candidate:");
                scanf(" %49[^\n]",candidate_name[*Rcandidate]);

                printf("Enter LOGO of the candidate:");
                scanf(" %1[^\n]",candidate_logo[*Rcandidate]);

                (*Rcandidate)++;
               
    break;
    case 2: do{
                idresult=0;
                printf("Enter your 7 digit voter id:");
                scanf(" %7[^\n]",temp_id);

                for(i=0;i<*voterCount;i++){
                       if(strcmp(temp_id,voter_id[i])==0){
                        printf("Voter ID already exists! Try again...\n");
                        idresult=1;
                        break;
                       }                               
                }
                if(idresult==0){
                    strcpy(voter_id[*voterCount],temp_id);
                }
            }while(idresult==1);

            printf("Enter the Name of the Voter --->"); 
            scanf(" %49[^\n]", voter_name[*voterCount]);
            (*voterCount)++;
    break;
    case 3: printf("\n============= CANDIDATE INFORMATION ============\n");
            printf("%-15s %-25s %-15s %-10s\n", "Candidate ID", "Candidate Name", "Logo", "Votes");

            total_votes = 0;
    
            for(int i=0;i<*Rcandidate;i++){
                printf("%-15s %-25s %-15s %-10d\n",candidate_id[i],candidate_name[i],candidate_logo[i],no_of_votes[i]);
                total_votes+=no_of_votes[i];
            }
            printf("\n\n");
            printf("The total votes that have been casted are %d",total_votes);
    break;
    case 4: printf("\n============= VOTER INFORMATION ============\n");
            printf("%-12s %-20s %-12s\n","voter_id","voter_name","voter_candidate_choice");
            for(int i=0;i<*voterCount;i++){
                printf("%-12s %-20s %-12s\n",voter_id[i],voter_name[i],voter_logo[i]);
            }
    break;
    case 5: MaxNoVotes=0;

            for(int i=0;i<*Rcandidate;i++){
             if(no_of_votes[i]>MaxNoVotes){
                MaxNoVotes=no_of_votes[i];
             }
            }
            
            if(MaxNoVotes == 0){
             printf("\nNo votes have been cast yet... no winner can be declared!\n");
             break; 
            }

            printf("================== ELECTION RESULT (WINNER) ====================\n");
            for(int i=0;i<*Rcandidate;i++){
             if(no_of_votes[i]==MaxNoVotes){
                printf("%-12s %-20s %-12s \n",candidate_id[i],candidate_name[i],candidate_logo[i]);
             }
            }
            
            printf("\n\n");
            printf("The winner/winners recieved %d votes!",MaxNoVotes);
    break;
    case 6: printf("Returning to the main menu...");
            return;
    break;        
    }
    }while(options!=6); 

    return;  
    

}

void voting(char voter_id[][8],int *voterCount,char voter_logo[][2],int Rcandidate,char candidate_logo[][2],int no_of_votes[10],char voter_name[][50]){
    char tempVoterid[9];
    int logo_check=0;
    if(Rcandidate<1){
        printf("There is no registered candidate to vote, please register a candiate to vote\n\n");
        return;
    }

    printf("Enter the registered voter id:");
    scanf(" %8[^\n]",tempVoterid);

    for(int i=0;i<*voterCount;i++){
    if(strcmp(tempVoterid,voter_id[i])==0){
        if(voter_logo[i][0] != '\0') { 
        printf("\nError... This voter Id has already cast a vote!\n");
        return;
        }

       printf("Enter the logo of the candidate you want to vote to:\n");
       for(int k=0;k<Rcandidate;k++){
        printf(" %d.%s\n ",k+1,candidate_logo[k]);
       }
       printf("Enter--->");
       scanf(" %1[^\n]",voter_logo[i]); 

       for(int j=0;j<Rcandidate;j++){
         if(strcmp(voter_logo[i],candidate_logo[j])==0){
          (no_of_votes[j])++;
          logo_check=1;
         }
       }
       if(logo_check==1){
        printf("Vote has been Casted successfully!");
       }else{
        printf("invalid choice of logo... ---vote did not cast---");
        voter_logo[i][0] = '\0';
       }
       return;
    }
    }

    printf("The voter does not exist in the database, please register it\n\n ");
    return;

}

void saveFiles(int Rcandidate,int voterCount,char candidate_name[][50],char candidate_id[][10],char candidate_logo[][2],int no_of_votes[10],char voter_id[][8],char voter_name[][50],char voter_logo[][2]){
    FILE *fp;
    fp=fopen("candidates.txt","w");
    if(fp!=NULL){
        fprintf(fp,"%d\n",Rcandidate);
        for(int i=0;i<Rcandidate;i++){
            fprintf(fp,"%s\n%s\n%s\n%d\n",candidate_id[i],candidate_name[i],candidate_logo[i],no_of_votes[i]);
        }
        fclose(fp);
    }

    fp=fopen("voters.txt","w");
    if(fp!=NULL){
        fprintf(fp,"%d\n",voterCount);
        for(int i=0;i<voterCount;i++){
            char tempLogo[5];
            if(voter_logo[i][0]=='\0'){
                strcpy(tempLogo,"NV");
            }else{
                strcpy(tempLogo,voter_logo[i]);
            }
            fprintf(fp,"%s\n%s\n%s\n",voter_id[i],voter_name[i],tempLogo);
        }
        fclose(fp);
    }
    printf("\nData saved successfully to database!\n");
}

void loadFiles(int *Rcandidate,int *voterCount,char candidate_name[][50],char candidate_id[][10],char candidate_logo[][2],int no_of_votes[10],char voter_id[][8],char voter_name[][50],char voter_logo[][2]){
    FILE *fp;
    fp=fopen("candidates.txt","r");
    if(fp!=NULL){
        fscanf(fp,"%d",Rcandidate);
        fgetc(fp);
        for(int i=0;i<*Rcandidate;i++){
            fscanf(fp,"%[^\n]",candidate_id[i]); fgetc(fp);
            fscanf(fp,"%[^\n]",candidate_name[i]); fgetc(fp);
            fscanf(fp,"%s",candidate_logo[i]); fgetc(fp);
            fscanf(fp,"%d",&no_of_votes[i]); fgetc(fp);
        }
        fclose(fp);
    }

    fp=fopen("voters.txt","r");
    if(fp!=NULL){
        fscanf(fp,"%d",voterCount);
        fgetc(fp);
        for(int i=0;i<*voterCount;i++){
            fscanf(fp,"%[^\n]",voter_id[i]); fgetc(fp);
            fscanf(fp,"%[^\n]",voter_name[i]); fgetc(fp);
            
            char tempLogo[5];
            fscanf(fp,"%s",tempLogo); fgetc(fp);

            if(strcmp(tempLogo,"NV")==0){
                voter_logo[i][0]='\0';
            }else{
                strcpy(voter_logo[i],tempLogo);
            }
        }
        fclose(fp);
    }
}