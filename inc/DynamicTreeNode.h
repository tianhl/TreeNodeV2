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
		virtual ~Node() {};
		// pure virtual func
		virtual std::string path() = 0;
		virtual Node<O>* branch(const std::string& name) = 0;
		virtual Node<O>* root() = 0;
		virtual Node<O>* parent() = 0;
		virtual void registObj(O* o) = 0;
		virtual O* getObj() = 0;
		//virtual Node<O>* find(const std::string& name){
		Node<O>* find(const std::string& name){
			if(!name.empty() && _map.find(name) != _map.end()) return _map[name];
			else return 0;
		}
		bool regist(const std::string& name, Node<O>* node){
			if(!name.empty() && _map.find(name) == _map.end()){
			       	_map.insert(std::pair<std::string, Node<O>*>(name, node));
				return true;
			}
			return false;
		}

	private:
		typedef std::map<std::string, Node<O>*> NodeMap;
		NodeMap _map;

};



template<class O>
class DynamicTree: public Node<O>{
	public:
		DynamicTree(){ m_ref = 0; m_parent = 0; m_path   = "/"; m_root   = this; }

                // Branch

		Node<O>* find(const std::string& name){
			vector<std::string> dividedName;
			vector<std::string>::iterator itName;
			boost::split(dividedName, name, boost::is_any_of("/"), boost::token_compress_on);
			Node<O>* current = (0==name.find("/"))?m_root:this;
			for(itName=dividedName.begin(); itName!=dividedName.end(); itName++){
				if(0==(*itName).size()) continue;
				current = current->find(*itName);
				//current = current->Node<O>::find(*itName);
				//if(dynamic_cast<DynamicTree<O>*>(current)) current = current->Node<O>::find(*itName);
			        //else current = current->find(*itName);	
				// how to throw out error? path
			}
			return current;
		}

		virtual Node<O>* branch(const std::string& name){
			if(name.empty()) throw std::runtime_error("make branch error: no name for branch");
			DynamicTree<O>* br = new DynamicTree<O>(name, this);
			this->regist(name, br);
			// if error delete br!
			return br;
		}

		// OBJ

		virtual void registObj(O* o){
			m_ref = o;
		}

		virtual O* getObj(){ 
			if(m_ref) return m_ref; 
			else throw std::runtime_error("DynamicObj is not registed.\n");
		}


		// tree
		std::string     path(){return m_path;}
		Node<O>*        root(){return m_root;}
		Node<O>*        parent(){return m_parent;}
	private:
		DynamicTree(std::string name, DynamicTree<O>* parent){
			m_ref    = 0;
			m_parent = parent;
			m_root   = parent->root();
			m_path   = m_parent->path()+(m_parent->path()=="/"?name:"/"+name);
		}

	private:
		O*               m_ref;
		std::string      m_path;
		Node<O>*         m_root;
		Node<O>*         m_parent;
};


#endif
