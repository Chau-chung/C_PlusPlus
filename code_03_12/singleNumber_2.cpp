#define _CRT_SECURE_NO_WARNINGS

class Solution
{
public:
    int singleNumber(vector<int>& nums)
    {
        int ret = 0;
        for (int i = 0; i < 32; ++i)
        {
            int count = 0;
            for (auto e : nums)
            {
                // count += ((e >> i) & 1);
                if ((e >> i) & 1)
                {
                    ++count;
                }
            }

            if (count % 3)
            {
                ret |= (1 << i);
            }
        }

        return ret;
    }
};