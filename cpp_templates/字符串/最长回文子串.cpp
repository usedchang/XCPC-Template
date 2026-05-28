int Manacher(const string& st) {
    string s = "^$";
    for (char c : st) {
        s += c;
        s += '$';
    }
    s += '&';
    int len = s.size(), mid = 1, mx = 1, ans = -1;
    vector<int> p(len);
    for (int i = 1; i < len; ++i) {
        if (i < mx)
            p[i] = min(mx - i, p[2 * mid - i]);
        else
            p[i] = 1;
        while (s[i - p[i]] == s[i + p[i]])
            ++p[i];
        if (mx < i + p[i]) {
            mid = i;
            mx = i + p[i];
        }
        ans = max(ans, p[i] - 1);
    }
    return ans;
}
int main() {
    string st;
    cin >> st;
    cout << Manacher(st) << endl;
}
