#include<bits/stdc++.h>
using std::cin, std::cout;
std::vector<int> kmp(const std::string & s) {
	std::vector<int> b(s.size());
	for(int i = 1, j = 0;i < (int) s.size();++i) {
		for(;j && s[i] != s[j];) j = b[j - 1];
		b[i] = j += s[i] == s[j];
	}
	return b;
}
std::vector<int> match(const std::string & s, const std::string & t) {
	auto b = kmp(s);
	std::vector<int> ans;
	for(int i = 0, j = 0;i < (int) t.size();++i) {
		for(;j && t[i] != s[j];) j = b[j - 1];
		j += t[i] == s[j];
		if(j == (int) s.size()) ans.push_back(i - s.size() + 1), j = b[j - 1];
	}
	return ans;
}


using namespace std;

// 朴素匹配
vector<int> brute(const string &s, const string &t) {
    vector<int> res;
    for (int i = 0; i + (int)s.size() <= (int)t.size(); ++i) {
        if (t.substr(i, s.size()) == s)
            res.push_back(i);
    }
    return res;
}

std::mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

string rand_str(int n, int sigma) {
    string s(n, 'a');
    for (int i = 0; i < n; ++i)
        s[i] = char('a' + std::min(rng() % sigma, rng() % sigma));
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ================= 随机压力测试 =================
    for (int it = 1; it <= 50000; ++it) {
        int n = rng() % 10 + 1;
        int m = rng() % 500;
        int sigma = rng() % 4 + 1;

        string s = rand_str(n, sigma);
        string t = rand_str(m, sigma);

        auto a = match(s, t);
        auto b = brute(s, t);

        if (a != b) {
            cout << "Mismatch!\n";
            cout << "pattern = " << s << "\n";
            cout << "text    = " << t << "\n";
            cout << "kmp     = ";
            for (int x : a) cout << x << ' ';
            cout << "\nbrute   = ";
            for (int x : b) cout << x << ' ';
            cout << "\n";
            return 0;
        }
    }

    // ================= 强力构造数据 =================
    {
        // 全相同字符
        string t(100000, 'a');
        string s(50000, 'a');
        assert(match(s, t) == brute(s, t));
    }

    {
        // 高 border
        string t;
        for (int i = 0; i < 50000; ++i) t += "ab";
        string s = "abababababab";
        assert(match(s, t) == brute(s, t));
    }

    {
        // 几乎匹配，但最后一个字符不同
        string s = string(1000, 'a') + 'b';
        string t = string(100000, 'a');
        assert(match(s, t) == brute(s, t));
    }

    {
        // pattern 比 text 长
        string s = rand_str(100, 3);
        string t = rand_str(10, 3);
        assert(match(s, t) == brute(s, t));
    }

    {
        // 单字符
        string s = "a";
        string t = rand_str(100000, 1);
        assert(match(s, t) == brute(s, t));
    }

    cout << "ALL STRESS TESTS PASSED\n";
    return 0;
}
