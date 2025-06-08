class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> ans;

        if (digits.empty())
        {
            return ans;
        }

        // 建立数字到字母的映射表
        vector<string> tel = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

        // 初始放入一个空字符串，后续构建组合
        ans.push_back("");

        for (auto digit : digits)
        {
            vector<string> tmp;
            for (auto s : ans)
            {
                for (auto ch : tel[digit - '0'])
                {
                    tmp.push_back(s + ch);
                }
            }

            // move语义将临时容器的内容转移到结果容器
            ans = move(tmp);
        }

        return ans;
    }
};