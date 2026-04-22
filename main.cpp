#include <bits/stdc++.h>
// Problem 097 - Find the cnt-th largest value in a BST given by level-order list

using namespace std;

/*
Input format (from README):
root = [12, 5, 18, 2, 9, 15, 20], cnt = 4
We will parse from a single line stdin, tolerant to spaces.
Assumptions:
- Array given as level-order, no null markers are mentioned; we will treat all entries as valid nodes.
- The array corresponds to a BST's values in level order, but BST property holds across values, so we can simply collect values and find cnt-th largest.
Efficient approach: parse values, sort descending, pick cnt-1 index.
Time O(n log n). Alternatively, nth_element for O(n).
We'll implement nth_element for performance.
*/

static bool parse_input_line(const string &line, vector<long long> &vals, long long &cnt){
    vals.clear();
    cnt = 0;
    // Try parsing the part inside brackets []
    size_t lb = line.find('[');
    size_t rb = line.find(']');
    if (lb != string::npos && rb != string::npos && rb > lb) {
        string arr = line.substr(lb+1, rb-lb-1);
        for (char &c : arr) if (c == ',') c = ' ';
        stringstream ss(arr);
        long long x;
        while (ss >> x) vals.push_back(x);
        // Find cnt =
        size_t pos_cnt = line.find("cnt");
        if (pos_cnt != string::npos) {
            size_t eq = line.find('=', pos_cnt);
            if (eq != string::npos) {
                string rest = line.substr(eq+1);
                for (char &c : rest) if (!isdigit((unsigned char)c) && c != '-') c = ' ';
                stringstream ss2(rest);
                if (ss2 >> cnt) {
                    return !vals.empty() && cnt >= 1 && cnt <= (long long)vals.size();
                }
            }
        }
    }
    // Fallback: parse all integers and assume last is cnt
    vector<long long> all;
    {
        string cleaned = line;
        for (char &c : cleaned) if (!(isdigit((unsigned char)c) || c=='-' )) c = ' ';
        stringstream ss(cleaned);
        long long x;
        while (ss >> x) all.push_back(x);
    }
    if (all.size() >= 2) {
        cnt = all.back();
        all.pop_back();
        vals = move(all);
        return !vals.empty() && cnt >= 1 && cnt <= (long long)vals.size();
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    {
        // Read entire stdin into one string (may include newlines)
        string line, all;
        while (getline(cin, line)){
            if (!all.empty()) all += ' ';
            all += line;
        }
        input = all;
    }

    vector<long long> vals;
    long long cnt = 0;
    if (!parse_input_line(input, vals, cnt)){
        return 0; // or print nothing per OJ expectations
    }

    // Find cnt-th largest using nth_element
    // cnt-th largest => index = cnt-1 in descending order
    // Transform to ascending by selecting nth = size-cnt
    size_t n = vals.size();
    size_t idx = n - cnt; // 0-based index for ascending order
    nth_element(vals.begin(), vals.begin()+idx, vals.end());
    long long ans = vals[idx];
    cout << ans << "\n";
    return 0;
}
