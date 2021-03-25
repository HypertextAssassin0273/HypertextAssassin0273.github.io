#include<iostream>
using namespace std;

/* Improved Custom Vector Class (minimal STL Vector) */
/*  Highlights:
	1) Main emphasis on 'rule of five' (move semantics applicable with C++11 settings)
	2) Elements are mapped/constructed on dynamically allocated buffer (i.e. use of 'placement new' operator)
	3) Safe when accessing elements with accessors (Exception somewhat handled)
	4) Perfect container for other classes & itself (i.e. 2D,3D,... Nested Vector)
	5) All neccessary STL Vector class 'modifiers' & 'iterators' are provided
*/

#if __cplusplus < 201103L
	const short nullptr=0L;
#define noexcept
#define override
#endif

template<typename T>
class Vector{
	typedef unsigned char __uchar;
	typedef unsigned int __uint32;
	typedef unsigned long long __uint64;
	
	static const __uint32 max_capacity=~((__uint32)0);
	//Tip: negate the min. value with extension (by typecasting) to get max. of any predefined datatype.
	__uint32 _size,_capacity;
	__uchar *data;//i.e. data-buffer on heap

public:
	Vector(__uint64 n=0)noexcept://i.e. default ctor
		_size((n>max_capacity)?throw:n),_capacity(_size),
		data((_size>0)?new __uchar[sizeof(T)*_size]:nullptr){//i.e. allocating new buffer 'data'
		for(__uint64 i=0;i<_size;++i)
			new(data+sizeof(T)*i) T();
		/*Note: empty-brackets initializes primitives with '0','\0',"\0" & for non-primitives,
				it invokes default ctors */
	}
	Vector(__uint64 n,const T& val)noexcept://i.e. ctor for initializing whole vector with given value
		_size((n>max_capacity)?throw:n),_capacity(_size),data(new __uchar[sizeof(T)*_size]){ 
		for(__uint64 i=0;i<_size;++i)
			new(data+sizeof(T)*i) T(val);
	}
#if __cplusplus >= 201103L
	Vector(std::initializer_list<T> list)noexcept://i.e. ctor for initializer-list (C++11 Construct)
		_size(0),_capacity(list.size()),data(new __uchar[sizeof(T)*_capacity]){
		for(const auto& it:list)//i.e. initializer_list can only be traversed with iterators
			new(data+sizeof(T)*_size++) T(it);//i.e. performs copy of list iterator's elements
	}
#endif
	Vector(const Vector& other)noexcept://i.e. copy ctor
		_size(other._size),_capacity(other._capacity),
		data((_capacity>0)?new __uchar[sizeof(T)*_size]:nullptr){
 		for(__uint64 i=0;i<_size;++i)
			new(data+sizeof(T)*i) T(other[i]);
	}
	Vector& operator=(const Vector& other)noexcept{//i.e. copy assignment func
		if(this==&other)//i.e. self-assignment protection
			return *this;
 		clear();//1) clear existing resources
  		delete[] data;
  		if(other._capacity){
  			data=new __uchar[sizeof(T)*other._size];
 			for(__uint64 i=0;i<other._size;++i)//2) constructing & copying resource from 'other'
				new(data+sizeof(T)*i) T(other[i]);
 		}
 		else
 			data=nullptr;
 		_size=other._size;
 		_capacity=other._capacity;
	 	return *this;
 	}
#if __cplusplus >= 201103L
 	Vector(Vector&& other)noexcept://i.e. move ctor (C++11 Construct)
  		data(other.data),_size(other._size),_capacity(other._capacity){//1) steal other's data
		other.data=nullptr;//2) set other's ptr to null state
  		other._size=0;
  		other._capacity=0;
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	Vector& operator=(Vector&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();//1) clear existing resources
  		delete[] data;
  		data=other.data;//2) steal other's data
  		_size=other._size;
  		_capacity=other._capacity;
  		other.data=nullptr;//3) set other to null state
  		other._size=0;
  		other._capacity=0;
  		return *this;
	}
#endif
	
 	/*i.e. Accessors & Mutators */
	T& operator[](__uint32 n)const{//i.e. gives read & write both access
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";			
	 		std::terminate();
		}
		return *(T*)(data+sizeof(T)*n);
	}
	T* operator+(__uint32 n)const{//i.e. returns address of current pointed element (stored in 'data' buffer)
		if (n>=_size){
			cout<<"\nError: Given Index is Out of Bound!\n";
	 		std::terminate();
		}
		return (T*)(data+sizeof(T)*n);
		//Note: use with '*' operator to access elements of 'data' buffer (i.e. cout<<*(vec+2);)
	}
	__uint32 size()const{ return _size; }
 	__uint32 capacity()const{ return _capacity; }
	
	/*i.e. Modifiers */
private:
	void reallocate(__uint64 n){
		__uchar* new_data=new __uchar[sizeof(T)*n];
		for(__uint64 i=0;i<(sizeof(T)*_size);++i)
			new_data[i]=data[i];//i.e. copying buffer (byte by byte)
		/*Note: 
			->this saves us from extra constructions & destructions
			->also copies ptr addresses, so no loss for non-P.O.D mapped objs */
		
		/*Alternate for copying objs (slower process): */
//		for(__uint64 i=0;i<_size;++i)//i.e. constructing & copying resource from 'other'
//				new(new_data+sizeof(T)*i) T(*(T*)(data+sizeof(T)*i));
//		for(__uint64 i=0;i<_size;++i)//i.e. destroying previously stored objs from 'data' buffer
//			((T*)(data+sizeof(T)*i))->~T();
		delete[] data;
		data=new_data;
	}
public:
    void push_back(const T& val){
    	if(_size>=_capacity)
			reallocate(_capacity?_capacity*=2:++_capacity);
			//i.e. if capacity is '0' then set it to '1' else twice it
    	new(data+sizeof(T)*_size++) T(val);
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	void emplace_back(_T&&... val){//i.e. more efficient (as direct obj initialization is possible)
    	if(_size>=_capacity)
    		reallocate(_capacity?_capacity*=2:++_capacity);
    	new(data+sizeof(T)*_size++) T(std::forward<_T>(val)...);
	}
#endif
	void pop_back(){
		if(_size)
    		((T*)(data+sizeof(T)*--_size))->~T();
	}
	void clear(){
		while(_size)
			((T*)(data+sizeof(T)*--_size))->~T();//i.e. explicit dtor call
		/*Note: we can destruct objects of 'T' type that are mapped on buffer 'data'
				by simply type-casting the buffer to object's ptr type */
	}
	bool reserve(__uint64 n){
		if(n>max_capacity)
			return false;
		if(n>_capacity)
			reallocate(_capacity=n);
		return true;
	}
	void resize(__uint64 n,const T& val=T()){
		if(n>_size&&reserve(n)){
	    	while(_size<_capacity)
    			new(data+sizeof(T)*_size++) T(val);
    		_size=n;
    	}
    	else while(n<_size)
			((T*)(data+sizeof(T)*--_size))->~T();
	}
	void shrink_to_fit(){//i.e. opppsite to reserve func
		if(_size<_capacity)
   	 	    reallocate(_capacity=_size);
	}
#if __cplusplus >= 201103L
	static void swap(T &xp,T &yp){
    	T temp=move(xp);//i.e. move ctor for temp gets invoked
    	xp=move(yp);//i.e. move ctor gets invoked for xp's pointed obj
    	yp=move(temp);//i.e. move ctor gets invoked for yp's pointed obj
	}
#else
	static void swap(T &xp,T &yp){
    	T temp=xp;
    	xp=yp;
    	yp=temp;
	}
#endif
	void sort(bool direction_flag=true){//i.e. improved bubble_sort (still not better than std::sort)
		for (__uint64 i=0;i<_size-1;++i){
			bool swapped=false;
	    	for (__uint64 j=0;j<_size-i-1;++j){
  	    		if(direction_flag){
					if(*(T*)(data+sizeof(T)*j)>*(T*)(data+sizeof(T)*(j+1))){//i.e. ascending (by default)
        		    	swap(*(T*)(data+sizeof(T)*j),*(T*)(data+sizeof(T)*(j+1)));
						swapped=true;
					}
				}
        		else if(*(T*)(data+sizeof(T)*j)<*(T*)(data+sizeof(T)*(j+1))){//i.e. descending 
    	    		swap(*(T*)(data+sizeof(T)*j),*(T*)(data+sizeof(T)*(j+1)));
    	    		swapped=true;
    	    	}
			}
			if (!swapped)
				break;
		}
	}

	/*i.e. Comparison Operators */
	bool operator==(const Vector& other)const{
		if(other._size<_size)
			return false;
		for (__uint64 i=0;i<_size;++i)
    		if (*(T*)(data+sizeof(T)*i)!=*(T*)(other.data+sizeof(T)*i))
      			return false;
  		return true;
	}
	bool operator!=(const Vector& other)const{ return !(*this==other); }
	
	bool operator<(const Vector& other)const{//i.e. follows lexicographical-order (Dictionary order)
  		__uint64 i=0;
  		for (;i!=_size;++i){
  			if(i==other._size||*(T*)(other.data+sizeof(T)*i)<*(T*)(data+sizeof(T)*i))
  				return false;
  			else if(*(T*)(data+sizeof(T)*i)<*(T*)(other.data+sizeof(T)*i))
  				return true;
		}
		return i!=other._size;
	}
    bool operator>(const Vector& other)const{ return other<*this; }
	
 	/*i.e. Iterators */
	template<bool flag>//i.e. true-> forward_iterator, false->reverse_iterator
	struct iterator{
    	iterator(T* ptr):ptr(ptr){}//i.e. default ctor
    	T& operator*()const{ return *ptr; }//i.e. gives read & write both access
    	T& operator++(){ flag?++ptr:--ptr; return *ptr; }//i.e. pre-increment
    	T& operator--(){ flag?--ptr:++ptr; return *ptr; }//i.e. pre-decrement
		bool operator!=(const iterator& other)const{ return ptr!=other.ptr; }
	private:
		T* ptr;
    };
    iterator<true> begin()const{ return iterator<true>((T*)data); }//i.e. points to first element (returning rvalue iterator obj)
	iterator<true> end()const{ return iterator<true>((T*)data+_size); }//i.e. points to last element
	
    iterator<false> rbegin()const{ return iterator<false>((T*)data+_size-1); }//i.e. points to last element
	iterator<false> rend()const{ return iterator<false>((T*)data-1); }//i.e. points to first element
#if __cplusplus >= 201103L
private:
	struct reverse_adapter{//i.e. defined to use reverse_iterator on 'range-based' loop
		reverse_adapter(const Vector<T>& vec):vec_ref(vec){}
		iterator<false> begin(){ return vec_ref.rbegin(); }
		iterator<false> end(){ return vec_ref.rend(); }
	private:
		const Vector<T>& vec_ref;
	};
public:
	//i.e. reversely traverse vector without changing it (inside range-based loop)
	reverse_adapter reverse_iterator(){ return reverse_adapter(*this); }
#endif
	
	~Vector(){//i.e. dtor
		clear();
		delete[] data;
	}
};


#if __cplusplus >= 201103L
	/*i.e. Type_Parse_Traits template struct for defining its' specialized templates*/
	template<typename T>
	struct type_parse_traits;
	#define REGISTER_PARSE_TYPE(type) \
	template<>struct type_parse_traits<type>{ static string name; }; \
    string type_parse_traits<type>::name = #type //i.e. '#' converts 'type' into string & initializes 'name'
    
	/*i.e. defining specialized templates to get their typename at run-time*/
	REGISTER_PARSE_TYPE(string);
	REGISTER_PARSE_TYPE(Vector<char>);
    REGISTER_PARSE_TYPE(Vector<float>);
    REGISTER_PARSE_TYPE(Vector<int>);
	REGISTER_PARSE_TYPE(Vector<Vector<int>>);
	REGISTER_PARSE_TYPE(Vector<Vector<Vector<int>>>);
	//Note: Here, macro replaces the specialized template struct alongwith its static member initialization
	
	/*i.e. Counter Class for keeping track of instance's resources*/					
	template <typename T>
	class instance_counter{//i.e. generates summary of each type after complete execution of main() func
		struct counter{
			bool flag;//i.e. pass 'true' in ctor to view summary
    	    __int64 num_construct,num_copy,num_move,num_destruct;
			
			counter(bool flag=0): //i.e. ctor
				flag(flag),num_construct(0),num_copy(0),num_move(0),num_destruct(0){}
			
			~counter(){//i.e. dtor
				if(flag){
					cout<<"\nSummary ("<<type_parse_traits<T>::name<<"):-\n"
					 	<<num_construct<<" direct constructions\n"
    	    		    <<num_copy<<" copies\n"
    	        		<<num_move<<" moves\n"
        	    		<<num_construct+num_copy+num_move<<" total constructions\n"
            			<<num_destruct<<" destructions ";
            		if ((num_construct+num_copy+num_move)==num_destruct)
            	    	cout<<"(no leaks)\n";
            		else
            	    	cout<<"(WARNING: potential leak)\n";
				}
        	}
    	};
		static counter icounter;//i.e. static counter obj
	
	public:
    	instance_counter()noexcept{ ++icounter.num_construct; }
    	instance_counter(const instance_counter&)noexcept{ ++icounter.num_copy; }
    	instance_counter(instance_counter&&)noexcept{ ++icounter.num_move; }
    	//i.e. simulates both copy-assign and move-assign funcs
    	instance_counter& operator=(instance_counter)noexcept{ return *this; }
    	~instance_counter(){ ++icounter.num_destruct; }
	};
	//Static Initialization Format: datatype class::static_variable;
	template<typename T>
	typename instance_counter<T>::counter instance_counter<T>::icounter(true);

	/*i.e. combining instantiated class with counter class to get same results*/
	template<typename T>
	struct counted:T,instance_counter<T>{
    	using T::T;//i.e. inheriting ctor (C++11 Construct)
		//Note: it provides the same interface for the class that is instantiated
	};
#endif


test_case_1(){
	typedef Vector<int> V1;
	V1 vec,	   	   		//i.e. just declaration, no allocation
	   vec1(10),	   	//i.e. allocate size with 1st arg & initialize the whole vector with 0/""/''
	   vec2(5,123);   	//i.e. allocate size with 1st arg & initialize the whole vector with 2nd arg
//	V1 vec4{99,88,77};	//i.e. allocate with brace enclosed initializer_list ctor(C++11)

	cout<<"\nvec:"<<endl
		<<"size: "<<vec.size()<<endl
		<<"capacity: "<<vec.capacity()<<endl;
	vec.push_back(2);
	vec.push_back(4);
	cout<<"(after 2 push_back)"<<endl
		<<"size: "<<vec.size()<<endl
		<<"capacity: "<<vec.capacity()<<endl
		<<"elements: ";
	for(int i=0;i<vec.size();++i)
		cout<<vec[i]<<" ";
	
	cout<<"\n\nvec1:\nelements: ";
	for(int i=0;i<vec1.size();++i)
		cout<<vec1[i]<<" ";
	cout<<"\nsize: "<<vec1.size()<<endl
		<<"capacity: "<<vec1.capacity()<<endl;
	vec1.push_back(4);
	cout<<"(after push_back)"<<endl
		<<"size: "<<vec1.size()<<endl
		<<"capacity: "<<vec1.capacity()<<endl;
	
	cout<<"\nvec2:\nelements: ";
	for(int i=0;i<vec2.size();++i)
		cout<<vec2[i]<<" ";
	cout<<"\nsize: "<<vec2.size()<<endl
		<<"capacity: "<<vec2.capacity()<<endl;
	vec2.pop_back();
	cout<<"(after pop_back)"<<endl
		<<"size: "<<vec2.size()<<endl
		<<"capacity: "<<vec2.capacity()<<endl;
	vec2.reserve(10);
	cout<<"(after reserve)"<<endl
		<<"size: "<<vec2.size()<<endl
		<<"capacity: "<<vec2.capacity()<<endl;
	vec2.shrink_to_fit();
	cout<<"(after shrink_to_fit)"<<endl
		<<"size: "<<vec2.size()<<endl
		<<"capacity: "<<vec2.capacity()<<endl
		<<"elements: ";
	for(int i=0;i<vec2.size();++i)
		cout<<vec2[i]<<" ";
	cout<<endl;
}

test_case_2(){
	{//i.e. destroying vector v
		Vector<int> v;
		cout<<"\nInt data_type (vector v):\nvector v is: ";
    	for(int i=5;i<13;++i)
		    v.push_back(i);
    	cout<<"After push_back: ";
    	for(int i=0;i<v.size();++i)
			cout<<v[i]<<", ";
    	cout << "(size: "<<v.size()<<", capacity: "<<v.capacity()<<")\nv[2]: "<<v[2]<<endl;
 		v.pop_back();
   		cout<<"After pop back: ";
		for(int i=0;i<v.size();++i)
			cout<<v[i]<<", ";
    	cout << "(size: "<<v.size()<<", capacity: "<<v.capacity()<<')'<<endl;
    	v.clear();
    	cout<<"After clear: "
    		<< "(size: "<<v.size()<<", capacity: "<<v.capacity()<<')'<<endl
    		<<"After 3 push_back: ";
		for(int i=1;i<=3;++i)
		    v.push_back(i),cout<<v[i-1]<<", ";
    	cout << "(size: "<<v.size()<<", capacity: "<<v.capacity()<<')'<<endl;
  	}
    Vector<char> c;
    for(char i='a';i<'i';++i)
	    c.push_back(i);
	cout<<"\nChar data_type (vector c):\nAfter push_back: ";
    for(int i=0;i<c.size();++i)
			cout<<c[i]<<", ";
    cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<")\nc[2]: "<<c[2]<<endl;
    c.pop_back();
    cout<<"After pop back: ";
    for(int i=0;i<c.size();++i)
			cout<<c[i]<<", ";
	cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<')'<<endl
		<<"After reserve: ";
	c.reserve(15);
	for(int i=0;i<c.size();++i)
		cout<<c[i]<<", ";
	cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<')'<<endl
		<<"After resize: ";
		c.resize(10,'z');
		for(int i=0;i<c.size();++i)
			cout<<c[i]<<", ";
		cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<')'<<endl;
	
	cout<<"\nString data_type\nElement in vector a: ";
#if __cplusplus >= 201103L
	Vector<string> a={"asad","ali","usman"}; //C++11
#else
	Vector<string> a;
	a.push_back("asad"),a.push_back("ali"),a.push_back("usman");
#endif
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<", ";
	cout<<"(size: "<<a.size()<<", capacity: "<<a.capacity()<<')'<<endl
		<<"After resize: ";
	a.resize(8);
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<", ";
	cout<<"(size: "<<a.size()<<", capacity: "<<a.capacity()<<')'<<endl;
}

void test_case_3(){
	cout<<"\nDeclaring Nested Vector without Initializer-List & Index-based Accessing:-";
	Vector<Vector<Vector<int>> > vec_3d;//i.e. 3D(l x m x n); l=3,m=10,n=10
	//Note: leave a space in defining nested vector (i.e. glitch in C++0x version)
	{//i.e. destroys 2d vec
		Vector<Vector<int>> vec_2d(10);
		{//i.e. destroys 1d vec
			Vector<int> vec_1d(10);
			for (short i=0;i<vec_1d.size();++i)
 				vec_1d[i]=i+10;//i.e. assigning values (1-10)
			for(short i=0;i<vec_2d.size();++i)
				vec_2d[i]=vec_1d;//i.e. assigning 1d vec address to 2d vec
			//Note: assigning same Vector obj (i.e. copy assignment)
		}
		for(short i=0;i<3;++i)
			vec_3d.push_back(vec_2d);//i.e. assigning 2d vec address to 3d vec
	}
	Vector<Vector<Vector<int>> > vec_x,vec_y=vec_x=vec_3d;
	/*Note: copy assignment (3d to x), copy ctor (x to y)
	  For Testing: Replace 'vec_x' with others in below nested loop */
	for(short i=0;i<vec_y.size();++i){
		cout<<"\n2D Vector "<<i+1<<":"<<endl;
		for(short j=0;j<vec_y[0].size();++j){
			for(short k=0;k<vec_y[0][0].size();++k)
				cout<<vec_y[i][j][k]+(i*10)<<" ";
			cout<<endl;
		}
	}
	cout<<"\nTotal Size Occupied: "<<vec_y.size()*vec_y[0].size()*vec_y[0][0].size()<<endl;//i.e. any index can be used as all are of same size
}

/*i.e. Abstract/Interface Class (for test-case 4) */
class Items{
	unsigned __int64 ID;
	unsigned short Quantity;//i.e. 0-65535
	float Price;
	string Name,Brand,Category;
public:
	Items():ID(ID_Generator()),Price(0),Quantity(1){}//i.e. default ctor
	Items(string Category):ID(ID_Generator()),Price(0),Quantity(1),Category(Category){}
	Items(float Price,string Name,string Brand,string Category):
		ID(ID_Generator()),Price(Price),Name(Name),Brand(Brand),Quantity(1),Category(Category){}
	
	static unsigned __int64 ID_Generator(const bool Reset_Flag=false){//i.e. can produce upto 20 digit no.
		static unsigned __int64 _ID=40400;
		if(Reset_Flag){
			_ID=40400;
			return _ID;
		}
		return ++_ID;
	}
	virtual void Input_Data(istream&)=0;//i.e. pure virtual func, acts like hooker for below friend '>>' operator func
	friend istream& operator>>(istream& in,Items &obj){
		cout<<"	Enter Product Name: ";
		in.sync();//i.e. neglects remaining buffer
		in>>obj.Name;
		cout<<"	Enter Brand Name: ";
		in.sync();
		in>>obj.Brand;
		in.sync();
		cout<<"	Enter Price: ";
		in>>obj.Price;
		cout<<"	Enter Quantity: ";
		in>>obj.Quantity;
		obj.Input_Data(in);
		return in;
	}
	virtual void Display_Data(ostream&)const=0;
	friend ostream& operator<<(ostream& out,const Items &obj){
		out<<") Category: "<<obj.Category<<", Name: "<<obj.Name<<", Brand: "<<obj.Brand
		   <<", ID: "<<obj.ID<<", Price: "<<obj.Price<<", Quantity: "<<obj.Quantity;
		obj.Display_Data(out);
		return out;
	}
	virtual ~Items(){}//i.e. virtual dtor -> to destruct in correct order
};

test_case_4(){
	/* Local Derived Classes for Abstract objs */
	class Beverages:public Items{
		string Unit; unsigned short Unit_Size;
	public:
		Beverages(string Unit="",unsigned short Unit_Size=0):
			Unit(Unit),Unit_Size(Unit_Size),Items("Beverages"){}
		Beverages(float Price,string Name,string Brand,string Unit="",unsigned short Unit_Size=0):
			Unit(Unit),Unit_Size(Unit_Size),Items(Price,Name,Brand,"Beverages"){}

		void Input_Data(istream& in)override{
			cout<<"	Enter Unit: "; in>>Unit; cout<<"	Enter Unit Size (",Unit,"): "; in>>Unit_Size;
		}
		void Display_Data(ostream& out)const override{ out<<", Unit Size: "<<Unit_Size<<" ("<<Unit<<")"; }
		~Beverages(){ cout<<"Beverages dtor\n"; }//i.e. extra, explicitly defined to display the indication of destruction
	};
	
	class Bakery_Items:public Items{
		float Weight;
	public:
		Bakery_Items(float Weight=0):
			Weight(Weight),Items("Bakery_Items"){}
		Bakery_Items(float Price,string Name,string Brand,float Weight=0):
			Weight(Weight),Items(Price,Name,Brand,"Baking_Items"){}
	
		void Input_Data(istream& in)override{ cout<<"	Enter Weight: "; in>>Weight; }
		void Display_Data(ostream& out)const override{ out<<", Weight: "<<Weight; } 
		~Bakery_Items(){ cout<<"Bakery_Items dtor\n"; } 
	};
	
	class Baking_Items:public Items{
	public:
		Baking_Items():Items("Baking_Items"){}
		Baking_Items(float Price,string Name,string Brand):Items(Price,Name,Brand,"Baking_Items"){}
	
		void Input_Data(istream& in)override{}
		void Display_Data(ostream& out)const override{} 
		~Baking_Items(){ cout<<"Baking_Items dtor\n"; }
	};
	
	Vector<Items*> items_list;//i.e. initializing double-ptr for pointing dynamic abstract objs
	
	items_list.push_back(new Beverages(111,"pepsi","pepsico","ml",500));
	items_list.push_back(new Bakery_Items(222,"sandwitch","home-made"));
	items_list.push_back(new Baking_Items);
	
	cout<<"\nItems List (Abstract Objs):"<<endl;
	for(int i=0;i<items_list.size();++i)
		cout<<i+1<<*items_list[i]<<endl;//i.e. direct use of cout with abstract ptr
	
	cout<<"\nClearing Items List:"<<endl;
	for(int i=0;i<items_list.size();++i)
		delete items_list[i];
}

#if __cplusplus >= 201103L
test_case_5(){
	cout<<"\nJagged Vector Demonstration:-";
	//i.e. passing 'Vector<int>' in 'counted' to get track/summary of its resources
	typedef counted<Vector<int>> V1; typedef counted<Vector<Vector<int>>> V2;
	V1 obj={123,321};//i.e. lvalue obj
	//i.e. using as Jagged Array
	Vector<V2> vec_3d={	
						{	
							V1{1,2,3,4},
					   		V1{11,22,33},
							V1{111,222,333,444},
						 	std::move(obj)							
					    },
					   	{	
						   	V1{5,6,7,8},
						  	V1{55,66,77,88},
						  	V1{555,666,777,888}
					  	}
					};//i.e. size (3Dx2Dx1D): 2x3x4
	
	for(const auto &__it:vec_3d){
		cout<<"\n2D Vector "<<(&__it-&vec_3d[0])+1<<":"<<endl;
		for(const auto &_it:__it){
			for(const auto &it:_it)
				cout<<it<<" ";
			cout<<endl;
		}
	}
	
	cout<<"\nMoved obj: ";
	if(!obj.size())
		cout<<"yes";
	else
		cout<<"no";
	cout<<"\nRe-assigning rvalue obj to lvalue holder (invokes move assignment func):"<<endl;
	obj=V1(5,404); 
	for(const auto &it:obj)
		cout<<it<<" ";

	cout<<"\n-------------\n";
	cout<<"clearing row 2 of vector 1 & row 1 of vector 2:";
	vec_3d[0][1].clear();
	vec_3d[1][0].clear();
	for(short i=0;i<vec_3d.size();++i){
		cout<<"\n2D Vector "<<i+1<<":"<<endl;
		for(short j=0;j<vec_3d[i].size();++j){
			for(short k=0;k<vec_3d[i][j].size();++k)
				cout<<vec_3d[i][j][k]<<" ";
			cout<<endl;
		}
	}
	cout<<"\n------------\n";
	cout<<"clearing vector 1:";
	vec_3d[0].clear();
	for(const auto &__it:vec_3d){
		cout<<"\n2D Vector "<<(&__it-&vec_3d[0])+1<<":"<<endl;
		for(const auto &_it:__it){
			for(const auto &it:_it)
				cout<<it<<" ";
			cout<<endl;
		}
	}
}

class Fun{//i.e. for test-case 6
	char c;
	int i;
	string s;
public:
	Fun(char c='\0',int i=0,string s=""):c(c),i(i),s(s){}
	
	friend ostream& operator<<(ostream& out,const Fun& obj){
		out<<obj.c<<", "<<obj.i<<", "<<obj.s<<endl;
		return out;
	}
};
REGISTER_PARSE_TYPE(Fun);//i.e. defining specialized template for 'Fun' type to get its name for 'Summary'

test_case_6(){
	{//i.e. destroys vec obj
		Vector<counted<Fun>> vec;
		cout<<"\nEmplaced-back objs:"<<endl;
		counted<Fun> obj('1',22,"333");
		vec.emplace_back(obj);//i.e. here works same as push_back (passing const reference)
		vec.emplace_back(counted<Fun>('2',33,"444"));//i.e. pasing temporary (rvalue) obj of 'Fun' type
		vec.emplace_back('3',44,"555");//i.e. direct initialization (same as initializing any obj)
		{
			counted<Fun> temp_obj('4',55,"666");
			vec.emplace_back(move(temp_obj));//i.e. moving/stealing temp_obj (passing rvalue reference)
		}
		for(const auto& it:vec)
		 	cout<<it;
	}
	
	counted<Vector<int>> vec={1,2,3,4,5};
	cout<<"\nReversely traversed:"<<endl;
	for (const auto& it:vec.reverse_iterator())
		cout<<it<<" ";
	cout<<"\nNormally traversed:"<<endl;
	for ( auto& it:vec)
		cout<<it<<" ";
	cout<<endl;
}
#endif

/*  Test Cases:
	1) covers the basic operations (use of modifiers)
	2) covers the basic operations (use of modifiers)
	3) demonstration of copy assingment & construction in nested Vector while safely using/storing same objs inside Vector
	4) using Vector as container for local abstract objs of Items class by utilizing the concept of polymorphism
	5) direct initialization of 3d jagged vector & understanding move-semantics, while utilizing instance_counter to keep 
	   track of vector's constructions & destructions
	6) focus on best use of emplace_back & reverse_iterator while using Vector as container for another class objs
*/

int main(){
	test_case_1();
	test_case_2();
	test_case_3();
	test_case_4();
	/*Note: Enable C++11 in order to see the working of following test-cases */
//	test_case_5();
//	test_case_6();
	return 0;
}
