This utility is used to create and/or modify DOS FAT12 formatted, 1.44 MB (.img, .ima) image files used in various emulators, Windows and Linux.
This program can copy files from to OS to the image file, add, remove, rename, label and manupulate image subdirectores.
This is a branch of https://github.com/jxzhn/fat12 with additional features.  This is a Windows Visual Studio C file.
This program can be run in interactive mode or command line mode, features differ between modes.  The command line mode can easily create complex disk images.


general help info
This utility is used to create and/or modify DOS FAT12 formatted, 1.44 MB (.img, .ima) image files.  This program has an command line mode and interactive mode, exact features differ.
Cmd syntax: Fat12FloppyImg <img_file>   excp <src> <dest> | mkdir <dir> | label <label>
	   img_file          - required .img file to process, created if it does not exist
	   excp <src> <dest> - Copy src from OS to dest on image, use '/' for dest path delimiter
	   mkdir <dir>       - Make the die subdirectory on the img
	   label <label>     - Add a disk lable to the img file
	   
	Interactive: Fat12FloppyImg [<img_file>]
	   img_file is optional, if specified it will be created if it does not exist
	     type 'help' in interactive mode for more information

interactive help info
    info                -- print FAT12 header infomation of the disk.
    bootable            -- check if the floppy is bootable. (by verifying 0x55AA)
    ls                  -- list all file and sub-directory in current directory.
    cd {path}           -- change current directory to {path}.
    type {file}         -- print the content of {file}. (decode as ASCII)
    tree                -- print directory tree of current directory.
    cp {src} {des}      -- copy from {src} file to {des} file.
    excp {src} {des}    -- copy from local file system {src} file to {des} file.
                           {dest} uses Unix path format, not native format.
    mv {src} {des}      -- move {src} file or directory to {des} position.
    rm {file}           -- delete {file}.
    mkdir {dir}         -- create a new directory {dir}.
    rmdir {dir}         -- delete directory {dir} (include file and sub-directory in it)
    cpdir {src} {des}   -- copy from {src} directory to {des} directory (recursive)
    concat {1} {2} {des}-- concat content of file {1} and {2} to {des} file.
    label {name}        -- change the volume lable to {name}, 11 characters max.
    quit                -- quit and save all changed.\n
