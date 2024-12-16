#ifndef SCORE_HEADER_
#define SCORE_HEADER_

class Score
{
private:
    int score = 0;
public:
    void increaseScore() { score++; }
    int getScore() { return score; }
};

#endif