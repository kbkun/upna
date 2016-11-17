#ifndef CRC_H
#define CRC_H

namespace kama {

inline unsigned char crc(unsigned char *b, unsigned int len)
{

      unsigned int rg1, i;
      unsigned char crc = 0;

      for(i = 0; i < len; i++) {
            rg1 = 0;
            rg1 = crc + b[i];
            if(rg1 >= 0400) ++rg1;
            crc = (unsigned char)rg1;
      }
      return crc;
}
}

#endif // CRC_H
