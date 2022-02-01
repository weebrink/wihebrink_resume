package WihebrinkMatrixProgram;

/**
 * An implementation of the Matrix ADT. Provides four basic operations over an
 * immutable type.
 *
 * Last updated 10/20/2020.
 *
 * @author Matthew Wihebrink, Ruben Acuna
 * @version 2.0
 */
public class WihebrinkMatrix implements Matrix {

    private int X, Y, i, j; // rows, columns, indexes
    private int[][] MatrixValue;

    // helper method for later in the program
    public WihebrinkMatrix(int X, int Y) {
        this.X = X;
        this.Y = Y;
        MatrixValue = new int[X][Y];
    }

    public WihebrinkMatrix(int[][] matrix) {

        // create initial 2D array
        X = matrix.length;
        Y = matrix[0].length;
        this.MatrixValue = new int[X][Y];

        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                this.MatrixValue[i][j] = MatrixValue[i][j];
            }
        }
    }
    /**
     * Returns the element at particular point in the matrix.
     * @param y y position
     * @param x x position
     * @return element
     */
    public int getElement(int y, int x) {

        i = x;
        j = y;

        int elementValue = MatrixValue[i][j];

        return elementValue;
    }
    /**
     * Returns the number of rows in the matrix.
     * @return rows
     */
    public int getRows() {

        boolean empty = false;

        if (empty) {
            throw new RuntimeException("Does not exist");
        } else {
            int rows = MatrixValue.length;
            return rows;
        }
    }

    /**
     * Returns the number of columns in the matrix.
     * @return columns
     */
    public int getColumns() {

        boolean empty = false;

        if (empty) {
            throw new RuntimeException("Does not exist");
        } else {
            int columns = MatrixValue[j].length;
            return columns;
        }
    }
    /**
     * Returns this matrix scaled by a factor. That is, computes kA where k is a
     * constant and A is a matrix (this object).
     *
     * @param scalar scalar
     * @return matrix
     */
    public Matrix scale(int scalar) {

        Matrix A = this;
        int K = scalar;
        Matrix k = new WihebrinkMatrix(K,K);
        // k*A
        Matrix scaledMatrix = k.multiply(A);
        return scaledMatrix;
    }
    /**
     * Returns this matrix added with another matrix. That is, computes A+B
     * where A and B are matrices (this object, and another respectively).
     * @param other addend
     * @return matrix
     * @throws RuntimeException if matrices do not have matching dimensions.
     */
    public Matrix plus(Matrix other) {

        Matrix A = this;
        // DIMENSIONS DO NOT MATCH TO ADD MATRICES VALUES
        if (A != other) {
            throw new RuntimeException("Dimensions do not match");
        }
        Matrix sumMatrix = new WihebrinkMatrix(X,Y);
        int[][] C = new int[0][0];
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                // C = A + B
                C[i][j] = A[i][j] + other[i][j];
                sumMatrix = C;
            }
        }
        return sumMatrix;
    }
    /**
     * Returns this matrix subtracted by another matrix. That is, computes A-B
     * where A and B are matrices (this object, and another respectively).
     * @param other subtrahend
     * @return matrix
     * @throws RuntimeException if matrices do not have matching dimensions.
     */
    public Matrix minus(Matrix other) {

        Matrix A = this;
        // DIMENSIONS DO NOT MATCH TO ADD MATRICES VALUES
        if (A != other) {
            throw new RuntimeException("Dimensions do not match");
        }
        Matrix differenceMatrix = new WihebrinkMatrix(X,Y);
        int[][] C = new int[0][0];
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                // C = A + B
                C[i][j] = A[i][j] + other[i][j];
                differenceMatrix = C;
            }
        }
        return differenceMatrix;
    }
    /**
     * Returns this matrix multiplied by another matrix (using dot products).
     * That is, computes AB where A and B are matrices (this object, and another
     * respectively).
     * @param other multiplicand
     * @return matrix
     * @throws RuntimeException if matrices do not have matching dimensions.
     */
    public Matrix multiply(Matrix other) {

        Matrix A = this;
        // DIMENSIONS DO NOT MATCH TO ADD MATRICES VALUES
        if (A != other) {
            throw new RuntimeException("Dimensions do not match");
        }
        Matrix productMatrix = new WihebrinkMatrix(X,Y);
        int[][] C = new int[0][0];
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                // C = A + B
                C[i][j] = A[i][j] + other[i][j];
                productMatrix = C;
            }
        }
        return productMatrix;
    }
    /**
     * Returns true if this matrix matches another matrix.
     * @param other another matrix
     * @return equality
     */
    @Override
    public boolean equals(Object other) {

        if (MatrixValue == other) {
            return true;
        }
        else {
            return false;
        }
    }
    /**
     * Returns a string representation of this matrix. A new line character will
     * separate each row, while a space will separate each column.
     * @return string representation
     */
    @Override
    public String toString() {

        String stringOutput = "";
        stringOutput += MatrixValue[i][j];
        return stringOutput;
    }
    /**
     * Entry point for matrix testing.
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        int[][] data1 = new int[0][0];
        int[][] data2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        int[][] data3 = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
        int[][] data4 = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
        int[][] data5 = {{1, 4, 7}, {2, 5, 8}};

        Matrix m1 = new WihebrinkMatrix(data1);
        Matrix m2 = new WihebrinkMatrix(data2);
        Matrix m3 = new WihebrinkMatrix(data3);
        Matrix m4 = new WihebrinkMatrix(data4);
        Matrix m5 = new WihebrinkMatrix(data5);

        System.out.println("m1 --> Rows: " + m1.getRows() + " Columns: " + m1.getColumns());
        System.out.println("m2 --> Rows: " + m2.getRows() + " Columns: " + m2.getColumns());
        System.out.println("m3 --> Rows: " + m3.getRows() + " Columns: " + m3.getColumns());

        //check for reference issues
        System.out.println("m2 -->\n" + m2);
        data2[1][1] = 101;
        System.out.println("m2 -->\n" + m2);

        //test equals
        System.out.println("m2==null: " + m2.equals(null));             //false
        System.out.println("m3==\"MATRIX\": " + m2.equals("MATRIX"));   //false
        System.out.println("m2==m1: " + m2.equals(m1));                 //false
        System.out.println("m2==m2: " + m2.equals(m2));                 //true
        System.out.println("m2==m3: " + m2.equals(m3));                 //false
        System.out.println("m3==m4: " + m3.equals(m4));                 //true

        //test operations (valid)
        System.out.println("m1 + m1:\n" + m1.plus(m1));
        System.out.println("m1 + m1:\n" + m1.plus(m1));
        System.out.println("2 * m2:\n" + m2.scale(2));
        System.out.println("m2 + m3:\n" + m2.plus(m3));
        System.out.println("m2 - m3:\n" + m2.minus(m3));
        System.out.println("3 * m5:\n" + m5.scale(3));

        //not tested... multiply(). you know what to do.

        //test operations (invalid)
        //System.out.println("m1 + m2" + m1.plus(m2));
        //System.out.println("m1 + m5" + m1.plus(m5));
        //System.out.println("m1 - m2" + m1.minus(m2));
    }
}