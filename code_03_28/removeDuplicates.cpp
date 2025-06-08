class Solution
{
public:
    int removeDuplicates(vector<int>& nums)
    {
        int slow = 1, fast = 1;

        while (fast < nums.size())
        {
            if (nums[fast] == nums[fast - 1])
            {
                ++fast;
            }
            else
            {
                nums[slow++] = nums[fast++];
            }
        }

        return slow;
    }
};