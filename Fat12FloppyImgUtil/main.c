#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fat12.h"

//  Ignore unsafe functions: project > properties > C/C++ > Preprocessor > Preprocessor Definitions add:  _CRT_SECURE_NO_WARNINGS

#define BUFF_SIZE  256
#define XSTRING(S)  STR(S)      // Causes the passed #define symbol to expand to a value
    #define STR(S) #S              // Turns the value into a String
const char* scanFormat = { "%"  XSTRING(BUFF_SIZE) "s" };     // Causes the passed #define symbol to expand to a value


void printHelpInfo() {
    printf("info                -- print FAT12 header infomation of the disk.\n");
    printf("bootable            -- check if the floppy is bootable. (by verifying 0x55AA)\n");
    printf("ls                  -- list all file and sub-directory in current directory.\n");
    printf("cd {path}           -- change current directory to {path}.\n");
    printf("type {file}         -- print the content of {file}. (decode as ASCII)\n");
    printf("tree                -- print directory tree of current directory.\n");
    printf("cp {src} {des}      -- copy from {src} file to {des} file.\n");
    printf("excp {src} {des}    -- copy from local file system {src} file to {des} file.\n");
    printf("                       {dest} uses Unix path format, not native format.\n");
    printf("mv {src} {des}      -- move {src} file or directory to {des} position.\n");
    printf("rm {file}           -- delete {file}.\n");
    printf("mkdir {dir}         -- create a new directory {dir}.\n");
    printf("rmdir {dir}         -- delete directory {dir} (include file and sub-directory in it)\n");
    printf("cpdir {src} {des}   -- copy from {src} directory to {des} directory (recursive)\n");
    printf("concat {1} {2} {des}-- concat content of file {1} and {2} to {des} file.\n");
    printf("label {name}        -- change the volume lable to {name}, 11 characters max.\n");
    printf("quit                -- quit and save all changed.\n");
}

int main(int argc, char *argv[]) {
    char name[BUFF_SIZE];
    char* buffer = (char*)malloc(BUFF_SIZE*4);
    char* const command = buffer;
    char* const path = buffer + BUFF_SIZE;
    char* const path2 = buffer + BUFF_SIZE * 2;
    char* const path3 = buffer + BUFF_SIZE * 3;
    int changed = 0; // if the disk is written

    
    // get file name from command line argument or user input
    if (argc > 1) {
        strncpy(name,  argv[1], BUFF_SIZE);
    }
    else {
        printf("Input file name: ");
 
        scanf(scanFormat, name);
    }
    name[BUFF_SIZE-1] = 0;
   printf("Input file %s\n", name);


   // Try to read floppy disk image from the file
    floppy* disk = (floppy*)calloc(1,   sizeof(floppy));

    // Create a blank FAT12 image in memory, return 1 when success, else return 0
    if (createBlankDisk(disk)) {
        printf("Failed to create a blank FAT12 disk image.\n");
        free(disk);
        return 1;
	}   
	changed = 1; // the disk is written by createBlankDisk, so set changed to 1 to make sure it would be written to file when quit

#if 0
    if (!readFloppyDisk(name, disk)) {
        printf("Failed to read %s image from file.\n", name);
        free(disk);
        return 1;
    }
#endif
    directory dir;
    initDirWithRoot(&dir);

 
    printf("Input \"help\" to get help infomation.\n");
    while (1) {
        printf("[%s]$ ", dir.path_str);
        scanf(scanFormat, command);
		command[BUFF_SIZE-1] = 0;

        if ((!strcmp(command, "help")) || (!strcmp(command, "h"))) {
            printHelpInfo();

        } else if (!strcmp(command, "bootable")) {
            if (verifyBootId(disk)) {
                printf("This image is bootable.\n");
            } else {
                printf("This image is NOT bootable.\n");
            }

        } else if (!strcmp(command, "info")) {
            printFat12Info(disk)
                ;
        } else if (!strcmp(command, "ls")) {
            printAllInDir(disk, &dir);

        } else if (!strcmp(command, "cd")) {
            scanf(scanFormat, path);
            if (!changeDirectory(disk, &dir, path)) {
                printf("Failed to change directory into \"%s\"\n", path);
            }

        } else if (!strcmp(command, "type")) {
            scanf(scanFormat, path);
            if (!printFileContentByPath(disk, &dir, path)) {
                printf("Failed to read content of file \"%s\"\n", path);
            }

        } else if (!strcmp(command, "tree")) {
            printDirTree(disk, &dir);

        } else if (!strcmp(command, "cp")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE-1] = 0;
            scanf(scanFormat, path2);
            path2[BUFF_SIZE - 1] = 0;

            if (!copyFileByPath(disk, &dir, path, path2)) {
                printf("Failed to copy file from \"%s\" to \"%s\"\n", path, path2);
            } else changed = 1;

        }
        else if (!strcmp(command, "excp")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE - 1] = 0;
            scanf(scanFormat, path2);
            path2[BUFF_SIZE - 1] = 0;

            if (!copyFileFromSys(disk, &dir, path, path2)) {   //needs new fucntion
                printf("Failed to copy file from \"%s\" to \"%s\"\n", path, path2);
            }
            else changed = 1;
        }

        else if (!strcmp(command, "label")) {
            scanf("%11s", command);  // only 11 characters
            command[11] = 0;
            changeLabel(disk, command);
            changed = 1;

        } else if (!strcmp(command, "mv")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE - 1] = 0;
            scanf(scanFormat, path2);
            path2[BUFF_SIZE - 1] = 0;
            if (!moveFileByPath(disk, &dir, path, path2)) {
                printf("Failed to move file from \"%s\" to \"%s\"\n", path, path2);
            } else changed = 1;

        } else if (!strcmp(command, "rm")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE - 1] = 0;
            if (!removeFileByPath(disk, &dir, path)) {
                printf("Failed to remove file \"%s\"\n", path);
            } else changed = 1;

        } else if (!strcmp(command, "mkdir")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE - 1] = 0;
            if (!makeDirByPath(disk, &dir, path)) {
                printf("Failed to make directory \"%s\"\n", path);
            } else changed = 1;

        } else if (!strcmp(command, "rmdir")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE - 1] = 0;
            if (!removeDirByPath(disk, &dir, path)) {
                printf("Failed to remove directory \"%s\"\n", path);
            } else changed = 1;

        } else if (!strcmp(command, "cpdir")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE - 1] = 0;
            scanf(scanFormat, path2);
            path2[BUFF_SIZE - 1] = 0;
            if (!copyDirByPath(disk, &dir, path, path2)) {
                printf("Failed to copy directory \"%s\" to \"%s\"\n", path, path2);
            } else changed = 1;

        } else if (!strcmp(command, "concat")) {
            scanf(scanFormat, path);
            path[BUFF_SIZE - 1] = 0;
            scanf(scanFormat, path2);
            path2[BUFF_SIZE - 1] = 0;
            scanf(scanFormat, path3);
            path3[BUFF_SIZE - 1] = 0;
            if (!concatFileByPath(disk, &dir, path, path2, path3)) {
                printf("Failed to concat \"%s\" and \"%s\" to \"%s\"\n", path, path2, path3);
            } else changed = 1;

        } else if ((!strcmp(command, "quit")) || (!strcmp(command, "q"))) {
            break;

        } else {
            printf("Unkown command: %s\n", command);
        }
    }
    free(buffer);
    destroyDir(&dir);
    if (changed) {
        printf("Virtual disk content has changed, trying to writing back...\n");
        if (!writeFloppyDisk(name, disk)) {
            printf("Failed to write the file back.\n");
        } else {
            printf("Successfully write back.\n");
        }
    }
    free(disk);
    return 0;
}