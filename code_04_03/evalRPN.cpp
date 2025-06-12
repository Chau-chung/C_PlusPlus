class Solution 
{
public:
    int evalRPN(vector<string>& tokens) 
    {
        stack<int> st;
        set<string> op = {"+","-","*","/"};

        for(auto& str : tokens)
        {
            // 操作数入栈，操作符运算
            if(op.find(str) != op.end())
            {
                int right = st.top();
                st.pop();
                int left = st.top();
                st.pop();

                switch(str[0])
                {
                    case '+':
                        st.push(left + right);
                        break;
                    case '-':
                        st.push(left - right);
                        break;
                    case '*':
                        st.push(left * right);
                        break;
                    case '/':
                        st.push(left / right);
                        break;
                }
            }
            else
            {
                st.push(stoi(str));
            }
        }
        
        return st.top();
    }
};