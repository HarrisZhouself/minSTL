#pragma once

/*

//运算符重载
	//赋值运算符重载
	//[]运算符重载
	//===运算符重载
//添加元素
	push_back
	insert
删除元素
	pop_back
	erase
其他函数
	value_type front()const
	value_type front()const
	iterator begin()
	itorator end()
	size_t size()const
	size_t capacity()const
	bool empty()
代码总结
*/

#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

namespace minSTL {

	template <typename T>
	class myVector {

	public:
		typedef T value_type; //不是成员变量，只是增加可读性
		typedef T* iterator;	//重新起别名
	private:
		value_type* _data;
		size_t _size;
		size_t _capacity;

	public:
		//构造
		myVector() :_data(nullptr), _size(0), _capacity(0) {}
		//析构
		~myVector() {
			delete[] _data; //使用delete[] 加数组名来清除数组中的元素来释放空间，
			//如果只使用delete 加数组名，只会清除数组第一个元素，释放第一个元素的空间
			_data = nullptr;
			_size = 0;
			_capacity = 0;
		}
		//拷贝构造
		//功能是用于实现vector<int> vect1 = vect2该功能的实现代码，
		//即实例化一个对象时，使用另一个对象的成员变量来初始化该对象
		myVector(const myVector& vec)  {
			_size = vec._size;
			_capacity = vec._capacity;
			_data = new value_type[_capacity];
			for (int i = 0; i < _size; i++) {

				_data[i] = vec._data[i];

			}
		}
		//运算符重载，将会重载 = ，[]， ==
		// 运算符重载函数的格式是	返回值 operator运算符(传入的参数)
		//以==运算符为例，该运算符功能是判断两个对象是否相等，，所以返回一个bool类型的返回值，
		//传入参数为比较的另一个对象，故函数为：bool operator== (const vector& vect) const，
		//其中const的作用是指传入的参数是不可修改的
		//判断成立返回true，不成立返回false，  vect1.operator==(vect2)
		bool operator==(const myVector& vect) const {

			if (_size != vect._size) return false;

			for (int i = 0; i < _size; i++) {

				if (_data[i] != vect._data[i]) return false;

			}

			return true;
		}

		//赋值运算符重载，将传入的参数的所有信息拷贝一份。
		//针对myVector而言，赋值运算符重载的是vect1 = vect2，按函数调用的方式来说就是vect1.operator=(vect2).

		myVector& operator=(const myVector& vect) {
			if (this == &vect) return *this;

			value_type* temp = new value_type[vect._capacity];

			for (int i = 0; i < vect.size; i++) {

				temp[i] = vect._data[i];//把vect中每一个数据全部拷贝给temp；

			}
			delete[] _data;//清空_data的值
			_data = temp;
			_size = vect._size;
			_capacity = vect._capacity;

			return *this;
		}

		//[]运算符重载,它的具体实现是vect[0]，按函数调用来理解就是vect.operator()[0]

		value_type& operator[](size_t index) { return _data[index]; }
		//增添元素，有两种方法，一种是在末尾处增添元素，也就是push_back，还有一种是在指定位置增添元素，也就是insert
		//这两种方式的总体思路都是在连续的空间中增添元素，我们需要将插入的位置至最后一个元素同意向后移动一个位置
		//从而空出一个位置来插入新的元素。在此我们也会申请倍增的内存空间，也就是_capacity*2,
		//需要注意的是，当vect为空的时候，我们无法使用该代码来统一处理

		//push_back

		void push_back(value_type val) {
			if (0 == _capacity) { //如果内存空间为零，也就是vector为空
				_capacity = 1;		//设置_capacity为1
				_data = new value_type[1];	//new一个valve_type[]类型的数组
			}
			else if (_size + 1 > _capacity) {//空间内存不够，需要申请更大的内存
				_capacity = _capacity * 2;
				value_type* temp = new value_type[_capacity];

				for (int i = 0; i < _size; i++) {
					temp[i] = _data[i];

				}
				delete[] _data;
				_data = temp;

			}
			_data[_size] = val;
			++_size;
		}

		//insert

		void insert(value_type val, iterator it) {
			int index = it - _data;
			if (0 == _capacity) {
				_capacity = 1;
				_data = new value_type[1];
				_data[0] = val;
			}
			else if (size + 1 > _capacity) {
				_capacity = _capacity * 2;
				value_type* temp = new value_type[_capacity];

				for (int i = 0; i < index; i++) {
					temp[i] = _data[i];

				}
				for (int i = index; i < _size; i++) {
					temp[i + 1] = _size[i];

				}
				delete[] _data;

				_data = temp;


			}
			else {
				for (int i = _size - 1; i >= index; --i) {
					_data[i + 1] = _data[i];
				}
				_data[index] = val;
			}

			++size;
		}

		//删除元素，分为两种方式，一种是末尾删除，pop_back，一种是指定位置删除，是erase；

		void pop_back() { --_size; }
		void erase(iterator it) {

			size_t index = it - _data;

			for (int i = index; i < size - 1; i++) {

				_data[i] = _data[i - 1];
			}
			--_size;
		}


		//返回第一个元素

		value_type front() const { return _data[0]; }

		//返回最后一个元素
		value_type back() const { return _data[_size - 1]; }

		//返回第一个元素地址

		iterator begin() { return _data; }

		//返回最后一个元素地址
		iterator end() { return _data + _size; }

		//返回vector的元素个数

		size_t size() { return _size; }
		//返回vector中申请空间的大小

		size_t capitor() { return _capacity; }

		//判断vector是否为空

		bool empty() { return _size == 0; }



	};
}


