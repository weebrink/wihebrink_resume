package WihebrinkGraph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class IntuitiveTopological implements TopologicalSort {

    BetterDiGraph digraph;

    public IntuitiveTopological(BetterDiGraph graph) {
        digraph = graph;
    }

    /**
     * Returns an iterable object containing a topological sort.
     * @return a topological sort.
     */
    @Override
    public Iterable<Integer> order() {
        List<Integer> topologicalSort = new ArrayList();
        int count = digraph.getVertexCount();
        if (isDAG()) {
            while (!digraph.isEmpty()) {
                for (Object v: digraph.vertices()) {
                    if (digraph.getIndegree((Integer) v) == 0) {
                        topologicalSort.add((Integer) v);
                        digraph.removeVertex((Integer) v);
                    }
                }
            }
        }
        return topologicalSort;
    }

    /**
     * Returns true if the graph being sorted is a DAG, false otherwise.
     * @return is graph a DAG
     */
    @Override
    public boolean isDAG() {
        return !isCyclic();
    }

    private boolean isCyclic() {
        Map<Integer, Boolean> marked = new HashMap<Integer, Boolean>();
        Map<Integer, Boolean> recursiveStack = new HashMap<Integer, Boolean>();
        for (Object v: digraph.vertices()) {
            marked.put((Integer) v, false);
            recursiveStack.put((Integer) v, false);
        }
        for (Object v: digraph.vertices()) {
            if (isCyclicHelper((Integer) v, marked, recursiveStack)) {
                return true;
            }
        }
        return false;
    }

    private boolean isCyclicHelper(int i, Map<Integer, Boolean> marked, Map<Integer, Boolean> recursiveStack) {
        if (recursiveStack.get(i)) { return true; }
        if (marked.get(i)) { return false; }

        marked.put(i, true);
        recursiveStack.put(i, true);
        Iterable<Integer> children = digraph.getAdj(i);
        for (Integer c: children) {
            if (isCyclicHelper(c, marked, recursiveStack)) { return true; }
        }
        recursiveStack.put(i, false);

        return false;
    }

    private boolean hasCycle(int node, List<Integer> marked) {
        if (marked.contains(node)) { return true; }

        marked.add(node);
        for (Object nextNode: digraph.getAdj(node)) {
            if (hasCycle((Integer) nextNode, marked)) {
                return true;
            }
        }
        marked.remove(marked.size() - 1);
        return false;
    }
}
