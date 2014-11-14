#ifndef DYNAMIC_TREENODE_H
#define DYNAMIC_TREENODE_H


#include <map>
#include <vector>
#include <iostream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>



template<class O>
class Node{
	public:
		Node(){m_ref=0;}

		virtual ~Node() {};
		// pure virtual func for tree
		virtual std::string path() = 0;
		virtual Node<O>* branch(const std::string& name) = 0;
		virtual Node<O>* root() = 0;
		virtual Node<O>* parent() = 0;

		// map
		Node<O>* find(const std::string& name){
			if(!name.empty() && _map.find(name) != _map.end()) return _map[name];
			else return NULL;
		}
		bool regist(const std::string& name, Node<O>* node){
			if(!name.empty() && _map.find(name) == _map.end()){
				_map.insert(std::pair<std::string, Node<O>*>(name, node));
				return true;
			}
			return false;
		}

		// obj
		void registObj(O* o){ m_ref = o; }
		O* getObj(){ 
			if(m_ref) return m_ref; 
			else throw std::runtime_error("DynamicObj is not registed.\n");
		}
		//template<class C>
		//C* getObj1(std::string path){return dynamic_cast<C*>(find(path)->getObj());}


	private:
		O*               m_ref;
	        std::map<std::string, Node<O>*> _map;

};



template<class O>
class DynamicTree: public Node<O>{
	public:
		// sington in one datamgr
		DynamicTree(){ m_parent = 0; m_path   = "/"; m_root   = this; }

		// Branch
		Node<O>* find(const std::string& name){
			vector<std::string> dividedName;
			vector<std::string>::iterator itName;
			boost::split(dividedName, name, boost::is_any_of("/"), boost::token_compress_on);
			Node<O>* current = (0==name.find("/"))?m_root:this;
			for(itName=dividedName.begin(); itName!=dividedName.end(); itName++){
				if(0==(*itName).size()) continue;
				current = current->find(*itName);
				if(not current )return NULL;
			}
			return current;
		}

		//template<class C>
		//C* getObj(std::string path){return dynamic_cast<C*>(find(path)->getObj());}

		virtual DynamicTree<O>* branch(const std::string& name){
			if(name.empty()) throw std::runtime_error("make branch error: no name for branch");
			DynamicTree<O>* br = new DynamicTree<O>(name, this);
			if(not this->regist(name, br)){
				delete br;
				return NULL;
			}
			return br;
		}

		// tree
		std::string     path(){return m_path;}
		Node<O>*        root(){return m_root;}
		Node<O>*        parent(){return m_parent;}

	private:
		DynamicTree(std::string name, DynamicTree<O>* parent){
			m_parent = parent;
			m_root   = parent->root();
			m_path   = m_parent->path()+(m_parent->path()=="/"?name:"/"+name);
		}

	private:
		std::string      m_path;
		Node<O>*         m_root;
		Node<O>*         m_parent;
};


#endif
