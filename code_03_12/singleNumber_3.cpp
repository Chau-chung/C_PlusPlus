class Solution 
{
public:
    vector<int> singleNumber(vector<int>& nums) 
    {
        int xor_res = 0;

        for(auto e : nums)
        {
            xor_res ^= e;
        }

        int index = 0;
        while(((xor_res >> index) & 1) == 0)
        {
            ++index;
        }
        
        int a = 0, b = 0;
        vector<int> ans(2);

        for(auto e : nums)
        {
            if((e >> index) & 1)
            {
                ans[0] ^= e;
            }
            else
            {
                ans[1] ^= e;
            }
        }
        
        return ans;
    }
};