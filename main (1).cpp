#include<bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

#define int long long
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

map<pair<int, int>, int> pts;

struct node{
    int x, y, val;
};

int n, m;
vector<node> crystal, mine;
int achieved;
int totalPositive;
int totalNegative; 
int total;
int total_achieved;

void _input(){

    pts.clear();

    cin >> n;
    crystal.clear();
    crystal.resize(n);

    totalPositive = 0;
    totalNegative = 0;

    for(int i = 0; i < n; i++){
        cin >> crystal[i].x >> crystal[i].y >> crystal[i].val;
        totalPositive += crystal[i].val;
        pts[{crystal[i].x, crystal[i].y}] += crystal[i].val;
    }

    cin >> m; 
    mine.clear();
    mine.resize(m);

    for(int i = 0; i < m; i++){
        cin >> mine[i].x >> mine[i].y >> mine[i].val;
        mine[i].val *= -1;
        totalNegative += mine[i].val;
        pts[{mine[i].x, mine[i].y}] += mine[i].val;
    }
}

pair<int, set<pair<pair<double, double>, pair<double, double>>>> generate_stripperX(int threshold){
    map<int, int> m;
    
    map<double, double> e1, e2;

    for(auto i : crystal){
        m[i.x] += i.val;
    }
    for(auto i : mine){
        m[i.x] += i.val;
    }

    vector<pair<int, pair<int, int>>> v;
    int curr = 0;

    int st = 0;
    for(int i = 0; i <= 1e4; i++){
        if(m[i] >= threshold){
            curr += m[i];
        }
        else{
            if(st == i){
                curr = 0;
                st++;
                continue;
            }
            
            v.push_back({curr, {st, i - 1}});
            curr = 0;
            st = i + 1;
        }
    }

    if(curr > 0) v.push_back({curr, {st, 10000}});

    sort(rall(v));

    int cost = 0;

    vector<pair<pair<double, double>, pair<double, double>>> edgeH, edgeV; 
    set<pair<pair<double, double>, pair<double, double>>> fin;

    for(int i = 0; i < min((int) v.size(), 250ll); i++){
        if(v[i].first <= 0) break;

        double st = v[i].second.first;
        double en = v[i].second.second;

        if(st == en) en += 0.5;

        edgeV.push_back({{st, 0}, {st, 1e4}});
        edgeV.push_back({{en, 0}, {en, 1e4}});

        edgeH.push_back({{st, 0}, {en, 0}});
        edgeH.push_back({{st, 1e4}, {en, 1e4}});
        e1[st] = en;
        e1[en] = st;

        e2[st] = en;
        e2[en] = st;

        cost += v[i].first;
    }

    for(auto i : edgeV) fin.insert(i);
    for(auto i : edgeH) fin.insert(i);

    sort(all(edgeH));
    sort(all(edgeV));

    int ex = 0;

    for(int i = 0; i + 2 < edgeH.size(); i += 2){
        int up = 0;
        int down = 0;

        for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
            up += pts[{j, 0}];
        }
        for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
            down += pts[{j, 1e4}];
        }

        double pehle = edgeH[i].second.first;
        double baad = edgeH[i + 2].first.first;

        if(up >= down){

            fin.erase({{e1[pehle] , 0}, {pehle, 0}});
            fin.erase({{baad, 0}, {e1[baad], 0}});
            fin.insert({{e1[pehle], 0}, {e1[baad], 0}});

            fin.insert({{pehle, 0.5}, {baad, 0.5}});

            fin.erase({{pehle, 0}, {pehle, 1e4}});
            fin.erase({{baad, 0}, {baad, 1e4}});

            fin.insert({{pehle, 0.5}, {pehle, 1e4}});
            fin.insert({{baad, 0.5}, {baad, 1e4}});

            e1[e1[baad]] = e1[pehle];
            
            ex += up;
        }
        else{

            fin.erase({{e2[pehle] , 1e4}, {pehle, 1e4}});
            fin.erase({{baad, 1e4}, {e2[baad], 1e4}});
            fin.insert({{e2[pehle], 1e4}, {e2[baad], 1e4}});

            fin.insert({{pehle, 9999.5}, {baad, 9999.5}});

            fin.erase({{pehle, 0}, {pehle, 1e4}});
            fin.erase({{baad, 0}, {baad, 1e4}});

            fin.insert({{pehle, 0}, {pehle, 9999.5}});
            fin.insert({{baad, 0}, {baad, 9999.5}});

            e2[e2[baad]] = e2[pehle];

            ex += down;
        }
    }

    achieved = max(achieved, cost + ex);

    return {cost + ex, fin};
}

pair<int, set<pair<pair<double, double> , pair<double, double>>>> generate_stripperY(int threshold){
    map<int, int> m;
    
    map<double, double> e1, e2;

    for(auto i : crystal){
        m[i.y] += i.val;
    }
    for(auto i : mine){
        m[i.y] += i.val;
    }

    vector<pair<int, pair<int, int>>> v;
    int curr = 0;

    int st = 0;
    for(int i = 0; i <= 1e4; i++){
        if(m[i] >= threshold){
            curr += m[i];
        }
        else{
            if(st == i){
                curr = 0;
                st++;
                continue;
            }
            
            v.push_back({curr, {st, i - 1}});
            curr = 0;
            st = i + 1;
        }
    }

    if(curr > 0) v.push_back({curr, {st, 10000}});

    sort(rall(v));

    int cost = 0;

    vector<pair<pair<double, double>, pair<double, double>>> edgeH, edgeV; 
    set<pair<pair<double, double>, pair<double, double>>> fin;

    for(int i = 0; i < min((int) v.size(), 250ll); i++){
        if(v[i].first <= 0) break;

        double st = v[i].second.first;
        double en = v[i].second.second;

        if(st == en) en += 0.5;

        edgeV.push_back({{st, 0}, {st, 1e4}});
        edgeV.push_back({{en, 0}, {en, 1e4}});

        edgeH.push_back({{st, 0}, {en, 0}});
        edgeH.push_back({{st, 1e4}, {en, 1e4}});
        e1[st] = en;
        e1[en] = st;

        e2[st] = en;
        e2[en] = st;

        cost += v[i].first;
    }

    for(auto i : edgeV) fin.insert(i);
    for(auto i : edgeH) fin.insert(i);

    sort(all(edgeH));
    sort(all(edgeV));

    int ex = 0;

    for(int i = 0; i + 2 < edgeH.size(); i += 2){
        int up = 0;
        int down = 0;

        for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
            up += pts[{0, j}];
        }
        for(int j = (int)edgeH[i].second.first + 1; j < (int)edgeH[i + 2].first.first; j++){
            down += pts[{1e4, j}];
        }

        double pehle = edgeH[i].second.first;
        double baad = edgeH[i + 2].first.first;

        if(up >= down){

            fin.erase({{e1[pehle] , 0}, {pehle, 0}});
            fin.erase({{baad, 0}, {e1[baad], 0}});
            fin.insert({{e1[pehle], 0}, {e1[baad], 0}});

            fin.insert({{pehle, 0.5}, {baad, 0.5}});

            fin.erase({{pehle, 0}, {pehle, 1e4}});
            fin.erase({{baad, 0}, {baad, 1e4}});

            fin.insert({{pehle, 0.5}, {pehle, 1e4}});
            fin.insert({{baad, 0.5}, {baad, 1e4}});

            e1[e1[baad]] = e1[pehle];
            
            ex += up;
        }
        else{

            fin.erase({{e2[pehle] , 1e4}, {pehle, 1e4}});
            fin.erase({{baad, 1e4}, {e2[baad], 1e4}});
            fin.insert({{e2[pehle], 1e4}, {e2[baad], 1e4}});

            fin.insert({{pehle, 9999.5}, {baad, 9999.5}});

            fin.erase({{pehle, 0}, {pehle, 1e4}});
            fin.erase({{baad, 0}, {baad, 1e4}});

            fin.insert({{pehle, 0}, {pehle, 9999.5}});
            fin.insert({{baad, 0}, {baad, 9999.5}});

            e2[e2[baad]] = e2[pehle];

            ex += down;
        }
    }

    achieved = max(achieved, cost + ex);

    achieved = max(achieved, cost + ex);
    return {cost + ex, fin};
}

pair<int, set<pair<pair<double, double> , pair<double, double>>>> generateBest165(){
    vector<pair<int, pair<int, int>>> t;

    for(auto i : crystal){
        t.push_back({pts[{i.x, i.y}], {i.x, i.y}});
    }

    sort(rall(t));

    int curr = 0;
    map<int, set<pair<int, int>>> s;

    int took = 0;
    for(int i = 0; i < t.size() && took < 166; i++){
        
        if(t[i].second.second == 0) continue;
        if(t[i].second.second == 1e4) continue;
        if(t[i].second.first == 0) continue;
        if(t[i].second.first == 1e4) continue;

        curr += t[i].first;

        if(s[t[i].second.first].find(t[i].second) != s[t[i].second.first].end()){
            continue;
        }

        s[t[i].second.first].insert(t[i].second);
        took++;
    }

    double minx = 1e4, maxx = 0;
    for(auto i : s){
        minx = min(minx, (double) i.first);
        maxx = max(maxx, (double) i.first);
    }

    double top = 1e4;
    int tempsc = 0;

    for(int i = minx; i <= maxx; i++){
        tempsc += pts[{i, 1e4}];
    }
    
    set<pair<pair<double, double>, pair<double, double>>> fin;

    if(tempsc < 0){
        top = 1e4 - 0.1;
    }

    if(minx != 0) minx -= 0.2;
    if(maxx != 1e4) maxx -= 0.1;

    fin.insert({{minx, top}, {maxx, top}});

    double lst = minx;

    for(auto i : s){
        if(i.first - 0.2 == minx){

            auto it = i.second.begin();
            double mxy = it -> second;

            mxy -= 0.1;
            fin.insert({{minx, top}, {minx, mxy}});

            double currx = minx;

            fin.insert({{currx, mxy}, {currx + 0.3, mxy}});
            fin.insert({{currx + 0.3, mxy}, {currx + 0.3, mxy + 0.2}});
            fin.insert({{currx + 0.3, mxy + 0.2}, {currx + 0.1, mxy + 0.2}});

            currx += 0.1;
            double curry = mxy + 0.2;

            int n1 = i.second.size();

            it = i.second.begin();
            it++;

            for(int j = 1; j < n1 && it != i.second.end(); j++){    
                int x1 = it -> first;;
                int y1 = it -> second;

                fin.insert({{currx, curry}, {currx, y1 - 0.1}});
                fin.insert({{currx, y1 - 0.1}, {x1 + 0.1, y1 - 0.1}});
                fin.insert({{x1 + 0.1, y1 - 0.1}, {x1 + 0.1, y1 + 0.1}});
                fin.insert({{x1 + 0.1, y1 + 0.1}, {currx, y1 + 0.1}});

                curry = y1 + 0.1;
                it++;
            }

            fin.insert({{currx, curry}, {currx, top - 0.1}});
            lst = currx;
        }
        else if(i.first - 0.1 == maxx){

            auto it = i.second.begin();
            double mxy = it -> second;
            mxy -= 0.1;

            double currx = i.first - 0.2;
            fin.insert({{lst, top - 0.1}, {currx, top - 0.1}});

            fin.insert({{currx, top - 0.1}, {currx, mxy}});
            fin.insert({{currx, mxy}, {currx + 0.3, mxy}});
            fin.insert({{currx + 0.3, mxy}, {currx + 0.3, mxy + 0.2}});
            fin.insert({{currx + 0.3, mxy + 0.2}, {currx + 0.1, mxy + 0.2}});

            currx += 0.1;

            double curry = mxy + 0.2;

            int n1 = i.second.size();

            it = i.second.begin();
            it++;

            for(int j = 1; j < n1 && it != i.second.end(); j++){
                int x1 = it -> first;
                int y1 = it -> second;

                fin.insert({{currx, curry}, {currx, y1 - 0.1}});
                fin.insert({{currx, y1 - 0.1}, {x1 + 0.1, y1 - 0.1}});
                fin.insert({{x1 + 0.1, y1 - 0.1}, {x1 + 0.1, y1 + 0.1}});
                fin.insert({{x1 + 0.1, y1 + 0.1}, {currx, y1 + 0.1}});

                curry = y1 + 0.1;
                it++;
            }

            fin.insert({{currx, curry}, {currx, top}});
            lst = currx;
        }
        else{
            auto it = i.second.begin();

            double mxy = it -> second;
            mxy -= 0.1;

            double currx = i.first - 0.2;
            fin.insert({{lst, top - 0.1}, {currx, top - 0.1}});

            fin.insert({{currx, top - 0.1}, {currx, mxy}});
            fin.insert({{currx, mxy}, {currx + 0.3, mxy}});
            fin.insert({{currx + 0.3, mxy}, {currx + 0.3, mxy + 0.2}});
            fin.insert({{currx + 0.3, mxy + 0.2}, {currx + 0.1, mxy + 0.2}});

            currx += 0.1;
            double curry = mxy + 0.2;

            int n1 = i.second.size();
            it = i.second.begin();
            it++;

            for(int j = 1; j < n1 && it != i.second.end(); j++){
                int x1 = it -> first;
                int y1 = it -> second;

                fin.insert({{currx, curry}, {currx, y1 - 0.1}});
                fin.insert({{currx, y1 - 0.1}, {x1 + 0.1, y1 - 0.1}});
                fin.insert({{x1 + 0.1, y1 - 0.1}, {x1 + 0.1, y1 + 0.1}});
                fin.insert({{x1 + 0.1, y1 + 0.1}, {currx, y1 + 0.1}});

                curry = y1 + 0.1;
                it++;
            }

            fin.insert({{currx, curry}, {currx, top - 0.1}});
            lst = currx;
        }
    }

    return {curr + max(0ll, tempsc), fin};
}

pair<int, set<pair<pair<double, double>, pair<double, double>>>> generateWorst165(){
    vector<pair<int, pair<int, int>>> t;

    for(auto i : mine){
        t.push_back({pts[{i.x, i.y}], {i.x, i.y}});
    }

    sort(all(t));

    int curr = totalPositive + totalNegative;
    map<int, set<pair<int, int>>> s;

    int took = 0;
    for(int i = 0; i < t.size() && took < 166; i++){
        
        if(t[i].second.second == 0) continue;
        if(t[i].second.second == 1e4) continue;
        if(t[i].second.first == 0) continue;
        if(t[i].second.first == 1e4) continue;

        if(s[t[i].second.first].find(t[i].second) != s[t[i].second.first].end()){
            continue;
        }

        curr -= t[i].first;

        s[t[i].second.first].insert(t[i].second);

        took++;
    }

    double top = 1e4 - 0.1;
    
    set<pair<pair<double, double>, pair<double, double>>> fin;

    fin.insert({{1e4 - 0.1, top}, {1e4 - 0.1, 0.1}});
    fin.insert({{1e4 - 0.1, 0.1}, {0.1, 0.1}});
    fin.insert({{0.1, 0.1}, {0.1, top}});

    double lst = 0.1;

    for(auto i : s){
        auto it = i.second.begin();

        double mxy = it->second;
        mxy -= 0.1;

        double currx = i.first - 0.2;
        fin.insert({{lst, top}, {currx, top}});

        fin.insert({{currx, top}, {currx, mxy}});
        fin.insert({{currx, mxy}, {currx + 0.3, mxy}});
        fin.insert({{currx + 0.3, mxy}, {currx + 0.3, mxy + 0.2}});
        fin.insert({{currx + 0.3, mxy + 0.2}, {currx + 0.1, mxy + 0.2}});

        currx += 0.1;
        double curry = mxy + 0.2;

        int n1 = i.second.size();

        it++;

        it = i.second.begin();
        it++;

        for(int j = 1; j < n1 && it != i.second.end(); j++){    
            int x1 = it -> first;
            int y1 = it -> second;

            fin.insert({{currx, curry}, {currx, y1 - 0.1}});
            fin.insert({{currx, y1 - 0.1}, {x1 + 0.1, y1 - 0.1}});
            fin.insert({{x1 + 0.1, y1 - 0.1}, {x1 + 0.1, y1 + 0.1}});
            fin.insert({{x1 + 0.1, y1 + 0.1}, {currx, y1 + 0.1}});

            curry = y1 + 0.1;
            it++;
        }

        fin.insert({{currx, curry}, {currx, top}});
        lst = currx;
    }

    fin.insert({{lst, top}, {1e4 - 0.1, top}});

    for(int i = 0; i <= 1e4; i++){
        curr -= pts[{i, 1e4}];
        curr -= pts[{i, 0}];
    }

    for(int i = 1; i < 1e4; i++){
        curr -= pts[{0, i}];
        curr -= pts[{1e4, i}];
    }

    return {curr, fin};
}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int start = 0, end = 19;

    total = 0;
    total_achieved = 0;

    for(int i = start; i <= end; i++){

        string inp = "";
        string out = "";

        string num = to_string(i);
        if(num.size() == 1) num = "0" + num;

        inp = "input/input" + num + ".txt";
        out = "output/output" + num + ".txt";

        freopen(inp.c_str(), "r", stdin); // input
        freopen(out.c_str(), "w", stdout); // output

        achieved = 0;

        _input();   

        pair<int, set<pair<pair<double, double>, pair<double, double>>>> ans = {0, {}};

        for(int j = 0; j >= -45000; j-= 1000){
            pair<int, set<pair<pair<double, double>, pair<double, double>>>> temp = generate_stripperX(j);
            if(ans.first < temp.first){
                ans = temp;
            }
        }

        for(int j = 0; j >= -45000; j -= 1000){
            pair<int, set<pair<pair<double, double>, pair<double, double>>>> temp = generate_stripperY(j);
            if(ans.first < temp.first){
                ans = temp;
            }
        }

        pair<int, set<pair<pair<double, double>, pair<double, double>>>> ans1 = generateBest165();
        if(ans1.first >= ans.first) ans = ans1;

        ans1 = generateWorst165();

        if(ans1.first >= ans.first) ans = ans1;

        cout << ans.first << endl;
        cout << ans.first * 100.0 / totalPositive << "%" << endl;
        cout << ans.second.size() << endl;
        for(auto i : ans.second){
            cout << "(" << i.first.first << ", " << i.first.second << "), (" << i.second.first << ", " << i.second.second << ")" << endl;
        }

        total_achieved += ans.first;
        total += totalPositive;
    }

    freopen("output/final_output.txt", "w", stdout);
    cout << total << endl;
    cout << total_achieved << endl;
    cout << total_achieved * 100.0 / total << "%" << endl;

    return 0;
}