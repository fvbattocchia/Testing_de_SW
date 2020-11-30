
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wave.h"
#define TRUE 1
#define FALSE 0

// WAVE header structure

unsigned char buffer4[4];
unsigned char buffer2[2];

char* seconds_to_time(float seconds);

FILE *ptr;

int openWaveFile(char * filename){
  // open file

  printf("Opening  file..\n");
  ptr = fopen(filename, "rb");
  if (ptr == NULL) {
 	  printf("Error opening file\n");
    return ERROR;
  }
  return OK;
}

int parse_header_char(unsigned char * buf, int size){
 int read = 0;
 read = fread(buf, size, 1, ptr);
 return read;
}


int parse_header_int(unsigned int * var, int size){
 int read = 0;
 if(size==INT32){
   read = fread(buffer4, sizeof(buffer4), 1, ptr);
   // convert little endian to big endian 4 byte int
   *var  = buffer4[0] | (buffer4[1]<<8) | (buffer4[2]<<16) | 	(buffer4[3]<<24);
 }else{
   read = fread(buffer2, sizeof(buffer2), 1, ptr);
   *var = buffer2[0] | (buffer2[1] << 8);
 }
 return read;
}


int calculate_samples(struct HEADER header,long * size_of_each_sample,long *num_samples){


  int  size_is_correct = TRUE;
 // calculate no.of samples
 *num_samples = (8 * header.data_size) / (header.channels * header.bits_per_sample);
 
 *size_of_each_sample = (header.channels * header.bits_per_sample) / 8;

 // calculate duration of file
 float duration_in_seconds = (float) header.overall_size / header.byterate;
 printf("Approx.Duration in seconds=%f\n", duration_in_seconds);
 printf("Approx.Duration in h:m:s=%s\n", seconds_to_time(duration_in_seconds));

 // make sure that the bytes-per-sample is completely divisible by num.of channels
 long bytes_in_each_channel = (*size_of_each_sample / header.channels);
 if ((bytes_in_each_channel  * header.channels) != *size_of_each_sample) {
   printf("Error: %ld x %ud <> %ld\n", bytes_in_each_channel, header.channels, *size_of_each_sample);
   size_is_correct = FALSE;
 }
 return size_is_correct;

}

int parse_data(char * data_buffer,int size){
  int read;
  read = fread(data_buffer, size, 1, ptr);
  return read;
}


int coseWaveFile(){
  printf("Closing file..\n");
  return fclose(ptr);
}
/**
 * Convert seconds into hh:mm:ss format
 * Params:
 *	seconds - seconds value
 * Returns: hms - formatted string
 **/
 char* seconds_to_time(float raw_seconds) {
  char *hms;
  int hours, hours_residue, minutes, seconds, milliseconds;
  hms = (char*) malloc(100);

  sprintf(hms, "%f", raw_seconds);

  hours = (int) raw_seconds/3600;
  hours_residue = (int) raw_seconds % 3600;
  minutes = hours_residue/60;
  seconds = hours_residue % 60;
  milliseconds = 0;

  // get the decimal part of raw_seconds to get milliseconds
  char *pos;
  pos = strchr(hms, '.');
  int ipos = (int) (pos - hms);
  char decimalpart[15];
  memset(decimalpart, ' ', sizeof(decimalpart));
  strncpy(decimalpart, &hms[ipos+1], 3);
  milliseconds = atoi(decimalpart);


  sprintf(hms, "%d:%d:%d.%d", hours, minutes, seconds, milliseconds);
  return hms;
}
