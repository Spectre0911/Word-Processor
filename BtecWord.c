#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>



void createFile(){
    FILE *fp;
    char fileName[30];
    printf("Please enter the name of the file you wish to create: ");
    // ***Change this to be safe***
    scanf("%s", fileName);
    // Reference https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
    if ((fp = fopen(fileName, "r"))){
        printf("The named file allready exists\n Exiting... \n");
    }
    else{
        printf("Creating file... \n");
        fp = fopen(fileName,"a");
        printf("Your file has been created! Check in the directory this software is in  \n");

    }
    fclose(fp);
}

void copyFile(){
    char fileName[30];
    FILE *sourceFile;
    FILE *copyFile;
    printf("Please enter a file name to copy: \n");
    // Make safe with validation
    scanf("%s" ,fileName);
    // Reference https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
    if ((sourceFile = fopen(fileName, "r"))){
        printf("Copying file.... \n");
        // Pointers for file to copy anf file that is being copied to
        char copyFileName[30];
        strcpy(copyFileName, fileName);
        strcpy(copyFileName, "Copy");
        copyFile = fopen(copyFileName,"a");
        // Average number of characters per page.
        char ch;
        while ((ch = fgetc(sourceFile)) != EOF){
            fputc(ch,copyFile);
        }
    }
    else{
        printf("File does not exist \n Please enter a file that exists \n Exiting... \n");
    }
    fclose(sourceFile);
    fclose(copyFile);
}

void deleteFile(){
    char fileName[30];
    FILE *fp;
    printf("Please enter the name of the file you wish to delete: \n");
    // ***Change this to be safe***
    scanf("%s", fileName);
    // Reference https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
    if ((fp = fopen(fileName, "r"))){
        printf("Deleting file... \n");
        // remove returns an integer that states whether file deletion worked or not
        int check = remove(fileName);
        if (check == 0){
            printf("The file has been deleted \n ");
        }
        else{
            printf("There was an errot deleting the specified file \n");
        }
    }
    else{
        printf("The named file cannot be deleted as it does not exist in the current directory \n ");
    }
}


void showFileAndCountLines(int mode){
    int count = 0;
    FILE *fp;
    char fileName[30];
    printf("Please enter the name of the file you wish to show the contents of: ");
    // ***Change this to be safe***
    scanf("%s", fileName);
    // Reference https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
    if ((fp = fopen(fileName, "r"))){
        char ch = fgetc(fp);
        while (ch != EOF){
            // Checks if the function is being used as show file
            if ((int) ch == 10){
                count ++;
            }
            if (mode == 0){
                printf ("%c", ch);
            }
            ch = fgetc(fp);
        }
        // Checks if the function is being used as count lines
        if (mode == 1){
            printf("There are %d lines in %s \n",count,fileName);
        }
    }
    
    else{
        printf("The file you are trying to read does not exist please enter a alternate name or create the file first \n");
    }
    fclose(fp);

}

void appendLine(){
    FILE *fp;
    char fileName[30];
    printf("\nPlease enter the name of the file you wish to append to: ");
    // ***Change this to be safe***
    fgets(fileName,30,stdin);
    int length = strlen(fileName);
    fileName[length-1] = '\0';
    /*
    printf("%d \n",length);
    for (int i = 0; i < length; i++){
        printf("%d ", fileName[i]);
    }
    */
    // printf("\nThe stored name of the file you are trying to access is: %s\n", fileName);
    if ((fp = fopen(fileName, "r"))){
        char line[100];
        fclose(fp);
        fp = fopen(fileName, "a");
        printf("\nPlease enter the text (MAX 80 characters) you wish to append to the file: ");
        // ***Change this to be safe***
        fgets(line,100,stdin);
        fputs(line,fp);
    }
    else{
        printf("The file you are trying to append to does not exist please enter a alternate name or create the file first \n");
    }
    fclose(fp);
}



void deleteLine(){
    FILE *initialFile;
    FILE *tempFile;

 
    char ch;
    char lineNumberString[10];
    char fileName[30];
    int count = 1;
    int length;
    int lineNumber;


    printf("Please enter the file name you wish to delete a line from: ");
    fgets(fileName,30,stdin);

    length = strlen(fileName);
    fileName[length-1] = '\0'; 

   

    if ((initialFile = fopen(fileName, "r"))){
        printf("Please enter the line number you wish to delete: ");
        fgets(lineNumberString,10,stdin);
        lineNumber = atoi(lineNumberString);

        tempFile = fopen("temp.txt","w+");

        ch = fgetc(initialFile);
        while (ch != EOF){

            if (count != lineNumber){
                fputc(ch,tempFile);
            }


            // Important this comes after
            if ((int) ch == 10){
                 count ++;
            }
            ch = fgetc(initialFile);
        }
        fclose(initialFile);
        fclose(tempFile);
        remove(fileName);
        rename("temp.txt",fileName);
        printf("Deleted the line...");
    }

    else{
        printf("The file you are trying to edit does not exist please enter a alternate name or create the file first \n");
        fclose(initialFile);
    }

}

void insertLine(){
    FILE *initialFile;
    FILE *tempFile;

 
    char ch;
    char lineNumberString[10];
    char fileName[30];
    char lineToInsert[100];
    int count = 1;
    int length;
    int lineNumber;


    printf("Please enter the file name you wish to insert a line into: ");
    fgets(fileName,30,stdin);

    length = strlen(fileName);
    fileName[length-1] = '\0'; 

   

    if ((initialFile = fopen(fileName, "r"))){
        printf("Please enter the line number you wish to insert to: ");
        fgets(lineNumberString,10,stdin);
        lineNumber = atoi(lineNumberString);

        printf("Please enter the text you wish to insert to line %d: ",lineNumber);
        fgets(lineToInsert,100,stdin);


        tempFile = fopen("temp.txt","w+");

        ch = fgetc(initialFile);
        int completedInsertion = 0;
        while (ch != EOF){

            if (count == lineNumber && completedInsertion == 0){
                fputs(lineToInsert,initialFile);
                completedInsertion = 1;
            }
            
            fputc(ch,tempFile);

            // Important this comes after
            if ((int) ch == 10){
                 count ++;
            }
            ch = fgetc(initialFile);
        }
        fclose(initialFile);
        fclose(tempFile);
        remove(fileName);
        rename("temp.txt",fileName);
        printf("Inserted the line...");
    }

    else{
        printf("The file you are trying to edit does not exist please enter a alternate name or create the file first \n");
        fclose(initialFile);
    }

}


void fileOperations(){
    printf("\n \nBelow are the avaliable file operations: \n");
    printf("1. Create a file \n");
    printf("2. Copy a file \n");
    printf("3. Delete a file \n");
    printf("4. Show a file \n");
    printf("Please enter the number relating to the file operation you wish to perform: ");
    // Sanitise this input
    char functionality[5];
    // scanf("%d\n",&functionality);
    fgets(functionality,5,stdin);
    switch (functionality[0] - '0'){
        case 1:
            createFile();
            break;
        case 2:
            copyFile();
            break;
        case 3:
            deleteFile();
            break;
        case 4:
            showFileAndCountLines(0);
            break;
        default:
            break;
    }
}

void lineOperations(){
    int i;
    printf("\n \nBelow are the avaliable line operations: \n");
    printf("1. Append a line \n");
    printf("2. Delete a line \n");
    printf("3. Insert a line \n");
    printf("4. Show line \n");
    printf("Please enter the number relating to the line operation you wish to perform: ");
    // Sanitise this input
    char functionality[5];
    // scanf("%d\n",&functio§ality);
    fgets(functionality,5,stdin);
    switch (functionality[0] - '0'){
        case 1:
            appendLine();   
            break;
        case 2:
            deleteLine();
            break;
        case 3:
            insertLine();
            break;
        default:
            break;
    }
}

void specialOperations(){
    printf("1. Show change log \n"); 
    printf("2. Show number of lines \n");
    printf("Please enter the number relating to the line operation you wish to perform: ");

    char functionality[5];
    // scanf("%d\n",&functio§ality);
    fgets(functionality,5,stdin);
    switch (functionality[0] - '0'){
        case 1:
            break;
        case 2:
            showFileAndCountLines(1);
        default:
            break;
    }
}




int main(){
    
    printf("1. File operations \n2. Line operations \n3. Special operations \nPlease enter the number relation to the operation type you wish to perform: ");
    char functionType[5];
    // scanf("%d\n",&functionType);
    fgets(functionType,5,stdin);
    if (functionType[0] - '0' == 1){      
         fileOperations();
    }
    else if (functionType[0] - '0' == 2){
        lineOperations();
    }
    else if (functionType[0] - '0' == 3){
        specialOperations();
    }
    else{
        printf("None of the inputs are within the given range, try again \n");
    }
    
}

