package WihebrinkGraph;

/**
 * Program for generating kanji component dependency order via topological sort.
 *
 * @author Wihebrink, Acuna
 * @version 1.0, 12/02/2020
 */

import java.io.*;
import java.util.HashMap;
import java.util.LinkedList;

public class WihebrinkMain {

    private static final int hash_size = 997;

    private int N;
    private int M;

    /**
     * Entry point for testing.
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {

        BufferedReader indexReader = new BufferedReader(new InputStreamReader(new FileInputStream(new File("data-kanji.txt")), "UTF8"));
        BufferedReader indexReader2  = new BufferedReader(new InputStreamReader(new FileInputStream(new File("data-components.txt", "UTF8"))));

        BetterDiGraph wihebrink_graph = new BetterDiGraph(indexReader);
        BetterDiGraph graphEdges = BetterDiGraph(indexReader2);
        String line;

        while ((line = indexReader.readLine()) != null) {
            String[] tokens = line.split(" ");
            int firstNode = Integer.parseInt(tokens[0]);
            int secondNode = Integer.parseInt(tokens[1]);

            if (!wihebrink_graph.containsVertex(firstNode)) {
                wihebrink_graph.put(firstNode, new LinkedList());
                wihebrink_graph.put(secondNode, new LinkedList());
            }
        }

        while ((line = indexReader2.readLine()) != null) {
            String[] tokens = line.split(" ");
            int firstNode2 = Integer.parseInt(tokens[0]);
            int secondNode2 = Integer.parseInt(tokens[1]);

            if (!wihebrink_graph.containsVertex(firstNode2)) {
                graphEdges.get(firstNode2).add(secondNode2);
            }
        }

        IntuitiveTopological topological_sort = new IntuitiveTopological();

        topological_sort.order(wihebrink_graph);

        System.out.println(graphEdges);
        indexReader.close();
    }
}