#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { UNPACK, PACK } RomPackOption;

void	      on_error(const char *msg);
void	      help_and_exit();
size_t	      get_file_size(FILE *fp);
uint16_t      u16_cmp_little_endian();
RomPackOption get_option(int argc, char **argv);
void	      unpack(const char *rom_path);

/* prints msg to stderr and exits */
void
on_error(const char *msg)
{
	fputs(msg, stderr);
	fputc(10, stderr);
	exit(1);
	__builtin_unreachable();
}

/* prints the help text to stdout and exits the programm */
void
help_and_exit()
{
	fputs("rompack <option> <file> [name] [image.png]\n\n-u "
	      "--unpack\tunpack a "
	      "packed "
	      "rom\n-p "
	      "--pack\tpack a rom together with a png image\n",
	      stdout);
	exit(0);
	__builtin_unreachable();
}

/* get the size of an file in bytes */
size_t
get_file_size(FILE *fp)
{
	size_t size;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	return size;
}

/* determine option */
RomPackOption
get_option(int argc, char **argv)
{
	if (argc < 3)
		help_and_exit();

/* short options are only 2 bytes long (without null delimiter), so we can just
 * interpret them as a 2 byte number and compare them. This is way faster than
 * strcmp.*/
#if BYTE_ORDER == LITTLE_ENDIAN
	if (*(uint16_t *)argv[1] == 0x752d && argv[1][2] == 0)
		return UNPACK;

	if (*(uint16_t *)argv[1] == 0x702d && argv[1][2] == 0)
		return PACK;
#endif

#if BYTE_ORDER == BIG_ENDIAN
	if (*(uint16_t *)&argv[1] == 0x2d75 && argv[1][2] == 0)
		return UNPACK;

	if (*(uint16_t *)&argv[1] == 0x2d75 && argv[1][2] == 0)
		return PACK;
#endif

#if BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN
	if (strcmp(argv[1], "-u") == 0)
		return UNPACK;

	if (strcmp(argv[1], "-p") == 0)
		return PACK;
#endif

	if (strcmp(argv[1], "--unpack") == 0)
		return UNPACK;

	if (strcmp(argv[1], "--pack") == 0)
		return UNPACK;

	help_and_exit();
	__builtin_unreachable();
}

/* unpack a packed rom and extract the raw rom and the image */
void
unpack(const char *rom_path)
{
	FILE	*fp;
	size_t	 file_size;
	uint8_t	 name_size;
	uint16_t rom_size;
	uint8_t *rom_buffer;
	uint16_t image_size;
	uint8_t *file_buffer;
	uint8_t *image_buffer;

	/* open file */
	fp = fopen(rom_path, "rb");
	if (!fp)
		on_error("open file failed\n");

	/* get file size */
	file_size = get_file_size(fp);
	if (!file_size) {
		fclose(fp);
		on_error("file is empty\n");
	}

	/* allocate memory for file */
	file_buffer = (uint8_t *)malloc(file_size);
	if (!file_buffer) {
		fclose(fp);
		on_error("memory allocation failed\n");
	}

	/* read file */
	if (fread(file_buffer, sizeof(uint8_t), file_size, fp) !=
	    file_size * sizeof(uint8_t)) {
		fclose(fp);
		free(file_buffer);
		on_error("error while reading file\n");
	}

	if (file_buffer[0] != 0xA2 || file_buffer[1] != 0xCF) {
		fclose(fp);
		free(file_buffer);
		on_error("file is not a packed rom\n");
	}
	/* get name size (1 byte) */
	name_size = file_buffer[2];
	printf("unpacking %.*s\n...", name_size, (const char *)&file_buffer[3]);

	/* get rom size */
}

int
main(int argc, char **argv)
{
	switch (get_option(argc, argv)) {
	case UNPACK:
		unpack(argv[2]);
		break;
	case PACK:
		break;
	}
}
