class Solution
{
public:
    int MoreThanHalfNum_Solution(vector<int>& nums)
    {
        int sz = nums.size();

        if (sz < 2)
            return nums[sz - 1];

        sort(nums.begin(), nums.end());

        int min = nums[0], max = nums[sz - 1];
        int range = max - min + 1;

        vector<int> count(range);

        for (auto e : nums)
        {
            ++count[e - min];
        }

        int i = 0;
        for (i = 0; i < range; ++i)
        {
            if (count[i] > sz / 2)
            {
                break;
            }
        }

        return i + min;
    }
};