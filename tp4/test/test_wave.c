#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unity.h"
#include "wave.h"

struct HEADER header;

void setUp(void) {

}
void test_OpenFile(void) {
  char filename[1024];

   // get file path
   char cwd[1024];
   getcwd(cwd, sizeof(cwd));
   strcpy(filename, cwd);
   strcat(filename, "/src/piano2.wav");
   printf("%s\n", filename);

   TEST_ASSERT_EQUAL_INT(OK, openWaveFile(filename));

}


void test_parseRiff(){
  char src[5];
  parse_header_char(header.riff, sizeof(header.riff));
  strcpy(src, header.riff);
  src[sizeof(header.riff)]='\0';
  printf("(1-4): %s \n", src);
  TEST_ASSERT_EQUAL_STRING("RIFF",src);
}
void test_parseOverallSize(){
  parse_header_int(&header.overall_size,INT32);
  printf("(5-8) Overall size: bytes:%u, Kb:%u \n", header.overall_size, header.overall_size/1024);
  TEST_ASSERT_EQUAL_INT(1210884,header.overall_size);
}

void test_parseWave(){
  char src[5];
  parse_header_char(header.wave, sizeof(header.wave));
  strcpy(src, header.wave);
  src[sizeof(header.wave)]='\0';
  printf("(9-12) Wave marker: %s\n", src);
  TEST_ASSERT_EQUAL_STRING("WAVE",src);
}
void test_parseFmtChunkMarker(){
  char src[5];
  parse_header_char(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker));
  strcpy(src, header.fmt_chunk_marker);
  src[sizeof(header.fmt_chunk_marker)-1]='\0';
  printf("(13-16) Fmt marker: %s\n", src);
  TEST_ASSERT_EQUAL_STRING("fmt",src);
}

void test_parseLengthOfFmt(){
  parse_header_int(&header.length_of_fmt,INT32);
  printf("(17-20) Length of Fmt header: %u \n", header.length_of_fmt);
  TEST_ASSERT_EQUAL_INT(16,header.length_of_fmt);
}
void test_parseFormatype(){
  parse_header_int(&header.format_type,INT16);
  char format_name[10] = "";
  if (header.format_type == 1)
    strcpy(format_name,"PCM");
   printf("(21-22) Format type: %u %s \n", header.format_type, format_name);
   TEST_ASSERT_EQUAL_INT(1,header.format_type);
}
void test_parseChannels(){
  parse_header_int(&header.channels,INT16);
  printf("(23-24) Channels: %u \n", header.channels);
  TEST_ASSERT_EQUAL_INT(2,header.channels);
}
void test_parseSampleRate(){
  parse_header_int(&header.sample_rate,INT32);
  printf("(25-28) Sample rate: %u\n", header.sample_rate);
  TEST_ASSERT_EQUAL_INT(48000, header.sample_rate);
}
void test_parseByterate(){
  parse_header_int(&header.byterate,INT32);
  printf("(29-32) Byte Rate: %u , Bit Rate:%u\n", header.byterate, header.byterate*8);
  TEST_ASSERT_EQUAL_INT(192000, header.byterate);
}
void test_parseBlockAlign(){
  parse_header_int(&header.block_align,INT16);
  printf("(33-34) Block Alignment: %u \n", header.block_align);
  TEST_ASSERT_EQUAL_INT(4, header.block_align);
}
void test_parseBitsPerSample(){
  parse_header_int(&header.bits_per_sample,INT16);
  printf("(35-36) Bits per sample: %u \n", header.bits_per_sample);
  TEST_ASSERT_EQUAL_INT(16, header.bits_per_sample);
}
void test_parseDataChunkHeader(){
  char src[5];
  parse_header_char(header.data_chunk_header, sizeof(header.data_chunk_header));
  strcpy(src, header.data_chunk_header);
  src[sizeof(header.data_chunk_header)]='\0';
  printf("(37-40) Data Marker: %s \n", src);
  TEST_ASSERT_EQUAL_STRING("data",src);
}
void test_parseDataSize(){
  parse_header_int(&header.data_size,INT32);
  printf("(41-44) Size of data chunk: %u \n", header.data_size);
  TEST_ASSERT_EQUAL_INT(1210848, header.data_size);
}
void test_parseData(){
  long size_of_each_sample;
  long num_samples;
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
  TEST_ASSERT_EQUAL_INT(302712,i);
}

void test_closeFile(){
  TEST_ASSERT_EQUAL_INT(OK,coseWaveFile());
}
