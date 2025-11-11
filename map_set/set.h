#pragma once

namespace sl
{
	template <class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key) 
			{
				return key;
			}
		};

	private:
		RBtree<K, K, SetKeyOfT> _t;
	};
}