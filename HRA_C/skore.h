#include <fstream>
#include <iostream>




int zistiskore()
{
std::ifstream rfile;
int high_score;
rfile.open("High_score.txt");
    if (rfile.is_open())
    {
        std::string line;
        getline(rfile, line);
        high_score = stoi(line);
        rfile.close();
    }
    return high_score;
}

void ulozskore(int highest_score)
{
    std::ofstream wfile;
    wfile.open("High_score.txt");
    wfile << highest_score;
    wfile.close();
}