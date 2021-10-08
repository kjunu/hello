#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
class Stone
{
public:
    int h;
    int w;
    float v;
    Stone(int height, int weight) : h(height), w(weight) { v = (float)h/(float)w; }
    bool operator < (const Stone &s) const { return (v == s.v)?(w < s.w):(v < s.v); }
};
 
int main()
{
    int TC;
    vector<Stone> tower;
    tower.reserve(1000);
    cin >> TC;
 
    while(TC--)
    {
        int N;
        cin >> N;
        for(int i=0;i < N; i++)
        {
            int h,w;
            cin >> h >> w;
            tower.push_back(Stone(h, w));
        }
 
        sort(tower.begin(), tower.end());
 
        int height = 0, total = 0;
        vector<Stone>::iterator it = tower.begin();
 
        for(; it != tower.end(); ++it)
        {
            total += height * it->w;
            height += it->h;
        }
        cout << "cost:" << total/10 << endl;
        tower.clear();
    }
    return 0;
}
