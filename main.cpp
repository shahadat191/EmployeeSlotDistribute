#include<bits/stdc++.h>
using namespace std;
#define pb              push_back

#define input           freopen("/Users/shahadat/Desktop/input.txt", "r", stdin)
#define output          freopen("/Users/shahadat/Desktop/output.txt", "w", stdout)

struct eTime{
    int id;
    int timeRemain;
    bool operator < (const eTime& b)const{
        if(timeRemain == b.timeRemain)
            return id > b.id;
        return timeRemain < b.timeRemain;
    }
};


vector<int> daySlot[8][5];
set<int> S[8];

string dayName[] = {"", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void solve(){
    int numberOfEmployees;
    cin >> numberOfEmployees;
    
    priority_queue<eTime> Q;
    for(int i = 1; i <= 6; i++)
        for(int j = 1; j <= numberOfEmployees; j++)
            S[i].insert(j);
    
    for(int i = 1; i <= numberOfEmployees; i++){
        Q.push({i, 40});
    }
    
    for(int i = 1; i <= 6; i++){
        vector<eTime> temp;
        for(int j = 1; j <= 4; j++){
            temp.pb(Q.top());
            Q.pop();
        }
        for(int j = 0; j < 4; j++){
            if(j < 2){
                daySlot[i][1].pb(temp[j].id);
                daySlot[i][2].pb(temp[j].id);
            }
            else{
                daySlot[i][3].pb(temp[j].id);
                daySlot[i][4].pb(temp[j].id);
            }
            S[i].erase(temp[j].id);
            if(temp[j].timeRemain > 8)
                Q.push({temp[j].id, temp[j].timeRemain - 8});
        }
    }

    priority_queue<pair<int,int> > day;
    for(int i = 1; i <= 4; i++){
        day.push({0, i});
    }
    while(!Q.empty()){
        while(S[day.top().second].find(Q.top().id) == S[day.top().second].end()){
            day.push({day.top().first - 1, day.top().second});
            day.pop();
        }
        daySlot[day.top().second][2].pb(Q.top().id);
        daySlot[day.top().second][3].pb(Q.top().id);
        S[day.top().second].erase(Q.top().id);
        day.push({day.top().first - 2, day.top().second});
        day.pop();
        Q.pop();
    }
    
    printf("     7:00-11:00  11:00 - 3:00   3:00 - 7:00   8:00 - 12:00\n");
    for(int i = 1; i <= 6; i++){
        cout << dayName[i] << "     ";
        for(int j = 1; j <= 4; j++){
            cout << daySlot[i][j].front();
            for(int k = 1; k < daySlot[i][j].size(); k++){
                cout << "," << daySlot[i][j][k];
            }
            for(int k = 1; k <= 15 - 2*daySlot[i][j].size(); k++)
                cout << " ";
        }
        cout << endl;
    }
}


int32_t main(){
    //fast();
    solve();
}
