#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int vote;
}
candidate;

candidate get_candidate(string prompet);
int main(void)
{
    candidate presidant = get_candidate("Enter a candidate");
}

candidate get_candidate(string prompet)
{
    printf("%s\n", prompet);
    candidate a;
    a.name = get_string("Enert a name: ");
    a.vote = get_int("Enter your vote: ");
    return a;
}