#pragma once

/*

//���������
	//��ֵ���������
	//[]���������
	//===���������
//���Ԫ��
	push_back
	insert
ɾ��Ԫ��
	pop_back
	erase
��������
	value_type front()const
	value_type front()const
	iterator begin()
	itorator end()
	size_t size()const
	size_t capacity()const
	bool empty()
�����ܽ�
*/

#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

namespace minSTL {

	template <typename T>
	class myVector {

	public:
		typedef T value_type; //���ǳ�Ա������ֻ�����ӿɶ���
		typedef T* iterator;	//���������
	private:
		value_type* _data;
		size_t _size;
		size_t _capacity;

	public:
		//����
		myVector() :_data(nullptr), _size(0), _capacity(0) {}
		//����
		~myVector() {
			delete[] _data; //ʹ��delete[] ������������������е�Ԫ�����ͷſռ䣬
			//���ֻʹ��delete ����������ֻ����������һ��Ԫ�أ��ͷŵ�һ��Ԫ�صĿռ�
			_data = nullptr;
			_size = 0;
			_capacity = 0;
		}
		//��������
		//����������ʵ��vector<int> vect1 = vect2�ù��ܵ�ʵ�ִ��룬
		//��ʵ����һ������ʱ��ʹ����һ������ĳ�Ա��������ʼ���ö���
		myVector(const myVector& vec)  {
			_size = vec._size;
			_capacity = vec._capacity;
			_data = new value_type[_capacity];
			for (int i = 0; i < _size; i++) {

				_data[i] = vec._data[i];

			}
		}
		//��������أ��������� = ��[]�� ==
		// ��������غ����ĸ�ʽ��	����ֵ operator�����(����Ĳ���)
		//��==�����Ϊ������������������ж����������Ƿ���ȣ������Է���һ��bool���͵ķ���ֵ��
		//�������Ϊ�Ƚϵ���һ�����󣬹ʺ���Ϊ��bool operator== (const vector& vect) const��
		//����const��������ָ����Ĳ����ǲ����޸ĵ�
		//�жϳ�������true������������false��  vect1.operator==(vect2)
		bool operator==(const myVector& vect) const {

			if (_size != vect._size) return false;

			for (int i = 0; i < _size; i++) {

				if (_data[i] != vect._data[i]) return false;

			}

			return true;
		}

		//��ֵ��������أ�������Ĳ�����������Ϣ����һ�ݡ�
		//���myVector���ԣ���ֵ��������ص���vect1 = vect2�����������õķ�ʽ��˵����vect1.operator=(vect2).

		myVector& operator=(const myVector& vect) {
			if (this == &vect) return *this;

			value_type* temp = new value_type[vect._capacity];

			for (int i = 0; i < vect.size; i++) {

				temp[i] = vect._data[i];//��vect��ÿһ������ȫ��������temp��

			}
			delete[] _data;//���_data��ֵ
			_data = temp;
			_size = vect._size;
			_capacity = vect._capacity;

			return *this;
		}

		//[]���������,���ľ���ʵ����vect[0]��������������������vect.operator()[0]

		value_type& operator[](size_t index) { return _data[index]; }
		//����Ԫ�أ������ַ�����һ������ĩβ������Ԫ�أ�Ҳ����push_back������һ������ָ��λ������Ԫ�أ�Ҳ����insert
		//�����ַ�ʽ������˼·�����������Ŀռ�������Ԫ�أ�������Ҫ�������λ�������һ��Ԫ��ͬ������ƶ�һ��λ��
		//�Ӷ��ճ�һ��λ���������µ�Ԫ�ء��ڴ�����Ҳ�����뱶�����ڴ�ռ䣬Ҳ����_capacity*2,
		//��Ҫע����ǣ���vectΪ�յ�ʱ�������޷�ʹ�øô�����ͳһ����

		//push_back

		void push_back(value_type val) {
			if (0 == _capacity) { //����ڴ�ռ�Ϊ�㣬Ҳ����vectorΪ��
				_capacity = 1;		//����_capacityΪ1
				_data = new value_type[1];	//newһ��valve_type[]���͵�����
			}
			else if (_size + 1 > _capacity) {//�ռ��ڴ治������Ҫ���������ڴ�
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

		//ɾ��Ԫ�أ���Ϊ���ַ�ʽ��һ����ĩβɾ����pop_back��һ����ָ��λ��ɾ������erase��

		void pop_back() { --_size; }
		void erase(iterator it) {

			size_t index = it - _data;

			for (int i = index; i < size - 1; i++) {

				_data[i] = _data[i - 1];
			}
			--_size;
		}


		//���ص�һ��Ԫ��

		value_type front() const { return _data[0]; }

		//�������һ��Ԫ��
		value_type back() const { return _data[_size - 1]; }

		//���ص�һ��Ԫ�ص�ַ

		iterator begin() { return _data; }

		//�������һ��Ԫ�ص�ַ
		iterator end() { return _data + _size; }

		//����vector��Ԫ�ظ���

		size_t size() { return _size; }
		//����vector������ռ�Ĵ�С

		size_t capitor() { return _capacity; }

		//�ж�vector�Ƿ�Ϊ��

		bool empty() { return _size == 0; }



	};
}


