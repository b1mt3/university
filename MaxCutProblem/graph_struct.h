/*
 * graph_struct.h
 *
 *  Created on: May 15, 2015
 *      Author: hn40cn
 */

class Vertice // class of vertices of the graph
{
	int vertice_label; // the label of a vertice in the graph, {1,..., n)
	int number_of_edges;
public:
	Vertice(int a)
	{
		vertice_label = a;
		number_of_edges = 0;
	}
	int get_label() {return vertice_label; }

	int set_label(int v) {vertice_label = v; return 1; }

	int set_branch_degree() {number_of_edges ++; return 1; }
};

class Edge // class of edges of the graph
{
	Vertice *vertice_pair[2]; // the pair of vertices that form the edge
	int weight; // the weight of the edge
public:
	Edge(int u, int v, int w)
	{
		vertice_pair[0]->set_label(u);
		vertice_pair[0]->set_branch_degree();
		vertice_pair[1]->set_label(u);
		vertice_pair[1]->set_branch_degree();
		weight = w;
	}
};

class Graph
{
	int number_of_vertices, number_of_edges;
	Vertice * vertices_list;
	Edge *edges_list;
public:
	Graph(int n)
	{
		// initialization of the set of vertices
		int i, u, v, w, result;
		number_of_vertices = n;
		number_of_edges = 0;
		vertices_list = new Vertice[number_of_vertices];
		// TODO: correct initialization of the edges list
		edges_list = new Edge[number_of_vertices * number_of_vertices];
		for (i = 0; i < number_of_vertices; i++)
		{
			Vertice v(i + 1);
			vertices_list[i] = v;
		}
		i = 0;
		// initialization of the set of edges
		// TODO: fully random generation of edges - the case of disconnected graph
		u = rand() % n;
		v = rand() % n;
		if (v != u) {
			if ((u < v) && (edge_draw_criterion(u, v) == 13))
			{
				// Generation of an edge
				if (number_of_edges == 0)
				{
					number_of_edges = draw_edge(u, v, number_of_edges, edges_list);
				}
				else
				{
					result = edge_detect(u, v, number_of_edges, edges_list);
					// case of the edge already exists
					if (result == 14) { if ((number_of_edges == n * n) || (do_all_vertices_have_edge(n, vertices_list) == 15)) return; }
				}
				// End generation
				// TODO: correct weight random generation
				w = rand() % 1000 + 1;
				Edge e(vertices_list[u].get_label(), vertices_list[v].get_label(), w);
				edges_list[i] = e;
			}
		} else
			v = rand() % n;
	}

	int draw_edge(int v1, int v2, int n, Edge *list)
	{
		list[n].Edge(v1, v2, 1);
		n++;
		return n;
	}

	int edge_draw_criterion(int v1, int v2) {
		double prob;
		prob = -1;
		prob = (v1 / v2) * 100;
		if (prob > 50)
			return 13; // draw an edge between vertices v1 and v2
		else
			return -13; // not to draw the edge
	}

	int edge_detect(int v1, int v2, int n, Edge *list)
	{
		int i;
		for (i = 0; i < n; i++)
		{
			if (((list[i].vertice_pair[0] == v1) && (list[i].vertice_pair[1] == v2))
					|| ((list[i].vertice_pair[0] == v2) && (list[i].vertice_pair[1] == v1)))
				return 14;
		}
		return -14;
	}

	int do_all_vertices_have_edge(int n, Vertice *list)
	{
		int i;
		for (i = 0; i < n; i++)
			// case of that not all the vertices have at least an edge
			if (list[i].number_of_edges == 0)
				return -15;
		return 15;
	}

};
