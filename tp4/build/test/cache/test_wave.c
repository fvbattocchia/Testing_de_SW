#include "build/temp/_test_wave.c"
#include "src/wave.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


struct HEADER header;



void setUp(void) {



}

void test_OpenFile(void) {

  char filename[1024];





   char cwd[1024];

   getcwd(cwd, sizeof(cwd));

   strcpy(filename, cwd);

   strcat(filename, "/src/piano2.wav");

   printf("%s\n", filename);



   UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((openWaveFile(filename))), (

  ((void *)0)

  ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT);



}





void test_parseRiff(){

  char src[5];

  parse_header_char(header.riff, sizeof(header.riff));

  strcpy(src, header.riff);

  src[sizeof(header.riff)]='\0';

  printf("(1-4): %s \n", src);

  UnityAssertEqualString((const char*)(("RIFF")), (const char*)((src)), (

 ((void *)0)

 ), (UNITY_UINT)(34));

}

void test_parseOverallSize(){

  parse_header_int(&header.overall_size,4);

  printf("(5-8) Overall size: bytes:%u, Kb:%u \n", header.overall_size, header.overall_size/1024);

  UnityAssertEqualNumber((UNITY_INT)((1210884)), (UNITY_INT)((header.overall_size)), (

 ((void *)0)

 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}



void test_parseWave(){

  char src[5];

  parse_header_char(header.wave, sizeof(header.wave));

  strcpy(src, header.wave);

  src[sizeof(header.wave)]='\0';

  printf("(9-12) Wave marker: %s\n", src);

  UnityAssertEqualString((const char*)(("WAVE")), (const char*)((src)), (

 ((void *)0)

 ), (UNITY_UINT)(48));

}

void test_parseFmtChunkMarker(){

  char src[5];

  parse_header_char(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker));

  strcpy(src, header.fmt_chunk_marker);

  src[sizeof(header.fmt_chunk_marker)-1]='\0';

  printf("(13-16) Fmt marker: %s\n", src);

  UnityAssertEqualString((const char*)(("fmt")), (const char*)((src)), (

 ((void *)0)

 ), (UNITY_UINT)(56));

}



void test_parseLengthOfFmt(){

  parse_header_int(&header.length_of_fmt,4);

  printf("(17-20) Length of Fmt header: %u \n", header.length_of_fmt);

  UnityAssertEqualNumber((UNITY_INT)((16)), (UNITY_INT)((header.length_of_fmt)), (

 ((void *)0)

 ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

}

void test_parseFormatype(){

  parse_header_int(&header.format_type,2);

  char format_name[10] = "";

  if (header.format_type == 1)

    strcpy(format_name,"PCM");

   printf("(21-22) Format type: %u %s \n", header.format_type, format_name);

   UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((header.format_type)), (

  ((void *)0)

  ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);

}

void test_parseChannels(){

  parse_header_int(&header.channels,2);

  printf("(23-24) Channels: %u \n", header.channels);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((header.channels)), (

 ((void *)0)

 ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);

}

void test_parseSampleRate(){

  parse_header_int(&header.sample_rate,4);

  printf("(25-28) Sample rate: %u\n", header.sample_rate);

  UnityAssertEqualNumber((UNITY_INT)((48000)), (UNITY_INT)((header.sample_rate)), (

 ((void *)0)

 ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_INT);

}

void test_parseByterate(){

  parse_header_int(&header.byterate,4);

  printf("(29-32) Byte Rate: %u , Bit Rate:%u\n", header.byterate, header.byterate*8);

  UnityAssertEqualNumber((UNITY_INT)((192000)), (UNITY_INT)((header.byterate)), (

 ((void *)0)

 ), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_INT);

}

void test_parseBlockAlign(){

  parse_header_int(&header.block_align,2);

  printf("(33-34) Block Alignment: %u \n", header.block_align);

  UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((header.block_align)), (

 ((void *)0)

 ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);

}

void test_parseBitsPerSample(){

  parse_header_int(&header.bits_per_sample,2);

  printf("(35-36) Bits per sample: %u \n", header.bits_per_sample);

  UnityAssertEqualNumber((UNITY_INT)((16)), (UNITY_INT)((header.bits_per_sample)), (

 ((void *)0)

 ), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_INT);

}

void test_parseDataChunkHeader(){

  char src[5];

  parse_header_char(header.data_chunk_header, sizeof(header.data_chunk_header));

  strcpy(src, header.data_chunk_header);

  src[sizeof(header.data_chunk_header)]='\0';

  printf("(37-40) Data Marker: %s \n", src);

  UnityAssertEqualString((const char*)(("data")), (const char*)((src)), (

 ((void *)0)

 ), (UNITY_UINT)(103));

}

void test_parseDataSize(){

  parse_header_int(&header.data_size,4);

  printf("(41-44) Size of data chunk: %u \n", header.data_size);

  UnityAssertEqualNumber((UNITY_INT)((1210848)), (UNITY_INT)((header.data_size)), (

 ((void *)0)

 ), (UNITY_UINT)(108), UNITY_DISPLAY_STYLE_INT);

}

void test_parseData(){

  long size_of_each_sample;

  long num_samples;

  calculate_samples(header,&size_of_each_sample,&num_samples);

  printf("Number of samples:%lu \n", num_samples);

  printf("Size of each sample:%ld bytes\n", size_of_each_sample);



  char data_buffer[size_of_each_sample];

  long i=0;



  while(i<num_samples) {

    i+=parse_data(data_buffer,size_of_each_sample);

  }

  printf("samples readed: %ld\n", i);

  UnityAssertEqualNumber((UNITY_INT)((302712)), (UNITY_INT)((i)), (

 ((void *)0)

 ), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_INT);

}



void test_closeFile(){

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((coseWaveFile())), (

 ((void *)0)

 ), (UNITY_UINT)(128), UNITY_DISPLAY_STYLE_INT);

}
