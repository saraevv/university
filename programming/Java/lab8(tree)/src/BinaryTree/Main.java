package BinaryTree;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        BinaryTree<Integer> tree = new BinaryTree<Integer>();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 0; i < n; ++i)
            tree.add(in.nextInt());
        System.out.println(tree.find(7));
        tree.print("preOrder");
        tree.print("inOrder");
        tree.print("postOrder");
        tree.delete(in.nextInt());
        tree.print("preOrder");

        in.nextLine();
        BinaryTree<Person> ptree = new BinaryTree<Person>();
        n = 4;
        for (int i = 0; i < n; ++i)
            ptree.add(new Person(in.nextLine()));
        ptree.print("preOrder");
        ptree.print("inOrder");
        ptree.print("postOrder");
        ptree.delete(new Person(in.nextLine()));
        ptree.print("preOrder");
    }
}
