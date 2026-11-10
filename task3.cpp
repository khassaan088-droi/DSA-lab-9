#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TravelRoute {
public:
float travel_cost;
TravelRoute(float cost=0.0f) {
travel_cost=cost;
}
};

class StarSystem {
public:
int system_id;
string name;
int num_planets;
float x,y,z;
bool is_habitable;
vector<StarSystem*> children;
vector<TravelRoute> routes;

StarSystem(int id,string n,int planets,float px,float py,float pz,bool habitable) {
system_id=id;
name=n;
num_planets=planets;
x=px;
y=py;
z=pz;
is_habitable=habitable;
}

void addChild(StarSystem* childSystem,float cost) {
children.push_back(childSystem);
routes.push_back(TravelRoute(cost));
}
};

class Galaxy {
private:
int M;
StarSystem* root;

int getSubtreeSize(StarSystem* x) const {
if(x==NULL) return 0;
int count=1;
for(size_t i=0;i<x->children.size();i++) {
count+=getSubtreeSize(x->children[i]);
}
return count;
}

int getAbsoluteDiff(int a,int b) const {
int diff=a-b;
return (diff<0)?-diff:diff;
}

public:
Galaxy(int max_m,StarSystem* rootNode=NULL) {
M=max_m;
root=rootNode;
}

StarSystem* getRoot() const {
return root;
}

bool is_balanced(StarSystem* x) const {
if(x==NULL) return true;
if(x->children.empty()) return true;
int first_size=getSubtreeSize(x->children[0]);
for(size_t i=1;i<x->children.size();i++) {
int current_size=getSubtreeSize(x->children[i]);
if(getAbsoluteDiff(first_size,current_size)>1) {
return false;
}
}
for(size_t i=0;i<x->children.size();i++) {
if(!is_balanced(x->children[i])) {
return false;
}
}
return true;
}
bool is_balanced() const {
return is_balanced(root);
}

int count_leaves(StarSystem* x) const {
if(x==NULL) return 0;
if(x->children.empty()) {
return 1;
}
int total_leaves=0;
for(size_t i=0;i<x->children.size();i++) {
total_leaves+=count_leaves(x->children[i]);
}
return total_leaves;
}
int count_leaves() const {
return count_leaves(root);
}
};
int main() {
StarSystem* sol=new StarSystem(1,"Sol",8,0.0f,0.0f,0.0f,true);
StarSystem* alpha=new StarSystem(2,"Alpha Centauri",3,4.3f,1.2f,0.5f,false);
StarSystem* sirius=new StarSystem(3,"Sirius",1,8.6f,-2.1f,1.1f,true);
StarSystem* vega=new StarSystem(4,"Vega",5,25.0f,10.5f,-4.2f,true);
sol->addChild(alpha,4.3f);
sol->addChild(sirius,8.6f);
sol->addChild(vega,25.0f);
Galaxy galaxy(3,sol);
cout<<"Total Leaf Systems: "<<galaxy.count_leaves()<<endl;
cout<<"Is Galaxy Balanced? "<<(galaxy.is_balanced()?"Yes":"No")<<endl;
return 0;
}