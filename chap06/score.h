#ifndef __PRIVATE_SCORE_H__
#define __PRIVATE_SCORE_H__

#include <stddef.h>

struct Score {
    unsigned int number;
    float score;
};

extern struct Score score_data_set[];

size_t SCORE_NrData(void);

#endif /* __PRIVATE_SCORE_H__ */
