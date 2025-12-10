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

	size_t operator()(const std::vector<unsigned char>& v) const {
		std::hash<unsigned char> hasher;
		size_t seed = 0;
		for (unsigned char i : v) {
			seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		}
		return seed;
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

ll calc(vector<vector<unsigned char>> & buttons, vector<unsigned char> & res, unordered_set<vector<unsigned char>, custom_hash> &m)
{
	ll ans = 0;
	queue<vector<unsigned char>> q;

	q.push(res);

	bool z = true;
	for (int j = 0; j < (int)q.front().size(); ++j)
	{
		if (q.front()[j] > 0) 
		{
			z = false;
			break;
		}
	}
	if (z)
		return (ans);

	while (!q.empty())
	{

		ll s = q.size();

		debug(q);
		
		for (int i = 0; i < s; ++i)
		{
			for (int j = 0; j < (int) buttons.size(); ++j)
			{
				vector<unsigned char> to_push = q.front();
				bool _push = true;
				for (int k = 0; k < (int) buttons[j].size(); ++k)
				{
					if (to_push[buttons[j][k]] == 0)
					{
						_push = false;
						break;
					}
					--to_push[buttons[j][k]];
				}
				if (_push && m.find(to_push) == m.end())
				{
					z = true;
					for (int l = 0; l < (int)to_push.size(); ++l)
					{
						if (to_push[l] > 0) 
						{
							z = false;
							break;
						}
					}
					if (z)
					{
						debug(to_push);
						return (ans + 1);
					}
					m.insert(to_push);
					q.push(to_push);
				}
			}
			q.pop();
		}
		++ans;
	}
	return (ans);
}

// ll calc(vector<vector<int>> & buttons, vector<int> & res)
// {
// 	// debug(res);
// 	bool z = true;
// 	for (int i = 0; i < (int)res.size(); ++i)
// 	{
// 		if (res[i] > 0) 
// 		{
// 			z = false;
// 			break;
// 		}
// 	}
// 	if (z)
// 		return (0);

// 	ll ans = INT_MAX;
// 	for (int i = 0; i < (int)buttons.size(); ++i)
// 	{
// 		bool valid = true;
// 		vector<int> res2 = res;
// 		for (int j = 0; j < (int) buttons[i].size(); ++j)
// 		{
// 			res2[buttons[i][j]]--;
// 			if (res2[buttons[i][j]] < 0)
// 			{
// 				valid = false;
// 				break;
// 			}
// 		}

// 		if (valid)
// 		{
// 			// debug(res, "        ");
// 			// debug(buttons[i]);
// 			// debug(res2);
// 			if (m.find(res2) == m.end())
// 				m[res2] = calc(buttons, res2);
// 			ans = min(ans, 1LL + m[res2]);
// 		}
// 	}

// 	return (ans);
// }

void solve(vector<string> & in)
{

	ll val = 0;
	// int m = 0;
	for (int i = 0; i < (int) in.size(); ++i)
	{
		cout << i << " begin" << endl;
		cout.flush();
		vector<string> s = split(in[i]);

		string o = s[s.size() - 1];
		o = o.substr(1);
		o.resize(o.size() - 1);
		vector<string> sp = split(o, ",");
		vector<unsigned char> res;
		for (int j = 0; j < (int) sp.size(); ++j)
		{
			res.push_back(stoi(sp[j]));
		}

		// debug(res);
		// debug(s);

		vector<vector<unsigned char>> buttons;

		for (int j = 1; j < (int) s.size() - 1; ++j)
		{
			string S = s[j].substr(1);
			S.resize(S.size() - 1);

			vector<string> ss = split(S, ",");

			vector<unsigned char> a;

			// debug(ss);

			for (int k = 0; k < (int) ss.size(); ++k)
			{
				a.push_back(stoi(ss[k]));
			}

			buttons.push_back(a);
		}

		// m = max(m, (int)res.size());
		// m.clear();
		// debug(buttons, res);
		unordered_set<vector<unsigned char>, custom_hash> m;
		ll a = calc(buttons, res, m);
		val += a;
		cout << i << " end, " << "val = "<< a << endl;
		cout.flush();

	}

	// cout << m << endl;
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
