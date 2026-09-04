# This utility is used to create and/or modify DOS FAT12 formatted, 1.44 MB (.img, .ima) image files used in various emulators, Windows and Linux.
This program can copy files from to OS to the image file, add, remove, rename, label and manupulate image subdirectores.
<p>This is a branch of https://github.com/jxzhn/fat12 with additional features.  This is a Windows Visual Studio C file.
This program can be run in interactive mode or command line mode, features differ between modes.  The command line mode can easily create complex disk images.</p>


# General help info
This utility is used to create and/or modify DOS FAT12 formatted, 1.44 MB (.img, .ima) image files.  This program has an command line mode and interactive mode, exact features differ.
<p>Cmd syntax: Fat12FloppyImg img_file   [excp src dest | mkdir dir | label label]</p>

<ul>
	   <li>img_file          - required .img file to process, created if it does not exist         </li>
	   <li>excp src dest - Copy src from OS to dest on image, use '/' for dest path delimiter  </li>
	   <li>mkdir dir       - Make the die subdirectory on the img                                </li>
	   <li>label label     - Add a disk lable to the img file                                    </li>
</ul>	   


# Interactive: Fat12FloppyImg [img_file]
<p>	   img_file is optional, if specified it will be created if it does not exist </p>
<p>	     type 'help' in interactive mode for more information</p>		 

# Interactive help info
<ul>
    <li>info                -- print FAT12 header infomation of the disk.                     </li>
    <li>bootable            -- check if the floppy is bootable. (by verifying 0x55AA)         </li>
    <li>ls                  -- list all file and sub-directory in current directory.          </li>
    <li>cd {path}           -- change current directory to {path}.                            </li>
    <li>type {file}         -- print the content of {file}. (decode as ASCII)                 </li>
    <li>tree                -- print directory tree of current directory.                     </li>
    <li>cp {src} {des}      -- copy from {src} file to {des} file.                            </li>
    <li>excp {src} {des}    -- copy from local file system {src} file to {des} file.          </li>
    <li>                       {dest} uses Unix path format, not native format.               </li>
    <li>mv {src} {des}      -- move {src} file or directory to {des} position.                </li>
    <li>rm {file}           -- delete {file}.                                                 </li>
    <li>mkdir {dir}         -- create a new directory {dir}.                                  </li>
    <li>rmdir {dir}         -- delete directory {dir} (include file and sub-directory in it)  </li>
    <li>cpdir {src} {des}   -- copy from {src} directory to {des} directory (recursive)       </li>
    <li>concat {1} {2} {des}-- concat content of file {1} and {2} to {des} file.              </li>
</ul>

# Sample IMG file data can be found at 
https://github.com/rambkk/floppy-disk-image-file-.img
