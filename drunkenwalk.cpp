#include <stdio.h>

#include <list>

const int max_N = 10000;
const int max_M = 100000;

struct Edge;

typedef std::list<Edge*> EdgeList;

struct Vertex {
    int id;
    int n_out_edges;
    int n_out_checked;
    int n_in_edges;
    int n_in_checked;
    int out_weight_sum;
    double weighted_exp_sum;
    double exp;
    double influence;
    EdgeList in;
    EdgeList out;
} vertices[max_N];

struct Edge {
    Vertex *from, *to;
    int weight;
} edges[max_M];

typedef std::list<Vertex*> VertexList;

int N, M;

void init()
{
    for (int i=0; i<max_N; i++)
        vertices[i].id = i;
}

void read_input()
{
    for (int i=0; i<N; i++) {
        vertices[i].n_out_edges = 0;
        vertices[i].n_out_checked = 0;
        vertices[i].n_in_edges = 0;
        vertices[i].n_in_checked = 0;
        vertices[i].out_weight_sum = 0;
        vertices[i].influence = 0;
        vertices[i].in.clear();
        vertices[i].out.clear();
    }

    for (int i=0; i<M; i++) {
        int from, to;
        Edge &e = edges[i];
        scanf("%d %d %d", &from, &to, &e.weight);
        e.from = &vertices[from];
        e.to = &vertices[to];
        e.from->out.push_back(&e);
        e.from->n_out_edges++;
        e.from->out_weight_sum += e.weight;
        e.to->in.push_back(&e);
        e.to->n_in_edges++;
    }
}

void remove_vertex_without_in_edge()
{
    VertexList vl;
    for (int i=1; i<N; i++)
        if (vertices[i].n_in_edges == 0)
            vl.push_back(&vertices[i]);

    while (!vl.empty()) {
        Vertex *v = vl.front();
        vl.pop_front();
        v->n_out_edges = 0;
        for (EdgeList::iterator i=v->out.begin(); i!=v->out.end(); i++) {
            Edge *e = *i;
            if (--e->to->n_in_edges == 0 && e->to != &vertices[0])
                vl.push_back(e->to);
            for (EdgeList::iterator j=e->to->in.begin(); j!=e->to->in.end(); j++)
                if (*j == e) {
                    e->to->in.erase(j);
                    break;
                }
        }
    }
}

void set_exp(Vertex *v)
{
    v->weighted_exp_sum = 0;
    for (EdgeList::iterator i = v->out.begin(); i != v->out.end(); i++) {
        Edge *e = *i;
        v->weighted_exp_sum += (e->to->exp + 1) * e->weight;
    }
    v->exp = v->weighted_exp_sum / v->out_weight_sum;
}

double find_all_edge_exp()
{
    VertexList vl;
    for (int i = 0; i < N; i++)
        if (vertices[i].n_out_edges == 0) {
            vertices[i].exp = 0;
            vl.push_back(&vertices[i]);
        }
    while (!vl.empty()) {
        EdgeList &in = vl.front()->in;
        vl.pop_front();
        for (EdgeList::iterator i = in.begin(); i != in.end(); i++) {
            Vertex *from = (*i)->from;
            if (++from->n_out_checked == from->n_out_edges) {
                vl.push_back(from);
                set_exp(from);
            }
        }
    }
    return vertices[0].exp;
}

void add_checked_vertex(VertexList &vl, Vertex *v, double &max_inc)
{
    vl.push_back(v);
    for (EdgeList::iterator i=v->out.begin(); i!=v->out.end(); i++) {
        Edge *e = *i;
        if (e->to->exp + 1 < v->exp) {
            double increased_exp = (v->weighted_exp_sum - e->weight * (e->to->exp + 1)) / (v->out_weight_sum - e->weight);
            double inc = (increased_exp - v->exp) * v->influence;
            if (inc > max_inc)
                max_inc = inc;
        }
    }
}

double max_exp()
{
    VertexList vl;
    double max_increase = 0;
    vertices[0].influence = 1;
    add_checked_vertex(vl, &vertices[0], max_increase);

    while (!vl.empty()) {
        Vertex *v = vl.front();
        vl.pop_front();
        EdgeList &out = v->out;
        for (EdgeList::iterator i=out.begin(); i!=out.end(); i++) {
            Vertex *to = (*i)->to;
            to->influence += v->influence * (*i)->weight / v->out_weight_sum;
            if (++to->n_in_checked == to->n_in_edges)
                add_checked_vertex(vl, to, max_increase);
        }
    }
    return vertices[0].exp + max_increase;
}

int main()
{
    init();
    while (true) {
        scanf("%d %d", &N, &M);
        if (N == 0) break;

        read_input();
        remove_vertex_without_in_edge();

        find_all_edge_exp();
//        printf("%.8lf =>\n", find_all_edge_exp());
        printf("%.8lf\n", max_exp());
    }
    return 0;
}
