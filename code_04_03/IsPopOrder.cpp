class Solution 
{
public:
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) 
    {
        int pushi = 0, popi = 0;
        stack<int> st;

        while(pushi < pushV.size())
        {
            st.push(pushV[pushi++]);

            // 序列匹配 -- 持续出数据 -- 直到不匹配 or 栈为空
            while(!st.empty() && st.top() == popV[popi])
            {
                ++popi;
                st.pop();
            }
        }

        return st.empty();
    }
};