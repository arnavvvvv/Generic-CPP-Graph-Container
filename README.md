```markdown
Graph
-----------------------------------------------------------------------------------
The project implements a generic graph data structure in C++. The template class
Graph supports two type parameters, vertex that determines the type of the node
and edge that determines the type of the weight connecting link between two nodes
as follows:

template<
        typename vertex = int,       //Graph::vertex_type
        typename edge = double       //Graph::edge_type
>class Graph;

type vertex - defaults to int
	    - should support 
		- default constructor
		- copy constructor
		- copy assignment operator
		- operator==
		- operator<
		- hashing	

type edge - default to double
	  - should support
		- default constrctor
		- copy constructor
		- copy assignment operator
		- operator<

Instantiation
	Graph<string, int> G1;
-----------------------------------------------------------------------------------
Iterators supported
1. iterator (Bidirectional iterator) 
	- Delegated to map iterator 
	- Supports functions from algorithms by providing necessary predicates
	- Instantiation: Graph<key, vertex>::iterator itr;

2. breath_first_search_iterator (Forward iterator)
	- Supports functions from algorithms by providing necessary predicates
	- Instantiation: Graph<key, vertex>::breadth_first_search_iterator itr;

3. depth_first_search_iterator (Forward iterator)
	- Instantiation: Graph<key, vertex>::depth_first_search_iterator itr;       
-----------------------------------------------------------------------------------       
Operations (defined as member function of class Graph)
1. add_edge
Syntax:		graph_obj.add_edge(vertex1, vertex2, edge_weight);
Return:		void
Example:	G1.add_edge("A", "B", 5);

2. delete_edge
Syntax:		graph_obj.delete_edge(vertex1, vertex2);
Return:		void
Example:	G1.delete_edge("B", "C");

3. modify_edge
Syntax:		graph_obj.modify_edge(vertex1, vertex2, edge_weight);
Return:		void
Example:	G1.modify_edge("A", "B", 6);

4. find
Syntax:		graph_obj.find(vertex);
Return:		Graph<vertex, edge>::iterator
Example:	Graph<string, int>::iterator it = G1.find("A");

5. djikstra
Syntax:		graph_obj.dijkstra(vertex);
Return:		map<vertex, pair<vertex, edge>>
Example:	map<string,pair<string,int>> m = G1.dijkstra("A");

6. size
Syntax:		graph_obj.size();
Return:		size_type
Example:	int graph_size = G1.size();

7. empty
Syntax:		graph_obj.empty();
Return:		bool
Example:	bool is_empty = G1.empty();
----------------------------------------------------------------------------------- 
```
Graph
-----------------------------------------------------------------------------------
The project implements a generic graph data structure in C++. The template class
Graph supports two type parameters, vertex that determines the type of the node
and edge that determines the type of the weight connecting link between two nodes
as follows:

template<
        typename vertex = int,       //Graph::vertex_type
        typename edge = double       //Graph::edge_type
>class Graph;

type vertex - defaults to int
	    - should support 
		- default constructor
		- copy constructor
		- copy assignment operator
		- operator==
		- operator<
		- hashing	

type edge - default to double
	  - should support
		- default constrctor
		- copy constructor
		- copy assignment operator
		- operator<

Instantiation
	Graph<string, int> G1;
-----------------------------------------------------------------------------------
Iterators supported
1. iterator (Bidirectional iterator) 
	- Delegated to map iterator 
	- Supports functions from algorithms by providing necessary predicates
	- Instantiation: Graph<key, vertex>::iterator itr;

2. breath_first_search_iterator (Forward iterator)
	- Supports functions from algorithms by providing necessary predicates
	- Instantiation: Graph<key, vertex>::breadth_first_search_iterator itr;

3. depth_first_search_iterator (Forward iterator)
	- Instantiation: Graph<key, vertex>::depth_first_search_iterator itr;       
-----------------------------------------------------------------------------------       
Operations (defined as member function of class Graph)
1. add_edge
Syntax:		graph_obj.add_edge(vertex1, vertex2, edge_weight);
Return:		void
Example:	G1.add_edge("A", "B", 5);

2. delete_edge
Syntax:		graph_obj.delete_edge(vertex1, vertex2);
Return:		void
Example:	G1.delete_edge("B", "C");

3. modify_edge
Syntax:		graph_obj.modify_edge(vertex1, vertex2, edge_weight);
Return:		void
Example:	G1.modify_edge("A", "B", 6);

4. find
Syntax: 	graph_obj.find(vertex);
Return:		Graph<vertex, edge>::iterator
Example:	Graph<string, int>::iterator it = G1.find("A");

5. djikstra
Syntax: 	graph_obj.dijkstra(vertex);
Return:		map<vertex, pair<vertex, edge>>
Example:	map<string,pair<string,int>> m = G1.dijkstra("A");

6. size
Syntax:		graph_obj.size();
Return:		size_type
Example:	int graph_size = G1.size();

7. empty
Syntax:		graph_obj.empty();
Return:		bool
Example:	bool is_empty = G1.empty();
----------------------------------------------------------------------------------- 