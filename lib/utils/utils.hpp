#pragma once

namespace utstl
{
	namespace utils
	{
		template <typename T>
		void swap(T *a, T *b)
		{
			T temp = *a;
			*a = *b;
			*b = temp;
		}

		template <typename T>
		void swap(T &a, T &b)
		{
			T temp = a;
			a = b;
			b = temp;
		}
	} // namespace utils
} // namespace utstl