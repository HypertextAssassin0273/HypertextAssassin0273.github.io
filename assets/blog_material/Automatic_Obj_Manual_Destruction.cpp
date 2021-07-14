#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Friend{
	string name;
	int age,ID;
	float height;
	static int obj_counter;
public:
	Friend():ID(++obj_counter),age(0),height(0){ }
	Friend(string name,int age,float height):
		ID(++obj_counter),name(name),age(age),height(height){}
	
	void set_name(string name){ this->name=name; }
	void set_age(int age){ this->age=age; }
	void set_height(float height){ this->height=height; }
	void display_info()const{ cout<<"Obj ID: "<<ID<<", Name: "<<name<<", Age: "<<age<<", Height:"<<height<<endl; }
	static void Total_objs(){ cout<<"Total Objects Present: "<<obj_counter<<endl; }
	~Friend(){ --obj_counter; cout<<"? "; }
};
int Friend::obj_counter=0;

int main(){
	{//i.e. outer local scope, destroys the list alongwith objs
		vector <Friend>vector_list;
		{//i.e. inner local scope, destroys all objs
			Friend obj1,obj2("Ahmed",19,6.0),obj3("Hamza",17,6.0),obj4;
			obj1.set_name("Shahzaib");
			obj1.set_age(21);
			obj1.set_height(6.5);
			Friend::Total_objs();
			
			cout<<"\nAfter push_back:-"<<endl;
			vector_list.push_back(obj1);
			vector_list.push_back(obj3);
			vector_list.insert(vector_list.begin()+1,obj2);
			vector_list.push_back(obj4);
			cout<<"(indicates the realloction of objs)"<<endl;
			Friend::Total_objs();
			//Note: vector.push_back() calls dtors of objs if vector-size is reallocted
			cout<<"\nAfter getting out of inner local scope:-"<<endl;
		}
		cout<<"(indicates the actual destruction of friend objs)"<<endl;
		Friend::Total_objs();
		cout<<"\nvector_list Size: "<<vector_list.size()<<endl
			<<"Display vector_list:-"<<endl;
		for(vector <Friend>::iterator it=vector_list.begin();it!=vector_list.end();++it)
			it->display_info();
		
		cout<<"\nAfter Reverse:-"<<endl;
		reverse(vector_list.begin(),vector_list.end());
		cout<<"(indicates the realloction of objs in vector_list; i.e. 2 objs destroyed & 2 were updated)"<<endl;
		Friend::Total_objs();
		cout<<"\nDisplay vector_list:-"<<endl;
		for(vector <Friend>::iterator it=vector_list.begin();it!=vector_list.end();++it)
			it->display_info();
		
		cout<<"\nAfter Swap:-"<<endl;
		swap(vector_list[1],vector_list[2]);
		cout<<"(indicates the realloction of obj in vector_list)"<<endl;
		Friend::Total_objs();
		cout<<"\nDisplay vector_list:-"<<endl;
		for(vector <Friend>::iterator it=vector_list.begin();it!=vector_list.end();++it)
			it->display_info();
		cout<<"\nAfter getting out of outer local scope:-"<<endl;
	}
	cout<<"(indicates the dectruction of objs alongwith the vector_list)"<<endl;
	Friend::Total_objs();
	return 0;
}
