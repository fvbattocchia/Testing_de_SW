
#define INT16 2
#define INT32 4
#define OK 0
#define ERROR -1
// WAVE file header format
struct HEADER {
	unsigned char riff[4];						// RIFF string
	unsigned int overall_size	;				// overall size of file in bytes
	unsigned char wave[4];						// WAVE string
	unsigned char fmt_chunk_marker[4];			// fmt string with trailing null char
	unsigned int length_of_fmt;					// length of the format data
	unsigned int format_type;					// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	unsigned int channels;						// no.of channels
	unsigned int sample_rate;					// sampling rate (blocks per second)
	unsigned int byterate;						// SampleRate * NumChannels * BitsPerSample/8
	unsigned int block_align;					// NumChannels * BitsPerSample/8
	unsigned int bits_per_sample;				// bits per sample, 8- 8bits, 16- 16 bits etc
	unsigned char data_chunk_header [4];		// DATA string or FLLR string
	unsigned int data_size;						// NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};

int coseWaveFile();
int openWaveFile(char * filename);
int parse_header_char(unsigned char * buf, int size);
int parse_header_int(unsigned int *var, int size);
int calculate_samples(struct HEADER header,long * size_of_each_sample,long *num_samples);
int parse_data(char * data_buffer,int size);
