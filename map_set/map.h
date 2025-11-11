#pragma once

namespace sl
{
	template <class K>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	private:
		RBtree<K, pair<K, V>, MapKeyOfT> _t;
	};
}