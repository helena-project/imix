#ifndef BITS_H
#define BITS_H

inline int setb(int word, int bit)
{
    word |= (0x1 << bit);
    return word; 
}

inline int flpb(int word, int bit)
{
    word ^= (0x1 << bit);
    return word; 
}

inline int clrb(int word, int bit)
{
    word &= ~(0x1 << bit);
    return word;
}

inline int is_set(int word, int bit)
{
    return word & (0x1 << bit);
}

#endif // BITS_H
