#ifndef FONT_H
#define FONT_H

int section_parser();
char* element_parser(char *buffer);
void char_index_parser(char *buffer,int len);
uint16_t be2le(uint16_t val);
void data_parser(int offset);
int memcmp(const char* val_1, const char* val_2, int n);

#endif
