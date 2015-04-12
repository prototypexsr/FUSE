/*Stefan N. Cherubin
N16336054
currently has create function and write function. There are some functions borrowed from listed header files
so credit goes to their rightful places for implementing the functions already. FIle listed as create.c
but will have a name change as more functions are implemented. -March 18 2015
Destroy function implemented, though the print statement doesn't execute if file doesn't exist. If file exists,
it is completely removed from the system. NO idea where it goes since it doesn't end up in Trash bin
Mass reproduction function being worked on to create 10,000 text files (ultimate zerg) - March 19 2015 (actually 11:57 on March 18)
Mass reproduction works, only creates 1 file though... March 20 2015
Init function ready to go, untested currently March 28 2015
Use the following command in terminal:
gcc -Wall salocinnafets.c  -o salocinnafets `pkg-config fuse --cflags --libs`
This can be mounted without the "sudo" command.
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#define FUSE_USE_VERSION 26
#define FILE_OFFSET_BITS 64
//#define BLOCK_SIZE 4096
//#define science_max_blocks 10000
//#define science_max_filesize 1638400
#define CHAR_FILE_LENGTH 50
#define SCIENCE_DATA ((struct science_state *) fuse_get_context()->private_data)
#define PATHLEN_MAX 1024
#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <fuse_lowlevel.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <sys/time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

//#include <sys/ioctl.h>
//#include "fuse_opt.h"

static const int science_block_size = 4096;
static const int science_max_blocks = 10000;
static const int science_max_filesize = 1638400;


struct science_state {

  char* r_directory;
};

struct superblock{

int creation_time;
int number_of_mounts;
int devID;
int freestart;
int freeend;
int root;
int maxblocks;

};

struct directory_inode{

  int size;
  int uid;
  int gid;
  int mode;
  int access_time;
  int create_time;
  int mod_time;
  int num_links;
  struct file_inode;

};
struct file_inode{

  int size;
  int uid;
  int gid;
  int mode;
  int access_time;
  int create_time;
  int mod_time;
  int location;
  int indirective;

};


static char *science_str = "SCIENCE!\n";
static char* science_path = "/fusedata/";
static char* science_block_name = "fusedata.";

char* concaterizer(char* first, char* second){

  char* result = malloc(strlen(first) + strlen(second) + 1);

  strcpy(result, first);

  strcat(result, second);

  return result;

}



static int existence(const char* name){

  FILE* f;
  f = fopen(name,"r");
  if (f){
    fclose(f);
    return 1;
  }
return 0;

}

static int file_size(FILE* name){
  if (!name){ return 1;}
  fseek(name, 0L, SEEK_END);
  int final_size = ftell(name);
  rewind(name);
  return final_size;

}
static void* science_init(struct fuse_conn_info* conn)
{

  printf("VANU SMILES UPON ME\n");

  struct stat power;

  char* supe_block = "/home/stefan/Desktop/fusedata/fusedata.0";
  //FILE* gate_shield = fopen(supe_block, "r");
/*  if ( gate_shield){
    printf(stderr, "#Error: Please delete existing fusedata blocks before mounting");
    abort();
  }*/
  int i = 0;
  FILE* fp;




  for   (i = 0; i < science_max_blocks; ++i) {
	char num[6];
	sprintf(num, "%d", i);

  char* blocker = concaterizer("/home/stefan/Desktop/fusedata/fusedata.", num);
    fp = fopen(blocker, "w+");
    char* buffer = (char*) malloc(science_block_size);
    memset(buffer, '0', science_block_size);
    malloc(science_block_size);
    fwrite(buffer, science_block_size, sizeof(char), fp);
    free(buffer);
    fclose(fp);
  }
      printf("Creating Super Block\n");
      printf("GO\n");
    int checker = stat(supe_block, &power);
    if ( checker == 0){
      ++i;
    }

    FILE* block_party = fopen(supe_block, "w+");
    //fclose(supe_block);
    //block_party = fopen(supe_block, "a+");
    //char* doom = (char*) malloc(1);
    fprintf(block_party, "{creation_time:%ld, number_of_mounts: %d, devID: %d, freestart: %d,freeend: %d, root: %d, maxblocks: %d}\n", time(NULL), 1, 20, 1, 25, 26, science_max_blocks);
    //int length_of_info = strlen("{creation_time:%ld, number_of_mounts: %d, devID: %d, freestart: %d,freeend: %d, root: %d, maxblocks: %d}");
    int size = file_size(block_party);
    char* more_buffer = (char*) malloc(science_block_size);
    fseek(block_party, size , SEEK_SET);
    memset(more_buffer, '0', science_block_size);
    fwrite(more_buffer, science_block_size - size, sizeof(char), block_party);
    //free(more_buffer);
    //fprintf(block_party, "{creation_time:%ld, number_of_mounts: %d}", time(NULL), 1);
    //fprintf(block_party, "{creation_time:%ld, number_of_mounts: %d}", time(NULL), 1);
    //memset(doom, "creation_time", 1);
    //fwrite(doom, 1, sizeof(char), block_party);
    fclose(block_party);
    //++i;
  //}
  printf("NOW\n");

  printf("LEAVE\n");
  printf("Creating Free Block List\n");
	char* free_block_begins = concaterizer("/home/stefan/Desktop/fusedata/fusedata.", "1");
	for (i = 27; i < 400; ++i){
		if (i == 27){
			block_party = fopen(free_block_begins, "w+");
			fprintf(block_party, "{ %d", i);
      //int size2 = file_size(block_party);
      //fseek(block_party, size2 , SEEK_SET);
      //memset(more_buffer, '0', science_block_size);
      //fwrite(more_buffer, science_block_size - size2, sizeof(char), block_party);
      //free(more_buffer);
			fclose(block_party);
		}
		else if (i == 399){
			block_party = fopen(free_block_begins, "a+");
			fprintf(block_party, ", %d}", i);
      fseek(block_party, 0, SEEK_END);
      int size2 = file_size(block_party);
      fwrite(more_buffer, science_block_size - size2, sizeof(char), block_party);
			fclose(block_party);
		}
		block_party = fopen(free_block_begins, "a+");
		fprintf(block_party, ", %d", i);
    rewind(block_party);

		fclose(block_party);

	}

  int j;
  for (j = 2; j < 26; ++j){
    char* num[6];
    sprintf(num, "%d", j);
    char* next_free_block = concaterizer("/home/stefan/Desktop/fusedata/fusedata.", num);
    for (i = 0; i < 400; ++i){
      if (i == 0){
        block_party = fopen(next_free_block, "w+");
        fprintf(block_party, "{ %d", ((j - 1) * 400) + i);
        fclose(block_party);
      }
      else if (i == 399){
        block_party = fopen(next_free_block, "a+");
        fprintf(block_party, ", %d}", ((j - 1) * 400) + i);
        int size3 = file_size(block_party);
        fwrite(more_buffer, science_block_size - size3, sizeof(char), block_party);
        fclose(block_party);
      }
      block_party = fopen(next_free_block, "a+");
      fprintf(block_party, ", %d", ((j - 1) * 400) + i);
      fclose(block_party);
    }
  }
  printf("Creating Root Block\n");
	char* r_block = concaterizer("/home/stefan/Desktop/fusedata/fusedata.", "26");
	block_party = fopen(r_block, "w+");
  //the followint fprintf is what I call a ghost print, though after checking file size, it says its non zero but no contents written.
	fprintf(block_party, "{size:%d, uid:%d, gid:%d, mode:%d, access_time:%ld, create_time:%ld, mod_time:%ld, num_links:%d, file_inode: {d:.:%d, d:..:%d}}", 0, 1, 1, S_IFDIR | S_IRWXU, time(NULL), time(NULL), time(NULL), 2, 26, 26);
  int size4 = file_size(block_party);
  fwrite(more_buffer, science_block_size - size4, sizeof(char), block_party);
  fprintf(block_party, "{size:%d, uid:%d, gid:%d, mode:%d, access_time:%ld, create_time:%ld, mod_time:%ld, num_links:%d, file_inode: {d:.:%d, d:..:%d}}", 0, 1, 1, S_IFDIR | S_IRWXU, time(NULL), time(NULL), time(NULL), 2, 26, 26);
	fclose(block_party);




  umask(0);

  printf("DONE\n");
  return SCIENCE_DATA;
}

static void* science_destroy(void* private_data){

  (void)private_data;
  return NULL;
}


//function taken from fusexmp.c
static int science_getattr(const char *path, struct stat *stbuf)
{
	int res;

	res = lstat(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}
//function taken from fusexmp.c
static int science_readlink(const char* path_name, char* buffer, size_t size){


	int data = readlink(path_name, buffer, size -1 );
	if (data == -1){ return -errno; }
	buffer[data] = '\0';
	return 0;
}
//function taken from hello.c file
static int science_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	filler(buf, science_path + 1, NULL, 0);

	return 0;
}
static int science_mkdir(const char* path_name, const char* mode){

   //char c[] = "create function";
   //cFILE* fpoint;har buffer[20];

   FILE* fpoint;
    if ( fopen(path_name, "r") ) {
printf("This directory already exists\n");
  fclose(path_name);
}


	printf("Directory did not exist previously, so creating a directoty with given name\n");
	fpoint = fopen(path_name,"w+");
  fclose(path_name);


     return 0;

}
//function taken from fuse_xmp.c
static int science_unlink(const char* path_name){


	int res = unlink(path_name);
	if (res == -1 ) { return -errno; }
	return 0;
}
//function taken from fuse_xmp.c
static int science_rename(const char* current_name, const char* new_name){

  int data = rename(current_name, new_name);
  if (data == -1){ return -errno; }
  return 0;
}
//function taken from fuse_xmp.c
static int science_link(const char* path_name, const char* dest_path){


	int res = link(path_name, dest_path);
	if (res == -1 ) { return -errno; }
	return 0;
}
//function taken from hello.c file
static int science_open(const char *path, struct fuse_file_info *fi)
{
	if (strcmp(path, science_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	return 0;
}



static int science_create(const char* filename, const char* mode){

   //char c[] = "create function";
   //cFILE* fpoint;char buffer[20];

   FILE* fpoint;
    if ( fopen(filename, "r") ) {
printf("This file already exists\n");
fclose(filename);
return 1;
}




	printf("File did not exist previously, so creating a file with given name\n");
	fpoint = fopen(filename,"w+");
  fclose(filename);


     return 0;

}
//function taken from hello.c file
static int science_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;
	if(strcmp(path, science_path) != 0)
		return -ENOENT;

	len = strlen(science_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, science_str + offset, size);

	}
  else{
		size = 0;}

	return size;
}
//function taken from fuse_xmp
static int science_write(const char* path_name, char* buffer, size_t size, off_t offset, struct fuse_file_info* file_info){

	int data, source;

	(void) file_info;
	data = open(path_name, O_WRONLY);
	if (data == -1){
	return -errno;
	}

	source = pwrite(data, buffer, size, offset);
	if (source == -1) { return -errno; }

	close(data);
	return source;

}
//function taken from fuse_xmp
static int science_statfs(const char* path_name, struct statvfs* stbuffer){
  int data = statvfs(path_name, stbuffer);
  if (data == -1){ return -errno;}

  return 0;

}

static int science_release(const char* path_name, struct fuse_file_info* file_info){


	(void) path_name;
	(void) file_info;
	return 0;
}

static
int science_opendir(const char* path_name, struct fuse_file_info* file_info){

   //char c[] = "create function";
   //char buffer[20];
   int data = fopen(path_name, "r" );
   if (data == -1){ return -errno;}

   return 0;

}


static int science_releasedir(const char* path_name, struct fuse_file_info* file_info){


	(void) path_name;
	(void) file_info;
	return 0;
}










static struct fuse_operations science_tools = {
    .init        = science_init,
    .destroy     = science_destroy,
     .getattr     = science_getattr,
    .readlink    = science_readlink,
    .readdir     = science_readdir,
   .mkdir       = science_mkdir,
   .unlink      = science_unlink,
   .rename      = science_rename,
  .link        = science_link,
    .create      = science_create,
    .open        = science_open,
    .read        = science_read,
    .write       = science_write,
    .statfs      = science_statfs,
    .release     = science_release,
    .opendir     = science_opendir,
    .releasedir  = science_releasedir,

};

int main(int argc, char *argv[])
{


   int result;
    result = fuse_main(argc, argv, &science_tools, NULL);
    return result;


}
