#include <stdio.h>
#include <string.h>

struct team {
    char country[20];
    char date[20];
    int goals_scored;
    int goals_conceded;
} t;

void record(){
    printf("\e[1;1H\e[2J");
    FILE *p;
    int cond = 1;
    p = fopen("teams.txt", "a");
    while(cond){
        printf("\e[1;1H\e[2J");
        printf("Enter the Country Name:...");
        scanf("%s", t.country);
        printf("Enter the date in the format dd-mm-yy:...");
        scanf("%s", t.date);
        printf("Enter the number of goals scored:...");
        scanf("%d", &t.goals_scored);
        printf("Enter the number of goals conceded:...");
        scanf("%d", &t.goals_conceded);
        if(p != NULL){
            fprintf(p,"%s\t%s\t%d\t%d\n",  t.date, t.country, t.goals_scored, t.goals_conceded);
            printf("\n\n The game has been recorded successfully");
        }else{
            printf("\n\n System Error\n");
        }

        printf("\n\n Do you want to record another game\n Press 1: To continue \n Press 0: to Quit");
        scanf("%d", &cond);

    }
    fclose(p);

}

void display(){
    printf("\e[1;1H\e[2J");
    FILE *p;
    p = fopen("teams.txt", "r");
    if(p != NULL){
        printf("\n\n Diplaying all Matches\n");
        printf("Date\t\tCountry\t\tGoals Scored\t\tGoals Conceded\n");
        printf("====\t\t=======\t\t===== ======\t\t===== ========\n");
        while(!feof(p) && fscanf(p,"%s\t%s\t%d\t%d", t.date, t.country, &t.goals_scored, &t.goals_conceded) == 4){
            printf("%s\t\t%s\t\t%d\t\t    %d\n", t.date, t.country, t.goals_scored, t.goals_conceded);
        }
        printf("\n\nThese are the recorded games right now in our system\n");
    }else{
        printf("\n\n Currently no records in our system.\n");
    }
    fclose(p);
}

void display_Teams(){
    struct team ts[50];
    struct team new_ts[50] = {};
    int ts_no = 0;
    int total_goals = 0, goals_conceded = 0, c = 0;
    FILE *p;
    p = fopen("teams.txt", "r");
    if(p != NULL){
        printf("\n\n Diplaying teams with more goals than the conceded ones\n");
        printf("______________________________________________________________\n");
        while(!feof(p) && c < 50){
            if(fscanf(p, "%s\t%s\t%d\t%d\n", ts[c].date, ts[c].country, &ts[c].goals_scored, &ts[c].goals_conceded) == 4){
                c++;
            }else{
                break;
            }

        }
        for(int i = 0; i < c; i++){
            for(int k = 0;k <= i ; k++){
                if(strcmp(ts[i].country, new_ts[k].country) == 0){
                    new_ts[k].goals_scored += ts[i].goals_scored;
                    new_ts[k].goals_conceded += ts[i].goals_conceded;
                }else if(strcmp(new_ts[k].country, "") == 0 && new_ts[k].goals_scored == 0){
                    int my_check = 0;
                    for(int y = 0; y <= i; y++){
                        if(strcmp(ts[i].country, new_ts[y].country) == 0){
                            my_check++;
                        }
                    }
                    if(my_check == 0){
                        strcpy(new_ts[k].date, ts[i].date);
                        strcpy(new_ts[k].country, ts[i].country);
                        new_ts[k].goals_scored = ts[i].goals_scored;
                        new_ts[k].goals_conceded = ts[i].goals_conceded;
                        ts_no++;
                    }

                }

            }
        }
        for(int i = 0; i < ts_no; i++){
            if(new_ts[i].goals_scored >  new_ts[i].goals_conceded){
                printf("%s\t\t%d\t\t%d\n", new_ts[i].country, new_ts[i].goals_scored, new_ts[i].goals_conceded);
            }

        }
    }else{
        printf("\n\nSystem Error\n");
    }
    fclose(p);
}

void main(){
    int cond = 1, choice;
    printf("___WELCOME TO THE TEAMS MANAGEMENT SYSTEM___\n");
    while(cond){
        printf("\nPress the following keys to interact with the system");
        printf("\n1: To record a new game\n2: To display all Games\n3: To diplay teams with more goals than the conceded ones\n0: To quit the program\n");
        printf("Enter your choice:...");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                record();
                break;
            case 2:
                display();
                break;
            case 3:
                display_Teams();
                break;
            case 0:
                cond = 0;
                break;
            default:
                printf("\nEnter a valid choice please!!!\n");
        }
    }
    return;
}
