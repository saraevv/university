import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        try (BufferedReader bufferedReader1 = new BufferedReader(new FileReader("input1.txt"))) {
            String s1;
            String[] strings1;
            TreeList<ForestTree> treeList1 = new TreeList<ForestTree>();
            while ((s1 = bufferedReader1.readLine()) != null) {
                strings1 = s1.split(" ", 4);
                treeList1.add(new ForestTree(strings1[0], Integer.parseInt(strings1[1]), LeavesType.valueFromString(strings1[2]),
                        Double.parseDouble(strings1[3])));
            }
            treeList1.printSort();
            ForestTree example = new ForestTree("alder", 100, LeavesType.FOLIAR, 123);
            System.out.println(treeList1.frequency(example));
            System.out.println(treeList1.min());
            System.out.println(treeList1.countOfLeaves(LeavesType.CONIFEROUS));
            System.out.println(treeList1.countOfLeaves(LeavesType.INDEFINITE));
        } catch (FileNotFoundException e) {
            System.err.println("File not found!");
        } catch (IOException e) {
            System.err.println("Incorrect input!");
        } catch (ListIsEmptyException e) {
            System.err.println(e.getMessage());
        }

        System.out.println("--------------------------------");


        try (BufferedReader bufferedReader2 = new BufferedReader(new FileReader("input2.txt"))) {
            String s2;
            String[] strings2;
            TreeList<FruitTree> treeList2 = new TreeList<FruitTree>();
            while ((s2 = bufferedReader2.readLine()) != null) {
                strings2 = s2.split(" ", 4);
                treeList2.add(new FruitTree(strings2[0], Integer.parseInt(strings2[1]), LeavesType.valueFromString(strings2[2]),
                        Double.parseDouble(strings2[3])));
            }
            treeList2.printSort();
            FruitTree example = new FruitTree("cedar", 100, LeavesType.CONIFEROUS, 54);
            System.out.println(treeList2.frequency(example));
            System.out.println(treeList2.min());
            System.out.println(treeList2.countOfLeaves(LeavesType.CONIFEROUS));
            System.out.println(treeList2.countOfLeaves(LeavesType.INDEFINITE));
        } catch (FileNotFoundException e) {
            System.err.println("File not found!");
        } catch (IOException e) {
            System.err.println("Incorrect input!");
        } catch (ListIsEmptyException e) {
            System.err.println(e.getMessage());
        }
    }
}
