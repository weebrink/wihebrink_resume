package WihebrinkGraph;

import java.util.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.HashMap;

public class BetterDiGraph implements EditableDiGraph {

    private HashMap<Integer, HashSet<Integer>> wihebrink_adj_graph;
    private int Vertices;
    private int Edges;

    /**
     * Default constructor
     */
    public BetterDiGraph() {
        this.wihebrink_adj_graph = new HashMap<>();
        //this.Vertices = Vertices;
        //this.Edges = 0;
        //this.wihebrink_adj_graph = new LinkedList<Integer>[];
        //for (int i = 0; i < Vertices; i++) {
        //    wihebrink_adj_graph[i] = new LinkedList<>();
        }

    /**
     * Adds an edge between two vertices, v and w. If vertices do not exist,
     * adds them first.
     *
     * @param v source vertex
     * @param w destination vertex
     */
    @Override
    public void addEdge(int v, int w) {
        addVertex(v);
        addVertex(w);

        if (this.wihebrink_adj_graph.containsKey(v)) {
            if (!this.wihebrink_adj_graph.get(v).contains(w)) {
                this.wihebrink_adj_graph.get(v).add(w);
                this.Edges++;
                return;
            }
        }
        return;
    }

    /**
     * Adds a vertex to the graph. Does not allow duplicate vertices.
     *
     * @param v vertex number
     */
    @Override
    public void addVertex(int v) {
        if (!this.wihebrink_adj_graph.containsKey(v)) {
            this.wihebrink_adj_graph.put(v, new HashSet<>());
            this.Vertices++;
            return;
        }
        return;
    }

    /**
     * Returns the direct successors of a vertex v.
     *
     * @param v vertex
     * @return successors of v
     */
    @Override
    public Iterable<Integer> getAdj(int v) {
        return wihebrink_adj_graph.get(v);
    }

    /**
     * Number of edges.
     *
     * @return edge count
     */
    @Override
    public int getEdgeCount() {
        return this.Edges;
    }

    /**
     * Returns the in-degree of a vertex.
     * @param v vertex
     * @return in-degree.
     * @throws NoSuchElementException exception thrown if vertex does not exist.
     */
    @Override
    public int getIndegree(int v) {
        if (!containsVertex(v)) {
            throw new NoSuchElementException();
        }
        List<Integer> inDegreeList = new ArrayList<Integer>();
        for (Integer to: this.wihebrink_adj_graph.keySet()) {
            for (Integer e: this.wihebrink_adj_graph.get(to)) {
                if (e.equals(v)) {
                    inDegreeList.add(to);
                }
            }
        }
        return inDegreeList.size();
    }

    /**
     * Returns number of vertices.
     * @return vertex count
     */
    @Override
    public int getVertexCount() {
        return this.Vertices;
    }

    /**
     * Removes edge from graph. If vertices do not exist, does not remove edge.
     *
     * @param v source vertex
     * @param w destination vertex
     */
    @Override
    public void removeEdge(int v, int w) {
        //adj[v].remove(w);
        //E--;
        if (this.wihebrink_adj_graph.containsKey(v) && this.wihebrink_adj_graph.containsKey(w)) {
            if (this.wihebrink_adj_graph.get(v).contains(w)) {
                this.wihebrink_adj_graph.get(v).remove(w);
                this.Edges--;
                return;
            }
        }
        return;
    }

    /**
     * Removes vertex from graph. If vertex does not exist, does not try to
     * remove it.
     *
     * @param v vertex
     */
    @Override
    public void removeVertex(int v) {
        if (this.wihebrink_adj_graph.containsKey(v)) {
            this.wihebrink_adj_graph.remove(v);
            for (Map.Entry<Integer, HashSet<Integer>> entry : this.wihebrink_adj_graph.entrySet()) {
                if (entry.getValue().contains(v)) {
                    this.wihebrink_adj_graph.get(entry.getKey()).remove(v);
                }
            }
            this.Vertices--;
            return;
        }
        return;
    }

    /**
     * Returns iterable object containing all vertices in graph.
     *
     * @return iterable object of vertices
     */
    @Override
    public Iterable<Integer> vertices() {
        List<Integer> verticeList = new ArrayList<Integer>();
        for (Integer to: this.wihebrink_adj_graph.keySet()) {
            if (!verticeList.contains(to)) {
                verticeList.add(to);
            }
        }
        return verticeList;
    }

    /**
     * Returns false if the graph contains at least one vertex.
     *
     * @return boolean
     */
    @Override
    public boolean isEmpty() {
        return this.Vertices == 0;
    }

    /**
     * Returns true if the graph contains a specific vertex.
     *
     * @param v vertex
     * @return boolean
     */
    @Override
    public boolean containsVertex(int v) {
        if (this.wihebrink_adj_graph.containsKey(v)) {
            return true;
        }
        return false;
    }
}
