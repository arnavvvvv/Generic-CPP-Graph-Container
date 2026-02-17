#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>

#define INF INT32_MAX

template<typename vertex, typename edge>
struct uniquePair
{
    bool operator()(const std::pair<vertex, edge>& lhs, const std::pair<vertex, edge>& rhs) const
    {
        return lhs.first < rhs.first;
    }
};

template<typename vertex, typename edge>
struct weightedOrder 
{
    bool operator()(const std::pair<vertex, edge>& lhs, const std::pair<vertex, edge>& rhs) const
    {
        return (lhs.second < rhs.second)  || (!(lhs.second < rhs.second) && (lhs.first < rhs.first));
    }
};

template < typename vertex = int,         //Graph::vertex_type
           typename edge = double         //Graph::edge_type
         > class Graph
{
    private:
        std::unordered_map<vertex, std::set<std::pair<vertex, edge>, uniquePair<vertex, edge>>> network;

        typename std::set<std::pair<vertex, edge>, uniquePair<vertex, edge>>::iterator isConnected(const vertex&, const vertex&);

        typedef typename std::set<std::pair<vertex, edge>, uniquePair<vertex, edge>>::iterator set_iterator;

    public:
        typedef vertex vertex_type;
        typedef edge edge_type;
        typedef std::pair<const vertex, std::set<std::pair<vertex, edge>, uniquePair<vertex, edge>>> list_type;
        typedef typename std::unordered_map<vertex, std::set<std::pair<vertex, edge>, uniquePair<vertex, edge>>>::iterator iterator;
        typedef size_t size_type;

        void add_edge(const vertex&, const vertex&, const edge = edge_type());
        void delete_edge(const vertex, const vertex);
        void modify_edge(const vertex, const vertex, const edge = edge_type());
        typename Graph<vertex, edge>::iterator find(const vertex);
        std::map<vertex, std::pair<vertex,edge>> dijkstra(const vertex&);
        Graph<vertex, edge>::size_type size() const;
        bool empty() const;

        iterator begin();
        iterator end();
        void disp();

        class breadth_first_search_iterator 
        {
            private: 
                std::unordered_map<vertex, bool> visited;
                std::queue<Graph<vertex, edge>::iterator> q;
                typename Graph<vertex,edge>::iterator it;
                Graph<vertex,edge>& obj;

            public:
                breadth_first_search_iterator(Graph<vertex,edge>&, Graph<vertex,edge>::iterator);

                breadth_first_search_iterator& operator++();
                breadth_first_search_iterator operator++(int);
                Graph<vertex, edge>::list_type& operator*();
                typename Graph<vertex, edge>::iterator operator->();
                bool operator==(const breadth_first_search_iterator&) const;
                bool operator!=(const breadth_first_search_iterator&) const;
                bool bfsend();                    
        };

        class depth_first_search_iterator 
        {
            private: 
                std::unordered_map<vertex, bool> visited;
                std::stack<Graph<vertex, edge>::iterator> st;
                typename Graph<vertex,edge>::iterator it;
                Graph<vertex,edge>& obj;
                     
            public:
                depth_first_search_iterator(Graph<vertex,edge>&, Graph<vertex,edge>::iterator);
                
                depth_first_search_iterator& operator++();
                depth_first_search_iterator operator++(int);
                Graph<vertex, edge>::list_type& operator*();
                typename Graph<vertex, edge>::iterator operator->();
                bool operator==(const depth_first_search_iterator& rhs) const;
                bool operator!=(const depth_first_search_iterator& rhs) const;
                bool dfsend();
        };
};

template<typename vertex, typename edge>
typename Graph<vertex, edge>::set_iterator Graph<vertex, edge>::isConnected(const vertex& node1, const vertex& node2)
{
    typename Graph<vertex, edge>::set_iterator b = network[node1].begin();
    typename Graph<vertex, edge>::set_iterator e = network[node1].end();
    while(b != e)
    {
        if(b->first == node2)
            break;
        ++b;
    }
    return b;
}

template<typename vertex, typename edge>
void Graph<vertex, edge>::add_edge(const vertex& node1, const vertex& node2, const edge weight)
{
    network[node1].insert(std::make_pair(node2, weight));
    network[node2].insert(std::make_pair(node1, weight));
}

template<typename vertex, typename edge>
void Graph<vertex, edge>::delete_edge(vertex node1, vertex node2)
{
    typename Graph<vertex, edge>::set_iterator it1 = isConnected(node1, node2);
    if(it1 != network[node1].end())
        network[node1].erase(it1);

    it1 = isConnected(node2, node1);
    if(it1 != network[node2].end())
        network[node2].erase(it1);
}

template<typename vertex, typename edge>
void Graph<vertex, edge>::modify_edge(const vertex node1, const vertex node2, const edge new_weight)
{
    delete_edge(node1, node2);
    add_edge(node1, node2, new_weight);
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::iterator Graph<vertex, edge>::find(const vertex node)
{
    Graph<vertex, edge>::iterator tmp = network.begin();
    while(tmp != network.end() && tmp->first != node)
        ++tmp;
    return tmp;
}

template<typename vertex, typename edge>
std::map<vertex, std::pair<vertex, edge>> Graph<vertex, edge>::dijkstra(const vertex& src)
{
	std::set<std::pair<vertex, edge>, weightedOrder<vertex, edge>> setds;
	std::map<vertex, std::pair<vertex, edge>> path;

    for(Graph<vertex, edge>::list_type x : network)
        path[x.first].second = INF;

	setds.insert(std::make_pair(src, edge()));
	path[src] = std::make_pair(src, edge());

    std::pair<vertex, edge> tmp;
    vertex u, v;
    edge weight;

	while (!setds.empty())
	{
        tmp = *(setds.begin());
		setds.erase(setds.begin());
		u = tmp.first;

		for(typename Graph<vertex, edge>::set_iterator i = network[u].begin(); i != network[u].end(); ++i)
		{
			v = (*i).first;
			weight = (*i).second;

			if (path[v].second > path[u].second + weight)
			{
				if (path[v].second != INF)
					setds.erase(setds.find(std::make_pair(v, path[v].second)));

				path[v].second = path[u].second + weight;
				path[v].first = u;
				setds.insert(std::make_pair(v, path[v].second));
			}
		}
	}
    return path;
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::size_type Graph<vertex,edge>::size() const
{
    return network.size();
}

template<typename vertex, typename edge>
bool Graph<vertex,edge>::empty() const
{
    return network.empty();
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::iterator Graph<vertex,edge>::begin()
{
    return network.begin();
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::iterator Graph<vertex,edge>::end()
{
    return network.end();
}

template<typename vertex, typename edge>
void Graph<vertex, edge>::disp()
{
    for(Graph<vertex, edge>::list_type x : network)
    {
        std::cout<<x.first<<"--->"<<'\t';
        for(std::pair<vertex,edge> y : x.second)
        {
            std::cout<<y.first<<'-'<<y.second<<'\t';
        }
        std::cout<<"\n";
    }
}

template<typename vertex, typename edge>
Graph<vertex, edge>::breadth_first_search_iterator::breadth_first_search_iterator(Graph<vertex,edge>& obj_, Graph<vertex,edge>::iterator it_)
:obj(obj_), it(it_)
{
    visited[it->first] = true;
    q.push(it);
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::breadth_first_search_iterator& Graph<vertex, edge>::breadth_first_search_iterator::operator++()
{
    if(!q.empty())
    {
        Graph<vertex, edge>::set_iterator begin = q.front()->second.begin();
        Graph<vertex, edge>::set_iterator end = q.front()->second.end();
        q.pop();
        while(begin != end)
        {
            if(!visited[begin->first])
            {
                visited[begin->first] = true;
                q.push(obj.find(begin->first));
            }
            ++begin;
        }
        it = q.front();
    }
    return *this;
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::breadth_first_search_iterator Graph<vertex, edge>::breadth_first_search_iterator::operator++(int)
{
    breadth_first_search_iterator tmp(*this);
    ++(*this);
    return tmp;
} 

template<typename vertex, typename edge>
typename Graph<vertex, edge>::list_type& Graph<vertex, edge>::breadth_first_search_iterator::operator*()
{
    return *it;
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::iterator Graph<vertex, edge>::breadth_first_search_iterator::operator->()
{
    return it;
}

template<typename vertex, typename edge>
bool Graph<vertex, edge>::breadth_first_search_iterator::operator==(const breadth_first_search_iterator& rhs) const
{
    return it == rhs.it;
}

template<typename vertex, typename edge>
bool Graph<vertex, edge>::breadth_first_search_iterator::operator!=(const breadth_first_search_iterator& rhs) const
{
    return !(*this == rhs);
} 

template<typename vertex, typename edge>
bool Graph<vertex, edge>::breadth_first_search_iterator::bfsend()
{
    return q.empty();
}

template<typename vertex, typename edge>
Graph<vertex, edge>::depth_first_search_iterator::depth_first_search_iterator(Graph<vertex,edge>& obj_, Graph<vertex,edge>::iterator it_)
:obj(obj_), it(it_)
{
    visited[it->first] = true;
    Graph<vertex, edge>::set_iterator begin = it->second.begin();
    Graph<vertex, edge>::set_iterator end = it->second.end();
    while(begin != end)
    {
        st.push(obj.find(begin->first));
        ++begin;
    }
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::depth_first_search_iterator& Graph<vertex, edge>::depth_first_search_iterator::operator++()
{
    while(!st.empty() && visited[st.top()->first])
        st.pop();  
    
    if(!st.empty())
    {
        it = st.top();
        st.pop();
        visited[it->first] = true;
        Graph<vertex, edge>::set_iterator begin = it->second.begin();
        Graph<vertex, edge>::set_iterator end = it->second.end();
        while(begin != end)
        {
            if(!visited[begin->first])
                st.push(obj.find(begin->first));
            ++begin;
        }
        if(st.empty())
            st.push(it);
    }
    return *this;
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::depth_first_search_iterator Graph<vertex, edge>::depth_first_search_iterator::operator++(int)
{
    depth_first_search_iterator temp(*this);
    ++(*this);
    return temp;
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::list_type& Graph<vertex, edge>::depth_first_search_iterator::operator*()
{
    return *it;
}

template<typename vertex, typename edge>
typename Graph<vertex, edge>::iterator Graph<vertex, edge>::depth_first_search_iterator::operator->()
{
    return it;
}

template<typename vertex, typename edge>
bool Graph<vertex, edge>::depth_first_search_iterator::operator==(const depth_first_search_iterator& rhs) const
{
    return it == rhs.it;
}

template<typename vertex, typename edge>
bool Graph<vertex, edge>::depth_first_search_iterator::operator!=(const depth_first_search_iterator& rhs) const
{
    return !(*this == rhs);
}

template<typename vertex, typename edge>
bool Graph<vertex, edge>::depth_first_search_iterator::dfsend()
{
    return st.empty();
}