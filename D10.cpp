#include <bits/stdc++.h>

#ifdef LOCAL
# include "template/debug.hpp"
#else
# define debug(...)
# define debugArr(...)
#endif

using namespace std;

typedef long long ll;
#define endl "\n"

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}

	size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

// unordered_map<int, pair<int,int>, custom_hash>

template <typename T>
void	print(T cont, ostream & os)
{
	bool	w = false;
	for (typename T::iterator it = cont.begin(); it != cont.end(); ++it)
	{
		if (w)
			os << " ";
		else
			w = true;
		os << *it;
	}
	os << endl;
}

ll pow(ll a, ll b)
{
	return ((ll) round(std::pow(a, b)));
}

ll sqrt(ll a)
{
	ll res = sqrtl(a);

	while (res * res < a) ++res;
	while (res * res > a) --res;

	return (res);
}

vector<string> split(const string &str, string del = " ") {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(del, start)) != string::npos) {

		string res = str.substr(start, end - start);
		// if (res != "")
		tokens.push_back(res);

		start = end + 1;
	}
	// if (str.substr(start) != "")
	tokens.push_back(str.substr(start));

	return tokens;
}

vector<pair<int,int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<pair<int,int>> dir8 = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};

int calc(int i , string const & res, vector<string> & s, string cur)
{
	if (cur == res)
		return (0);
	if (i == (int)s.size() - 1)
		return (99999999);

	string but = s[i].substr(1);
	but.resize(but.size() - 1);

	string cur1 = cur;


	vector<string> ss = split(but, ",");
	debug(ss);

	for (int j = 0; j < (int) ss.size(); ++j)
	{
		// debug(ss[j]);
		int a = stoi(ss[j]);

		if (cur1[a] == '.')
			cur1[a] = '#';
		else
			cur1[a] = '.';
	}


	int a = 1 + calc(i + 1, res, s, cur1);
	int b = calc(i + 1, res, s, cur);

	return (min(a, b));
	
}

void solve(vector<string> & in)
{

	ll val = 0;
	for (int i = 0; i < (int) in.size(); ++i)
	{
		vector<string> s = split(in[i]);

		string res = s[0].substr(1);
		res.resize(res.size() - 1);
		debug(res);

		string cur;
		for (int j = 0; j < (int) res.size(); ++j)
			cur += '.';

		val += calc(1, res, s, cur);
		debug(val);

	}

	cout << val << endl;
}

int main(void)
{
	bool solved = false; 
	(void) solved;
	
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t;

	t = 1;

	////////////////////////////////////
	// INPUT
	vector<string> in;
	string s;
	while (getline(cin, s))
	{
		in.push_back(s);
	}
	///////////////////////////////////

	for (int o = 0; o < t; ++o)
	{
		solve(in);
	}
	return 0;
}
