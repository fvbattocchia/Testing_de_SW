#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wave.h"


int main(int argc, char **argv) {

  char *filename;
  struct HEADER header;
  char src[5];
  long size_of_each_sample;
  long num_samples;
  //---open file----
  filename = (char*) malloc(sizeof(char) * 1024);
  if (filename == NULL) {
     printf("Error in mallocn");
     exit(1);
   }

   // get file path
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {

     strcpy(filename, cwd);

     // get filename from command line
     if (argc < 2) {
    	  printf("No wave file specifiedn");
    	  return -1;
    	}

    	strcat(filename, "/");
    	strcat(filename, argv[1]);
    	printf("%s\n", filename);
   }
   //open file
   openWaveFile(filename);

   //parse HEADER
   parse_header_char(header.riff, sizeof(header.riff));
   strcpy(src, header.riff);
   src[sizeof(header.riff)]='\0';
   printf("(1-4): %s \n", src);
   parse_header_int(&header.overall_size,INT32);
   printf("(5-8) Overall size: bytes:%u, Kb:%u \n", header.overall_size, header.overall_size/1024);
   parse_header_char(header.wave, sizeof(header.wave));
   strcpy(src, header.wave);
   src[sizeof(header.wave)]='\0';
   printf("(9-12) Wave marker: %s\n", src);
   parse_header_char(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker));
   strcpy(src, header.fmt_chunk_marker);
   src[sizeof(header.fmt_chunk_marker)-1]='\0';
   printf("(13-16) Fmt marker: %s\n", src);
   parse_header_int(&header.length_of_fmt,INT32);
   printf("(17-20) Length of Fmt header: %u \n", header.length_of_fmt);
   parse_header_int(&header.format_type,INT16);
   char format_name[10] = "";
   if (header.format_type == 1)
     strcpy(format_name,"PCM");
   else if (header.format_type == 6)
    strcpy(format_name, "A-law");
   else if (header.format_type == 7)
    strcpy(format_name, "Mu-law");

   printf("(21-22) Format type: %u %s \n", header.format_type, format_name);
   parse_header_int(&header.channels,INT16);
   printf("(23-24) Channels: %u \n", header.channels);
   parse_header_int(&header.sample_rate,INT32);
   printf("(25-28) Sample rate: %u\n", header.sample_rate);
   parse_header_int(&header.byterate,INT32);
   printf("(29-32) Byte Rate: %u , Bit Rate:%u\n", header.byterate, header.byterate*8);
   parse_header_int(&header.block_align,INT16);
   printf("(33-34) Block Alignment: %u \n", header.block_align);
   parse_header_int(&header.bits_per_sample,INT16);
   printf("(35-36) Bits per sample: %u \n", header.bits_per_sample);
   parse_header_char(header.data_chunk_header, sizeof(header.data_chunk_header));
   strcpy(src, header.data_chunk_header);
   src[sizeof(header.data_chunk_header)]='\0';
   printf("(37-40) Data Marker: %s \n", src);
   parse_header_int(&header.data_size,INT32);
   printf("(41-44) Size of data chunk: %u \n", header.data_size);

   calculate_samples(header,&size_of_each_sample,&num_samples);
   printf("Number of samples:%lu \n", num_samples);
   printf("Size of each sample:%ld bytes\n", size_of_each_sample);

   char data_buffer[size_of_each_sample];
   long i=0;
   //parse DATA
   while(i<num_samples) {
     i+=parse_data(data_buffer,size_of_each_sample);
   }
   printf("samples readed: %ld\n", i);
   //close file
   coseWaveFile();
   free(filename);
   return 0;

}
